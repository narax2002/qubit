# qubit

A small C++17 quantum computing library for experimenting with qubit state vectors, common quantum gates, and a few introductory quantum algorithms.

The project builds a static library, several example programs, and a small test suite.

## Features

- `qubit::Qubit` state-vector container
- One-qubit and multi-qubit gate operations
- Quantum algorithms such as:
  - Grover
  - Bernstein-Vazirani
  - Shor
  - QFT
- Classical Fourier transform helpers on the state vector:
  - `FFT`
  - `IFFT`

## Dependencies

Required:

- CMake 3.16 or newer
- A C++17 compiler

Optional:

- `clang-format`
  - Used by `./lint.sh`

There are no external third-party runtime dependencies beyond the standard C++ library.

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

## Run

Examples:

```bash
./build/bin/bernstein_vazirani -n 5 -s 10
./build/bin/grover -n 5 -k 3
./build/bin/qft -n 3 -k 1
./build/bin/shor -n 7
```

Tests:

```bash
./build/bin/test_one_qubit_gates
./build/bin/test_multi_qubit_gates
./build/bin/test_algorithms
```

## Public Headers

- `include/qubit.hpp`
- `include/qubit_gates.hpp`
- `include/qubit_algorithms.hpp`

## Minimal Example

```cpp
#include "qubit.hpp"
#include "qubit_gates.hpp"

int main() {
    qubit::Qubit q(2);
    q.initial();

    qubit::gates::H(q, 0);
    qubit::gates::CX(q, 0, 1);

    q.printQnorm();
    return 0;
}
```

## Project Layout

- `include/`: public headers
- `src/`: library implementation
- `examples/`: small runnable examples
- `tests/`: lightweight test executables

## Formatting

```bash
./lint.sh
```
