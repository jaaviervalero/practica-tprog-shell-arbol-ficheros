#pragma once
#include <string>
#include <vector>
#include <memory>
#include "nodo.h"
using namespace std;

class Directorio : public Nodo {
        vector<shared_ptr<Nodo>> hijos;
    public:
        
        Directorio(Directorio* padre, const string& nombre) : Nodo(nombre, padre) {}
        ~Directorio() {}
        
        vector<shared_ptr<Nodo>>& getHijos() { return hijos; }
        
        void agregarHijo(shared_ptr<Nodo> hijo) { hijos.push_back(hijo); }

        shared_ptr<Nodo> buscarHijo(const string& nombre) {
            for (const auto& hijo : hijos) {
                if (hijo->getNombre() == nombre) {
                    return hijo;
                }
            }
            return nullptr;
        }

        int getTamaño() const override {
            int tamaño = 0;
            for (const auto& hijo : hijos) {
                tamaño += hijo->getTamaño();
            }
            return tamaño;
        }

        void borrarHijo(const string& nombre_hijo) {
            for (size_t i = 0; i < hijos.size(); i++) {
                if (hijos[i]->getNombre() == nombre_hijo){
                    hijos.erase(hijos.begin() + i);
                    return;
                }
            }
        }

        virtual bool isDirectorio() const  override { return true; }  
};