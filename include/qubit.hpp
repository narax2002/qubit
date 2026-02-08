#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

constexpr double PI = 3.1415926535897932384646;

namespace qubit {

class Qubit {
private:
    int n_;
    std::vector<std::complex<double>> q_;

public:
    Qubit();
    explicit Qubit(int n);

    void initial();
    [[nodiscard]] int num_qubits() const;
    [[nodiscard]] int size() const;

    [[nodiscard]] std::vector<std::complex<double>>& state();
    [[nodiscard]] const std::vector<std::complex<double>>& state() const;

    friend std::ostream& operator<<(std::ostream& os, const Qubit& Q);
    [[nodiscard]] std::vector<double> Qnorm() const;
    void printQnorm() const;
};

} // namespace qubit
