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

/**
 * @brief Represents a token in the tokenizer.
 * 
 * A token consists of a type and a value. The type indicates the kind of token
 * (e.g., string, number, etc.), and the value holds the actual content of the token.
 */
struct Token {
    TokenType type; ///< The type of the token.
    std::string value; ///< The value of the token.
    
    /**
     * @brief Constructs a Token with the specified type and value.
     * 
     * @param t The type of the token.
     * @param v The value of the token.
     */
    explicit Token(const TokenType t, std::string v) : type(t), value(std::move(v)) {}
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
