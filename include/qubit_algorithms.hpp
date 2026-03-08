#pragma once

#include "qubit.hpp"

namespace qubit::algorithms {

void Grover(Qubit& q, int k);
void Bernstein_Vazirani(Qubit& q, int s);
void Shor(Qubit& q);

void QFT(Qubit& q);

// Classical Fourier transform helpers operating on the state vector.
void FFT(Qubit& q);
void IFFT(Qubit& q);

} // namespace qubit::algorithms
