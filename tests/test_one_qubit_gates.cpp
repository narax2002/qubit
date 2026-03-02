#include "qubit_gates.hpp"
#include "test_framework.hpp"
#include "test_helpers.hpp"

#include <complex>
#include <vector>

using qubit::Qubit;
namespace g = qubit::gates;

TEST(H_gate) {
    Qubit q(1);

    qubit::test::set_basis_state(q, 0);
    g::H(q, 0);
    qubit::test::expect_state("H |0>", q, {1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)});

    qubit::test::set_basis_state(q, 1);
    g::H(q, 0);
    qubit::test::expect_state("H |1>", q, {1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)});
}

TEST(X_gate) {
    Qubit q(1);

    qubit::test::set_basis_state(q, 0);
    g::X(q, 0);
    qubit::test::expect_state("X |0>", q, {0.0, 1.0});

    qubit::test::set_basis_state(q, 1);
    g::X(q, 0);
    qubit::test::expect_state("X |1>", q, {1.0, 0.0});
}

TEST(Y_gate) {
    Qubit q(1);

    qubit::test::set_basis_state(q, 0);
    g::Y(q, 0);
    qubit::test::expect_state("Y |0>", q, {0.0, std::complex<double>(0.0, 1.0)});

    qubit::test::set_basis_state(q, 1);
    g::Y(q, 0);
    qubit::test::expect_state("Y |1>", q, {std::complex<double>(0.0, -1.0), 0.0});
}

TEST(phase_gates) {
    Qubit q(1);

    std::vector<std::complex<double>> plus = {
        1.0 / std::sqrt(2.0),
        1.0 / std::sqrt(2.0),
    };

    qubit::test::set_state(q, plus);
    g::Z(q, 0);
    qubit::test::expect_state("Z |+>", q, {1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)});

    qubit::test::set_state(q, plus);
    g::S(q, 0);
    qubit::test::expect_state(
        "S |+>", q, {1.0 / std::sqrt(2.0), std::complex<double>(0.0, 1.0) / std::sqrt(2.0)});

    qubit::test::set_state(q, plus);
    g::Sd(q, 0);
    qubit::test::expect_state(
        "Sd |+>", q, {1.0 / std::sqrt(2.0), std::complex<double>(0.0, -1.0) / std::sqrt(2.0)});

    qubit::test::set_state(q, plus);
    g::T(q, 0);
    qubit::test::expect_state("T |+>", q,
                              {1.0 / std::sqrt(2.0),
                               std::complex<double>(1.0, 1.0) / std::sqrt(2.0) / std::sqrt(2.0)});

    qubit::test::set_state(q, plus);
    g::Td(q, 0);
    qubit::test::expect_state("Td |+>", q,
                              {1.0 / std::sqrt(2.0),
                               std::complex<double>(1.0, -1.0) / std::sqrt(2.0) / std::sqrt(2.0)});

    qubit::test::set_state(q, plus);
    g::R(q, 0, PI / 3.0);
    qubit::test::expect_state("R |+>", q,
                              {1.0 / std::sqrt(2.0),
                               std::polar(1.0, PI / 3.0) / std::sqrt(2.0)});
}

TEST(SRX_gate) {
    Qubit q(1);

    const std::complex<double> a(0.5, 0.5);  // (1+i)/2
    const std::complex<double> b(0.5, -0.5); // (1-i)/2

    qubit::test::set_basis_state(q, 0);
    g::SRX(q, 0);
    qubit::test::expect_state("SRX |0>", q, {a, b});

    qubit::test::set_basis_state(q, 1);
    g::SRX(q, 0);
    qubit::test::expect_state("SRX |1>", q, {b, a});
}
