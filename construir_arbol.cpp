
#include <vector>
#include <string>
#include "pugixml.hpp"
#include "clases.hpp"
/// @brief Funcion que toma el xml sobre un nodo que contiene los datos de un similarbook obteniendo los datos de interes
/// @param nodo xml que contiene los datos de un similar_book
/// @return Struct que tiene los datos de interes
SimilarBook parsear_similar_book(pugi::xml_node nodo) {

    SimilarBook sb;
    sb.title = nodo.child_value("title");
    sb.isbn = nodo.child_value("isbn");
    std::string year  = nodo.child_value("publication_year");
    sb.publication_year = year.empty() ? 0 : std::stoi(year); //si no reporta fecha de publicacion, lo dejamos como 0.
    return sb;
}
/// @brief Funcion que toma el xml sobre un libro, obteniendo los datos de interes. Ademas, usa parsear_similar_book() para guardar los libros similares.
/// @param nodo xml que contiene los datos de un book
/// @return Puntero a un Book
Book* parsear_libro(pugi::xml_node nodo) {
    Book* libro = new Book();
    libro->id          = nodo.child_value("id");
    libro->title       = nodo.child_value("title");

    libro->isbn        = nodo.child_value("isbn");
    libro->language    = nodo.child_value("language_code");
    libro->description = nodo.child_value("description");

    std::string year   = nodo.child_value("publication_year");
    libro->publication_year = year.empty() ? 0 : std::stoi(year);

    std::string rating = nodo.child_value("average_rating");
    libro->average_rating = rating.empty() ? 0.0f : std::stof(rating);

    std::string pages  = nodo.child_value("num_pages");
    libro->num_pages   = pages.empty() ? 0 : std::stoi(pages);

    // Parsear similar_books
    pugi::xml_node similar = nodo.child("similar_books");
    //verificamos que similar_books tenga hijos (que hayan libros similares)
    if (!similar.empty()) {
        for (pugi::xml_node sb : similar.children("book")) {
            libro->similar_books.push_back(parsear_similar_book(sb));
        }
    }
    return libro;
}
/// @brief Funcion que usa las funciones de parseo anteriores para construir el arbol, tomamos cada nodo GoodreadsResponse para acceder a cada book.
/// @param ruta dirrecion del archivo del xml de arbol de todos los libros
/// @return Arbol donde sus hijos son los libros
Arbol construir_arbol(const std::string& ruta) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(ruta.c_str());
    
    if (!result) {
        std::cerr << "Error al cargar XML: " << result.description() << "\n";
        return {};
    }

    Arbol arbol;
    pugi::xml_node root = doc.child("root");
    for (pugi::xml_node GRResponse : root.children("GoodreadsResponse")) {
        pugi::xml_node nodo= GRResponse.child("book");
    
        arbol.libros.push_back(parsear_libro(nodo));

    }
    return arbol;
}