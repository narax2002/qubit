#include <cstdlib>
#include <iostream>

namespace qubit {

inline void printError(int nv) {
    switch (nv) {
    case 1:
        std::cout << "Array index is out of bound" << std::endl;
        break;
    case 2:
        std::cout << "Number of qubits is insufficient for this gate" << std::endl;
        break;
    case 3:
        std::cout << "Invalid parameter for the algorithm" << std::endl;
        break;
    default:
        std::cout << "Unknown error" << std::endl;
        break;
    }
}

} // namespace qubit
