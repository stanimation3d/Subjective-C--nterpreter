#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

std::shared_ptr<Stmt> Parser::declaration() {
    if (match({TokenType::SUBJECT})) return subjectDeclaration();
    if (match({TokenType::VAR})) return varDeclaration();
    return statement();
}

std::shared_ptr<Stmt> Parser::subjectDeclaration() {
    Token name = consume(TokenType::IDENTIFIER, "Subject ismi bekleniyor.");
    consume(TokenType::LBRACE, "Subject blogu '{' ile baslamalidir.");
    
    std::vector<std::shared_ptr<Stmt>> body;
    while (!check(TokenType::RBRACE) && !isAtEnd()) {
        body.push_back(declaration());
    }
    
    consume(TokenType::RBRACE, "Subject blogu '}' ile kapatilmalidir.");
    return std::make_shared<SubjectStmt>(name, body);
}

// Matematiksel İşlem Önceliği (Düşükten Yükseğe)
std::shared_ptr<Expr> Parser::expression() {
    return equality();
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();
    while (match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = power();
    // 'x' ve '÷' operatörlerini burada işliyoruz
    while (match({TokenType::MULTIPLY, TokenType::DIVIDE})) {
        Token op = previous();
        std::shared_ptr<Expr> right = power();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::power() {
    std::shared_ptr<Expr> expr = primary();
    // Üst simge operatörü (¹²³) en yüksek önceliğe sahip
    if (match({TokenType::POWER})) {
        Token op = previous();
        std::shared_ptr<Expr> right = primary(); // Basit üs mantığı
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

// Yardımcı Metotlar
bool Parser::match(std::vector<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();
    throw std::runtime_error("Satir " + std::to_string(peek().line) + ": " + message);
}

bool Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }
Token Parser::peek() { return tokens[current]; }
Token Parser::previous() { return tokens[current - 1]; }