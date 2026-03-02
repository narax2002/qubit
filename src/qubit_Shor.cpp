#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

namespace qubit::algorithms {

void Shor(Qubit& q) {
    gates::H(q, 0);
    gates::H(q, 1);
    gates::H(q, 2);

    gates::CX(q, 2, 4);
    gates::CX(q, 2, 5);
    gates::CX(q, 3, 5);
    gates::CCX(q, 1, 5, 3);
    gates::CX(q, 3, 5);
    gates::CX(q, 6, 4);
    gates::CCX(q, 1, 4, 6);
    gates::CX(q, 6, 4);

    gates::H(q, 0);
    gates::CR(q, 0, -PI / 2, 1);
    gates::H(q, 1);
    gates::CR(q, 0, -PI / 4, 2);
    gates::CR(q, 1, -PI / 2, 2);
    gates::H(q, 2);
}

} // namespace qubit::algorithms
