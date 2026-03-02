#include "qubit_gates.hpp"

#include <cmath>

// One-qubit gate definitions.

namespace qubit {
namespace gates {

void H(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::vector<std::complex<double>> temp(len);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref) == 0) {
            int j = i | ref;
            temp[i] = (state[i] + state[j]) / std::sqrt(2.0);
            temp[j] = (state[i] - state[j]) / std::sqrt(2.0);
        }
    }
    state.swap(temp);
}

void X(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref) == 0) {
            int j = i | ref;
            std::complex<double> temp = state[i];
            state[i] = state[j];
            state[j] = temp;
        }
    }
}

void SRX(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c_a(0.5, 0.5);
    std::complex<double> c_b(0.5, -0.5);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref) == 0) {
            int j = i | ref;
            std::complex<double> temp_a = state[i];
            std::complex<double> temp_b = state[j];
            state[i] = c_a * temp_a + c_a * temp_b;
            state[j] = c_b * temp_a + c_b * temp_b;
        }
    }
}

void Y(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c(0.0, 1.0);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (!(i & ref)) {
            int j = i | ref;
            std::complex<double> temp = state[i];
            state[i] = c * state[j];
            state[j] = -c * temp;
        }
    }
}

void Z(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= -1.0;
        }
    }
}

void S(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c(0.0, 1.0);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= c;
        }
    }
}

void Sd(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c(0.0, -1.0);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= c;
        }
    }
}

void T(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c(1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0));
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= c;
        }
    }
}

void Td(Qubit& q, int idx) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c(1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0));
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= c;
        }
    }
}

void R(Qubit& q, int idx, double phi) {
    if (idx >= q.num_qubits())
        q.PrintError(1);
    int len = q.size();
    int ref = 1 << idx;
    std::complex<double> c = std::polar(1.0, phi);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if (i & ref) {
            state[i] *= c;
        }
    }
}

} // namespace gates
} // namespace qubit
