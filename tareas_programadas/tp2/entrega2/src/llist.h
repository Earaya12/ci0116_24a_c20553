// Copyright 2024 Ericka Araya Hidalgo
//
//  llist.h
//

#ifndef llist_h
#define llist_h

#include <string>

/// @brief Nodos de la lista doblemente enlazada.
/// @tparam T Tipo de dato de la llave almacenada en el nodo.
template <typename T>
class llnode {
 private:
    T key;  ///< Llave del nodo.
    llnode<T>* prev;  ///< Puntero al nodo anterior.
    llnode<T>* next;  ///< Puntero al nodo siguiente.

 public:
    /// @brief Constructor por omisión.
    llnode() : key(T()), prev(nullptr), next(nullptr) {}

    /// @brief Constructor que inicializa los datos miembro.
    /// @param k Llave del nodo.
    /// @param w Puntero al nodo anterior.
    /// @param y Puntero al nodo siguiente.
    llnode(const T& k, llnode<T>* w = nullptr,
                     llnode<T>* y = nullptr) : key(k), prev(w), next(y) {}

    /// @brief Destructor.
    ~llnode() {}

    /// @brief Obtiene la llave del nodo.
    /// @return Llave del nodo.
    T& getKey() {
        return this->key;
    }

    /// @brief Obtiene el puntero al siguiente nodo.
    /// @return Puntero al siguiente nodo.
    llnode<T>* getNext() const {
        return this->next;
    }

    /// @brief Obtiene el puntero al nodo anterior.
    /// @return Puntero al nodo anterior.
    llnode<T>* getPrev() const {
        return this->prev;
    }

    /// @brief Establece la llave del nodo.
    /// @param k Nueva llave del nodo.
    void setKey(const T& k) {
        this->key = k;
    }

    /// @brief Establece el puntero al siguiente nodo.
    /// @param n Puntero al siguiente nodo.
    void setNext(llnode<T>* n) {
        this->next = n;
    }

    /// @brief Establece el puntero al nodo anterior.
    /// @param p Puntero al nodo anterior.
    void setPrev(llnode<T>* p) {
        this->prev = p;
    }
};

/// @brief Lista doblemente enlazada con nodo centinela.
/// @tparam T Tipo de dato de las llaves almacenadas en la lista.
template <typename T>
class llist {
 private:
    llnode<T>* nil;  ///< Nodo centinela.


 public:
    /// @brief Retorna informacion de estudiante
    std::string ImprimirDatosDeTarea() {
        return "c20553 Tarea 2 Etapa 1";
    }

    /// @brief Constructor por omisión (crea una lista vacía).
    llist() {
        this->nil = new llnode<T>();  // Crea el nodo centinela.
        // Inicializa el nodo centinela apuntándose a sí mismo.
        this->nil->setNext(this->nil);
        this->nil->setPrev(this->nil);
    }

    /// @brief Destructor (borra la lista).
    ~llist() {
        // Empieza desde el primer nodo.
        llnode<T>* current = this->nil->getNext();
        // Recorre la lista hasta llegar al nodo centinela.
        while (current != this->nil) {
            llnode<T>* temp = current;  // Guarda el nodo actual.
            current = current->getNext();  // Avanza al siguiente nodo.
            delete temp;  // Elimina el nodo guardado.
        }
        delete this->nil;  // Elimina el nodo centinela.
    }

    /// @brief Inserta el nodo x en la lista.
    /// @param x Puntero al nodo a insertar.
    void Insert(llnode<T>* x) {
        // Establece el siguiente nodo de x como el primer nodo actual.
        x->setNext(this->nil->getNext());
        // Establece x como el nodo anterior del primer nodo actual.
        this->nil->getNext()->setPrev(x);
        // Establece el nodo centinela como el nodo anterior de x.
        x->setPrev(this->nil);
        // Establece x como el primer nodo después del nodo centinela.
        this->nil->setNext(x);
    }

    /// @brief Busca la llave k iterativamente en la lista.
    /// @param k Llave a buscar.
    /// @return Puntero al nodo que contiene la llave, o el nodo centinela si no
    /// se encuentra.
    llnode<T>* Search(const T& k) {
        // Usa el nodo centinela para simplificar la lógica de búsqueda.
        this->nil->setKey(k);
        llnode<T>* x = this->nil->getNext();  // Empieza desde el primer nodo.
        // Recorre la lista hasta encontrar la llave o llegar al nodo centinela.
        while (x->getKey() != k) {
            x = x->getNext();  // Avanza al siguiente nodo.
        }
        // Devuelve el nodo encontrado o el nodo centinela.
        return (x == this->nil) ? this->nil : x;
    }

    /// @brief Elimina la llave contenida en el nodo apuntado por x.
    /// @param x Puntero al nodo a eliminar.
    void Delete(llnode<T>* x) {
        // Asegura que el nodo a eliminar no sea el nodo centinela.
        if (x != this->nil) {
            // Establece el siguiente nodo del anterior como el siguiente del
            // nodo a eliminar.
            x->getPrev()->setNext(x->getNext());
            // Establece el nodo anterior del siguiente como el anterior del
            // nodo a eliminar.
            x->getNext()->setPrev(x->getPrev());
            delete x;  // Elimina el nodo.
        }
    }
};


#endif /* llist_h */
