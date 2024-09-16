#include <iostream>
#include <vector>
#include <pthread.h>
#include <sys/time.h>

using namespace std;

// Estructura para pasar parámetros a los hilos
struct ThreadData {
    int thread_id;
    int N;
    int num_threads;
    const vector<vector<float>>* A;
    const vector<vector<float>>* B;
    vector<vector<float>>* C;
};

// Función para imprimir las esquinas de una matriz NxN
void printCorners(const vector<vector<float>>& matrix, int N) {
    cout << "Esquinas de la matriz:\n";
    cout << matrix[0][0] << " ... " << matrix[0][N-1] << endl;
    cout << "...        ...\n";
    cout << matrix[N-1][0] << " ... " << matrix[N-1][N-1] << endl;
}

// Multiplicación de matrices sin multihilos
vector<vector<float>> multiplyMatrices(const vector<vector<float>>& A, const vector<vector<float>>& B, int N) {
    vector<vector<float>> result(N, vector<float>(N, 0.0f));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Función que ejecutará cada hilo para realizar parte de la multiplicación de matrices
void* threadMultiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int N = data->N;
    int thread_id = data->thread_id;
    int num_threads = data->num_threads;
    const vector<vector<float>>* A = data->A;
    const vector<vector<float>>* B = data->B;
    vector<vector<float>>* C = data->C;

    int start_row = (thread_id * N) / num_threads;
    int end_row = ((thread_id + 1) * N) / num_threads;

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                (*C)[i][j] += (*A)[i][k] * (*B)[k][j];
            }
        }
    }
    pthread_exit(nullptr);
}

// Multiplicación de matrices con multihilos
vector<vector<float>> multiplyMatricesMultithreaded(const vector<vector<float>>& A, const vector<vector<float>>& B, int N, int num_threads) {
    vector<vector<float>> C(N, vector<float>(N, 0.0f));
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    // Crear hilos
    for (int i = 0; i < num_threads; ++i) {
        thread_data[i] = {i, N, num_threads, &A, &B, &C};
        pthread_create(&threads[i], nullptr, threadMultiply, &thread_data[i]);
    }

    // Esperar que todos los hilos terminen
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    return C;
}

// Sumatoria de todos los elementos de la matriz
float sumMatrix(const vector<vector<float>>& matrix, int N) {
    float sum = 0.0f;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

int main() {
    int N, num_threads;
    cout << "Ingrese el tamaño de las matrices NxN: ";
    cin >> N;
    cout << "Ingrese el número de hilos: ";
    cin >> num_threads;

    // Inicializar matrices con valores ejemplo
    vector<vector<float>> A(N, vector<float>(N, 0.1f));
    vector<vector<float>> B(N, vector<float>(N, 0.2f));

    // Imprimir esquinas de las matrices iniciales
    cout << "Matriz A:\n";
    printCorners(A, N);

    cout << "\nMatriz B:\n";
    printCorners(B, N);

    
    // --- Multiplicación con multihilos ---
    struct timeval time1, time2;
    gettimeofday(&time1, NULL);
    vector<vector<float>> C_threads = multiplyMatricesMultithreaded(A, B, N, num_threads);
    gettimeofday(&time2, NULL);
    double time_taken_threads = (time2.tv_sec - time1.tv_sec) + (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "\nTiempo de ejecución con multihilos: " << time_taken_threads << " segundos" << endl;

    // Imprimir esquinas de la matriz resultante
    cout << "\nMatriz resultante C con multihilos:\n";
    printCorners(C_threads, N);

    // Sumatoria de los elementos de la matriz resultante
    float sum_threads = sumMatrix(C_threads, N);
    cout << "\nSumatoria de todos los elementos de la matriz resultante con multihilos: " << sum_threads << endl;


    // --- Multiplicación sin multihilos ---
    gettimeofday(&time1, NULL);
    vector<vector<float>> C_no_threads = multiplyMatrices(A, B, N);
    gettimeofday(&time2, NULL);
    double time_taken_no_threads = (time2.tv_sec - time1.tv_sec) + (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "\nTiempo de ejecución sin multihilos: " << time_taken_no_threads << " segundos" << endl;

    // Imprimir esquinas de la matriz resultante
    cout << "\nMatriz resultante C sin multihilos:\n";
    printCorners(C_no_threads, N);

    // Sumatoria de los elementos de la matriz resultante
    float sum_no_threads = sumMatrix(C_no_threads, N);
    cout << "\nSumatoria de todos los elementos de la matriz resultante sin multihilos: " << sum_no_threads << endl;

    // Calcular el speedup
    double speedup = time_taken_no_threads / time_taken_threads;
    cout << "\nSpeedup: " << speedup << endl;

    return 0;
}
