#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"

// Terminal başlığı ve yardımcı bilgiler
void printHeader() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Subjective-C IDE & Terminal v1.0    " << std::endl;
    std::cout << "   SOP & SBMM Mimari Yapısı Aktif      " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Kısayol Bilgisi: x (Çarp), ÷ (Böl), ²³ (Üs)" << std::endl;
    std::cout << "Çıkış için 'exit' yazın.\n" << std::endl;
}

// Bir kod satırını veya dosyasını çalıştıran yardımcı fonksiyon
void run(const std::string& source, Evaluator& evaluator) {
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.scanTokens();

    Parser parser(tokens);
    try {
        std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
        evaluator.interpret(statements);
    } catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    Evaluator evaluator;

    // DOSYA MODU: Eğer argüman olarak dosya yolu verilmişse (.sc)
    if (argc > 1) {
        std::string filename = argv[1];
        if (filename.substr(filename.find_last_of(".") + 1) != "sc") {
            std::cerr << "Hata: Sadece .sc uzantılı dosyalar desteklenir!" << std::endl;
            return 1;
        }

        std::ifstream file(filename);
        std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        run(source, evaluator);
    } 
    // TERMINAL MODU: İnteraktif kullanım
    else {
        printHeader();
        std::string line;
        while (true) {
            std::cout << "sc > ";
            if (!std::getline(std::cin, line) || line == "exit") break;
            if (line.empty()) continue;
            
            run(line, evaluator);
        }
    }

    return 0;
}