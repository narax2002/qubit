#pragma once

#include <stdexcept>

namespace qubit {

/// \brief Error categories used by the public API.
enum class ErrorCode {
    IndexOutOfBounds = 1,
    InsufficientQubits = 2,
    InvalidAlgorithmParameter = 3,
    InvalidQubitCount = 4,
};

/// \brief Exception type thrown by qubit validation helpers.
class QubitError : public std::runtime_error {
public:
    /// \brief Constructs an exception with a specific error category and message.
    /// \param code Machine-readable error category.
    /// \param message Human-readable error message.
    QubitError(ErrorCode code, const char* message) : std::runtime_error(message), code_(code) {}

    /// \brief Returns the machine-readable error category.
    [[nodiscard]] ErrorCode code() const noexcept { return code_; }

private:
    ErrorCode code_;
};

/// \brief Returns a human-readable message for an error code.
/// \param code Error category to stringify.
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

/// \brief Throws QubitError for the given error category.
/// \param code Error category to throw.
[[noreturn]] inline void throwError(ErrorCode code) {
    throw QubitError(code, errorMessage(code));
}

/// \brief Throws the invalid-qubit-count exception.
[[noreturn]] inline void throwInvalidQubitCount() {
    throwError(ErrorCode::InvalidQubitCount);
}

/// \brief Throws QubitError from a legacy numeric error code.
/// \param nv Legacy numeric error code.
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
