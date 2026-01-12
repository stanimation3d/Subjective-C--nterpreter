#include "SubjectManager.h"
#include <stdexcept>

void SubjectManager::enterSubject(const std::string& subjectName) {
    std::cout << "[SBMM] " << subjectName << " bağlamına girildi. Bellek ayrılıyor...\n";
    scopeStack.push_back({subjectName, {}});
}

void SubjectManager::exitSubject() {
    if (!scopeStack.empty()) {
        std::cout << "[SBMM] " << scopeStack.back().name << " bağlamı bitti. Değişkenler siliniyor...\n";
        scopeStack.pop_back(); // Bloğun sonu: Bellek otomatik temizlenir!
    }
}

void SubjectManager::defineVariable(const std::string& name, double value) {
    if (!scopeStack.empty()) {
        // Eğer bir subject içindeysek, o bağlama özel kaydet
        scopeStack.back().variables[name] = value;
    } else {
        // Değilsek global belleğe kaydet
        globalMemory[name] = value;
    }
}

double SubjectManager::getVariable(const std::string& name) {
    // Önce en içteki bağlamdan aramaya başla (En güncel bakış açısı)
    for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
        if (it->variables.find(name) != it->variables.end()) {
            return it->variables[name];
        }
    }

    // Bağlamda yoksa globalde ara
    if (globalMemory.find(name) != globalMemory.end()) {
        return globalMemory[name];
    }

    throw std::runtime_error("Hata: '" + name + "' tanımlı değil!");
}

std::string SubjectManager::getCurrentSubjectName() const {
    return scopeStack.empty() ? "Global" : scopeStack.back().name;
}