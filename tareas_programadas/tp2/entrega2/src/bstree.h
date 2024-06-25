// Copyright 2024 Ericka Araya Hidalgo
//
//  bstree.h
//
#ifndef bstree_h
#define bstree_h

#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Nodos del árbol binario de búsqueda.
 *
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template <typename T>
class bstnode {
 private:
    T key;  ///< Llave del nodo
    bstnode<T> *p, *left, *right;  ///< Punteros padre, hijo izquierdo-derecho

 public:
    /// Constructor por omisión
    bstnode() : key(T()), p(nullptr), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor con inicialización de datos miembro.
     *
     * @param k Llave del nodo.
     * @param w Puntero al padre del nodo.
     * @param y Puntero al hijo izquierdo del nodo.
     * @param z Puntero al hijo derecho del nodo.
     */
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr,
                bstnode<T> *z = nullptr) : key(k), p(w), left(y), right(z) {}

    ~bstnode() {}

    /// Métodos de acceso (getters)
    T getKey() const { return this->key; }
    bstnode<T>* getParent() const { return this->p; }
    bstnode<T>* getLeft() const { return this->left; }
    bstnode<T>* getRight() const { return this->right; }

    /// Métodos de modificación (setters)
    void setKey(const T& k) { this->key = k; }
    void setParent(bstnode<T>* p) { this->p = p; }
    void setLeft(bstnode<T>* l) { this->left = l; }
    void setRight(bstnode<T>* r) { this->right = r; }
};

/**
 * @brief Árbol de búsqueda binario.
 *
 * @tparam T Tipo de dato almacenado en el árbol.
 */
template <typename T>
class bstree {
 private:
    bstnode<T> *root;  ///< Raíz del árbol

