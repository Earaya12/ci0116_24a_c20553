// Copyright Ericka Araya 2024
#ifndef Ordenador_h
#define Ordenador_h


#include <iostream>
#include <chrono>
#include <cstdlib>  // Para la generación de números aleatorios
#include <ctime>   // Para la semilla de generación de números aleatorios
#include <string>
#include <utility>

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
    return "c20553 Tarea 1 Etapa 1";
  }
};

// Implementación de los métodos de ordenamiento fuera de la clase

void Ordenador::seleccion(int *A, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (A[j] < A[minIndex]) {
          minIndex = j;
      }
    }
    if (minIndex != i) {
      swap(A[i], A[minIndex]);
    }
  }
}

void Ordenador::insercion(int *A, int n) {
  for (int i = 1; i < n; i++) {
    int key = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      j = j - 1;
    }
    A[j + 1] = key;
  }
}

void Ordenador::merge(int *A, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = A[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = A[mid + 1 + j];

  int i = 0;
  int j = 0;
  int k = left;
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

  while (i < n1) {
    A[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    A[k] = R[j];
    j++;
    k++;
  }
}

void Ordenador::mergeSortHelper(int *A, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSortHelper(A, left, mid);
    mergeSortHelper(A, mid + 1, right);

    merge(A, left, mid, right);
  }
}

void Ordenador::mergesort(int *A, int n) {
    mergeSortHelper(A, 0, n - 1);
}
#endif
