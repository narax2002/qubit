#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

/// \brief Shared angle constant used by gate and transform implementations.
constexpr double PI = 3.1415926535897932384646;

namespace qubit {

/// \brief State-vector representation of an n-qubit register.
class Qubit {
private:
    int n_;
    std::vector<std::complex<double>> q_;

public:
    /// \brief Constructs a single-qubit register initialized to |0>.
    Qubit();
    /// \brief Constructs an n-qubit register initialized to |0...0>.
    /// \param n Number of logical qubits in the register. Must be positive.
    explicit Qubit(int n);

    /// \brief Resets the register to the all-zero basis state.
    void initial();
    /// \brief Returns the number of logical qubits in the register.
    [[nodiscard]] int num_qubits() const;
    /// \brief Returns the size of the state vector, equal to 2^n.
    [[nodiscard]] int size() const;

    /// \brief Provides direct access to amplitudes in computational-basis order.
    [[nodiscard]] std::vector<std::complex<double>>& state();
    /// \brief Provides read-only access to amplitudes in computational-basis order.
    [[nodiscard]] const std::vector<std::complex<double>>& state() const;

    /// \brief Streams the amplitudes of Q to os.
    /// \param os Output stream that receives the formatted amplitudes.
    /// \param Q Register whose amplitudes are printed.
    friend std::ostream& operator<<(std::ostream& os, const Qubit& Q);
    /// \brief Returns the per-basis-state probabilities.
    [[nodiscard]] std::vector<double> Qnorm() const;
    /// \brief Prints Qnorm() as a tuple.
    void printQnorm() const;
};

} // namespace qubit
