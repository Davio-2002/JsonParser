#include <gtest/gtest.h>
#include <core/Parser.hpp>

class ParserTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::shared_ptr<JsonValue> parseJson(const std::string &json) {
        Tokenizer tokenizer(json);
        const auto tokens = tokenizer.tokenize();
        Parser parser(tokens);
        return parser.parse();
    }
};

TEST_F(ParserTestFixture, SimpleTypes) {
    const std::string json = R"(
        {
            "string": "value",
            "number": 42,
            "boolean": true,
            "null": null
        }
    )";

    const auto root = parseJson(json);

    ASSERT_TRUE(std::holds_alternative<JsonObject>(root->value()));
    const auto &obj = std::get<JsonObject>(root->value());

    ASSERT_EQ(obj.size(), 4);
    EXPECT_EQ(std::get<std::string>(obj.at("string")->value()), "value");
    EXPECT_EQ(std::get<double>(obj.at("number")->value()), 42);
    EXPECT_EQ(std::get<bool>(obj.at("boolean")->value()), true);
    EXPECT_EQ(std::get<std::nullptr_t>(obj.at("null")->value()), nullptr);
}

TEST_F(ParserTestFixture, NestedObject) {
    const std::string json = R"(
        {
            "nested": {
                "key": "value",
                "number": 123
            }
        }
    )";

    const auto root = parseJson(json);

    ASSERT_TRUE(std::holds_alternative<JsonObject>(root->value()));
    const auto &obj = std::get<JsonObject>(root->value());

    ASSERT_TRUE(std::holds_alternative<JsonObject>(obj.at("nested")->value()));
    const auto &nestedObj = std::get<JsonObject>(obj.at("nested")->value());
    EXPECT_EQ(std::get<std::string>(nestedObj.at("key")->value()), "value");
    EXPECT_EQ(std::get<double>(nestedObj.at("number")->value()), 123);
}

TEST_F(ParserTestFixture, Array) {
    const std::string json = R"(
        [1, "text", false, null, {"key": "value"}]
    )";

    const auto root = parseJson(json);

    ASSERT_TRUE(std::holds_alternative<JsonArray>(root->value()));
    const auto &array = std::get<JsonArray>(root->value());

    ASSERT_EQ(array.size(), 5);
    EXPECT_EQ(std::get<double>(array[0]->value()), 1);
    EXPECT_EQ(std::get<std::string>(array[1]->value()), "text");
    EXPECT_EQ(std::get<bool>(array[2]->value()), false);
    EXPECT_EQ(std::get<std::nullptr_t>(array[3]->value()), nullptr);

    ASSERT_TRUE(std::holds_alternative<JsonObject>(array[4]->value()));
    const auto &obj = std::get<JsonObject>(array[4]->value());
    EXPECT_EQ(std::get<std::string>(obj.at("key")->value()), "value");
}

TEST_F(ParserTestFixture, LargeNestedObject) {
    const std::string json = R"(
        {
            "user": {
                "id": 123,
                "name": "John Doe",
                "isActive": true,
                "roles": ["admin", "editor", "viewer"],
                "settings": {
                    "theme": "dark",
                    "notifications": {
                        "email": true,
                        "sms": false
                    }
                }
            }
        }
    )";

    auto root = parseJson(json);

    ASSERT_TRUE(std::holds_alternative<JsonObject>(root->value()));
    const auto& obj = std::get<JsonObject>(root->value());

    ASSERT_TRUE(std::holds_alternative<JsonObject>(obj.at("user")->value()));
    const auto& userObj = std::get<JsonObject>(obj.at("user")->value());

    EXPECT_EQ(std::get<double>(userObj.at("id")->value()), 123);
    EXPECT_EQ(std::get<std::string>(userObj.at("name")->value()), "John Doe");
    EXPECT_EQ(std::get<bool>(userObj.at("isActive")->value()), true);

    ASSERT_TRUE(std::holds_alternative<JsonArray>(userObj.at("roles")->value()));
    const auto& roles = std::get<JsonArray>(userObj.at("roles")->value());
    ASSERT_EQ(roles.size(), 3);
    EXPECT_EQ(std::get<std::string>(roles[0]->value()), "admin");
    EXPECT_EQ(std::get<std::string>(roles[1]->value()), "editor");
    EXPECT_EQ(std::get<std::string>(roles[2]->value()), "viewer");

    ASSERT_TRUE(std::holds_alternative<JsonObject>(userObj.at("settings")->value()));
    const auto& settings = std::get<JsonObject>(userObj.at("settings")->value());

    EXPECT_EQ(std::get<std::string>(settings.at("theme")->value()), "dark");

    ASSERT_TRUE(std::holds_alternative<JsonObject>(settings.at("notifications")->value()));
    const auto& notifications = std::get<JsonObject>(settings.at("notifications")->value());
    EXPECT_EQ(std::get<bool>(notifications.at("email")->value()), true);
    EXPECT_EQ(std::get<bool>(notifications.at("sms")->value()), false);
}

TEST_F(ParserTestFixture, MixedArrayTypes) {
    const std::string json = R"(
        [42, "string", true, null, [1, 2, 3], {"key": "value"}]
    )";

    auto root = parseJson(json);

    ASSERT_TRUE(std::holds_alternative<JsonArray>(root->value()));
    const auto& array = std::get<JsonArray>(root->value());
    ASSERT_EQ(array.size(), 6);

    EXPECT_EQ(std::get<double>(array[0]->value()), 42);
    EXPECT_EQ(std::get<std::string>(array[1]->value()), "string");
    EXPECT_EQ(std::get<bool>(array[2]->value()), true);
    EXPECT_EQ(std::get<std::nullptr_t>(array[3]->value()), nullptr);


    ASSERT_TRUE(std::holds_alternative<JsonArray>(array[4]->value()));
    const auto& nestedArray = std::get<JsonArray>(array[4]->value());
    ASSERT_EQ(nestedArray.size(), 3);
    EXPECT_EQ(std::get<double>(nestedArray[0]->value()), 1);
    EXPECT_EQ(std::get<double>(nestedArray[1]->value()), 2);
    EXPECT_EQ(std::get<double>(nestedArray[2]->value()), 3);


    ASSERT_TRUE(std::holds_alternative<JsonObject>(array[5]->value()));
    const auto& nestedObject = std::get<JsonObject>(array[5]->value());
    EXPECT_EQ(std::get<std::string>(nestedObject.at("key")->value()), "value");
}


