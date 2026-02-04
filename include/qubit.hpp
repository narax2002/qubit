#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

constexpr double pi = 4.0 * std::atan(1.0);

class Qubit {
private:
    int n_;
    std::vector<std::complex<double>> q_;

public:
    Qubit();
    explicit Qubit(int n);

    void Initial();
    [[nodiscard]] int num_qubits() const;
    [[nodiscard]] int size() const;

    [[nodiscard]] std::vector<std::complex<double>>& state();
    [[nodiscard]] const std::vector<std::complex<double>>& state() const;

    friend std::ostream& operator<<(std::ostream& os, const Qubit& Q);
    [[nodiscard]] std::vector<double> Qnorm() const;
    void PrintQnorm() const;
    [[noreturn]] void PrintError(int nv) const;
};
