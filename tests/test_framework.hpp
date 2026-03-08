#pragma once

#include <exception>
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

template <typename Exception, typename Fn>
inline void expect_throw(Fn&& fn, const char* expr, const char* file, int line,
                         const char* exception_name) {
    try {
        fn();
    } catch (const Exception&) {
        return;
    } catch (const std::exception& ex) {
        fail(expr, file, line,
             std::string("expected ") + exception_name + ", got std::exception: " + ex.what());
        return;
    } catch (...) {
        fail(expr, file, line,
             std::string("expected ") + exception_name + ", got non-std exception");
        return;
    }

    fail(expr, file, line, std::string("expected ") + exception_name + " to be thrown");
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

#define EXPECT_THROW(stmt, exception_type)                                                   \
    ::qubit::test::expect_throw<exception_type>(                                             \
        [&]() {                                                                              \
            static_cast<void>(stmt);                                                         \
        },                                                                                   \
        #stmt, __FILE__, __LINE__, #exception_type)
