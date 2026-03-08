#include "qubit/qubit.hpp"

#include <iostream>
#include <string>

using qubit::Qubit;
namespace algo = qubit::algorithms;

static void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [-n NUM_QUBITS]\n"
              << "  -n NUM_QUBITS   number of qubits (>=7)\n"
              << "Example:\n"
              << "  " << prog << " -n 7\n";
}

static void print_shor_summary(const Qubit& q) {
    std::vector<double> a_temp = q.Qnorm();
    double temp = 0;
    std::cout << "summary=(";
    for (int i = 0; i < 8; ++i) {
        temp = 0;
        for (int j = 0; j < 16; ++j) {
            temp += a_temp[8 * j + i];
        }
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << temp;
    }
    std::cout << ")\n";
}

int main(int argc, char** argv) {
    int n = 7;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            print_usage(argv[0]);
            return 0;
        }
        if ((arg == "-n") && (i + 1 < argc)) {
            n = std::stoi(argv[++i]);
            continue;
        }
        std::cerr << "Unknown or incomplete option: " << arg << "\n";
        print_usage(argv[0]);
        return 1;
    }

    if (n < 7) {
        std::cerr << "n must be >= 7\n";
        return 1;
    }

    std::cout << "n=" << n << "\n";

    Qubit q(n);
    algo::Shor(q);

    print_shor_summary(q);
    std::cout << q << "\n";

    return 0;
}
