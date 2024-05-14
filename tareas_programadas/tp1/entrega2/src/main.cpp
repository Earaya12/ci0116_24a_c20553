#include "Ordenador.h"
using namespace std;
using namespace std::chrono;

void generarArregloAleatorio(int *arr, int n) {
	for (int j = 0; j < n; j++) {
    arr[j] = rand() % 100000000; // Números aleatorios entre 0 y 999
  }
}

// Main privado
int main() {
  Ordenador* ordenador = new class Ordenador();
  srand(time(nullptr)); // Semilla para la generación de números aleatorios
  // Aquí puedes probar tus algoritmos si lo deseas
  const int tamanios[] = {50000, 100000, 150000, 200000}; // Tamaños de los arreglos
  const int repeticiones = 5; // Número de repeticiones por tamaño de arreglo

  for (int tam : tamanios) {
    cout << "Tamaño del arreglo: " << tam << endl;
    // Variables para medir el tiempo
    double tiempoTotal = 0;
    // Ejecutar cada algoritmo al menos tres veces
    for (int i = 0; i < repeticiones; i++) {
      // Crear el arreglo
      int *arr = new int[tam];
      generarArregloAleatorio(arr, tam);
      // for (int i = 0; i < tam; ++i) {
      //   cout << arr[i] << " ";
      // }
      // cout << endl;
      // Medir el tiempo antes de ejecutar el algoritmo
      auto inicio = high_resolution_clock::now();
      // Ejecutar el algoritmo de selección
      ordenador->radixsort(arr, tam);
      // Medir el tiempo después de ejecutar el algoritmo
      auto fin = high_resolution_clock::now();
      // Calcular la duración en milisegundos
      double duracion = duration_cast<milliseconds>(fin - inicio).count();
      // for (int i = 0; i < tam; ++i) {
      //   cout << arr[i] << " ";
      // }
      // cout << endl;
      cout << "Tiempo duracion: " << duracion << endl;
      // Acumular el tiempo total
      tiempoTotal += duracion;
      // Liberar memoria del arreglo copiado
      delete[] arr;
    }
    // Calcular el tiempo promedio de ejecución
    double tiempoPromedio = tiempoTotal / repeticiones;
    cout << "Tiempo promedio de ejecución del algoritmo de quicksort: " << tiempoPromedio << " milisegundos" << endl;
    cout << endl;
  }

  delete ordenador;
  return 0;
}