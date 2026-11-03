#pragma once
#include  <sstream>
#include <string>
#include <memory>
#include <iomanip>
#include <vector>
#include <iostream>

#include "enlace.h"
#include "directorio.h"
#include "fichero.h"
#include "excepciones.h"

using namespace std;


class Shell{
        vector<shared_ptr<Directorio>> actual;
        shared_ptr<Directorio> raiz;
        shared_ptr<Nodo> resolverRuta(string path, vector<shared_ptr<Directorio>>& ruta_navegada, bool resolver_ultimo = true) {
            ruta_navegada = actual; 
            
            if (path.length() > 0 && path[0] == '/') {
                ruta_navegada.clear();
                ruta_navegada.push_back(raiz);
            }

            shared_ptr<Nodo> ultimo_nodo = ruta_navegada.back();
            stringstream ss(path);
            string token;

            while (getline(ss, token, '/')) {
                if (token.empty() || token == ".") continue;
                
                if (token == "..") {
                    if (ruta_navegada.size() > 1) ruta_navegada.pop_back();
                    ultimo_nodo = ruta_navegada.back();
                    continue;
                }

                shared_ptr<Nodo> buscado = ruta_navegada.back()->buscarHijo(token);
                if (buscado == nullptr) return nullptr; 
                
                
                if (buscado->isEnlace() && (!ss.eof() || resolver_ultimo)){ 
                    buscado = static_pointer_cast<Enlace>(buscado)->getDestino();
                }
                
                ultimo_nodo = buscado;

                if (buscado->isDirectorio()) {
                    ruta_navegada.push_back(static_pointer_cast<Directorio>(buscado));
                } else {
                    string sobrante;
                    if (getline(ss, sobrante, '/')) return nullptr; 
                    return buscado;
                }
            }
            return ultimo_nodo;
        }

        shared_ptr<Nodo> getNodo(string path, bool resolver_ultimo = true) {
            vector<shared_ptr<Directorio>> ruta_basura; 
            return resolverRuta(path, ruta_basura, resolver_ultimo);
        }
        
        public:
        Shell(){
            raiz = make_shared<Directorio>(nullptr, "");
            actual.push_back(raiz);
        }
        ~Shell() {}


        string pwd(){
            ostringstream oss;

            if (actual.size() == 1) return "/";

            for (const auto& dir : actual){
                if(dir->getPadre() == nullptr) continue;
                oss << "/" << dir->getNombre();
            }
            return oss.str();
        }

        string ls() {
            ostringstream oss;
            vector<shared_ptr<Nodo>> hijos = actual.back()->getHijos();

            for (const auto& hijo : hijos){
                oss << hijo->getNombre() << endl;
            }
            return oss.str();

        }

        string du(){
            ostringstream oss;           
            vector<shared_ptr<Nodo>> hijos = actual.back()->getHijos();

            for (const auto& hijo : hijos){
                oss<< hijo->getNombre() << " " << hijo->getTamaño() << endl;
            }
            return oss.str();
        }

        void vi (string name, int size){
            shared_ptr<Nodo> fich = actual.back()->buscarHijo(name);

            if (fich == nullptr){
                auto newFich = make_shared<Fichero>(actual.back().get(), name, size);
                actual.back()->agregarHijo(shared_ptr<Nodo>(newFich));
            } else {
                if (fich->isFichero()) static_pointer_cast<Fichero>(fich)->newTamaño(size);
                else throw operacion_invalida_error("Error: '" + name + "' ya existe y no es un fichero." );
            }
        }

        void mkdir(string name){
            if (actual.back()->buscarHijo(name) != nullptr) {
                throw elemento_existente_error(name);
            }
            auto newDir = make_shared<Directorio>(actual.back().get(), name);
            actual.back()->agregarHijo(newDir);
        }

        void cd(string path){
            vector<shared_ptr<Directorio>> temporal = actual;
            
            shared_ptr<Nodo> destino = resolverRuta(path, temporal);
            
            if (destino == nullptr) {
                throw ruta_inexistente_error();
            }

            if (!destino->isDirectorio()) {
                throw no_es_directorio_error(destino->getNombre());
            }
            actual = temporal;
        }
        

        int stat(string path) {
            shared_ptr<Nodo> nodo = getNodo(path);
            
            if (nodo == nullptr) {
                throw ruta_inexistente_error();
            }
            
            return nodo->getTamaño();
        }

        void ln(string path, string name) {
            if (actual.back()->buscarHijo(name) != nullptr) {
                throw elemento_existente_error(name);
            }

            shared_ptr<Nodo> destino = getNodo(path);
            if (destino == nullptr) {
                throw ruta_inexistente_error();
            }

            auto nuevoEnlace = make_shared<Enlace>(actual.back().get(), name, destino);
            actual.back()->agregarHijo(nuevoEnlace);
        }

        void rm(string path) {
            shared_ptr<Nodo> nodo_a_borrar = getNodo(path, false);
            
            if (nodo_a_borrar == nullptr) {
                throw ruta_inexistente_error();
            }
            Directorio* padre = nodo_a_borrar->getPadre();
            
            if (nodo_a_borrar->getPadre() == nullptr) {
                throw operacion_invalida_error("Error: No se puede borrar el directorio raiz.");
            }
            padre->borrarHijo(nodo_a_borrar->getNombre());
            
        }

};