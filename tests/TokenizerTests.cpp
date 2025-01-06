#include <gtest/gtest.h>
#include <core/Tokenizer.hpp>

TEST(TokenizerTest, EmptyJSON) {
    const std::string json = "{}";
    Tokenizer tokenizer(json);
    const auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].type, TokenType::LeftBrace);
    EXPECT_EQ(tokens[1].type, TokenType::RightBrace);
}

TEST(TokenizerTest, SimpleObject) {
    const std::string json = R"({
        "key": "value",
        "number": 123,
        "boolean": true,
        "nullValue": null
    })";
    Tokenizer tokenizer(json);
    const auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 17);
    EXPECT_EQ(tokens[0].type, TokenType::LeftBrace);
    EXPECT_EQ(tokens[1].type, TokenType::String);  // "key"
    EXPECT_EQ(tokens[1].value, "key");
    EXPECT_EQ(tokens[10].type, TokenType::Colon); // colon
    EXPECT_EQ(tokens[10].value, ":");
    EXPECT_EQ(tokens[14].type, TokenType::Colon);   // colon
    EXPECT_EQ(tokens[14].value, ":");
}


TEST(TokenizerTest, Array) {
    const std::string json = R"([1, "text", false, null])";
    Tokenizer tokenizer(json);
    const auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 9);
    EXPECT_EQ(tokens[0].type, TokenType::LeftBracket);
    EXPECT_EQ(tokens[1].type, TokenType::Number);
    EXPECT_EQ(tokens[2].type, TokenType::Comma);
    EXPECT_EQ(tokens[3].type, TokenType::String);
}

TEST(TokenizerTest, InvalidJSON) {
    const std::string json = R"({
        "unclosedString: "value
    })";

    Tokenizer tokenizer(json);
    EXPECT_THROW(tokenizer.tokenize(), std::runtime_error);
}
