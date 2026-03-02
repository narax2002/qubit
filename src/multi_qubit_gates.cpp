#include "qubit_exceptions.hpp"
#include "qubit_gates.hpp"

#include <cmath>

// Multi-qubit gate definitions.

namespace qubit::gates {

static inline void validate_index(const Qubit& q, int idx) {
    if (idx < 0 || idx >= q.num_qubits()) {
        printError(1);
    }
}

static inline void validate_indices2(const Qubit& q, int idx_a, int idx_b) {
    validate_index(q, idx_a);
    validate_index(q, idx_b);
}

static inline void validate_indices3(const Qubit& q, int idx_a, int idx_b, int idx_c) {
    validate_index(q, idx_a);
    validate_index(q, idx_b);
    validate_index(q, idx_c);
}

void SWAP(Qubit& q, int idx_a, int idx_b) {
    if (q.num_qubits() < 2) {
        printError(2);
    }
    validate_indices2(q, idx_a, idx_b);

    int len = q.size();
    int ref_a = 1 << idx_a;
    int ref_b = 1 << idx_b;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref_a) && ((i & ref_b) == 0)) {
            int j = i ^ (ref_a + ref_b);
            std::complex<double> temp = state[i];
            state[i] = state[j];
            state[j] = temp;
        }
    }
}

void CX(Qubit& q, int control_idx, int target_idx) {
    if (q.num_qubits() < 2) {
        printError(2);
    }
    validate_indices2(q, control_idx, target_idx);

    int len = q.size();
    int ref_a = 1 << control_idx;
    int ref_b = 1 << target_idx;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref_a) && ((i & ref_b) == 0)) {
            int j = i | ref_b;
            std::complex<double> temp = state[i];
            state[i] = state[j];
            state[j] = temp;
        }
    }
}

void CZ(Qubit& q, int control_idx, int target_idx) {
    if (q.num_qubits() < 2) {
        printError(2);
    }
    validate_indices2(q, control_idx, target_idx);

    int len = q.size();
    int ref_a = 1 << control_idx;
    int ref_b = 1 << target_idx;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref_a) && (i & ref_b)) {
            state[i] *= -1.0;
        }
    }
}

void CCX(Qubit& q, int control_a_idx, int control_b_idx, int target_idx) {
    if (q.num_qubits() < 3) {
        printError(2);
    }
    validate_indices3(q, control_a_idx, control_b_idx, target_idx);

    int len = q.size();
    int ref_a = 1 << control_a_idx;
    int ref_b = 1 << control_b_idx;
    int ref_c = 1 << target_idx;
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        if ((i & ref_a) && (i & ref_b) && ((i & ref_c) == 0)) {
            int j = i | ref_c;
            std::complex<double> temp = state[i];
            state[i] = state[j];
            state[j] = temp;
        }
    }
}

void Toffoli(Qubit& q, int idx) {
    // BUG: Toffoli gate should have 3 parameters (2 control + 1 target)
    // This implementation only swaps last two states, which is incorrect
    // Should be similar to CCX gate with proper control logic
    if (q.num_qubits() < 2) {
        printError(2);
    }
    validate_index(q, idx);
    int len = q.size();
    int ref = 1 << idx;

    auto& state = q.state();
    int i = len - 1;
    int j = i ^ ref;
    std::complex<double> temp = state[i];
    state[i] = state[j];
    state[j] = temp;
}

void CR(Qubit& q, int idx_a, int idx_b, double phi) {
    if (q.num_qubits() < 2) {
        printError(2);
    }
    validate_indices2(q, idx_a, idx_b);
    int len = q.size();
    int ref_a = 1 << idx_a;
    int ref_b = 1 << idx_b;
    std::complex<double> c = std::polar(1.0, phi);
    auto& state = q.state();
    for (int i = 0; i < len; ++i) {
        // BUG: Should only check control (ref_a), not both qubits
        // Controlled-R applies phase when control=1, regardless of target state
        // Correct condition: if ((i & ref_a) && (i & ref_b))
        // But for standard CR, it should be: if (i & ref_a) { apply phase to |11> }
        if ((i & ref_a) && (i & ref_b)) {
            state[i] *= c;
        }
    }
}

} // namespace qubit::gates
