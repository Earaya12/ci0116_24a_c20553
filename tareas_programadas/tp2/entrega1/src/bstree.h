//
//  bstree.h
//

#ifndef bstree_h
#define bstree_h

#include <iostream>
#include <vector>

// Nodos del árbol:
template <typename T>
class bstnode
{
private:
    T key;
    bstnode<T> *p, *left, *right;

public:
    // Constructor por omisión
    bstnode() : key(T()), p(nullptr), left(nullptr), right(nullptr) {};

    // Inicialización de datos miembro
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr,
         bstnode<T> *z = nullptr)
        : key(k), p(w), left(y), right(z) {};

    ~bstnode() {};

    // Métodos de acceso (getters)
    T getKey() const { return this->key; }
    bstnode<T>* getParent() const { return this->p; }
    bstnode<T>* getLeft() const { return this->left; }
    bstnode<T>* getRight() const { return this->right; }

    // Métodos de modificación (setters)
    void setKey(const T& k) { this->key = k; }
    void setParent(bstnode<T>* p) { this->p = p; }
    void setLeft(bstnode<T>* l) { this->left = l; }
    void setRight(bstnode<T>* r) { this->right = r; }
};

// Árbol de búsqueda binario:
template <typename T>
class bstree
{
private:
    bstnode<T> *root;    // raíz del árbol
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
    void deleteSubTree(bstnode<T>* x){
        if (x != nullptr) {
            deleteSubTree(x->getLeft());
            deleteSubTree(x->getRight());
            delete x;
        }
    }

    bstnode<T>* buildBalancedTree(const std::vector<T>& keys, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = start + (end - start) / 2;
        bstnode<T>* node = new bstnode<T>(keys[mid]);
        node->setLeft(buildBalancedTree(keys, start, mid - 1));
        if (node->getLeft() != nullptr) {
            node->getLeft()->setParent(node);
        }
        node->setRight(buildBalancedTree(keys, mid + 1, end));
        if (node->getRight() != nullptr) {
            node->getRight()->setParent(node);
        }
        return node;
    }
public:
    // Esta clase es usada por otras clases. 
    // Modifique los atributos para que sean privados y se accedan solo mediante
    // métodos públicos de la clase.

    bstree() {
        // Constructor (crea un árbol vacío)
        this->root = nullptr;
    };
    
    ~bstree() {
        // Destructor (borra el árbol)
        this->deleteSubTree(this->root);
    };
    
    void Insert(bstnode<T>* z) {
        // Inserta el nodo z en la posición que le corresponde en el árbol.
        bstnode<T>* y = nullptr;
        bstnode<T>* x = root;
        while (x != nullptr) {
            y = x;
            if (z->getKey() < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        z->setParent(y);
        if (y == nullptr) {
            root = z;
        } else if (z->getKey() < y->getKey()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }
    };

    void createBalancedTree(int n) {
        std::vector<T> keys(n);
        for (int i = 0; i < n; ++i) {
            keys[i] = i;
        }
        root = buildBalancedTree(keys, 0, n - 1);
    }
    
    void InorderWalk(bstnode<T> *x) {
        // Recorre en orden el subárbol con raíz x, imprimiendo la llave de cada
        // nodo en en una nueva línea de la salida estándar después de recorrido
        // el subárbol izquierdo y antes de recorrer el subárbol derecho.
        if (x != nullptr) {
            InorderWalk(x->getLeft());
            std::cout << x->getKey() << std::endl;
            InorderWalk(x->getRight());
        }
    };
    
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        // Busca la llave k recursivamente en el subárbol con raíz x.
        // Si la encuentra devuelve un apuntador al nodo que la contiene,
        // sino devuelve nullptr.
        if (x == nullptr || k == x->getKey()) {
            return x;
        } if (k < x->getKey()) {
            return this->Search(x->getLeft(), k);
        } else {
            return this->Search(x->getRight(), k);
        }
    };
    
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raíz x.
        // Si la encuentra devuelve un apuntador al nodo que la contiene,
        // ssino devuelve nullptr.
        while (x != nullptr && k != x->getKey()) {
            if (k < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        return x;
    };
    
    bstnode<T>* Minimum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave menor. Si el árbol está vacío,
        // devuelve nullptr.
        while (x->getLeft() != nullptr)
            x = x->getLeft();
        return x;
    };
    
    bstnode<T>* Maximum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave mayor. Si el árbol esta vacío
        // devuelve nullptr.
        while (x->getRight() != nullptr)
            x = x->getRight();
        return x;
    };
    
    bstnode<T>* Successor(bstnode<T> *x) {
        // Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no
        // existe el nodo, devuelve nullptr.
        if (x->getRight() != nullptr) {
            return this->Minimum(x->getRight());
        }
        bstnode<T>* y = x->getParent();
        while (y != nullptr && x == y->getRight()) {
            x = y;
            y = y->getParent();
        }
        return y;
    };
    
    void Delete(bstnode<T>* z) {
        // Saca del árbol la llave contenida en el nodo apuntado por z.
        if (z->getLeft() == nullptr) {
            this->transplant(z, z->getRight());
        } else if (z->getRight() == nullptr) {
            this->transplant(z, z->getLeft());
        } else {
            bstnode<T>* y = this->Minimum(z->getRight());
            if (y->getParent() != z) {
                this->transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            this->transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
        }
    };  

    bstnode<T>* getRoot() const { return this->root; }
    void setRoot(bstnode<T>* r) { this->root = r; }
};

#endif /* bstree_h */

