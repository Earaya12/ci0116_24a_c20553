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
        rbtree<int> random_tree;
        srand(time(0));

        // Medir el tiempo de inserción aleatoria
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            int key = rand() % range;
            rbtnode<int>* newNode = new rbtnode<int>(key);
            random_tree.Insert(newNode);
        }
        auto end = high_resolution_clock::now();
        time_insert_random[run] = duration_cast<milliseconds>(end - start).count();

        // Medir el tiempo de búsqueda aleatoria
        start = high_resolution_clock::now();
        for (int i = 0; i < e; i++) {
            int key = rand() % range;
            random_tree.IterativeSearch(random_tree.getRoot(), key);
        }
        end = high_resolution_clock::now();
        time_search_random[run] = duration_cast<milliseconds>(end - start).count();


        // Inserción Ordenada
        rbtree<int> ordered_tree;

        // Medir el tiempo de inserción ordenada
        start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            rbtnode<int>* newNode = new rbtnode<int>(i);
            ordered_tree.Insert(newNode);
        }
        end = high_resolution_clock::now();
        time_insert_ordered[run] = duration_cast<milliseconds>(end - start).count();

        // Medir el tiempo de búsqueda ordenada
        start = high_resolution_clock::now();
        for (int i = 0; i < e; i++) {
            int key = rand() % range;
            ordered_tree.IterativeSearch(ordered_tree.getRoot(), key);
        }
        end = high_resolution_clock::now();
        time_search_ordered[run] = duration_cast<milliseconds>(end - start).count();
    }

    // Calcular los promedios
    double avg_insert_random = (time_insert_random[0] + time_insert_random[1] + time_insert_random[2]) / 3;
    double avg_search_random = (time_search_random[0] + time_search_random[1] + time_search_random[2]) / 3;
    double avg_insert_ordered = (time_insert_ordered[0] + time_insert_ordered[1] + time_insert_ordered[2]) / 3;
    double avg_search_ordered = (time_search_ordered[0] + time_search_ordered[1] + time_search_ordered[2]) / 3;

    // Mostrar los resultados
    cout << "Resultados de inserción y búsqueda en árboles rojinegros:" << endl;

    cout << "Inserción/Busqueda Aleatoria:" << endl;
    cout << "Corrida 1: " << time_insert_random[0] << " ms" << endl;
    cout << "Corrida 2: " << time_insert_random[1] << " ms" << endl;
    cout << "Corrida 3: " << time_insert_random[2] << " ms" << endl;
    cout << "Promedio: " << avg_insert_random << " ms" << endl;

    cout << "Búsqueda Aleatoria:" << endl;
    cout << "Corrida 1: " << time_search_random[0] << " ms" << endl;
    cout << "Corrida 2: " << time_search_random[1] << " ms" << endl;
    cout << "Corrida 3: " << time_search_random[2] << " ms" << endl;
    cout << "Promedio: " << avg_search_random << " ms" << endl;

    cout << "Inserción/Busqueda Ordenada:" << endl;
    cout << "Corrida 1: " << time_insert_ordered[0] << " ms" << endl;
    cout << "Corrida 2: " << time_insert_ordered[1] << " ms" << endl;
    cout << "Corrida 3: " << time_insert_ordered[2] << " ms" << endl;
    cout << "Promedio: " << avg_insert_ordered << " ms" << endl;

    cout << "Búsqueda Ordenada:" << endl;
    cout << "Corrida 1: " << time_search_ordered[0] << " ms" << endl;
    cout << "Corrida 2: " << time_search_ordered[1] << " ms" << endl;
    cout << "Corrida 3: " << time_search_ordered[2] << " ms" << endl;
    cout << "Promedio: " << avg_search_ordered << " ms" << endl;

    return 0;
}