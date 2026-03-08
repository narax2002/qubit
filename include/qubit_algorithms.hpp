#pragma once

#include "qubit.hpp"

namespace qubit::algorithms {

/// \brief Runs Grover search using the last qubit as an ancilla.
/// \param q Register to modify.
/// \param k Marked data-register basis index.
void Grover(Qubit& q, int k);
/// \brief Runs Bernstein-Vazirani using the last qubit as an ancilla.
/// \param q Register to modify.
/// \param s Hidden bit-string value encoded as an integer.
void Bernstein_Vazirani(Qubit& q, int s);
/// \brief Runs the built-in Shor demonstration circuit.
/// \param q Register to modify.
void Shor(Qubit& q);

/// \brief Applies the quantum Fourier transform to the full register.
/// \param q Register to transform.
void QFT(Qubit& q);

/// \brief Applies a classical discrete Fourier transform to the state vector.
/// \param q Register whose amplitudes are transformed in place.
void FFT(Qubit& q);
/// \brief Applies the inverse classical discrete Fourier transform to the state vector.
/// \param q Register whose amplitudes are transformed in place.
void IFFT(Qubit& q);

} // namespace qubit::algorithms
