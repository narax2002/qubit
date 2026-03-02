#pragma once

#include "qubit.hpp"

namespace qubit::gates {

// One-qubit gates
void H(Qubit& q, int idx);
void X(Qubit& q, int idx);
void SRX(Qubit& q, int idx);
void Y(Qubit& q, int idx);
void Z(Qubit& q, int idx);
void S(Qubit& q, int idx);
void Sd(Qubit& q, int idx);
void T(Qubit& q, int idx);
void Td(Qubit& q, int idx);
void R(Qubit& q, int idx, double phi);

// Multi-qubit gates
void SWAP(Qubit& q, int idx_a, int idx_b);
void CX(Qubit& q, int control_idx, int target_idx);
void CZ(Qubit& q, int control_idx, int target_idx);
void CCX(Qubit& q, int control_a_idx, int control_b_idx, int target_idx);
void Toffoli(Qubit& q, int idx);
void CR(Qubit& q, int idx_a, int idx_b, double phi);

} // namespace qubit::gates
