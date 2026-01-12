#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"
#include "SubjectManager.h"
#include <memory>
#include <cmath>

class Evaluator {
public:
    Evaluator();
    
    // Tüm programı yürütür
    void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);

private:
    SubjectManager subjectManager;

    // Deyimleri ve ifadeleri değerlendirme metotları
    void execute(std::shared_ptr<Stmt> stmt);
    double evaluate(std::shared_ptr<Expr> expr);

    // Üst simgeleri sayıya çeviren yardımcı (¹²³ -> 123)
    double parseSuperscript(const std::string& superscript);
};

#endif