#include "test_framework.hpp"

#include <iostream>

int main() {
    using qubit::test::current_failures;
    using qubit::test::current_test_name;
    using qubit::test::registry;
    using qubit::test::total_failures;

    int failed_tests = 0;
    for (const auto& test : registry()) {
        current_test_name() = test.name;
        current_failures() = 0;
        test.fn();
        if (current_failures() == 0) {
            std::cout << "[PASS] " << test.name << "\n";
        } else {
            std::cout << "[FAIL] " << test.name << " (" << current_failures() << " failure(s))\n";
            ++failed_tests;
        }
    }

    std::cout << "Tests run: " << registry().size() << ", Failed tests: " << failed_tests
              << ", Assertions failed: " << total_failures() << "\n";

    return failed_tests == 0 ? 0 : 1;
}
