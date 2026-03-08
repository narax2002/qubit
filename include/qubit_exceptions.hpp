#pragma once

#include <stdexcept>

namespace qubit {

enum class ErrorCode {
    IndexOutOfBounds = 1,
    InsufficientQubits = 2,
    InvalidAlgorithmParameter = 3,
    InvalidQubitCount = 4,
};

class QubitError : public std::runtime_error {
public:
    QubitError(ErrorCode code, const char* message) : std::runtime_error(message), code_(code) {}

    [[nodiscard]] ErrorCode code() const noexcept { return code_; }

private:
    ErrorCode code_;
};

[[nodiscard]] inline const char* errorMessage(ErrorCode code) noexcept {
    switch (code) {
    case ErrorCode::IndexOutOfBounds:
        return "Array index is out of bound";
    case ErrorCode::InsufficientQubits:
        return "Number of qubits is insufficient for this gate";
    case ErrorCode::InvalidAlgorithmParameter:
        return "Invalid parameter for the algorithm";
    case ErrorCode::InvalidQubitCount:
        return "Number of qubits must be positive";
    }

    return "Unknown error";
}

[[noreturn]] inline void throwError(ErrorCode code) {
    throw QubitError(code, errorMessage(code));
}

[[noreturn]] inline void throwInvalidQubitCount() {
    throwError(ErrorCode::InvalidQubitCount);
}

[[noreturn]] inline void printError(int nv) {
    switch (nv) {
    case 1:
        throwError(ErrorCode::IndexOutOfBounds);
    case 2:
        throwError(ErrorCode::InsufficientQubits);
    case 3:
        throwError(ErrorCode::InvalidAlgorithmParameter);
    default:
        throw QubitError(static_cast<ErrorCode>(nv), "Unknown error");
    }
}

} // namespace qubit
