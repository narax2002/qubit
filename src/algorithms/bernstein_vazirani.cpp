#include "qubit/algorithms/search.hpp"
#include "qubit/exceptions.hpp"
#include "qubit/gates/one_qubit.hpp"

namespace qubit::algorithms {

void Bernstein_Vazirani(Qubit& q, int s) {
    int dim = q.num_qubits() - 1;
    int len = 1 << dim;

    if (s < 0 || len <= s) {
        printError(3);
    }
    q.initial();

    // State preparation
    q.initial();
    gates::X(q, dim);
    for (int i = 0; i <= dim; ++i) {
        gates::H(q, i);
    }

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
    for (int i = 0; i < dim; ++i) {
        gates::H(q, i);
    }
}

} // namespace qubit::algorithms
