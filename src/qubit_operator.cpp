#include "qubit.hpp"

#include <cstdlib>

/// <summary>
/// qubit operator
/// </summary>

Qubit::Qubit() {
    n_ = 1;
    size_ = 2;
    q_.assign(size_, std::complex<double>(0.0, 0.0));
    q_[0] = std::complex<double>(1.0, 0.0);
}

Qubit::Qubit(int nv) {
    if (nv <= 0) {
        PrintError(2);
    }
    n_ = nv;
    size_ = 1 << nv;
    q_.assign(size_, std::complex<double>(0.0, 0.0));
    q_[0] = std::complex<double>(1.0, 0.0);
}

void Qubit::Initial() {
    q_[0] = std::complex<double>(1.0, 0.0);
    for (int i = 1; i < size_; ++i) {
        q_[i] = std::complex<double>(0.0, 0.0);
    }
}

int Qubit::num_qubits() const {
    return n_;
}

int Qubit::size() const {
    return size_;
}

std::vector<std::complex<double>>& Qubit::state() {
    return q_;
}

const std::vector<std::complex<double>>& Qubit::state() const {
    return q_;
}

std::ostream& operator<<(std::ostream& os, const Qubit& Q) {
    // os << "(";
    os << Q.q_[0];
    for (int i = 1; i < Q.size_; ++i) {
        os << "," << Q.q_[i];
    }
    // os << ")";

    return os;
}

std::vector<double> Qubit::Qnorm() const {
    std::vector<double> result(size_);
    for (int i = 0; i < size_; ++i) {
        result[i] = std::norm(q_[i]);
    }

    return result;
}

void Qubit::PrintQnorm() const {
    std::vector<double> temp = this->Qnorm();
    std::cout << "(";
    for (int i = 0; i < size_ - 1; ++i) {
        std::cout << temp[i] << ", ";
    }
    std::cout << temp[size_ - 1] << ")" << std::endl;
}

void Qubit::PrintError(int n) const {
    switch (n) {
    case 1:
        std::cout << "Array index is out of bound" << std::endl;
        exit(1);
    case 2:
        std::cout << "The number of qubits is insufficient" << std::endl;
        exit(1);
    case 3:
        std::cout << "Can not implement this algorithm" << std::endl;
        exit(1);
    }
    std::cout << "Unknown error" << std::endl;
    exit(1);
}
