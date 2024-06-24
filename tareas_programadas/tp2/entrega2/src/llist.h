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
    T key; ///< Llave del nodo.
    llnode<T>* prev; ///< Puntero al nodo anterior.
    llnode<T>* next; ///< Puntero al nodo siguiente.

public:
    /// @brief Constructor por omisión.
    llnode() : key(T()), prev(nullptr), next(nullptr) {}

    /// @brief Constructor que inicializa los datos miembro.
    /// @param k Llave del nodo.
    /// @param w Puntero al nodo anterior.
    /// @param y Puntero al nodo siguiente.
    llnode(const T& k, llnode<T>* w = nullptr, llnode<T>* y = nullptr) : key(k), prev(w), next(y) {}

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
    llnode<T>* nil; ///< Nodo centinela.

    /// @brief Retorna informacion de estudiante
    std::string ImprimirDatosDeTarea() {
        return "c20553 Tarea 2 Etapa 1";
    }

public:
    /// @brief Constructor por omisión (crea una lista vacía).
    llist() {
        this->nil = new llnode<T>(); // Crea el nodo centinela.
        this->nil->setNext(this->nil); // Inicializa el nodo centinela apuntándose a sí mismo.
        this->nil->setPrev(this->nil); // Inicializa el nodo centinela apuntándose a sí mismo.
    }

    /// @brief Destructor (borra la lista).
    ~llist() {
        llnode<T>* current = this->nil->getNext(); // Empieza desde el primer nodo.
        while (current != this->nil) { // Recorre la lista hasta llegar al nodo centinela.
            llnode<T>* temp = current; // Guarda el nodo actual.
            current = current->getNext(); // Avanza al siguiente nodo.
            delete temp; // Elimina el nodo guardado.
        }
        delete this->nil; // Elimina el nodo centinela.
    }

    /// @brief Inserta el nodo x en la lista.
    /// @param x Puntero al nodo a insertar.
    void Insert(llnode<T>* x) {
        x->setNext(this->nil->getNext()); // Establece el siguiente nodo de x como el primer nodo actual.
        this->nil->getNext()->setPrev(x); // Establece x como el nodo anterior del primer nodo actual.
        x->setPrev(this->nil); // Establece el nodo centinela como el nodo anterior de x.
        this->nil->setNext(x); // Establece x como el primer nodo después del nodo centinela.
    }

    /// @brief Busca la llave k iterativamente en la lista.
    /// @param k Llave a buscar.
    /// @return Puntero al nodo que contiene la llave, o el nodo centinela si no se encuentra.
    llnode<T>* Search(const T& k) {
        this->nil->setKey(k); // Usa el nodo centinela para simplificar la lógica de búsqueda.
        llnode<T>* x = this->nil->getNext(); // Empieza desde el primer nodo.
        while (x->getKey() != k) { // Recorre la lista hasta encontrar la llave o llegar al nodo centinela.
            x = x->getNext(); // Avanza al siguiente nodo.
        }
        return (x == this->nil) ? this->nil : x; // Devuelve el nodo encontrado o el nodo centinela.
    }

    /// @brief Elimina la llave contenida en el nodo apuntado por x.
    /// @param x Puntero al nodo a eliminar.
    void Delete(llnode<T>* x) {
        if (x != this->nil) { // Asegura que el nodo a eliminar no sea el nodo centinela.
            x->getPrev()->setNext(x->getNext()); // Establece el siguiente nodo del anterior como el siguiente del nodo a eliminar.
            x->getNext()->setPrev(x->getPrev()); // Establece el nodo anterior del siguiente como el anterior del nodo a eliminar.
            delete x; // Elimina el nodo.
        }
    }
};


#endif /* llist_h */
