#include "qubit.hpp"
#include "qubit_exceptions.hpp"

#include <cstdlib>

/// <summary>
/// qubit operator
/// </summary>

namespace qubit {

Qubit::Qubit() : n_(1) {
    q_.assign(2, std::complex<double>(0.0, 0.0));
    q_[0] = std::complex<double>(1.0, 0.0);
}

Qubit::Qubit(int nv) {
    if (nv <= 0) {
        printError(2);
    }
    n_ = nv;
    q_.assign(1 << nv, std::complex<double>(0.0, 0.0));
    q_[0] = std::complex<double>(1.0, 0.0);
}

void Qubit::initial() {
    q_[0] = std::complex<double>(1.0, 0.0);
    int len = static_cast<int>(q_.size());
    for (int i = 1; i < len; ++i) {
        q_[i] = std::complex<double>(0.0, 0.0);
    }
}

int Qubit::num_qubits() const {
    return n_;
}

int Qubit::size() const {
    return static_cast<int>(q_.size());
}

std::vector<std::complex<double>>& Qubit::state() {
    return q_;
}

const std::vector<std::complex<double>>& Qubit::state() const {
    return q_;
}

std::ostream& operator<<(std::ostream& os, const Qubit& Q) {
    os << Q.q_[0];
    int len = static_cast<int>(Q.q_.size());
    for (int i = 1; i < len; ++i) {
        os << "," << Q.q_[i];
    }

    return os;
}

std::vector<double> Qubit::Qnorm() const {
    int len = static_cast<int>(q_.size());
    std::vector<double> result(len);
    for (int i = 0; i < len; ++i) {
        result[i] = std::norm(q_[i]);
    }

    return result;
}

void Qubit::printQnorm() const {
    std::vector<double> temp = this->Qnorm();
    std::cout << "(";
    int len = static_cast<int>(temp.size());
    for (int i = 0; i < len - 1; ++i) {
        std::cout << temp[i] << ", ";
    }
    std::cout << temp[len - 1] << ")" << std::endl;
}

} // namespace qubit
