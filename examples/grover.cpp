#include "qubit.hpp"
#include "qubit_algorithms.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using qubit::Qubit;

static int measure_marked(const Qubit& q) {
    int dim = q.num_qubits() - 1; // last qubit is ancilla
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

static int max_iter(int dim) {
    return static_cast<int>(std::ceil(PI * std::pow(2.0, static_cast<double>(dim) / 2) / 4));
}

static void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [-n NUM_QUBITS] [-k MARKED]\n"
              << "  -n NUM_QUBITS   total qubits (>=2), last is ancilla\n"
              << "  -k MARKED       marked index, 0 <= k < 2^(n-1)\n"
              << "Examples:\n"
              << "  " << prog << " -n 5 -k 7\n";
}

int main(int argc, char** argv) {
    int n = 5; // total qubits, last is ancilla
    int k = 3; // marked element

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
        if ((arg == "-k") && (i + 1 < argc)) {
            k = std::stoi(argv[++i], nullptr, 0);
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
    int max_k = (1 << (n - 1)) - 1;
    if (k < 0 || k > max_k) {
        std::cerr << "k must be in [0, " << max_k << "] for n=" << n << "\n";
        return 1;
    }

    std::cout << "n=" << n << " k=" << k << "\n";

    Qubit q(n);
    qubit::algorithms::Grover(q, k);

    int measured = measure_marked(q);
    int iters = max_iter(n - 1);
    std::cout << "measured=" << measured << " expected=" << k << "\n";
    std::cout << "max_iter=" << iters << "\n";
    return 0;
}
