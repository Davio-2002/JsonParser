#include <core/Tokenizer.hpp>

Tokenizer::Tokenizer(std::string json) : input{std::move(json)}, currentIndex{0} {
}

Tokenizer::TokenVector Tokenizer::tokenize() {
    TokenVector tokens;

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

char Tokenizer::peek() const {
    return this->input[currentIndex];
}

char Tokenizer::advance() {
    return this->input[currentIndex++];
}

void Tokenizer::skipWhiteSpace() {
    while (currentIndex < input.size() && isspace(input[currentIndex])) {
        ++currentIndex;
    }
}

Token Tokenizer::parseString() {
    std::string result;
    advance();
    while (currentIndex < input.size() && peek() != '"') {
        result += advance();
    }
    if (currentIndex == input.size() || peek() != '"') {
        throw std::runtime_error("Unterminated string");
    }
    advance();
    return Token(TokenType::String, result);
}

Token Tokenizer::parseNumber() {
    std::string result;
    while (currentIndex < input.size() && (isdigit(peek()) || peek() == '-' || peek() == '.' || peek() == 'e' || peek() == 'E')) {
        result += advance();
    }

    return Token(TokenType::Number, result);
}

Token Tokenizer::parseKeyword() {
    std::string result;
    while (currentIndex < input.size() && isalpha(peek())) {
        result += advance();
    }

    if (result == "true") {
        return Token(TokenType::Boolean, "true");
    }

    if (result == "false") {
        return Token(TokenType::Boolean, "false");
    }

    if (result == "null") {
        return Token(TokenType::Null, "null");
    }

    return Token(TokenType::Unknown, result);
}
