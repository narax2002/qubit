#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"

#include <iostream>

namespace qubit {
namespace algorithms {

void Shor(Qubit& q) {
    gates::H(q, 0);
    gates::H(q, 1);
    gates::H(q, 2);

    gates::CX(q, 4, 2);
    gates::CX(q, 5, 2);
    gates::CX(q, 5, 3);
    gates::CCX(q, 3, 1, 5);
    gates::CX(q, 5, 3);
    gates::CX(q, 4, 6);
    gates::CCX(q, 6, 1, 4);
    gates::CX(q, 4, 6);

    gates::H(q, 0);
    gates::CR(q, 0, 1, -pi / 2);
    gates::H(q, 1);
    gates::CR(q, 0, 2, -pi / 4);
    gates::CR(q, 1, 2, -pi / 2);
    gates::H(q, 2);

    std::vector<double> a_temp = q.Qnorm();
    double temp = 0;
    for (int j = 0; j < 16; ++j)
        temp += a_temp[8 * j];
    std::cout << "(" << temp;
    for (int i = 1; i < 8; ++i) {
        temp = 0;
        for (int j = 0; j < 16; ++j)
            temp += a_temp[8 * j + i];
        std::cout << ", " << temp;
    }
    std::cout << ")" << std::endl;

    std::cout << q << std::endl;
}

} // namespace algorithms
} // namespace qubit
