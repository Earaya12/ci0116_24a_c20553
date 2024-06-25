#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "llist.h"
#include "rbtree.h"
#include "chasht.h"

using namespace std;
using namespace chrono;

int main() {
    const int n = 1000000;
    const int e = 10000;
    const int range = 2 * n;

    // Variables para registrar los tiempos
    double time_insert_random[3] = {0};
    double time_search_random[3] = {0};
    double time_insert_ordered[3] = {0};
    double time_search_ordered[3] = {0};

    // Repetir el experimento tres veces
    for (int run = 0; run < 3; run++) {
        // Inserción Aleatoria
        chtable<int> random_table(n);  // Crear una tabla hash con tamaño n
        srand(time(0));

        // Medir el tiempo de inserción aleatoria
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            int key = rand() % range;
            random_table.Insert(key);
        }
        auto end = high_resolution_clock::now();
        time_insert_random[run] = duration_cast<milliseconds>(end - start).count();

        // Medir el tiempo de búsqueda aleatoria
        start = high_resolution_clock::now();
        for (int i = 0; i < e; i++) {
            int key = rand() % range;
            random_table.Search(key);
        }
        end = high_resolution_clock::now();
        time_search_random[run] = duration_cast<milliseconds>(end - start).count();


        // Inserción Ordenada
        chtable<int> ordered_table(n);  // Crear una tabla hash con tamaño n

        // Medir el tiempo de inserción ordenada
        start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            ordered_table.Insert(i);
        }
        end = high_resolution_clock::now();
        time_insert_ordered[run] = duration_cast<milliseconds>(end - start).count();

        // Medir el tiempo de búsqueda ordenada
        start = high_resolution_clock::now();
        for (int i = 0; i < e; i++) {
            int key = rand() % range;
            ordered_table.Search(key);
        }
        end = high_resolution_clock::now();
        time_search_ordered[run] = duration_cast<milliseconds>(end - start).count();
    }

    // Calcular los promedios
    double avg_insert_random = (time_insert_random[0] + time_insert_random[1] + time_insert_random[2]) / 3;
    double avg_search_random = (time_search_random[0] + time_search_random[1] + time_search_random[2]) / 3;
    double avg_insert_ordered = (time_insert_ordered[0] + time_insert_ordered[1] + time_insert_ordered[2]) / 3;
    double avg_search_ordered = (time_search_ordered[0] + time_search_ordered[1] + time_search_ordered[2]) / 3;

    // Mostrar los resultados usando printf
    printf("Resultados de inserción y búsqueda en tablas hash:\n\n");

    printf("Inserción/Busqueda Aleatoria:\n");
    printf("Corrida 1: %.2f ms\n", time_insert_random[0]);
    printf("Corrida 2: %.2f ms\n", time_insert_random[1]);
    printf("Corrida 3: %.2f ms\n", time_insert_random[2]);
    printf("Promedio: %.2f ms\n\n", avg_insert_random);

    printf("Búsqueda Aleatoria:\n");
    printf("Corrida 1: %.2f ms\n", time_search_random[0]);
    printf("Corrida 2: %.2f ms\n", time_search_random[1]);
    printf("Corrida 3: %.2f ms\n", time_search_random[2]);
    printf("Promedio: %.2f ms\n\n", avg_search_random);

    printf("Inserción/Busqueda Ordenada:\n");
    printf("Corrida 1: %.2f ms\n", time_insert_ordered[0]);
    printf("Corrida 2: %.2f ms\n", time_insert_ordered[1]);
    printf("Corrida 3: %.2f ms\n", time_insert_ordered[2]);
    printf("Promedio: %.2f ms\n\n", avg_insert_ordered);

    printf("Búsqueda Ordenada:\n");
    printf("Corrida 1: %.2f ms\n", time_search_ordered[0]);
    printf("Corrida 2: %.2f ms\n", time_search_ordered[1]);
    printf("Corrida 3: %.2f ms\n", time_search_ordered[2]);
    printf("Promedio: %.2f ms\n\n", avg_search_ordered);

    return 0;
}
