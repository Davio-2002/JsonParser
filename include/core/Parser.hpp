#pragma once

#include <core/Tokenizer.hpp>
#include <core/Parser.hpp>

#include <memory>
#include <variant>
#include <unordered_map>

class JsonValue;

using JsonObject = std::unordered_map<std::string, std::shared_ptr<JsonValue> >;
using JsonArray = std::vector<std::shared_ptr<JsonValue> >;

class JsonValue {
public:
    using ValueType = std::variant<JsonObject, JsonArray, std::string, double, bool, std::nullptr_t>;

    explicit JsonValue(ValueType v) : value_(std::move(v)) {
    }
    const ValueType &value() const { return value_; }

private:
    ValueType value_;
};

class Parser {
public:
    explicit Parser(std::vector<Token>& tokens);
    explicit Parser(const std::string& inputOrFilePath, bool isFile = false);

    std::shared_ptr<JsonValue> parse();

private:
    std::shared_ptr<JsonValue> parseValue();

    JsonObject parseObject();

    JsonArray parseArray();

    std::string parseString();

    double parseNumber();

    bool parseBoolean();

    std::nullptr_t parseNull();

    [[nodiscard]] const Token &peek() const;

    const Token &advance();

    void expect(TokenType type);

private:
    Tokenizer::TokenVector tokens_;
    size_t currentIndex_{};
};
