#include "qubit_gates.hpp"
#include "test_framework.hpp"
#include "test_helpers.hpp"

#include <complex>
#include <vector>

using qubit::Qubit;
namespace g = qubit::gates;

TEST(SWAP_gate) {
    Qubit q(2);

    qubit::test::set_basis_state(q, 1); // |01>
    g::SWAP(q, 0, 1);
    qubit::test::expect_state("SWAP |01>", q, {0.0, 0.0, 1.0, 0.0}); // |10>
}

TEST(CX_gate) {
    Qubit q(2);

    qubit::test::set_basis_state(q, 2); // |10>
    g::CX(q, 1, 0);
    qubit::test::expect_state("CX control=1 target=0 |10>", q, {0.0, 0.0, 0.0, 1.0}); // |11>

    qubit::test::set_basis_state(q, 1); // |01>
    g::CX(q, 0, 1);
    qubit::test::expect_state("CX control=0 target=1 |01>", q, {0.0, 0.0, 0.0, 1.0}); // |11>
}

TEST(CZ_gate) {
    Qubit q(2);

    qubit::test::set_basis_state(q, 3); // |11>
    g::CZ(q, 1, 0);
    qubit::test::expect_state("CZ |11>", q, {0.0, 0.0, 0.0, -1.0});

    qubit::test::set_basis_state(q, 2); // |10>
    g::CZ(q, 1, 0);
    qubit::test::expect_state("CZ |10>", q, {0.0, 0.0, 1.0, 0.0});
}

TEST(CR_gate) {
    Qubit q(2);

    std::vector<std::complex<double>> plusplus = {
        0.5,
        0.5,
        0.5,
        0.5,
    };

    qubit::test::set_state(q, plusplus);
    g::CR(q, 1, PI / 2.0, 0);
    qubit::test::expect_state("CR |++>", q, {0.5, 0.5, 0.5, std::complex<double>(0.0, 0.5)});
}

TEST(CCX_gate) {
    Qubit q(3);

    qubit::test::set_basis_state(q, 6); // |110>
    g::CCX(q, 2, 1, 0);
    qubit::test::expect_state("CCX |110>", q, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}); // |111>

    qubit::test::set_basis_state(q, 7); // |111>
    g::CCX(q, 2, 1, 0);
    qubit::test::expect_state("CCX |111>", q, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0}); // |110>
}

TEST(Toffoli_gate) {
    Qubit q(3);

    qubit::test::set_basis_state(q, 6); // |110>
    g::Toffoli(q, 2, 1, 0);
    qubit::test::expect_state("Toffoli |110>", q, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}); // |111>
}
