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

// Funcion que lista los id de cada libro 
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

// Funcion que libera recursivamente la memoria de un nodo y sus hijos
void Tree::liberarNodo(Node* nodo){
    if(!nodo) return;
    for(Tree::Node* hijoNodo : nodo->children){
        liberarNodo(hijoNodo);
    }
    delete nodo;
}

// Funcion que borra todos los libros con un rating igual o menor a r
void Tree::borrar_ratings(float r){
    // Si rootNode es nulo o no tiene hijos no se hace nada
    if(!rootNode || rootNode -> children.empty()){
        return;
    }

    auto it = rootNode -> children.begin(); // se declara un iterador para recorrer y a la vez poder modificar el vector facilmente

    // se recorren todos los hijos de rootNode (es decir los libros) 
    while(it != rootNode -> children.end()){
        Node* libroNodo = *it;
        float ratingLibro = 0.0;
        bool tieneRating = false;

        // se recorren los hijos de cada libroNodo hasta encontrar el que tiene como tag "average_rating"
        for(Node* hijoNodo : libroNodo -> children){
            if(hijoNodo -> tag == "average_rating"){
                try{
                    ratingLibro = std::stof(hijoNodo->text); // conversion del texto del tag a float
                    tieneRating = true;
                }
                catch(...){
                    tieneRating = false; // si el libroHijo no tiene un tag "average_rating" se ignora
                }
                break;
            }
        }

        // si se detecto rating al libro y ademas este es menor a r, el libro se borra
        if(tieneRating && ratingLibro <= r){
            liberarNodo(libroNodo); // se elimina el nodo asociado al libro y sus nodos hijos
            it = rootNode -> children.erase(it); // se actualiza el iterador
            cant_libros--;
        }
        // si no se detecto rating o si este es mayor a r, se continua al siguiente libroNodo
        else{
            it++;
        }
    }
}





