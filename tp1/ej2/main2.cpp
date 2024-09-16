#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "32hilos.cpp"
#include "sin_hilos.cpp"
using namespace std;
using namespace std::chrono;

int main() {
    ifstream archivoTexto("texto.txt");

    string texto;
    archivoTexto >> texto;
    archivoTexto.close();

    ifstream archivoPatrones("patrones.txt");

    vector<string> patrones;
    string patron;

    // almacena en "patron" cada patron del archivo 
    while (getline(archivoPatrones, patron)) {
        patrones.push_back(patron);
    }
    archivoPatrones.close();
    
    // Medir tiempo de ejecución
    std::cout << "Calculando secuencial... " << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    secuencial(patrones,texto);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end - start;

    std::cout << "Calculando con 32 hilos... " << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    multihilos(patrones,texto);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;


    // Mostrar tiempo de ejecución
    std::cout << "Tiempo de ejecución con 32 hilos: " << duration2.count() << " segundos\n";
    std::cout << "Tiempo de ejecución sin hilos: " << duration1.count() << " segundos\n";

    double speed_up = ((double) duration2.count()) / duration1.count();
    std::cout << "Speed up: " << speed_up << std::endl;
    return 0;
}