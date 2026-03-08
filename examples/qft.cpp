#include "qubit/qubit.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using qubit::Qubit;
namespace algo = qubit::algorithms;
namespace gates = qubit::gates;

static std::string bits(int idx, int n) {
    std::string out;
    out.reserve(n);
    for (int i = n - 1; i >= 0; --i) {
        out.push_back(((idx >> i) & 1) ? '1' : '0');
    }
    return out;
}

static void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [-n NUM_QUBITS] [-k BASIS_INDEX]\n"
              << "  -n NUM_QUBITS   number of qubits (1..30)\n"
              << "  -k BASIS_INDEX  basis state index, 0 <= k < 2^n\n"
              << "Examples:\n"
              << "  " << prog << " -n 3 -k 1\n";
}

int main(int argc, char** argv) {
    int n = 3;
    int k = 1;

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

    if (n < 1 || n > 30) {
        std::cerr << "n must be in [1, 30]\n";
        return 1;
    }
    int max_k = (1 << n) - 1;
    if (k < 0 || k > max_k) {
        std::cerr << "k must be in [0, " << max_k << "] for n=" << n << "\n";
        return 1;
    }

    std::cout << "n=" << n << " k=" << k << "\n";

    Qubit q(n);
    q.initial();
    for (int i = 0; i < n; ++i) {
        if (k & (1 << i)) {
            gates::X(q, i);
        }
    }

    algo::QFT(q);

    std::cout << "QFT amplitudes:\n";
    const auto& s = q.state();
    for (int i = 0; i < q.size(); ++i) {
        if (std::norm(s[i]) > 1e-12) {
            std::cout << "  |" << bits(i, n) << "> = " << s[i] << "\n";
        }
    }

    return 0;
}
