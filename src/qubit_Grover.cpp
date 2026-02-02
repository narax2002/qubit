#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

#include <cmath>
#include <iostream>

namespace qubit {
namespace algorithms {

void Grover(Qubit& q, int k) {
    int dim = q.num_qubits() - 1; // last qubit is ancilla
    int len = 1 << dim;

    if (k < 0 || len <= k)
        q.PrintError(3);
    q.Initial();

    int MaxIter = static_cast<int>(std::ceil(pi * std::pow(2.0, static_cast<double>(dim) / 2) / 4));
    std::cout << "MaxIter = " << MaxIter << std::endl;

    // State preparation
    for (int i = 0; i < dim; ++i)
        gates::H(q, i);
    gates::X(q, dim);
    gates::H(q, dim);

    auto& state = q.state();
    for (int iter = 0; iter < MaxIter; ++iter) {
        // Quantum oracle
        int yk = k + (1 << dim);
        std::complex<double> temp = state[k];
        state[k] = state[yk];
        state[yk] = temp;

        // Action identity - 2 * |psi><psi|
        for (int i = 0; i < dim; ++i)
            gates::H(q, i);

        // Action identity - 2 * |0><0|
        for (int i = 0; i < dim; ++i)
            gates::X(q, i);
        state[(2 << dim) - 1] *= -1.0;
        state[(1 << dim) - 1] *= -1.0;
        for (int i = 0; i < dim; ++i)
            gates::X(q, i);

        for (int i = 0; i < dim; ++i)
            gates::H(q, i);
    }

    // Measurement
    std::vector<double> a_temp = q.Qnorm();
    int max_idx = 0;
    for (int i = 1; i < len; ++i) {
        if (a_temp[i] + a_temp[i + len] > a_temp[max_idx] + a_temp[max_idx + len]) {
            max_idx = i;
        }
    }
    std::cout << "k=" << max_idx << std::endl;
}

} // namespace algorithms
} // namespace qubit
