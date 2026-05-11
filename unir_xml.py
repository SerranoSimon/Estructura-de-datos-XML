import xml.etree.ElementTree as ET
import glob

def exportar_xml_unificado(directorio, ruta_salida):
    """funcion que toma todos los archivos en la carpeta books_xml, los junta en un solo xml 
    y lo escribe en arbol.xml"""
    raiz = ET.Element("root")
    archivos=glob.glob(f"{directorio}/*.xml")
    for ruta in archivos:
        tree = ET.parse(ruta)
        raiz.append(tree.getroot())
    ET.ElementTree(raiz).write(ruta_salida, encoding="utf-8", xml_declaration=True)

exportar_xml_unificado("books_xml", "arbol.xml")