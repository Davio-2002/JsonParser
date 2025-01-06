# JSON Parser

A powerful and lightweight **JSON Parser** implemented in modern **C++**. This parser can handle JSON strings and JSON files, converting them into structured data. It supports objects, arrays, strings, numbers, booleans, and null values.

## **Features**

- Parse JSON strings or files.
- Handles nested JSON objects and arrays.
- Designed with modularity and scalability in mind.
- Comprehensive error handling with detailed messages.
- Lightweight and modern implementation using **C++20** features like `std::variant` and `std::filesystem`.
- Easy-to-run unit tests with Google Test.

---

## **Project Structure**

```plaintext
JsonParser/
├── src/
│   ├── core/
│   │   ├── Tokenizer.cpp    # Tokenizer implementation
│   │   ├── Parser.cpp       # JSON Parser implementation
│   │   └── FileReader.cpp   # File reading utility
│   └── main.cpp             # Entry point
├── include/
│   ├── core/
│   │   ├── Tokenizer.hpp    # Tokenizer definition
│   │   ├── Parser.hpp       # Parser definition
│   │   └── FileReader.hpp   # FileReader definition
├── tests/
│   ├── TokenizerTests.cpp   # Unit tests for Tokenizer
│   ├── ParserTests.cpp      # Unit tests for Parser
│   └── FileReaderTests.cpp  # Unit tests for FileReader
├── CMakeLists.txt           # Build system definition
└── README.md                # Project documentation
