//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include "llist.h"
#include <string>
#include <vector>


template <typename T>
class chtable {
public:
    // Constructor que especifica el tamaño de la tabla
    chtable(int sz) : size(sz), table(sz) {}

    // Destructor de la tabla hash
    ~chtable() {}

    // Inserta el elemento en la tabla
    void Insert(const T& k) {
        int index = HashFunction(k);
        llnode<T>* newNode = new llnode<T>(k);
        table[index].Insert(newNode);
    }

    // Retorna un puntero a la llave o nullptr si no se encuentra
    T* Search(const T& k) {
        int index = HashFunction(k);
        llnode<T>* foundNode = table[index].Search(k);
        if (foundNode != table[index].Search(0)) {
            return &foundNode->getKey();
        } else {
            return nullptr;
        }
    }

private:
    // Número de entradas en la tabla
    int size;
    
    // La tabla es un vector de listas doblemente enlazadas
    std::vector<llist<T>> table;

    // Función de dispersión
    int HashFunction(const T& k) const {
        return k % size;
    }
};

#endif /* chtable_h */
