# Estructura-de-datos-XML
En primer lugar, se debe descomprimir books_xml.zip y la carpeta resultante debe ser llamada books_xml donde
dentro de ella están todos los XML.
Luego se debe ejecutar en la terminal: python3 unir_xml.py
Ahora se tendrá un archivo arbol.xml que contiene todos los XML juntos y es el que procesará C++ para construir el arbol.
compilacion: g++ main.cpp construir_arbol.cpp pugixml.cpp Tree.cpp -o main