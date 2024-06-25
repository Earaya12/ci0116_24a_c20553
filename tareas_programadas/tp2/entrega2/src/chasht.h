// Copyright 2024 Ericka Araya Hidalgo
//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include <string>
#include <vector>

#include "llist.h"

/**
 * @class chtable
 * @brief Clase para representar una tabla hash encadenada.
 * @tparam T Tipo de dato almacenado en la tabla.
 */
template <typename T>
class chtable {
 public:
    /**
     * @brief Constructor que especifica el tamaño de la tabla.
     * @param sz Tamaño de la tabla hash.
     */
    explicit chtable(int sz) : size(sz), table(sz) {}

    /**
     * @brief Destructor de la tabla hash.
     */
    ~chtable() {}

    /**
     * @brief Inserta un elemento en la tabla hash.
     * @param k Elemento a insertar.
     */
    void Insert(const T& k) {
        int index = HashFunction(k);
        llnode<T>* newNode = new llnode<T>(k);
        table[index].Insert(newNode);
    }

    /**
     * @brief Busca un elemento en la tabla hash.
     * @param k Elemento a buscar.
     * @return Puntero al elemento encontrado o nullptr si no se encuentra.
     */
    T* Search(const T& k) {
        int index = HashFunction(k);
        llnode<T>* foundNode = table[index].Search(k);
        if (foundNode != nullptr) {
            return &foundNode->getKey();
        } else {
            return nullptr;
        }
    }

    /**
     * @brief Elimina un elemento de la tabla hash.
     * @param k Elemento a eliminar.
     */
    void Delete(const T& k) {
        int index = HashFunction(k);
        table[index].Delete(k);
    }

    /// @brief Retorna informacion de estudiante
    std::string ImprimirDatosDeTarea() {
        return "c20553 Tarea 2 Etapa 2";
    }

 private:
    int size;  ///< Número de entradas en la tabla.
    ///< La tabla es un vector de listas doblemente enlazadas.
    std::vector<llist<T>> table;

    /**
     * @brief Función de dispersión.
     * @param k Elemento del cual se calculará el índice.
     * @return Índice calculado a partir del elemento.
     */
    int HashFunction(const T& k) const {
        return k % size;
    }
};

#endif /* chtable_h */
