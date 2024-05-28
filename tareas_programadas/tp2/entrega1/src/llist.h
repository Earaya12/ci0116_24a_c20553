//
//  llist.h
//

#ifndef llist_h
#define llist_h

// Nodos de la lista:
template <typename T>
class llnode
{
public:
    // Esta clase es usada por otras clases. 
    // Modifique los atributos para que sean privados y se accedan solo mediante métodos públicos de la clase.
    T key;
    llnode<T> *prev, *next;
    
    // Constructor por omisión.
    llnode() {
    };
    
    // Inicialización de los datos miembro.
    llnode (const T& k, llnode<T> *w = nullptr, llnode<T> *y = nullptr):key(k), prev(w), next(y)  {};
    
    ~llnode() {
    };
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist
{
public:
    // Esta clase es usada por otras clases. 
    // Modifique los atributos para que sean privados y se accedan solo mediante métodos públicos de la clase.

    llnode<T> *nil;        // nodo centinela

    llist() {
        // Constructor (crea una lista vacía)
    };
    
    ~llist() {
        // Destructor (borra la lista)
    };
    
    void Insert(llnode<T>* x) {
        // Inserta el nodo x en la lista.
    };

    llnode<T>* Search(const T& k) {
        // Busca la llave iterativamente. Si la encuentra, devuelve un apuntador al nodo que la contiene; sino devuelve el nodo nil (el centinela).
    };
        
    void Delete(llnode<T>* x) {
        // Saca de la lista la llave contenida en el nodo apuntado por x.
    };    
};

#endif /* llist_h */
