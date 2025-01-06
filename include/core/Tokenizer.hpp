#pragma once

#include <string>
#include <utility>
#include <vector>

enum class TokenType {
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,
    Comma,
    Colon,
    String,
    Number,
    Boolean,
    Null,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
    
    explicit Token(const TokenType t, std::string  v) : type(t), value(std::move(v)) {}
};

class Tokenizer {
public:
    using TokenVector = std::vector<Token>;

    explicit Tokenizer(std::string  json);
    TokenVector tokenize();
private:
    std::string input;
    size_t currentIndex{};

    [[nodiscard]] char peek() const;
    char advance();
    void skipWhiteSpace();

    Token parseString();
    Token parseNumber();
    Token parseKeyword();
};
