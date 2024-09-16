#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*el metodo find de la clase std::string encuentra la primera aparición 
de una subcadena en otra cadena.*/
int contarPatron(const string& texto, const string& patron) {
    int count = 0;
    size_t pos = texto.find(patron);
    while (pos != string::npos) {
        count++; //cada vez que encuentra una cadena se incrementa
        pos = texto.find(patron, pos + 1);
    }
    return count;
}

void secuencial(vector<string> patrones, string texto) {
    for (const auto& p : patrones) {
        int count = contarPatron(texto, p);
        cout << "El patron \"" << p << "\" aparece " << count << " veces" << endl;
    }
}
