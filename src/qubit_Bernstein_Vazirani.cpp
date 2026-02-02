#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

#include <iostream>

namespace qubit {
namespace algorithms {

void Bernstein_Vazirani(Qubit& q, int s) {
    int dim = q.num_qubits() - 1;
    int len = 1 << dim;

    if (s < 0 || len <= s)
        q.PrintError(3);
    q.Initial();

    // State preparation
    q.Initial();
    gates::X(q, dim);
    for (int i = 0; i <= dim; ++i)
        gates::H(q, i);

    // Classical hidden string
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        int vec_dot = s & i;
        int f = 0;
        while (vec_dot) {
            f = f ^ (vec_dot & 1);
            vec_dot = vec_dot >> 1;
        }

        if (f) {
            std::complex<double> temp = state[i];
            state[i] = state[i + len];
            state[i + len] = temp;
        }
    }

    // Basis change
    for (int i = 0; i < dim; ++i)
        gates::H(q, i);

    // Measurement
    std::vector<double> a_temp = q.Qnorm();
    int max_idx = 0;
    for (int i = 1; i < len; ++i) {
        if (a_temp[i] + a_temp[i + len] > a_temp[max_idx] + a_temp[max_idx + len]) {
            max_idx = i;
        }
    }
    std::cout << "s=" << max_idx << std::endl;
}

} // namespace algorithms
} // namespace qubit
