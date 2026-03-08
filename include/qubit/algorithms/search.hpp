#pragma once

#include "qubit/register.hpp"

namespace qubit::algorithms {

/// \brief Runs Grover search using the last qubit as an ancilla.
/// \param q Register to modify.
/// \param k Marked data-register basis index.
void Grover(Qubit& q, int k);
/// \brief Runs Bernstein-Vazirani using the last qubit as an ancilla.
/// \param q Register to modify.
/// \param s Hidden bit-string value encoded as an integer.
void Bernstein_Vazirani(Qubit& q, int s);

} // namespace qubit::algorithms
