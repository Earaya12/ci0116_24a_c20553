//
//  llist.h
//

#ifndef llist_h
#define llist_h

// Nodos de la lista:
template <typename T>
class llnode
{
private: 
    T key;
    llnode<T> *prev, *next;
public:
    // Esta clase es usada por otras clases. 
    // Constructor por omisión.
    llnode() {
    };
    
    // Inicialización de los datos miembro.
    llnode (const T& k, llnode<T> *w = nullptr, llnode<T> *y = nullptr):key(k), prev(w), next(y)  {};
    
    ~llnode() {
    };

    // Métodos de acceso (getters).
    T getKey() const {
        return this->key;
    }

    llnode<T>* getNext() const {
        return this->next;
    }
    
    // Métodos de modificación (setters).
    void setKey(const T& k){
        this->key = k;
    }

    void setNext(llnode<T>* n){
        this->next = n;
    }
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist
{
private: 
    llnode<T> *nil;        // nodo centinela
public:
    // Esta clase es usada por otras clases. 
    llist() {
        // Constructor (crea una lista vacía)
        this->nil = new llnode<T>();
        // this->nil->setPrev(nil);
        this->nil->setNext(this->nil);
    };
    
    ~llist() {
        // Destructor (borra la lista)
        llnode<T>* current = this->nil->getNext();
        while (current != this->nil) {
            llnode<T>* temp = current;
            current = current->getNext();
            delete temp;
        }
        delete this->nil;
    };
    
    void Insert(llnode<T>* x) {
        // Inserta el nodo x en la lista.
        x->setNext(this->nil->getNext());
        // x->setPrev(this->nil);
        // this->nil->getNext()->setPrev(x)
        this->nil->setNext(x);
    };

    llnode<T>* Search(const T& k) {
        // Busca la llave iterativamente. Si la encuentra, devuelve un apuntador al nodo que la contiene; sino devuelve el nodo nil (el centinela).
        this->nil->setKey(k);
        llnode<T>* x = this->nil->getNext();
        while(x->getKey() != k) {
            x= x->getNext();
        }
        if(x == this->nil){
            return this->nil;
        } else {
            return x;
        }
    };
        
    void Delete(llnode<T>* x) {
        // Saca de la lista la llave contenida en el nodo apuntado por x.
        // x->getPrev()->setNext(x->getNext());
        // x->getNext()->setPrev(x->getPrev());
        // delete x;
        llnode<T>* current = this->nil;
        while (current->getNext() != x && current->getNext() != this->nil) {
            current = current->getNext();
        }
        if (current->getNext() == x) {
            current->setNext(x->getNext());
            delete x;
        } else {
            std::cout << "El nodo que intentas eliminar no está en la lista." << std::endl;
        }
    };    
};

#endif /* llist_h */
