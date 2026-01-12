#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "AST.h" // AST düğüm sınıflarını içermeli

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<std::shared_ptr<Stmt>> parse(); // Programı deyimler listesi olarak döndürür

private:
    std::vector<Token> tokens;
    int current = 0;

    // Dil kuralları (Hiyerarşik sıra ile)
    std::shared_ptr<Stmt> declaration();
    std::shared_ptr<Stmt> subjectDeclaration();
    std::shared_ptr<Stmt> varDeclaration();
    std::shared_ptr<Stmt> statement();
    
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> term();   // + ve -
    std::shared_ptr<Expr> factor(); // x ve ÷
    std::shared_ptr<Expr> power();  // Üst simgeler ¹²³
    std::shared_ptr<Expr> primary();

    // Yardımcılar
    bool match(std::vector<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Token consume(TokenType type, std::string message);
};

#endif