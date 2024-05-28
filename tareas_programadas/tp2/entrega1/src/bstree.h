//
//  bstree.h
//

#ifndef bstree_h
#define bstree_h

#include <iostream>

// Nodos del árbol:
template <typename T>
class bstnode
{
public:
    // Esta clase es usada por otras clases. 
    // Modifique los atributos para que sean privados y se accedan solo mediante métodos públicos de la clase.
    T key;
    bstnode<T> *p, *left, *right;
    
    // Constructor por omisión
    bstnode() {
    };
    
    // Inicialización de datos miembro
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr, bstnode<T> *z = nullptr):key(k), p(w), left(y), right(z) {};
    
    ~bstnode() {
    };
};

// Árbol de búsqueda binario:
template <typename T>
class bstree
{
public:
    // Esta clase es usada por otras clases. 
    // Modifique los atributos para que sean privados y se accedan solo mediante métodos públicos de la clase.
    bstnode<T> *root;    // raíz del árbol

    bstree() {
        // Constructor (crea un árbol vacío)
    };
    
    ~bstree() {
        // Destructor (borra el árbol)
    };
    
    void Insert(bstnode<T>* z) {
        // Inserta el nodo z en la posición que le corresponde en el árbol.
    };
    
    void InorderWalk(bstnode<T> *x) {
        // Recorre en orden el subárbol con raíz x, imprimiendo la llave de cada nodo en en una nueva línea de la salida estándar después de recorrido el subárbol izquierdo y antes de recorrer el subárbol derecho.
    };
    
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        // Busca la llave k recursivamente en el subárbol con raíz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
    };
    
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raíz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
    };
    
    bstnode<T>* Minimum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave menor. Si el árbol está vacío, devuelve nullptr.
    };
    
    bstnode<T>* Maximum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave mayor. Si el árbol esta vacío devuelve nullptr.
    };
    
    bstnode<T>* Successor(bstnode<T> *x) {
        // Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve nullptr.
    };
    
    void Delete(bstnode<T>* z) {
        // Saca del árbol la llave contenida en el nodo apuntado por z.
    };  
};

#endif /* bstree_h */

