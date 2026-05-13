#include "Tree.hpp"
#include <algorithm>
#include <functional>

// Node
Tree::Node::Node(std::string t,std::string txt, Node* p) {
    tag=t;
    text=txt;
    parent = p;
}

// Constructor
Tree::Tree() {;
    rootNode = nullptr;
    treeSize = 0;
    cant_libros=0;
}

bool Tree::isEmpty() {
    return treeSize == 0;
}

int Tree::size() {
    return treeSize;
}
 int Tree::getCantLibros(){
    return cant_libros;
 }

Tree::Node* Tree::root() {
    if (!rootNode) throw std::runtime_error("Árbol vacío");
    return rootNode;
}



Tree::Node* Tree::insert(Node* padre, std::string t, std::string txt) {
    if (!rootNode) {
        rootNode = new Node(t,txt);
        treeSize++;
        return rootNode;
    }

    Node* newNode = new Node(t, txt, padre);
    padre->children.push_back(newNode);
    treeSize++;
    return newNode;
}
void Tree::imprimir(Node* nodo, int nivel) {
    // Caso base: si el nodo es nulo, no hacemos nada
    if (!nodo) return;

    // Generamos la sangría visual (4 espacios por cada nivel de profundidad)
    std::string sangria(nivel * 4, ' ');

    // 2. Imprimimos el nodo actual
    // Formato sugerido:   - [tag]: texto
    std::cout << sangria << "- [" << nodo->tag << "]: " << nodo->text << "\n";

    // 3. Llamada recursiva para todos sus hijos (aumentando el nivel en 1)
    for (Node* hijo : nodo->children) {
        imprimir(hijo, nivel + 1);
    }
}

void Tree::listar(Node* nodo) {
    // Caso base: si el nodo es nulo no se hace nada
    if (!nodo) return;

    // Si el nodo actual es un book_id, se imprime
    if (nodo->tag == "book_id"){
        std::cout << nodo->text << "\n";
    }

    // Llamada recursiva para todos los hijos del nodo actual para mantener el recorrido PreOrder
    for (Node* hijo : nodo->children) {
        listar(hijo);
    }
}






