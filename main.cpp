#include <iostream>
#include "construir_arbol.hpp"

//compilacion: g++ main.cpp construir_arbol.cpp pugixml.cpp Tree.cpp -o main


int main(){
    Tree* arbol = construir_arbol("arbol.xml");
    std::cout << "cant libros: " << arbol->getCantLibros() << "\n";
    std::cout << "cant libros: " << arbol->root()<< "\n";
    //arbol->imprimir(arbol->root(),0);
    //arbol->listar(arbol->root());
    arbol->borrar_ratings(4);
    arbol->listar(arbol->root());
    return 0;
}