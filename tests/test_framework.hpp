#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace qubit::test {

struct TestCase {
    const char* name;
    void (*fn)();
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

class Registrar {
public:
    Registrar(const char* name, void (*fn)()) {
        registry().push_back({name, fn});
    }
};

inline const char*& current_test_name() {
    static const char* name = "";
    return name;
}

inline int& current_failures() {
    static int failures = 0;
    return failures;
}

inline int& total_failures() {
    static int failures = 0;
    return failures;
}

inline void fail(const char* expr, const char* file, int line, const std::string& msg) {
    std::cerr << "FAIL: " << current_test_name() << ": " << expr;
    if (!msg.empty()) {
        std::cerr << " (" << msg << ")";
    }
    std::cerr << " at " << file << ":" << line << "\n";
    ++current_failures();
    ++total_failures();
}

inline void expect_true(bool cond, const char* expr, const char* file, int line, const char* msg) {
    if (cond) {
        return;
    }
    fail(expr, file, line, msg ? std::string(msg) : std::string());
}

} // namespace qubit::test

#define TEST(name) \
    static void test_##name(); \
    static ::qubit::test::Registrar registrar_##name(#name, test_##name); \
    static void test_##name()

#define EXPECT_TRUE(cond) \
    ::qubit::test::expect_true((cond), #cond, __FILE__, __LINE__, "")

#define EXPECT_TRUE_MSG(cond, msg) \
    ::qubit::test::expect_true((cond), #cond, __FILE__, __LINE__, (msg))
