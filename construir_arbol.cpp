
#include <vector>
#include <string>
#include "pugixml.hpp"
#include "construir_arbol.hpp"


// Tags para filtrar los datos que nos interesan.
std::string tags_hojas[] = { "title", "isbn", "publication_year", "description", "num_pages", "average_rating", "lenguage_code"};
std::string tags_similar_book[] = { "title", "isbn", "publication_year"};

/// @brief Funcion que añade libros al arbol. 
/// @param arbol Un puntero al arbol
/// @param nodoLibro un nodo XML que contiene la informacion de un libro (lo que está entre <book> ... <book>)
void añadirLibro(Tree* arbol, pugi::xml_node nodoLibro){
    // Insertamos a la raiz el nodo que representa un Libro, usamos el id del libro para diferenciar los hijos en este nivel.
    std::string bookId = nodoLibro.child_value("id");
    Tree::Node* Libro= arbol->insert(arbol->root(),"book_id",bookId);
    // Insertamos hijos (hojas) a libro, usando los tags de interes.
    for(const std::string& tag : tags_hojas){
        arbol->insert(Libro,tag, nodoLibro.child_value(tag.c_str()) );
    }
    // añadimos el nodo similar_books
     pugi::xml_node similar_books_node= nodoLibro.child("similar_books");
     Tree::Node* similar_books= arbol->insert(Libro,"similar_books","libros similares");
    // recorremos todos los hijos de similar_books (es decir, cada libro similar) y lo insertamos al nodo similar_books.
    // Tambien usamos id para diferenciar los libros en este nivel.
     for (pugi::xml_node sb : similar_books_node.children("book")) {
           Tree::Node* similar_book= arbol->insert(similar_books,"similar_book", sb.child_value("id"));
           // A cada libro similar, le insertamos los atributos que nos interesan (en tags_similar_book).
           for(const std::string& tag : tags_similar_book){
            arbol->insert(similar_book,tag, sb.child_value(tag.c_str()));
           }
        }
    arbol->cant_libros++;    

}
/// @brief Funcion que usa funciones de pugixml para convertir los XML y la funcion propia añadirLibro. Ingresamos a cada nodo GoodreadsResponse para acceder a cada book.
/// @param ruta dirrecion del archivo del xml de arbol de todos los libros
/// @return puntero al arbol donde sus hijos son los libros
Tree* construir_arbol(const std::string& ruta) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(ruta.c_str());
    
    //Por si hay un error al cargar el XML.
    if (!result) {
        std::cerr << "Error al cargar XML: " << result.description() << "\n";
        return {};
    }

    Tree* tree = new Tree(); //creamos el arbol

    pugi::xml_node root = doc.child("root");
    tree->insert(nullptr,"root","catalogo de libros"); // definimos la raiz
    int i=0;
    //Vamos añadiendo los libros revisando entre las etiquetas <GoodreadsResponse><book> ... <book><GoodreadsResponse>
    for (pugi::xml_node GRResponse : root.children("GoodreadsResponse")) {
        //if(i==2) break;
        pugi::xml_node bookNodo= GRResponse.child("book");
        añadirLibro(tree,bookNodo);
        i++;
    }
    return tree;
}