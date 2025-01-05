#include <core/Tokenizer.hpp>
#include <utility>

Tokenizer::Tokenizer(std::string json) : input{std::move(json)}, currentIndex{0} {
}

Tokenizer::TokenVector Tokenizer::tokenize() {
    Tokenizer::TokenVector tokens;

    while (currentIndex < input.size()) {
        this->skipWhiteSpace();

        if (const char c = this->peek(); c == '{') {
            tokens.emplace_back(TokenType::LeftBrace, "{");
            this->advance();
        } else if (c == '}') {
            tokens.emplace_back(TokenType::RightBrace, "}");
            this->advance();
        } else if (c == '[') {
            tokens.emplace_back(TokenType::LeftBracket, "[");
            this->advance();
        } else if (c == ']') {
            tokens.emplace_back(TokenType::RightBracket, "]");
            this->advance();
        } else if (c == ',') {
            tokens.emplace_back(TokenType::Comma, ",");
            this->advance();
        } else if (c == ':') {
            tokens.emplace_back(TokenType::Colon, ":");
            this->advance();
        } else if (c == '"') {
            tokens.emplace_back(this->parseString());
        } else if (isdigit(c) || c == '-') {
            tokens.emplace_back(parseNumber());
        } else if (isalpha(c)) {
            tokens.emplace_back(parseKeyword());
        } else {
            tokens.emplace_back(TokenType::Unknown, std::string(1, c));
            this->advance();
        }
    }

    return tokens;
}

char Tokenizer::peek() {
}

char Tokenizer::advance() {
}

void Tokenizer::skipWhiteSpace() {
}

Token Tokenizer::parseString() {
}

Token Tokenizer::parseNumber() {
}

Token Tokenizer::parseKeyword() {
}
