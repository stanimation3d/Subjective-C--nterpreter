#ifndef AST_H
#define AST_H

#include <vector>
#include <memory>
#include <string>
#include "Token.h"

// Tüm ifade ve deyimlerin atası
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// --- İFADELER (Değer döndüren yapılar) ---
class Expr : public ASTNode {};

// İkili işlemler (5 x 2, a + b, 2³)
class BinaryExpr : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
        : left(left), op(op), right(right) {}
};

// Literaller (Sayılar, Değişken İsimleri)
class LiteralExpr : public Expr {
public:
    Token value;
    LiteralExpr(Token value) : value(value) {}
};

// --- DEYİMLER (Eylem bildiren yapılar) ---
class Stmt : public ASTNode {};

// Değişken Tanımlama (degisken maas = 5000;)
class VarStmt : public Stmt {
public:
    Token name;
    std::shared_ptr<Expr> initializer;

    VarStmt(Token name, std::shared_ptr<Expr> initializer)
        : name(name), initializer(initializer) {}
};

// Subject Bloğu (subject Muhasebe { ... })
class SubjectStmt : public Stmt {
public:
    Token name;
    std::vector<std::shared_ptr<Stmt>> body;

    SubjectStmt(Token name, std::vector<std::shared_ptr<Stmt>> body)
        : name(name), body(body) {}
};

#endif