#include <iostream>
#include <vector>
#include <string>


struct SimilarBook {
    std::string title;
    std::string isbn;
    int publication_year;
};

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

struct Arbol {
    std::vector<Book*> libros;  // hijos del root
};