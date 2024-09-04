#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <thread>
#include <vector>

void calculate_partial_sum(long double z, int start, int end, long double& result) {
    long double partial_sum = 0.0;

    for (int n = start; n < end; ++n) {
        partial_sum += (1.0 / (2 * n + 1)) * std::pow(z, 2 * n + 1);
    }

    result = partial_sum * 2;  // Ajuste final según la fórmula
}

int main() {
    long double x;
    int num_threads;

    std::cout << "Ingrese el valor para calcular el logaritmo natural (debe ser > 1500000): ";
    std::cin >> x;
    std::cout << "Ingrese el número de hilos: ";
    std::cin >> num_threads;

    int num_terms = 10000000;
    long double z = (x - 1) / (x + 1);  // (x-1)/(x+1)
    std::vector<std::thread> threads;
    std::vector<long double> partial_sums(num_threads);

    clock_t start_time = clock();

    int terms_per_thread = num_terms / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = i * terms_per_thread;
        int end = (i == num_threads - 1) ? num_terms : (i + 1) * terms_per_thread;

        threads.push_back(std::thread(calculate_partial_sum, z, start, end, std::ref(partial_sums[i])));
    }

    for (auto& t : threads) {
        t.join();
    }

    long double log_approx = 0.0;
    for (const auto& sum : partial_sums) {
        log_approx += sum;
    }

    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Logaritmo natural aproximado: " << std::setprecision(15) << log_approx << std::endl;
    std::cout << "Tiempo de ejecución (segundos): " << elapsed_time << std::endl;

    return 0;
}
