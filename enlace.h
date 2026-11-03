#pragma once
#include <string>
#include <memory>
#include "nodo.h"
#include "directorio.h"
using namespace std;

class Enlace : public Nodo {
    private:
        shared_ptr<Nodo> destino;
    public:
        Enlace(Directorio* padre, const string& nombre, shared_ptr<Nodo> destino) : Nodo(nombre, padre), destino(destino) {}
        shared_ptr<Nodo> getDestino() const { return destino; }
        int getTamaño() const override { return destino->getTamaño(); }
        virtual bool isEnlace() const override { return true; }

};