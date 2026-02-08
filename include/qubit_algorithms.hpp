#pragma once

#include "qubit.hpp"

namespace qubit::algorithms {

void Grover(Qubit& q, int k);
void Bernstein_Vazirani(Qubit& q, int s);
void Shor(Qubit& q);

void QFT(Qubit& q);
void FFT(Qubit& q);
void IFFT(Qubit& q);
void FFT_iter(Qubit& q);
void Multi(Qubit& out, const Qubit& a, const Qubit& b);

} // namespace qubit::algorithms
