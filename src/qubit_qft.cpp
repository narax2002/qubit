#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

#include <cmath>

namespace qubit::algorithms {

void QFT(Qubit& q) {
    int nv = q.num_qubits();
    for (int i = 0; i < nv / 2; ++i) {
        gates::SWAP(q, i, nv - 1 - i);
    }

    for (int i = 0; i < nv; ++i) {
        int k = 1 << i;
        for (int j = 0; j < i; ++j) {
            gates::CR(q, j, PI / k, i);
            k = k >> 1;
        }
        gates::H(q, i);
    }
}

void FFT(Qubit& q) {
    int n = q.num_qubits();
    int d1 = 1 << (n - 1);
    for (int m = 1; m <= n; ++m) {
        int dm = 1 << (n - m);
        int D = 1 << m;
        std::complex<double> xi = std::polar(1.0, -2.0 * PI / D);
        Qubit temp(n);

        D = 1 << (m - 1);

        auto& state = q.state();
        auto& temp_state = temp.state();
        for (int i = 0; i < dm; ++i) {
            std::complex<double> eta(1.0, 0.0);
            for (int k = 0; k < D; ++k) {
                int k1 = i + k * dm;
                int k2 = i + 2 * k * dm;
                temp_state[k1] = state[k2] + eta * state[k2 + dm];
                temp_state[k1 + d1] = state[k2] - eta * state[k2 + dm];

                eta *= xi;
            }
        }
        state = temp_state;
    }
}

void IFFT(Qubit& q) {
    int n = q.num_qubits();
    int d1 = 1 << (n - 1);
    for (int m = 1; m <= n; ++m) {
        int dm = 1 << (n - m);
        int D = 1 << m;
        std::complex<double> xi = std::polar(1.0, 2.0 * PI / D);
        Qubit temp(n);

        D = 1 << (m - 1);
        auto& state = q.state();
        auto& temp_state = temp.state();
        for (int i = 0; i < dm; ++i) {
            std::complex<double> eta(1.0, 0.0);
            for (int k = 0; k < D; ++k) {
                int k1 = i + k * dm;
                int k2 = i + 2 * k * dm;
                temp_state[k1] = state[k2] + eta * state[k2 + dm];
                temp_state[k1 + d1] = state[k2] - eta * state[k2 + dm];

                eta *= xi;
            }
        }
        state = temp_state;
    }
    for (int i = 0; i < q.size(); ++i) {
        q.state()[i] /= q.size();
    }
}

} // namespace qubit::algorithms
