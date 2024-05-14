// Copyright Ericka Araya 2024
#ifndef Ordenador_h
#define Ordenador_h


#include <iostream>
#include <chrono>
#include <cmath> // Para las funciones de matemáticas
#include <cstdlib>  // Para la generación de números aleatorios
#include <ctime>   // Para la semilla de generación de números aleatorios
#include <string>
#include <utility>
#include <vector>



using namespace std;
using namespace std::chrono;
class Ordenador {
private:
  // Funciones privadas de mergeSort
	// Defina aqui los metodos auxiliares de
  // los algoritmos de ordenamiento solamente.
  // Puede definir cuantos metodos quiera.
  void merge(int *A, int left, int mid, int right);
  void mergeSortHelper(int *A, int left, int right);

  // Funciones privadas de heapsort
  void heapify(int *arr, int n, int i);

  // Funciones privadas de quicksort
  int partition(int *arr, int low, int high);
  void quicksortHelper(int *arr, int low, int high);

  // Funciones privadas de radixsort
  // Ordenamiento por conteo
  void counting_sort(int* A, int digit, int base, int n);

public:
	Ordenador(){};
	~Ordenador(){};
	// Si piensa no implementar algunos de los metodos
  // de ordenamiento, no los borre, simplemente dejelos con el cuerpo vacio
  // para evitar errores de compilacion, ya
	// que se va a ej<utility> for swapecutar el mismo main para todas las tareas.
  // Implemente los algoritmos en este archivo  (no en un CPP aparte).
	void seleccion(int *A, int n);
	void insercion(int *A, int n);
	void mergesort(int *A, int n);
	void heapsort(int *A, int n);
	void quicksort(int *A, int n);
	void radixsort(int *A, int n);
  string ImprimirDatosDeTarea() {
    return "c20553 Tarea 1 Etapa 2";
  }
};

// Implementación de los métodos de ordenamiento fuera de la clase

void Ordenador::heapify(int *arr, int n, int i) {
    int largest = i; // Inicializa el nodo raíz como el más grande
    int left = 2 * i + 1; // índice del hijo izquierdo
    int right = 2 * i + 2; // índice del hijo derecho

    // Si el hijo izquierdo es más grande que el nodo raíz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es más grande que el nodo raíz o el hijo izquierdo
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el nodo raíz no es el más grande, lo cambia con el más grande
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Vuelve a comprobar la condición de heapify en el subárbol afectado
        heapify(arr, n, largest);
    }
}

void Ordenador::heapsort(int *arr, int n) {
    // Construye un max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrae elementos uno por uno del heap
    for (int i = n - 1; i > 0; i--) {
        // Mueve la raíz actual (el mayor elemento) al final
        swap(arr[0], arr[i]);

        // Llama a max heapify en el montículo reducido
        heapify(arr, i, 0);
    }
}

int Ordenador::partition(int *arr, int low, int high) {
    int pivot = arr[high]; // Selecciona el pivote
    int i = (low - 1); // índice del menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++; // Incrementa el índice del menor elemento
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void Ordenador::quicksortHelper(int *arr, int low, int high) {
    if (low < high) {
        // Partición de índice pi
        int pi = partition(arr, low, high);

        // Ordena los elementos antes y después de la partición
        quicksortHelper(arr, low, pi - 1);
        quicksortHelper(arr, pi + 1, high);
    }
}

void Ordenador::quicksort(int *arr, int n) {
    quicksortHelper(arr, 0, n - 1);
}

void Ordenador::counting_sort(int* A, int digit, int base, int n) {
    int* B = new int[n](); // Array auxiliar para almacenar los resultados intermedios
    int* C = new int[base](); // Array para contar la frecuencia de cada dígito
    for (int i = 0; i < base; i++){
      C[i] = 0;
    }
    // Contar el número de ocurrencias de cada dígito en A
    for (int i = 0; i < n; i++) {
        C[(A[i] / digit) % base]++;
    }
    // Modificar C para tener el número acumulado de dígitos hasta ese índice de C
    for (int j = 1; j < base; j++) {
        C[j] += C[j - 1];
    }
    // Construir la lista ordenada B
    for (int i = n - 1; i >= 0; i--) {
        B[C[(A[i] / digit) % base] - 1] = A[i];
        C[(A[i] / digit) % base]--;
    }
    // Copiar los elementos ordenados de B a A
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
    delete[] B; // Liberar memoria del array auxiliar B
    delete[] C; // Liberar memoria del array auxiliar C
}

void Ordenador::radixsort(int *A, int n) {
    // Encontrar el número más grande en la lista
    int max_num = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max_num) {
            max_num = A[i];
        }
    }
    long long base = pow(2,log2(n)); // Base es 2^log(n)
    // Ordenar por cada dígito, de menos significativo a más significativo
    for (int i = 1; max_num / i > 0; i *= base) {
        counting_sort(A, i, base, n); 
    }
}

// Implementación del algoritmo de selección
void Ordenador::seleccion(int *A, int n) {
  // Itera sobre todo el array
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i; // Supone que el elemento actual es el mínimo
    // Busca el mínimo en el resto del array
    for (int j = i + 1; j < n; j++) {
      if (A[j] < A[minIndex]) { // Si encuentra un elemento menor
          minIndex = j; // Actualiza el índice del mínimo
      }
    }
    // Intercambia el elemento actual con el mínimo encontrado
    if (minIndex != i) {
      swap(A[i], A[minIndex]);
    }
  }
}

// Implementación del algoritmo de inserción
void Ordenador::insercion(int *A, int n) {
  // Itera sobre el array, empezando desde el segundo elemento
  for (int i = 1; i < n; i++) {
    int key = A[i]; // Guarda el valor del elemento actual
    int j = i - 1; // Inicializa el índice del elemento anterior

    // Mueve los elementos mayores que key una posición adelante
    // para hacer espacio para key
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      j = j - 1;
    }
    A[j + 1] = key; // Inserta key en su posición correcta
  }
}

// Implementación de la función merge para el algoritmo merge sort
void Ordenador::merge(int *A, int left, int mid, int right) {
  int n1 = mid - left + 1; // Tamaño del subarray izquierdo
  int n2 = right - mid; // Tamaño del subarray derecho

  int L[n1], R[n2]; // Arrays temporales para almacenar los subarrays

  // Copia los elementos a los subarrays temporales
  for (int i = 0; i < n1; i++)
    L[i] = A[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = A[mid + 1 + j];

  int i = 0;
  int j = 0;
  int k = left;

  // Combina los subarrays en uno solo en el array original
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
    k++;
  }

  // Copia los elementos restantes de L[] si hay alguno
  while (i < n1) {
    A[k] = L[i];
    i++;
    k++;
  }

  // Copia los elementos restantes de R[] si hay alguno
  while (j < n2) {
    A[k] = R[j];
    j++;
    k++;
  }
}

// Implementación de la función auxiliar para el algoritmo merge sort
void Ordenador::mergeSortHelper(int *A, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2; // Calcula el punto medio

    // Llama recursivamente a mergeSortHelper para ordenar los subarrays izquierdo y derecho
    mergeSortHelper(A, left, mid);
    mergeSortHelper(A, mid + 1, right);

    // Combina los subarrays ordenados
    merge(A, left, mid, right);
  }
}

// Implementación del algoritmo merge sort
void Ordenador::mergesort(int *A, int n) {
    mergeSortHelper(A, 0, n - 1); // Llama a la función auxiliar para iniciar el ordenamiento
}

#endif
