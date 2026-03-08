#include "qubit_algorithms.hpp"
#include "qubit_exceptions.hpp"
#include "qubit_gates.hpp"
#include "test_framework.hpp"
#include "test_helpers.hpp"

#include <cmath>
#include <complex>
#include <vector>

using qubit::Qubit;
namespace a = qubit::algorithms;
namespace g = qubit::gates;

namespace {

int measure_data_register(const Qubit& q) {
    int dim = q.num_qubits() - 1;
    int len = 1 << dim;
    std::vector<double> probs = q.Qnorm();
    int max_idx = 0;
    for (int i = 1; i < len; ++i) {
        if (probs[i] + probs[i + len] > probs[max_idx] + probs[max_idx + len]) {
            max_idx = i;
        }
    }
    return max_idx;
}

std::vector<double> shor_summary(const Qubit& q) {
    std::vector<double> probs = q.Qnorm();
    std::vector<double> summary(8, 0.0);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            summary[i] += probs[8 * j + i];
        }
    }
    return summary;
}

} // namespace

TEST(Bernstein_Vazirani_finds_secret) {
    Qubit q(5);

    a::Bernstein_Vazirani(q, 10);

    EXPECT_TRUE_MSG(measure_data_register(q) == 10, "Bernstein-Vazirani should recover the secret");
}

TEST(Grover_finds_marked_state) {
    Qubit q(5);

    a::Grover(q, 3);

    EXPECT_TRUE_MSG(measure_data_register(q) == 3, "Grover should amplify the marked state");
}

TEST(QFT_transforms_basis_state) {
    Qubit q(3);

    q.initial();
    g::X(q, 0);
    a::QFT(q);

    qubit::test::expect_state("QFT |001>", q,
                              {std::complex<double>(0.3535533905932738, 0.0),
                               std::complex<double>(0.25, 0.25),
                               std::complex<double>(0.0, 0.3535533905932738),
                               std::complex<double>(-0.25, 0.25),
                               std::complex<double>(-0.3535533905932738, 0.0),
                               std::complex<double>(-0.25, -0.25),
                               std::complex<double>(0.0, -0.3535533905932738),
                               std::complex<double>(0.25, -0.25)});
}

TEST(Shor_matches_reference_summary) {
    Qubit q(7);

    a::Shor(q);

    std::vector<double> got = shor_summary(q);
    const std::vector<double> expected = {0.375, 0.0, 0.125, 0.0, 0.375, 0.0, 0.125, 0.0};
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_TRUE_MSG(std::abs(got[i] - expected[i]) <= qubit::test::kEps,
                        "Shor summary should match the reference distribution");
    }
}

TEST(Constructor_rejects_non_positive_qubits) {
    EXPECT_THROW(Qubit(0), qubit::QubitError);
}

TEST(Gates_reject_invalid_indices) {
    Qubit q1(1);
    Qubit q2(2);

    EXPECT_THROW(g::H(q1, -1), qubit::QubitError);
    EXPECT_THROW(g::H(q1, 1), qubit::QubitError);
    EXPECT_THROW(g::CX(q2, 0, 2), qubit::QubitError);
}

TEST(Algorithms_reject_invalid_parameters) {
    Qubit q(5);

    EXPECT_THROW(a::Grover(q, -1), qubit::QubitError);
    EXPECT_THROW(a::Bernstein_Vazirani(q, 16), qubit::QubitError);
}
