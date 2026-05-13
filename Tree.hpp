#include <iostream>
#include <vector>
#include <string>

/// @brief Struct que representa un libro similar, contiene los 3 atributos de interes.
struct SimilarBook {
    std::string title;
    std::string isbn;
    int publication_year;
};
/// @brief Struct que representa un libro con todos los atributos de interes, contiene un vector con los libros similares.
struct Book {
    std::string id;
    std::string title;
    std::string isbn;
    int publication_year;
    std::string language;
    std::string description;
    float average_rating;
    int num_pages;
    std::vector<SimilarBook> similar_books;
};
/// @brief Struct que representa un arbol, donde sus hijos son todos los libros.
struct Arbol {
    std::vector<Book*> libros;  // hijos de la raiz
    ~Arbol() {
        for (Book* libro : libros) {
            delete libro;
        }
    }
};


class Tree{

    private:
    public:
    struct Node {
        std::string tag;
        std::string text;
        Node* parent;
        std::vector<Node*> children;
        Node(std::string t, std::string txt, Node* p = nullptr);
        };
        Node* rootNode;
        int treeSize;
        int cant_libros;
    Tree();

    bool isEmpty();
    int size();
    int getCantLibros();
    Node* root();
    void imprimir(Node* nodo, int nivel = 0);
    void listar(Node* nodo);


    Node* insert(Node* padre, std::string t, std::string txt); //retorna el nodo insertado
    

    
};