    /**
     * @brief Reemplaza el subárbol en la posición de u con el subárbol en la posición de v.
     *
     * @param u Nodo a reemplazar.
     * @param v Nodo que reemplaza.
     */
    void transplant(bstnode<T>* u, bstnode<T>* v) {
        if (u->getParent() == nullptr) {
            root = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        if (v != nullptr) {
            v->setParent(u->getParent());
        }
    }

    /**
     * @brief Elimina el subárbol con raíz en el nodo x.
     *
     * @param x Raíz del subárbol a eliminar.
     */
    void eliminarSubTree(bstnode<T>* x) {
        if (x != nullptr) {
            eliminarSubTree(x->getLeft());
            eliminarSubTree(x->getRight());
            delete x;
        }
    }

    /**
     * @brief Construye un árbol balanceado a partir de un vector de claves.
     *
     * @param claves Vector de claves.
     * @param inicio Índice de inicio del vector.
     * @param fin Índice de fin del vector.
     * @return bstnode<T>* Nodo raíz del árbol balanceado.
     */
    bstnode<T>* buildBalancedTree(const std::vector<T>& claves,
                                                         int inicio, int fin) {
        // Verifica si el índice de inicio es mayor que el índice de fin, lo que
        // indica un rango vacío.
        if (inicio > fin) {
            return nullptr;  // Si es así, devuelve un puntero nulo.
        }
        // Calcula el índice medio del rango actual.
        int mid = inicio + (fin - inicio) / 2;
        // Crea un nuevo nodo con la clave en la posición media del rango.
        bstnode<T>* nodo = new bstnode<T>(claves[mid]);
        // Construye recursivamente el subárbol izquierdo con las claves antes
        // de la posición media.
        nodo->setLeft(buildBalancedTree(claves, inicio, mid - 1));
        // Establece el padre del hijo izquierdo si este no es nulo.
        if (nodo->getLeft() != nullptr) {
            nodo->getLeft()->setParent(nodo);
        }
        // Construye recursivamente el subárbol derecho con las claves después
        // de la posición media.
        nodo->setRight(buildBalancedTree(claves, mid + 1, fin));
        // Establece el padre del hijo derecho si este no es nulo.
        if (nodo->getRight() != nullptr) {
            nodo->getRight()->setParent(nodo);
        }
        // Devuelve el nodo raíz del subárbol construido.
        return nodo;
    }

    /// @brief Retorna informacion de estudiante
    std::string ImprimirDatosDeTarea() {
        return "c20553 Tarea 2 Etapa 1";
    }

 public:
    /**
     * @brief Constructor (crea un árbol vacío).
     */
    bstree() {
        this->root = nullptr;
    }

    /**
     * @brief Destructor (borra el árbol).
     */
    ~bstree() {
        this->eliminarSubTree(this->root);
    }

    /**
     * @brief Inserta el nodo z en la posición que le corresponde en el árbol.
     *
     * @param z Nodo a insertar.
     */
    void Insert(bstnode<T>* z) {
        bstnode<T>* y = nullptr;
        bstnode<T>* x = root;
        // Recorrer el árbol para encontrar la posición correcta para z
        while (x != nullptr) {
            y = x;
            if (z->getKey() < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        z->setParent(y);  // Establecer el padre de z
        if (y == nullptr) {
            root = z;  // El árbol estaba vacío
        } else if (z->getKey() < y->getKey()) {
            y->setLeft(z);  // z es hijo izquierdo
        } else {
            y->setRight(z);  // z es hijo derecho
        }
    }

    /**
     * @brief Crea un árbol balanceado con n nodos.
     *
     * @param n Número de nodos.
     */
    void createBalancedTree(int n) {
        std::vector<T> claves(n);
        for (int i = 0; i < n; ++i) {
            claves[i] = i;
        }
        root = buildBalancedTree(claves, 0, n - 1);
    }

    /**
     * @brief Recorre en orden el subárbol con raíz x.
     *
     * @param x Raíz del subárbol.
     */
    void InorderWalk(bstnode<T> *x) {
        if (x != nullptr) {
            InorderWalk(x->getLeft());  // Recorrer el subárbol izquierdo
            std::cout << x->getKey() << std::endl;  // Imprimir llave del nodo
            InorderWalk(x->getRight());  // Recorrer el subárbol derecho
        }
    }

    /**
     * @brief Busca la llave k recursivamente en el subárbol con raíz x.
     *
     * @param x Raíz del subárbol.
     * @param k Llave a buscar.
     * @return bstnode<T>* Nodo que contiene la llave, o nullptr si no se encuentra.
     */
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        // Si se encuentra la llave o se llega a un nodo nulo
        if (x == nullptr || k == x->getKey()) {
            return x;
        }
        if (k < x->getKey()) {
            // Buscar en el subárbol izquierdo
            return this->Search(x->getLeft(), k);
        } else {
            // Buscar en el subárbol derecho
            return this->Search(x->getRight(), k);
        }
    }

    /**
     * @brief Busca la llave k iterativamente en el subárbol con raíz x.
     *
     * @param x Raíz del subárbol.
     * @param k Llave a buscar.
     * @return bstnode<T>* Nodo que contiene la llave, o nullptr si no se 
     * encuentra.
     */
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        // Mientras no se alcance un nodo nulo y no se encuentre la llave
        while (x != nullptr && k != x->getKey()) {
            if (k < x->getKey()) {
                x = x->getLeft();  // Moverse al hijo izquierdo
            } else {
                x = x->getRight();  // Moverse al hijo derecho
            }
        }
        return x;
    }

    /// @brief Devuelve el nodo que tiene la llave menor
    /// @param x Raíz del subárbol donde buscar
    /// @return Puntero al nodo con la llave menor, o nullptr si el árbol está
    // vacío
    bstnode<T>* Minimum(bstnode<T> *x) {
        while (x->getLeft() != nullptr) {
            x = x->getLeft();  // Desciende al hijo izquierdo
        }
        return x;  // Devuelve el nodo con la llave menor
    }

    /// @brief Devuelve el nodo que tiene la llave mayor
    /// @param x Raíz del subárbol donde buscar
    /// @return Puntero al nodo con la llave mayor, o nullptr si el árbol está
    // vacío
    bstnode<T>* Maximum(bstnode<T> *x) {
        while (x->getRight() != nullptr) {
            x = x->getRight();  // Desciende al hijo derecho
        }
        return x;  // Devuelve el nodo con la llave mayor
    }

    /// @brief Devuelve el nodo cuya llave es la que le sigue a la del nodo x
    /// @param x Nodo de referencia
    /// @return Puntero al nodo sucesor, o nullptr si no existe
    bstnode<T>* Successor(bstnode<T> *x) {
        if (x->getRight() != nullptr) {
            // El sucesor es el mínimo del subárbol derecho
            return this->Minimum(x->getRight());
        }
        bstnode<T>* y = x->getParent();
        while (y != nullptr && x == y->getRight()) {
            x = y;  // Sube al nodo padre
            y = y->getParent();  // Actualiza el puntero al nodo padre
        }
        return y;  // Devuelve el sucesor
    }

    /// @brief Elimina la llave contenida en el nodo apuntado por z
    /// @param z Puntero al nodo a eliminar
    void Delete(bstnode<T>* z) {
        if (z->getLeft() == nullptr) {
            // Caso 2: z no tiene hijo derecho
            this->transplant(z, z->getRight());
        } else if (z->getRight() == nullptr) {
            // Caso 2: z no tiene hijo derecho
            this->transplant(z, z->getLeft());
        } else {
            // Encuentra el sucesor de z
            bstnode<T>* y = this->Minimum(z->getRight());
            if (y->getParent() != z) {
                // Reemplaza y por su hijo derecho
                this->transplant(y, y->getRight());
                // Establece el hijo derecho de z como hijo derecho de y
                y->setRight(z->getRight());
                // Establece y como padre del nuevo hijo derecho
                y->getRight()->setParent(y);
            }
            this->transplant(z, y);  // Reemplaza z por y
            // Establece el hijo izquierdo de z como hijo izquierdo de y
            y->setLeft(z->getLeft());
             // Establece y como padre del nuevo hijo izquierdo
            y->getLeft()->setParent(y);
        }
    }

    /// @brief Obtiene la raíz del árbol
    /// @return Puntero a la raíz del árbol
    bstnode<T>* getRoot() const { return this->root; }

    /// @brief Establece la raíz del árbol
    /// @param r Puntero a la nueva raíz del árbol
    void setRoot(bstnode<T>* r) { this->root = r; }
};

#endif /* bstree_h */
