// Copyright 2024 Ericka Araya Hidalgo
//
//  rbtree.h
//

#ifndef rbtree_h
#define rbtree_h

#include <iostream>
#include <string>

/**
 * @enum colors
 * @brief Enumeración para los colores de los nodos del árbol rojinegro.
 */
enum colors { RED, BLACK };

/**
 * @class rbtnode
 * @brief Clase para representar un nodo del árbol rojinegro.
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template <typename T>
class rbtnode {
 private:
    T key;                ///< Llave del nodo.
    rbtnode<T>* p;        ///< Puntero al nodo padre.
    rbtnode<T>* left;     ///< Puntero al nodo hijo izquierdo.
    rbtnode<T>* right;    ///< Puntero al nodo hijo derecho.
    enum colors color;    ///< Color del nodo (ROJO o NEGRO).

 public:
    /**
     * @brief Constructor por omisión.
     */
    rbtnode() : p(nullptr), left(nullptr), right(nullptr), color(RED) {}

    /**
     * @brief Constructor con inicialización de datos miembro.
     * @param k Llave del nodo.
     * @param w Puntero al nodo padre.
     * @param y Puntero al nodo hijo izquierdo.
     * @param z Puntero al nodo hijo derecho.
     * @param c Color del nodo.
     */
    rbtnode(const T& k, rbtnode<T>* w = nullptr, rbtnode<T>* y = nullptr,
                             rbtnode<T>* z = nullptr, enum colors c = RED)
        : key(k), p(w), left(y), right(z), color(c) {}

    /**
     * @brief Destructor.
     */
    ~rbtnode() {}

    // Métodos para acceder y modificar los atributos privados.
    T getKey() const { return this->key; }
    void setKey(const T& k) { this->key = k; }

    rbtnode<T>* getParent() const { return this->p; }
    void setParent(rbtnode<T>* parent) { this->p = parent; }

    rbtnode<T>* getLeft() const { return this->left; }
    void setLeft(rbtnode<T>* l) { this->left = l; }

    rbtnode<T>* getRight() const { return this->right; }
    void setRight(rbtnode<T>* r) { this->right = r; }

    enum colors getColor() const { return this->color; }
    void setColor(enum colors c) { this->color = c; }
};

/**
 * @class rbtree
 * @brief Clase para representar un árbol rojinegro.
 * @tparam T Tipo de dato almacenado en el árbol.
 */
template <typename T>
class rbtree {
 private:
    rbtnode<T>* root;    ///< Raíz del árbol.
    rbtnode<T>* nil;     ///< Nodo nil (hoja) del árbol.

    /**
     * @brief Realiza una rotación a la izquierda en el árbol.
     * @param x Nodo en el que se realiza la rotación.
     */
    void LeftRotate(rbtnode<T>* x) {
        rbtnode<T>* y = x->getRight();  // y es el hijo derecho de x
        // mueve el subárbol izquierdo de y a la derecha de x
        x->setRight(y->getLeft());
        if (y->getLeft() != this->nil) {
            y->getLeft()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == this->nil) {
            root = y;
        } else if (x == x->getParent()->getLeft()) {
            x->getParent()->setLeft(y);
        } else {
            x->getParent()->setRight(y);
        }
        y->setLeft(x);
        x->setParent(y);
    }

    /**
     * @brief Realiza una rotación a la derecha en el árbol.
     * @param x Nodo en el que se realiza la rotación.
     */
    void RightRotate(rbtnode<T>* x) {
        rbtnode<T>* y = x->getLeft();  // y es el hijo izquierdo de x
        // mueve el subárbol derecho de y a la izquierda de x
        x->setLeft(y->getRight());
        if (y->getRight() != this->nil) {
            y->getRight()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == this->nil) {
            root = y;
        } else if (x == x->getParent()->getRight()) {
            x->getParent()->setRight(y);
        } else {
            x->getParent()->setLeft(y);
        }
        y->setRight(x);
        x->setParent(y);
    }

