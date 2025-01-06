#include <iostream>
#include <core/Parser.hpp>

namespace {
    void printJson(const std::shared_ptr<JsonValue> &value, const int indent = 0) {
        const std::string padding(indent, ' ');

        std::visit(
            [&]<typename T0>(const T0 &val) {
                using T = std::decay_t<T0>;

                if constexpr (std::is_same_v<T, JsonObject>) {
                    std::cout << padding << "{\n";
                    for (const auto &[key, objVal]: val) {
                        std::cout << padding << "  \"" << key << "\": ";
                        printJson(objVal, indent + 2);
                    }
                    std::cout << padding << "}\n";
                } else if constexpr (std::is_same_v<T, JsonArray>) {
                    std::cout << padding << "[\n";
                    for (const auto &arrVal: val) {
                        printJson(arrVal, indent + 2);
                    }
                    std::cout << padding << "]\n";
                } else if constexpr (std::is_same_v<T, std::string>) {
                    std::cout << "\"" << val << "\"\n";
                } else if constexpr (std::is_same_v<T, double>) {
                    std::cout << val << "\n";
                } else if constexpr (std::is_same_v<T, bool>) {
                    std::cout << (val ? "true" : "false") << "\n";
                } else if constexpr (std::is_same_v<T, std::nullptr_t>) {
                    std::cout << "null\n";
                }
            },
            value->value()
        );
    }
}

int main(const int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <json_string_or_file_path> [--file]\n";
            return 1;
        }

        std::string input = argv[1];
        const bool isFile = (argc == 3 && std::string(argv[2]) == "--file");

        Parser parser(input, isFile);
        const auto root = parser.parse();

        std::cout << "Parsed JSON structure:\n";
        printJson(root);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}