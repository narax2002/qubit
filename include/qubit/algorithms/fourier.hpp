#pragma once

#include "qubit/register.hpp"

namespace qubit::algorithms {

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
