#include <iostream>
#include <iomanip>  // para std::setprecision
#include <cmath>    // para std::pow
#include <ctime>    // para medir el tiempo

int main() {
    long double x;

    // bucle que valida el numero ingresado
    do {
        std::cout << "Ingrese el valor para calcular el logaritmo natural (debe ser > 1500000): ";
        std::cin >> x;

        if (x <= 1500000) {
            std::cerr << "Error: El número ingresado debe ser mayor a 1500000." << std::endl;
        }
    } while (x <= 1500000);  

    int num_terms = 10000000;  // 10 millones de términos de la serie
    long double log_approx = 0.0;
    long double z = (x - 1) / (x + 1);  // (x-1)/(x+1)

    clock_t start_time = clock();

    // calculo de la serie de taylor
    for (int n = 0; n < num_terms; ++n) {
        log_approx += (1.0 / (2 * n + 1)) * std::pow(z, 2 * n + 1);
    }
    log_approx *= 2;  

    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC; // calculo el tiempo que se tardó

    std::cout << "Logaritmo natural aproximado: " << std::setprecision(15) << log_approx << std::endl;
    std::cout << "Tiempo de ejecución (en segundos): " << elapsed_time << std::endl;

    return 0;  // indica que el programa finalizó correctamente
}
