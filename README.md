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
│   └── ParserTests.cpp      # Unit tests for Parser
├── CMakeLists.txt           # Build system definition
└── README.md                # Project documentation
```

---

## **Getting Started**

### **Prerequisites**

- **C++20-compatible compiler**:
  - GCC 10+ / Clang 12+ / MSVC 19.29+
- **CMake** 3.20+ for build configuration.
- **Google Test** (optional for running unit tests).

### **Cloning the Repository**

Clone this repository to your local machine:
```bash
git clone https://github.com/Davio-2002/JsonParser.git
cd JsonParser
