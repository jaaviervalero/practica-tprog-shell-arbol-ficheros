#pragma once
#include <string>
#include "nodo.h"
#include "directorio.h"
using namespace std;

class Fichero : public Nodo {
        int tamaño;
    public:
        Fichero(Directorio* padre, const string& nombre, int tamaño) : Nodo(nombre, padre), tamaño(tamaño) {}

        int getTamaño() const override { return tamaño; }
        void newTamaño(int sz) { tamaño = sz;}
        virtual bool isFichero() const override { return true; }

};