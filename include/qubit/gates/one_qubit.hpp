#pragma once

#include "qubit/register.hpp"

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

} // namespace qubit::gates
