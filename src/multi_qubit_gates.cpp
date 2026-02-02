#include "qubit_gates.hpp"

#include <cmath>

// Multi-qubit gate definitions.

namespace qubit {
namespace gates {

void SWAP(Qubit& q, int idx_a, int idx_b)
{
	if (q.num_qubits() < 2) q.PrintError(2);
	if (idx_a >= q.num_qubits() || idx_b >= q.num_qubits()) q.PrintError(1);

	int len = q.size();
	int ref_a = 1 << idx_a;
	int ref_b = 1 << idx_b;
	auto& state = q.state();
	for (int i = 0; i < len; ++i) {
		if ((i & ref_a) && ((i & ref_b) == 0)) {
			int j = i ^ (ref_a + ref_b);
			std::complex<double> temp = state[i];
			state[i] = state[j];
			state[j] = temp;
		}
	}
}

void CX(Qubit& q, int idx_a, int idx_b)
{
	if (q.num_qubits() < 2) q.PrintError(2);
	if (idx_a >= q.num_qubits() || idx_b >= q.num_qubits()) q.PrintError(1);

	int len = q.size();
	int ref_a = 1 << idx_a;
	int ref_b = 1 << idx_b;
	auto& state = q.state();
	for (int i = 0; i < len; ++i) {
		if (((i & ref_a) == 0) && (i & ref_b)) {
			int j = i | ref_a;
			std::complex<double> temp = state[i];
			state[i] = state[j];
			state[j] = temp;
		}
	}
}

void CZ(Qubit& q, int idx_a, int idx_b)
{
	if (q.num_qubits() < 2) q.PrintError(2);
	if (idx_a >= q.num_qubits() || idx_b >= q.num_qubits()) q.PrintError(1);

	int len = q.size();
	int ref_a = 1 << idx_a;
	int ref_b = 1 << idx_b;
	std::complex<double> c(0.0, 1.0);
	auto& state = q.state();
	for (int i = 0; i < len; ++i) {
		if (((i & ref_a) == 0) && (i & ref_b)) {
			int j = i | ref_a;
			std::complex<double> temp = state[i];
			state[i] = c * state[j];
			state[j] = -c * temp;
		}
	}
}

void CCX(Qubit& q, int idx_a, int idx_b, int idx_c)
{
	if (q.num_qubits() < 3) q.PrintError(2);
	if (idx_a >= q.num_qubits() || idx_b >= q.num_qubits() || idx_c >= q.num_qubits()) q.PrintError(1);

	int len = q.size();
	int ref_a = 1 << idx_a;
	int ref_b = 1 << idx_b;
	int ref_c = 1 << idx_c;
	auto& state = q.state();
	for (int i = 0; i < len; ++i) {
		if (((i & ref_a) == 0) && (i & ref_b) && (i & ref_c)) {
			int j = i | ref_a;
			std::complex<double> temp = state[i];
			state[i] = state[j];
			state[j] = temp;
		}
	}
}

void Toffoli(Qubit& q, int idx)
{
	if (q.num_qubits() < 2) q.PrintError(2);
	int len = q.size();
	int ref = 1 << idx;

	auto& state = q.state();
	int i = len - 1;
	int j = i ^ ref;
	std::complex<double> temp = state[i];
	state[i] = state[j];
	state[j] = temp;
}

void CR(Qubit& q, int idx_a, int idx_b, double phi)
{
	if (q.num_qubits() < 2) q.PrintError(2);
	int len = q.size();
	int ref_a = 1 << idx_a;
	int ref_b = 1 << idx_b;
	std::complex<double> c = std::polar(1.0, phi);
	auto& state = q.state();
	for (int i = 0; i < len; ++i) {
		if ((i & ref_a) && (i & ref_b)) {
			state[i] *= c;
		}
	}
}

}  // namespace gates
}  // namespace qubit
