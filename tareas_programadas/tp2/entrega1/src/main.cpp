#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "llist.h"

using namespace std;
using namespace chrono;

int main() {
    const int n = 1000000;
    const int e = 10000;
    const int range = 2 * n;

    // Variables para registrar los tiempos
    double time_insert_random[3] = {0};
    // double time_search_random[3] = {0};
    double time_insert_ordered[3] = {0};
    // double time_search_ordered[3] = {0};

    // Repetir el experimento tres veces
    for (int run = 0; run < 3; run++) {
        // Inserción Aleatoria
        // llist<int> random_list;
        // srand(time(0));

        // // Medir el tiempo de inserción aleatoria
        // auto start = high_resolution_clock::now();
        // for (int i = 0; i < n; i++) {
        //     int key = rand() % range;
        //     llnode<int>* newNode = new llnode<int>(key);
        //     random_list.Insert(newNode);
        // }
        // // auto end = high_resolution_clock::now();
        // // time_insert_random[run] = duration_cast<milliseconds>(end - start).count();

        // // // Medir el tiempo de búsqueda aleatoria
        // // start = high_resolution_clock::now();
        // for (int i = 0; i < e; i++) {
        //     int key = rand() % range;
        //     random_list.Search(key);
        // }
        // auto end = high_resolution_clock::now();
        // // time_insert_random[run] = duration_cast<milliseconds>(end - start).count();
        // time_insert_random[run] = duration_cast<milliseconds>(end - start).count();

        // Inserción Ordenada
        llist<int> ordered_list;

        // Medir el tiempo de inserción ordenada
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            llnode<int>* newNode = new llnode<int>(i);
            ordered_list.Insert(newNode);
        }
        // end = high_resolution_clock::now();
        // time_insert_ordered[run] = duration_cast<milliseconds>(end - start).count();

        // // Medir el tiempo de búsqueda ordenada
        // start = high_resolution_clock::now();
        for (int i = 0; i < e; i++) {
            int key = rand() % range;
            ordered_list.Search(key);
        }
        auto end = high_resolution_clock::now();
        // time_search_ordered[run] = duration_cast<milliseconds>(end - start).count();
        time_insert_ordered[run] = duration_cast<milliseconds>(end - start).count();
    }

    // Calcular los promedios
    double avg_insert_random = (time_insert_random[0] + time_insert_random[1] + time_insert_random[2]) / 3;
    // double avg_search_random = (time_search_random[0] + time_search_random[1] + time_search_random[2]) / 3;
    double avg_insert_ordered = (time_insert_ordered[0] + time_insert_ordered[1] + time_insert_ordered[2]) / 3;
    // double avg_search_ordered = (time_search_ordered[0] + time_search_ordered[1] + time_search_ordered[2]) / 3;

    // Mostrar los resultados
    cout << "Resultados de inserción y búsqueda en listas enlazadas:" << endl;

    cout << "Inserción/Busqueda Aleatoria:" << endl;
    cout << "Corrida 1: " << time_insert_random[0] << " ms" << endl;
    cout << "Corrida 2: " << time_insert_random[1] << " ms" << endl;
    cout << "Corrida 3: " << time_insert_random[2] << " ms" << endl;
    cout << "Promedio: " << avg_insert_random << " ms" << endl;

    // cout << "Búsqueda Aleatoria:" << endl;
    // cout << "Corrida 1: " << time_search_random[0] << " ms" << endl;
    // cout << "Corrida 2: " << time_search_random[1] << " ms" << endl;
    // cout << "Corrida 3: " << time_search_random[2] << " ms" << endl;
    // cout << "Promedio: " << avg_search_random << " ms" << endl;

    cout << "Inserción/Busqueda Ordenada:" << endl;
    cout << "Corrida 1: " << time_insert_ordered[0] << " ms" << endl;
    cout << "Corrida 2: " << time_insert_ordered[1] << " ms" << endl;
    cout << "Corrida 3: " << time_insert_ordered[2] << " ms" << endl;
    cout << "Promedio: " << avg_insert_ordered << " ms" << endl;

    // cout << "Búsqueda Ordenada:" << endl;
    // cout << "Corrida 1: " << time_search_ordered[0] << " ms" << endl;
    // cout << "Corrida 2: " << time_search_ordered[1] << " ms" << endl;
    // cout << "Corrida 3: " << time_search_ordered[2] << " ms" << endl;
    // cout << "Promedio: " << avg_search_ordered << " ms" << endl;

    return 0;
}
