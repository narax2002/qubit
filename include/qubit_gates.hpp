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
void CX(Qubit& q, int idx_a, int idx_b);
void CZ(Qubit& q, int idx_a, int idx_b);
void CCX(Qubit& q, int idx_a, int idx_b, int idx_c);
void Toffoli(Qubit& q, int idx);
void CR(Qubit& q, int idx_a, int idx_b, double phi);

} // namespace qubit::gates
