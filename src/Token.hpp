#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

enum class TokenType {
    // Anahtar Kelimeler (Keywords)
    IMPORT, SUBJECT, FUNC, VAR, RETURN,

    // Operatörler (SOP Özel Operatörleri dahil)
    PLUS,       // +
    MINUS,      // -
    MULTIPLY,   // x
    DIVIDE,     // ÷
    EQUALS,     // =
    POWER,      // ¹²³⁴⁵⁶⁷⁸⁹⁰ (Üst simge olarak saklanacak)

    // Literaller ve Tanımlayıcılar
    IDENTIFIER, // Değişken veya fonksiyon isimleri
    NUMBER,     // Sayılar (Tamsayı veya Ondalıklı)

    // Semboller
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    SEMICOLON,  // ;
    DOT,        // . (Nesne özelliklerine erişim için)

    // Dosya Sonu
    END_OF_FILE
};

class Token {
public:
    TokenType type;
    std::string lexeme; // Kodun içindeki ham metin (örn: "500" veya "÷")
    int line;           // Hata ayıklama için satır numarası

    Token(TokenType type, std::string lexeme, int line);
    
    // Hata ayıklama sırasında token'ı ekrana yazdırmak için yardımcı metot
    std::string toString() const;
};

#endif