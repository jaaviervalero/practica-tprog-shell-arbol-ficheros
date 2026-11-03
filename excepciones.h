#pragma once
#include <string>
#include <stdexcept>

using namespace std;

class arbol_ficheros_error : public runtime_error {
public:
    arbol_ficheros_error(const string& msg) : runtime_error(msg) {}
};

class ruta_inexistente_error : public arbol_ficheros_error {
public:
    ruta_inexistente_error() 
        : arbol_ficheros_error("Error: La ruta especificada no existe.") {}
};

class no_es_directorio_error : public arbol_ficheros_error {
public:
    no_es_directorio_error(const string& nombre) 
        : arbol_ficheros_error("Error: '" + nombre + "' no es un directorio.") {}
};

class elemento_existente_error : public arbol_ficheros_error {
public:
    elemento_existente_error(const string& nombre) 
        : arbol_ficheros_error("Error: Ya existe un elemento con el nombre '" + nombre + "'.") {}
};

class operacion_invalida_error : public arbol_ficheros_error {
public:
    operacion_invalida_error(const string& mensaje) 
        : arbol_ficheros_error(mensaje) {}
};