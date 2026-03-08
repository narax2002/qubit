#include "qubit.hpp"
#include "qubit_algorithms.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

using qubit::Qubit;
namespace algo = qubit::algorithms;

static int measure_hidden_string(const Qubit& q) {
    int dim = q.num_qubits() - 1;
    int len = 1 << dim;
    std::vector<double> a_temp = q.Qnorm();
    int max_idx = 0;
    for (int i = 1; i < len; ++i) {
        if (a_temp[i] + a_temp[i + len] > a_temp[max_idx] + a_temp[max_idx + len]) {
            max_idx = i;
        }
    }
    return max_idx;
}

static void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [-n NUM_QUBITS] [-s SECRET]\n"
              << "  -n NUM_QUBITS   total qubits (>=2), last is ancilla\n"
              << "  -s SECRET       hidden string, 0 <= s < 2^(n-1)\n"
              << "Examples:\n"
              << "  " << prog << " -n 5 -s 0b1010\n"
              << "  " << prog << " -n 6 -s 21\n";
}

int main(int argc, char** argv) {
    int n = 5;      // total qubits, last is ancilla
    int s = 0b1010; // hidden string (must be < 2^(n-1))

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
        if ((arg == "-s") && (i + 1 < argc)) {
            s = std::stoi(argv[++i], nullptr, 0);
            continue;
        }
        std::cerr << "Unknown or incomplete option: " << arg << "\n";
        print_usage(argv[0]);
        return 1;
    }

    if (n < 2) {
        std::cerr << "n must be >= 2\n";
        return 1;
    }
    int max_s = (1 << (n - 1)) - 1;
    if (s < 0 || s > max_s) {
        std::cerr << "s must be in [0, " << max_s << "] for n=" << n << "\n";
        return 1;
    }

    std::cout << "n=" << n << " s=" << s << "\n";

    Qubit q(n);
    algo::Bernstein_Vazirani(q, s);

    int measured = measure_hidden_string(q);
    std::cout << "measured=" << measured << " expected=" << s << "\n";
    return 0;
}