    /**
     * @brief Ajusta el árbol rojinegro después de una inserción.
     * @param z Nodo recién insertado.
     */
    void RBInsertFixup(rbtnode<T>* z) {
        while (z->getParent()->getColor() == RED) {
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                rbtnode<T>* y = z->getParent()->getParent()->getRight();
                if (y->getColor() == RED) {
                    // Caso 1
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getRight()) {
                        // Caso 2
                        z = z->getParent();
                        LeftRotate(z);
                    }
                    // Caso 3
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    RightRotate(z->getParent()->getParent());
                }
            } else {
                rbtnode<T>* y = z->getParent()->getParent()->getLeft();
                if (y->getColor() == RED) {
                    // Caso 1
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getLeft()) {
                        // Caso 2
                        z = z->getParent();
                        RightRotate(z);
                    }
                    // Caso 3
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    LeftRotate(z->getParent()->getParent());
                }
            }
        }
        this->root->setColor(BLACK);
    }

    /**
     * @brief Transplanta un subárbol por otro.
     * @param u Nodo que será reemplazado.
     * @param v Nodo que reemplaza a u.
     */
    void RBTransplant(rbtnode<T>* u, rbtnode<T>* v) {
        if (u->getParent() == this->nil) {
            this->root = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        v->setParent(u->getParent());
    }

    /**
     * @brief Ajusta el árbol rojinegro después de una eliminación.
     * @param x Nodo ajustado.
     */
    void RBDeleteFixup(rbtnode<T>* x) {
        while (x != this->root && x->getColor() == BLACK) {
            if (x == x->getParent()->getLeft()) {
                rbtnode<T>* w = x->getParent()->getRight();
                if (w->getColor() == RED) {
                    // Caso 1
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    LeftRotate(x->getParent());
                    w = x->getParent()->getRight();
                }
                if (w->getLeft()->getColor() == BLACK
                                    && w->getRight()->getColor() == BLACK) {
                    // Caso 2
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getRight()->getColor() == BLACK) {
                        // Caso 3
                        w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        RightRotate(w);
                        w = x->getParent()->getRight();
                    }
                    // Caso 4
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getRight()->setColor(BLACK);
                    LeftRotate(x->getParent());
                    x = this->root;
                }
            } else {
                rbtnode<T>* w = x->getParent()->getLeft();
                if (w->getColor() == RED) {
                    // Caso 1
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    RightRotate(x->getParent());
                    w = x->getParent()->getLeft();
                }
                if (w->getRight()->getColor() == BLACK
                                    && w->getLeft()->getColor() == BLACK) {
                    // Caso 2
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getLeft()->getColor() == BLACK) {
                        // Caso 3
                        w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        LeftRotate(w);
                        w = x->getParent()->getLeft();
                    }
                    // Caso 4
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getLeft()->setColor(BLACK);
                    RightRotate(x->getParent());
                    x = this->root;
                }
            }
        }
        x->setColor(BLACK);
    }

    /**
     * @brief Elimina recursivamente los nodos de un subárbol.
     * @param node Nodo raíz del subárbol a eliminar.
     */
    void deleteSubtree(rbtnode<T>* node) {
        if (node != nil) {
            deleteSubtree(node->getLeft());
            deleteSubtree(node->getRight());
            delete node;
        }
    }

 public:
    /**
     * @brief Constructor (crea un árbol vacío).
     */
    rbtree() {
        this->nil = new rbtnode<T>();
        this->nil->setColor(BLACK);
        this->root = this->nil;
    }

    /**
     * @brief Destructor (borra el árbol).
     */
    ~rbtree() {
        deleteSubtree(this->root);
        delete this->nil;
    }

    /**
     * @brief Inserta un nodo en el árbol.
     * @param z Nodo a insertar.
     */
    void Insert(rbtnode<T>* z) {
        rbtnode<T>* y = this->nil;
        rbtnode<T>* x = this->root;
        while (x != this->nil) {
            y = x;
            if (z->getKey() < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        z->setParent(y);
        if (y == this->nil) {
            root = z;
        } else if (z->getKey() < y->getKey()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }
        z->setLeft(this->nil);
        z->setRight(this->nil);
        z->setColor(RED);
        RBInsertFixup(z);
    }

    /**
     * @brief Realiza un recorrido en orden del árbol.
     * @param x Nodo raíz para comenzar el recorrido.
     */
    void InorderWalk(rbtnode<T>* x) {
        if (x != nil) {
            InorderWalk(x->getLeft());
            std::cout << x->getKey() << " " << x->getColor() << std::endl;
            InorderWalk(x->getRight());
        }
    }

    /**
     * @brief Busca un nodo en el árbol.
     * @param x Nodo raíz desde donde comenzar la búsqueda.
     * @param k Llave a buscar.
     * @return Puntero al nodo encontrado o nil si no se encuentra.
     */
    rbtnode<T>* Search(rbtnode<T>* x, const T& k) {
        if (x == this->nil || k == x->getKey()) {
            return x;
        }
        if (k < x->getKey()) {
            return this->Search(x->getLeft(), k);
        } else {
            return this->Search(x->getRight(), k);
        }
    }

    /**
     * @brief Busca un nodo en el árbol de manera iterativa.
     * @param x Nodo raíz desde donde comenzar la búsqueda.
     * @param k Llave a buscar.
     * @return Puntero al nodo encontrado o nil si no se encuentra.
     */
    rbtnode<T>* IterativeSearch(rbtnode<T>* x, const T& k) {
        while (x != this->nil && k != x->getKey()) {
            if (k < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        return x;
    }

    /**
     * @brief Encuentra el nodo con la llave mínima en el subárbol.
     * @param x Nodo raíz del subárbol.
     * @return Puntero al nodo con la llave mínima.
     */
    rbtnode<T>* Minimum(rbtnode<T>* x) {
        while (x->getLeft() != this->nil) {
            x = x->getLeft();
        }
        return x;
    }

    /**
     * @brief Encuentra el nodo con la llave máxima en el subárbol.
     * @param x Nodo raíz del subárbol.
     * @return Puntero al nodo con la llave máxima.
     */
    rbtnode<T>* Maximum(rbtnode<T>* x) {
        while (x->getRight() != this->nil) {
            x = x->getRight();
        }
        return x;
    }

    /**
     * @brief Encuentra el sucesor de un nodo en el árbol.
     * @param x Nodo del que se quiere encontrar el sucesor.
     * @return Puntero al sucesor del nodo.
     */
    rbtnode<T>* Successor(rbtnode<T>* x) {
        if (x->getRight() != this->nil) {
            return Minimum(x->getRight());
        }
        rbtnode<T>* y = x->getParent();
        while (y != this->nil && x == y->getRight()) {
            x = y;
            y = y->getParent();
        }
        return y;
    }

    /**
     * @brief Elimina un nodo del árbol.
     * @param z Nodo a eliminar.
     */
    void Delete(rbtnode<T>* z) {
        rbtnode<T>* y = z;
        rbtnode<T>* x;
        colors y_original_color = y->getColor();
        if (z->getLeft() == this->nil) {
            x = z->getRight();
            RBTransplant(z, z->getRight());
        } else if (z->getRight() == this->nil) {
            x = z->getLeft();
            RBTransplant(z, z->getLeft());
        } else {
            y = Minimum(z->getRight());
            y_original_color = y->getColor();
            x = y->getRight();
            if (y->getParent() == z) {
                x->setParent(y);
            } else {
                RBTransplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            RBTransplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }
        if (y_original_color == BLACK) {
            RBDeleteFixup(x);
        }
        delete z;
    }

    /**
     * @brief Obtiene la raíz del árbol.
     * @return Puntero a la raíz del árbol.
     */
    rbtnode<T>* getRoot() const {
        return this->root;
    }

    /**
     * @brief Obtiene el nodo nil del árbol.
     * @return Puntero al nodo nil del árbol.
     */
    rbtnode<T>* getNil() const {
        return this->nil;
    }

    /// @brief Retorna informacion de estudiante
    std::string ImprimirDatosDeTarea() {
        return "c20553 Tarea 2 Etapa 1";
    }
};

#endif /* rbtree_h */
