#include "qubit.hpp"
#include "qubit_algorithms.hpp"
#include "qubit_gates.hpp"
#include <chrono>
#include <omp.h>
#include <string>

/// <summary>
/// Personal study  (Qubit algorithm implementation personal Study)
/// Reference
/// "Quantum algorithm implementations for beginners", 10 Apr 2018
/// </summary>

using namespace std;

class Timer {
public:
    static void start() { getInstance()->start_time = chrono::high_resolution_clock::now(); }

    static void stop() { getInstance()->end_time = chrono::high_resolution_clock::now(); }

    static void printTime(const string& msg, int repeat) {
        cout << "* " << msg << " time = " << elapsedMilliseconds() / repeat << " ms" << endl;
    }

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;
    ~Timer() = default;

private:
    static Timer* getInstance() {
        static Timer instance;
        return &instance;
    }

    Timer() = default;

    static double elapsedMilliseconds() {
        return (double)chrono::duration_cast<chrono::milliseconds>(getInstance()->end_time -
                                                                   getInstance()->start_time)
            .count();
    }

    chrono::high_resolution_clock::time_point start_time;
    chrono::high_resolution_clock::time_point end_time;
};

using namespace qubit;

int main() {
    std::cout << "There are " << omp_get_max_threads() << " max threads" << std::endl;
    std::cout << "There are " << omp_get_num_threads() << " threads currently" << std::endl;

#pragma omp parallel
    {
        if (omp_in_parallel()) {
            std::string message =
                "In parallel: thread number = " + std::to_string(omp_get_thread_num()) + " / " +
                std::to_string(omp_get_num_threads()) + "\n";
            std::cout << message;
        } else {
            std::string message =
                "Not in parallel: thread number = " + std::to_string(omp_get_thread_num()) + " / " +
                std::to_string(omp_get_num_threads()) + "\n";
            std::cout << message;
        }
    }

    std::cout << fixed;
    std::cout.precision(4);

    int N = 18;

    Timer::start();
    Qubit q1(N);
    Qubit q2(N);
    Timer::stop();
    Timer::printTime("Generate qubit", 2);

    Timer::start();
    q1.initial();
    q2.initial();
    Timer::stop();
    Timer::printTime("Initialize qubit", 2);

    Timer::start();
    gates::H(q1, 0);
    gates::H(q2, 0);
    Timer::stop();
    Timer::printTime("H gate", 2);

    Timer::start();
    gates::X(q1, 1);
    gates::X(q2, 1);
    Timer::stop();
    Timer::printTime("X gate", 2);

    Timer::start();
    algorithms::FFT(q1);
    algorithms::FFT(q2);
    Timer::stop();
    Timer::printTime("FFT", 2);

    Timer::start();
    algorithms::IFFT(q1);
    algorithms::IFFT(q2);
    Timer::stop();
    Timer::printTime("IFFT", 2);

    Timer::start();
    algorithms::QFT(q1);
    algorithms::QFT(q2);
    Timer::stop();
    Timer::printTime("QFT", 2);

    Timer::start();
    algorithms::IFFT(q1);
    algorithms::IFFT(q2);
    Timer::stop();
    Timer::printTime("IFFT", 2);

    // Timer::start();
    // algorithms::Shor(q1);
    // Timer::stop();
    // Timer::printTime("Shor", 1);

    return 0;
}
