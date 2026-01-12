#include "Token.h"
#include <map>

Token::Token(TokenType type, std::string lexeme, int line) 
    : type(type), lexeme(lexeme), line(line) {}

std::string Token::toString() const {
    static const std::map<TokenType, std::string> typeNames = {
        {TokenType::IMPORT, "IMPORT"}, {TokenType::SUBJECT, "SUBJECT"},
        {TokenType::FUNC, "FUNC"}, {TokenType::VAR, "VAR"},
        {TokenType::MULTIPLY, "MULTIPLY (x)"}, {TokenType::DIVIDE, "DIVIDE (÷)"},
        {TokenType::POWER, "POWER"}, {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::NUMBER, "NUMBER"}, {TokenType::END_OF_FILE, "EOF"}
    };

    auto it = typeNames.find(type);
    std::string typeStr = (it != typeNames.end()) ? it->second : "UNKNOWN";
    
    return "Token[" + typeStr + "]: '" + lexeme + "' at line " + std::to_string(line);
}