#pragma once

#include "qubit.hpp"
#include "test_framework.hpp"

#include <algorithm>
#include <complex>
#include <string>
#include <vector>

namespace qubit::test {

static constexpr double kEps = 1e-9;

inline bool approx_eq(const std::complex<double>& a, const std::complex<double>& b, double eps = kEps) {
    return std::abs(a - b) <= eps;
}

inline bool state_equiv_global(const std::vector<std::complex<double>>& got,
                               const std::vector<std::complex<double>>& expected,
                               double eps = kEps) {
    if (got.size() != expected.size()) {
        return false;
    }

    int anchor = -1;
    for (size_t i = 0; i < expected.size(); ++i) {
        if (std::abs(expected[i]) > eps) {
            anchor = static_cast<int>(i);
            break;
        }
    }
    if (anchor == -1) {
        for (size_t i = 0; i < got.size(); ++i) {
            if (std::abs(got[i]) > eps) {
                return false;
            }
        }
        return true;
    }

    std::complex<double> phase = got[anchor] / expected[anchor];
    for (size_t i = 0; i < got.size(); ++i) {
        if (!approx_eq(got[i], phase * expected[i], eps)) {
            return false;
        }
    }
    return true;
}

inline void set_basis_state(Qubit& q, int idx) {
    auto& s = q.state();
    std::fill(s.begin(), s.end(), std::complex<double>(0.0, 0.0));
    s[idx] = std::complex<double>(1.0, 0.0);
}

inline void set_state(Qubit& q, const std::vector<std::complex<double>>& state) {
    auto& s = q.state();
    if (s.size() != state.size()) {
        qubit::test::fail("state size mismatch", __FILE__, __LINE__, "set_state");
        return;
    }
    s = state;
}

inline void expect_state(const char* name, const Qubit& q,
                         const std::vector<std::complex<double>>& expected) {
    const auto& got = q.state();
    EXPECT_TRUE_MSG(state_equiv_global(got, expected), name);
}

} // namespace qubit::test
