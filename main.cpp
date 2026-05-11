#include <iostream>
#include "construir_arbol.hpp"
int main(){
    Arbol arbol = construir_arbol("arbol.xml");
    std::cout << "cant libros: " << arbol.libros.size() << "\n";

    return 0;
}