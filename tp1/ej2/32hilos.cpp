#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
//evitar escribir el prefijo std:: cada vez que se utiliza una función:
using namespace std;
using namespace std::chrono;

// se utiliza un hilo para cada patrón
void contarPatron(const string& texto, const string& patron, int& count) {
    count = 0;
    size_t pos = texto.find(patron);
    while (pos != string::npos) {
        count++;
        pos = texto.find(patron, pos + 1);
    }
}

void multihilos(vector<string> patrones, string texto) {
    vector<thread> hilos;
    vector<int> resultados(patrones.size(), 0);

    // crear un hilo para cada patrón
    for (size_t i = 0; i < patrones.size(); ++i) {
        hilos.push_back(thread(contarPatron, cref(texto), cref(patrones[i]), ref(resultados[i])));
        //hilos.push_back añade un nuevo hilo al vector hilos
    }

    /*hilo.join() espera a que el hilo termine su ejecución.
    este metodo se asegura de que todos los hilos terminen antes de que el programa siga.*/
    for (auto& hilo : hilos) {
        hilo.join();
    }

    for (size_t i = 0; i < patrones.size(); ++i) {
        cout << "El patron \"" << patrones[i] << "\" aparece " << resultados[i] << " veces" << endl;
    }
}
