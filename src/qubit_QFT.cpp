#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

#include <cmath>

namespace qubit {
namespace algorithms {

void QFT(Qubit& q) {
    int nv = q.num_qubits();
    for (int i = 0; i < nv / 2; ++i) {
        gates::SWAP(q, i, nv - 1 - i);
    }

    for (int i = 0; i < nv; ++i) {
        int k = 1 << i;
        for (int j = 0; j < i; ++j) {
            gates::CR(q, j, i, PI / k);
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

void Multi(Qubit& out, const Qubit& a, const Qubit& b) {
    auto& out_state = out.state();
    const auto& a_state = a.state();
    const auto& b_state = b.state();
    for (int i = 0; i < out.size(); ++i) {
        out_state[i] = a_state[i] * b_state[i];
    }
}

void FFT_iter(Qubit& q) {
    std::complex<double> w = std::polar(1.0, 2.0 * PI / q.size());
    if (q.num_qubits() == 1) {
        auto& state = q.state();
        std::complex<double> temp_a = state[0];
        std::complex<double> temp_b = state[1];
        state[0] = (temp_a + temp_b) / std::sqrt(2.0);
        state[1] = (temp_a + w * temp_b) / std::sqrt(2.0);
        return;
    }

    int nv = q.num_qubits() - 1;
    Qubit q_even(nv);
    Qubit q_odd(nv);

    int len = q_even.size();
    const auto& state = q.state();
    auto& even_state = q_even.state();
    auto& odd_state = q_odd.state();
    for (int i = 0; i < len; ++i) {
        even_state[i] = state[2 * i];
        odd_state[i] = state[2 * i + 1];
    }

    FFT_iter(q_even);
    FFT_iter(q_odd);

    auto& out_state = q.state();
    for (int i = 0; i < len; ++i) {
        out_state[i] = (even_state[i] + std::pow(w, i) * odd_state[i]) / std::sqrt(2.0);
        out_state[len + i] = (even_state[i] - std::pow(w, i) * odd_state[i]) / std::sqrt(2.0);
    }
}

} // namespace algorithms
} // namespace qubit
