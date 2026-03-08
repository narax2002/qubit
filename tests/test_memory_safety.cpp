#include "qubit/qubit.hpp"
#include "test_framework.hpp"
#include "test_helpers.hpp"

#include <complex>
#include <vector>

using qubit::Qubit;
namespace algo = qubit::algorithms;
namespace gates = qubit::gates;

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

std::vector<std::complex<double>> sample_state() {
    return {
        std::complex<double>(1.0, 0.0),    std::complex<double>(-0.5, 0.25),
        std::complex<double>(0.25, -0.75), std::complex<double>(0.0, 0.5),
        std::complex<double>(-1.0, 0.0),   std::complex<double>(0.75, 0.25),
        std::complex<double>(0.5, 0.5),    std::complex<double>(-0.25, -0.25),
    };
}

} // namespace

TEST(repeated_register_lifecycle) {
    for (int iter = 0; iter < 256; ++iter) {
        Qubit q(6);

        gates::H(q, 0);
        gates::X(q, 1);
        gates::SRX(q, 2);
        gates::R(q, 3, PI / 7.0);
        gates::CX(q, 0, 4);
        gates::CZ(q, 1, 5);
        gates::SWAP(q, 2, 3);
        gates::CCX(q, 5, 4, 0);
        gates::Toffoli(q, 5, 3, 1);

        EXPECT_TRUE(q.size() == 64);
    }
}

TEST(repeated_fourier_transforms) {
    const std::vector<std::complex<double>> expected = sample_state();

    for (int iter = 0; iter < 256; ++iter) {
        Qubit q(3);
        qubit::test::set_state(q, expected);

        algo::FFT(q);
        algo::IFFT(q);

        qubit::test::expect_state("IFFT(FFT(q)) == q", q, expected);
    }
}

TEST(repeated_algorithm_lifecycle) {
    for (int iter = 0; iter < 128; ++iter) {
        Qubit grover(5);
        algo::Grover(grover, 3);
        EXPECT_TRUE(measure_data_register(grover) == 3);

        Qubit bernstein_vazirani(5);
        algo::Bernstein_Vazirani(bernstein_vazirani, 10);
        EXPECT_TRUE(measure_data_register(bernstein_vazirani) == 10);
    }

    for (int iter = 0; iter < 32; ++iter) {
        Qubit shor(7);
        algo::Shor(shor);
        EXPECT_TRUE(shor.size() == 128);
    }
}

TEST(repeated_exception_paths) {
    for (int iter = 0; iter < 256; ++iter) {
        EXPECT_THROW(Qubit(0), qubit::QubitError);

        Qubit q(2);
        EXPECT_THROW(gates::H(q, -1), qubit::QubitError);
        EXPECT_THROW(gates::CX(q, 0, 2), qubit::QubitError);
        EXPECT_THROW(algo::Grover(q, -1), qubit::QubitError);
    }
}
