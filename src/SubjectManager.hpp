#ifndef SUBJECT_MANAGER_H
#define SUBJECT_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

// Her bir bağlamın (Subject) kendi bellek alanı
struct SubjectScope {
    std::string name;
    std::unordered_map<std::string, double> variables; // Basitlik için double kullanıyoruz
};

class SubjectManager {
public:
    // Bağlam yönetimi
    void enterSubject(const std::string& subjectName);
    void exitSubject();

    // Değişken yönetimi (SBMM kuralları dahilinde)
    void defineVariable(const std::string& name, double value);
    double getVariable(const std::string& name);

    // Mevcut aktif konunun adını al
    std::string getCurrentSubjectName() const;

private:
    // Aktif konu yığını (İç içe subject blokları için)
    std::vector<SubjectScope> scopeStack;
    
    // Global bellek (Subject dışı tanımlar için)
    std::unordered_map<std::string, double> globalMemory;
};

#endif