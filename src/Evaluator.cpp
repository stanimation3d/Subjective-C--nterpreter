#include "Evaluator.h"
#include <iostream>

Evaluator::Evaluator() {}

void Evaluator::interpret(const std::vector<std::shared_ptr<Stmt>>& statements) {
    try {
        for (const auto& stmt : statements) {
            execute(stmt);
        }
    } catch (const std::runtime_error& error) {
        std::cerr << "Çalışma Zamanı Hatası: " << error.what() << std::endl;
    }
}

void Evaluator::execute(std::shared_ptr<Stmt> stmt) {
    // Subject Bloğu Yönetimi (SBMM Giriş-Çıkış)
    if (auto s = std::dynamic_pointer_cast<SubjectStmt>(stmt)) {
        subjectManager.enterSubject(s->name.lexeme);
        for (const auto& bodyStmt : s->body) {
            execute(bodyStmt);
        }
        subjectManager.exitSubject();
    } 
    // Değişken Tanımlama
    else if (auto v = std::dynamic_pointer_cast<VarStmt>(stmt)) {
        double value = 0;
        if (v->initializer) {
            value = evaluate(v->initializer);
        }
        subjectManager.defineVariable(v->name.lexeme, value);
        std::cout << "[Bellek] " << v->name.lexeme << " = " << value << std::endl;
    }
}

double Evaluator::evaluate(std::shared_ptr<Expr> expr) {
    // Sayı veya Değişken Değeri
    if (auto l = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        if (l->value.type == TokenType::NUMBER) {
            return std::stod(l->value.lexeme);
        } else if (l->value.type == TokenType::IDENTIFIER) {
            return subjectManager.getVariable(l->value.lexeme);
        }
    }

    // İkili İşlemler (x, ÷, ¹²³, +, -)
    if (auto b = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        double left = evaluate(b->left);
        
        // Üst simge işlemi (Örn: 2³)
        if (b->op.type == TokenType::POWER) {
            double exponent = parseSuperscript(b->op.lexeme);
            return std::pow(left, exponent);
        }

        double right = evaluate(b->right);

        switch (b->op.type) {
            case TokenType::PLUS:     return left + right;
            case TokenType::MINUS:    return left - right;
            case TokenType::MULTIPLY: return left * right; // 'x' operatörü
            case TokenType::DIVIDE:   // '÷' operatörü
                if (right == 0) throw std::runtime_error("Sıfıra bölme hatası!");
                return left / right;
            default: return 0;
        }
    }
    return 0;
}

double Evaluator::parseSuperscript(const std::string& superscript) {
    // UTF-8 üst simgeleri normal rakamlara çevirme eşleşmesi
    static std::unordered_map<std::string, std::string> map = {
        {"⁰","0"}, {"¹","1"}, {"²","2"}, {"³","3"}, {"⁴","4"},
        {"⁵","5"}, {"⁶","6"}, {"⁷","7"}, {"⁸","8"}, {"⁹","9"}
    };
    
    // Not: Basitleştirilmiş versiyon, tek karakterli üst simgeyi çevirir
    if (map.count(superscript)) return std::stod(map[superscript]);
    return 1; // Varsayılan üs
}