#pragma once

#include "qubit.hpp"

namespace qubit::gates {

/// \brief Gate operations use zero-based qubit indices.

/// \brief Applies the Hadamard gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void H(Qubit& q, int idx);
/// \brief Applies the Pauli-X gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void X(Qubit& q, int idx);
/// \brief Applies the square-root of X gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void SRX(Qubit& q, int idx);
/// \brief Applies the Pauli-Y gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void Y(Qubit& q, int idx);
/// \brief Applies the Pauli-Z gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void Z(Qubit& q, int idx);
/// \brief Applies the S phase gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void S(Qubit& q, int idx);
/// \brief Applies the adjoint of the S gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void Sd(Qubit& q, int idx);
/// \brief Applies the T gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void T(Qubit& q, int idx);
/// \brief Applies the adjoint of the T gate to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
void Td(Qubit& q, int idx);
/// \brief Applies a phase rotation to one qubit.
/// \param q Register to modify.
/// \param idx Zero-based target qubit index.
/// \param phi Rotation angle in radians.
void R(Qubit& q, int idx, double phi);

/// \brief Swaps two qubits.
/// \param q Register to modify.
/// \param idx_a Zero-based index of the first qubit.
/// \param idx_b Zero-based index of the second qubit.
void SWAP(Qubit& q, int idx_a, int idx_b);
/// \brief Applies a controlled-X gate.
/// \param q Register to modify.
/// \param control_idx Zero-based control qubit index.
/// \param target_idx Zero-based target qubit index.
void CX(Qubit& q, int control_idx, int target_idx);
/// \brief Applies a controlled-Z gate.
/// \param q Register to modify.
/// \param control_idx Zero-based control qubit index.
/// \param target_idx Zero-based target qubit index.
void CZ(Qubit& q, int control_idx, int target_idx);
/// \brief Applies a controlled-controlled-X gate.
/// \param q Register to modify.
/// \param control_a_idx Zero-based first control qubit index.
/// \param control_b_idx Zero-based second control qubit index.
/// \param target_idx Zero-based target qubit index.
void CCX(Qubit& q, int control_a_idx, int control_b_idx, int target_idx);
/// \brief Applies a controlled phase rotation.
/// \param q Register to modify.
/// \param control_idx Zero-based control qubit index.
/// \param phi Rotation angle in radians.
/// \param target_idx Zero-based target qubit index.
void CR(Qubit& q, int control_idx, double phi, int target_idx);
/// \brief Applies the Toffoli gate.
/// \param q Register to modify.
/// \param control_a_idx Zero-based first control qubit index.
/// \param control_b_idx Zero-based second control qubit index.
/// \param target_idx Zero-based target qubit index.
void Toffoli(Qubit& q, int control_a_idx, int control_b_idx, int target_idx);

} // namespace qubit::gates
