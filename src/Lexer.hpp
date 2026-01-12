#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include <map>

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    // Yardımcı metotlar
    bool isAtEnd();
    char advance();
    char peek();
    bool match(char expected);
    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);

    // Özel tarayıcılar
    void identifier();
    void number();
    void handleUnicode(); // x, ÷ ve üst simgeler için
};

#endif