//
//  rbtree.h
//

#ifndef rbtree_h
#define rbtree_h

#include <iostream>
#include <string>

enum colors { RED, BLACK };

// Nodos del árbol:
template <typename T>
class rbtnode {
private:
    T key;
    rbtnode<T>* p;
    rbtnode<T>* left;
    rbtnode<T>* right;
    enum colors color;

public:
    // Constructor por omisión.
    rbtnode() : p(nullptr), left(nullptr), right(nullptr), color(RED) {}

    // Inicialización de datos miembro.
    rbtnode(const T& k, rbtnode<T>* w = nullptr, rbtnode<T>* y = nullptr, rbtnode<T>* z = nullptr, enum colors c = RED)
        : key(k), p(w), left(y), right(z), color(c) {}

    ~rbtnode() {}

    // Métodos para acceder y modificar los atributos privados.
    T getKey() const { return key; }
    void setKey(const T& k) { key = k; }

    rbtnode<T>* getParent() const { return p; }
    void setParent(rbtnode<T>* parent) { p = parent; }

    rbtnode<T>* getLeft() const { return left; }
    void setLeft(rbtnode<T>* l) { left = l; }

    rbtnode<T>* getRight() const { return right; }
    void setRight(rbtnode<T>* r) { right = r; }

    enum colors getColor() const { return color; }
    void setColor(enum colors c) { color = c; }
};

// Árbol rojinegro:
template <typename T>
class rbtree {
private:
    rbtnode<T>* root;    // raíz del árbol
    rbtnode<T>* nil;     // nodo nil (hoja) del árbol

    void LeftRotate(rbtnode<T>* x) {
        rbtnode<T>* y = x->getRight();
        x->setRight(y->getLeft());
        if (y->getLeft() != nil) {
            y->getLeft()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == nil) {
            root = y;
        } else if (x == x->getParent()->getLeft()) {
            x->getParent()->setLeft(y);
        } else {
            x->getParent()->setRight(y);
        }
        y->setLeft(x);
        x->setParent(y);
    }

    void RightRotate(rbtnode<T>* x) {
        rbtnode<T>* y = x->getLeft();
        x->setLeft(y->getRight());
        if (y->getRight() != nil) {
            y->getRight()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == nil) {
            root = y;
        } else if (x == x->getParent()->getRight()) {
            x->getParent()->setRight(y);
        } else {
            x->getParent()->setLeft(y);
        }
        y->setRight(x);
        x->setParent(y);
    }

    void RBInsertFixup(rbtnode<T>* z) {
        while (z->getParent()->getColor() == RED) {
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                rbtnode<T>* y = z->getParent()->getParent()->getRight();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getRight()) {
                        z = z->getParent();
                        LeftRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    RightRotate(z->getParent()->getParent());
                }
            } else {
                rbtnode<T>* y = z->getParent()->getParent()->getLeft();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getLeft()) {
                        z = z->getParent();
                        RightRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    LeftRotate(z->getParent()->getParent());
                }
            }
        }
        root->setColor(BLACK);
    }

    void RBTransplant(rbtnode<T>* u, rbtnode<T>* v) {
        if (u->getParent() == nil) {
            root = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        v->setParent(u->getParent());
    }

    void RBDeleteFixup(rbtnode<T>* x) {
        while (x != root && x->getColor() == BLACK) {
            if (x == x->getParent()->getLeft()) {
                rbtnode<T>* w = x->getParent()->getRight();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    LeftRotate(x->getParent());
                    w = x->getParent()->getRight();
                }
                if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getRight()->getColor() == BLACK) {
                        w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        RightRotate(w);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getRight()->setColor(BLACK);
                    LeftRotate(x->getParent());
                    x = root;
                }
            } else {
                rbtnode<T>* w = x->getParent()->getLeft();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    RightRotate(x->getParent());
                    w = x->getParent()->getLeft();
                }
                if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getLeft()->getColor() == BLACK) {
                        w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        LeftRotate(w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getLeft()->setColor(BLACK);
                    RightRotate(x->getParent());
                    x = root;
                }
            }
        }
        x->setColor(BLACK);
    }

public:
    // Constructor (crea un árbol vacío)
    rbtree() {
        nil = new rbtnode<T>();
        nil->setColor(BLACK);
        root = nil;
    }

    // Destructor (borra el árbol)
    ~rbtree() {
        // Aquí deberías implementar la lógica para eliminar todos los nodos del árbol y liberar la memoria
        delete nil;
    }

    void Insert(rbtnode<T>* z) {
        rbtnode<T>* y = nil;
        rbtnode<T>* x = root;
        while (x != nil) {
            y = x;
            if (z->getKey() < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        z->setParent(y);
        if (y == nil) {
            root = z;
        } else if (z->getKey() < y->getKey()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }
        z->setLeft(nil);
        z->setRight(nil);
        z->setColor(RED);
        RBInsertFixup(z);
    }

    void InorderWalk(rbtnode<T>* x) {
        if (x != nil) {
            InorderWalk(x->getLeft());
            std::cout << x->getKey() << " " << x->getColor() << std::endl;
            InorderWalk(x->getRight());
        }
    }

    rbtnode<T>* Search(rbtnode<T>* x, const T& k) {
        if (x == nullptr || k == x->getKey()) { // Si se encuentra la llave o se llega a un nodo nulo
            return x;
        }
        if (k < x->getKey()) {
            return this->Search(x->getLeft(), k); // Buscar en el subárbol izquierdo
        } else {
            return this->Search(x->getRight(), k); // Buscar en el subárbol derecho
        }
    }

    rbtnode<T>* IterativeSearch(rbtnode<T>* x, const T& k) {
        while (x != nullptr && k != x->getKey()) { // Mientras no se alcance un nodo nulo y no se encuentre la llave
            if (k < x->getKey()) {
                x = x->getLeft(); // Moverse al hijo izquierdo
            } else {
                x = x->getRight(); // Moverse al hijo derecho
            }
        }
        return x;
    }

    rbtnode<T>* Minimum(rbtnode<T>* x) {
        while (x->getLeft() != nil) {
            x = x->getLeft();
        }
        return x;
    }

    rbtnode<T>* Maximum(rbtnode<T>* x) {
        while (x->getRight() != nil) {
            x = x->getRight();
        }
        return x;
    }

    rbtnode<T>* Successor(rbtnode<T>* x) {
        if (x->getRight() != nil) {
            return Minimum(x->getRight());
        }
        rbtnode<T>* y = x->getParent();
        while (y != nil && x == y->getRight()) {
            x = y;
            y = y->getParent();
        }
        return y;
    }

    void Delete(rbtnode<T>* z) {
        rbtnode<T>* y = z;
        rbtnode<T>* x;
        colors y_original_color = y->getColor();
        if (z->getLeft() == nil) {
            x = z->getRight();
            RBTransplant(z, z->getRight());
        } else if (z->getRight() == nil) {
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

    rbtnode<T>* getRoot() const {
        return root;
    }

    rbtnode<T>* getNil() const {
        return nil;
    }
};

#endif /* rbtree_h */
