#include "Lexer.h"
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        char c = advance();
        switch (c) {
            case '(': addToken(TokenType::LPAREN); break;
            case ')': addToken(TokenType::RPAREN); break;
            case '{': addToken(TokenType::LBRACE); break;
            case '}': addToken(TokenType::RBRACE); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '.': addToken(TokenType::DOT); break;
            case '+': addToken(TokenType::PLUS); break;
            case '-': addToken(TokenType::MINUS); break;
            case '=': addToken(TokenType::EQUALS); break;
            case 'x': addToken(TokenType::MULTIPLY); break; // Çarpma
            case ' ': case '\r': case '\t': break; // Boşlukları atla
            case '\n': line++; break;

            default:
                if (isdigit(c)) {
                    number();
                } else if (isalpha(c)) {
                    identifier();
                } else {
                    // UTF-8 karakterlerini (÷ ve üst simgeler) burada yakalıyoruz
                    handleUnicode();
                }
                break;
        }
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, "", line));
    return tokens;
}

void Lexer::handleUnicode() {
    // Mevcut pozisyondaki bayt dizisini kontrol et
    std::string sub = source.substr(start, 3); // UTF-8 karakterleri genelde 2-3 bayttır

    if (sub.find("÷") == 0) {
        current += 1; // '÷' genelde 2 bayttır, biri 'advance' ile geçildi
        addToken(TokenType::DIVIDE, "÷");
    } 
    // Üst simgeler (¹²³...) kontrolü
    else if (sub.find("¹") == 0 || sub.find("²") == 0 || sub.find("³") == 0) {
        // Üst simge bloğunu tamamen tüket
        current += 1; 
        addToken(TokenType::POWER, source.substr(start, current - start));
    }
    else {
        std::cerr << "Satir " << line << ": Beklenmeyen karakter." << std::endl;
    }
}

void Lexer::identifier() {
    while (isalnum(peek())) advance();
    std::string text = source.substr(start, current - start);
    
    // Anahtar kelime kontrolü
    static std::map<std::string, TokenType> keywords = {
        {"İmport", TokenType::IMPORT},
        {"subject", TokenType::SUBJECT},
        {"fonksiyon", TokenType::FUNC},
        {"degisken", TokenType::VAR},
        {"don", TokenType::RETURN}
    };

    if (keywords.count(text)) addToken(keywords[text]);
    else addToken(TokenType::IDENTIFIER);
}

void Lexer::number() {
    while (isdigit(peek())) advance();
    addToken(TokenType::NUMBER, source.substr(start, current - start));
}

// Temel yardımcı fonksiyonlar
bool Lexer::isAtEnd() { return current >= source.length(); }
char Lexer::advance() { return source[current++]; }
char Lexer::peek() { return isAtEnd() ? '\0' : source[current]; }
void Lexer::addToken(TokenType type) { addToken(type, source.substr(start, current - start)); }
void Lexer::addToken(TokenType type, std::string literal) { tokens.push_back(Token(type, literal, line)); }