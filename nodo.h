#pragma once
#include <string>
#include <memory>

using namespace std;

class Directorio;

class Nodo {
    protected:
        string nombre;
        Directorio* padre;
    public:
        Nodo(const string& nombre, Directorio* padre) : nombre(nombre), padre(padre) {}
        virtual ~Nodo() {}

        virtual string getNombre() const { return nombre; }
        virtual Directorio* getPadre() const { return padre; }
        virtual int getTamaño() const = 0;

        virtual bool isDirectorio() const { return false; }
        virtual bool isFichero() const { return false; }
        virtual bool isEnlace() const { return false; }
};