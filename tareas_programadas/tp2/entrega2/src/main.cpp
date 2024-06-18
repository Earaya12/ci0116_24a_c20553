#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "llist.h"
#include "rbtree.h"
#include "chasht.h"

using namespace std;
using namespace chrono;

int main() {
    rbtree<int> tree;

    rbtnode<int>* node1 = new rbtnode<int>(10);
    rbtnode<int>* node2 = new rbtnode<int>(20);
    rbtnode<int>* node3 = new rbtnode<int>(30);
    rbtnode<int>* node4 = new rbtnode<int>(15);

    tree.Insert(node1);
    tree.Insert(node2);
    tree.Insert(node3);
    tree.Insert(node4);

    std::cout << "Elementos del árbol después de las inserciones:" << std::endl;
    tree.InorderWalk(tree.getRoot()); // Usamos la raíz del árbol para el recorrido

    rbtnode<int>* searchNode = tree.Search(tree.getRoot(), 20); // Pasamos la raíz y la clave a buscar
    if (searchNode != tree.getNil()) {
        std::cout << "Nodo con llave 20 encontrado." << std::endl;
    } else {
        std::cout << "Nodo con llave 20 no encontrado." << std::endl;
    }

    tree.Delete(node2);

    std::cout << "Elementos del árbol después de eliminar el nodo con llave 20:" << std::endl;
    tree.InorderWalk(tree.getRoot()); // Usamos la raíz del árbol para el recorrido

    return 0;
}
