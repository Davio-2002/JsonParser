#include <core/Parser.hpp>
#include <core/FileReader.hpp>
#include <iostream>

Parser::Parser(std::vector<Token> &tokens): tokens_(tokens) {
}

Parser::Parser(const std::string &inputOrFilePath, const bool isFile)
    : tokens_([&]() {
        const std::string jsonInput = isFile ? FileReader::read(inputOrFilePath) : inputOrFilePath;
        Tokenizer tokenizer(jsonInput);
        return tokenizer.tokenize();
    }()) {
}

std::shared_ptr<JsonValue> Parser::parse() {
    return parseValue();
}

std::shared_ptr<JsonValue> Parser::parseValue() {
    switch (const Token &token = peek(); token.type) {
        case TokenType::LeftBrace:
            return std::make_shared<JsonValue>(parseObject());
        case TokenType::LeftBracket:
            return std::make_shared<JsonValue>(parseArray());
        case TokenType::String:
            return std::make_shared<JsonValue>(parseString());
        case TokenType::Number:
            return std::make_shared<JsonValue>(parseNumber());
        case TokenType::Boolean:
            return std::make_shared<JsonValue>(parseBoolean());
        case TokenType::Null:
            return std::make_shared<JsonValue>(parseNull());
        default: throw std::runtime_error("Unexpected token:" + token.value);
    }
}


JsonObject Parser::parseObject() {
    expect(TokenType::LeftBrace);
    JsonObject object;

    while (peek().type != TokenType::RightBrace) {
        std::string key = parseString();
        expect(TokenType::Colon);
        auto value = parseValue();
        object.emplace(std::move(key), std::move(value));

        if (peek().type == TokenType::Comma) {
            advance();
        } else {
            break;
        }
    }

    expect(TokenType::RightBrace);
    return object;
}

JsonArray Parser::parseArray() {
    expect(TokenType::LeftBracket);
    JsonArray array;

    while (peek().type != TokenType::RightBracket) {
        array.push_back(parseValue());

        if (peek().type == TokenType::Comma) {
            advance();
        } else {
            break;
        }
    }

    expect(TokenType::RightBracket);
    return array;
}

std::string Parser::parseString() {
    const Token &token = advance();
    if (TokenType::String != token.type) {
        throw std::runtime_error("Expected string, got: " + token.value);
    }
    return token.value;
}

double Parser::parseNumber() {
    const Token &token = advance();
    if (TokenType::Number != token.type) {
        throw std::runtime_error("Expected number, got: " + token.value);
    }
    return std::stod(token.value);
}

bool Parser::parseBoolean() {
    const Token &token = advance();

    if (TokenType::Boolean != token.type) {
        throw std::runtime_error("Expected boolean, got: " + token.value);
    }

    return token.value == "true";
}

std::nullptr_t Parser::parseNull() {
    if (const Token &token = advance(); token.value != "null") {
        throw std::runtime_error("Expected null, got: " + token.value);
    }

    return nullptr;
}

const Token &Parser::peek() const {
    return tokens_[currentIndex_];
}

const Token &Parser::advance() {
    if (currentIndex_ >= tokens_.size()) {
        throw std::runtime_error("Unexpected end of input");
    }

    return tokens_[currentIndex_++];
}

void Parser::expect(TokenType type) {
    if (this->peek().type != type) {
        throw std::runtime_error(
            "Expected token: " + std::to_string(static_cast<int>(type)) + ", got: " + std::to_string(
                static_cast<int>(this->peek().type)));
    }
    advance();
}
