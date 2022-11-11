#ifndef __GRAPU_HPP__
#define __GRAPU_HPP__

#include <iostream>
#include <vector>
#include <list>

template<class T = int>
class UndirectedGraph {
    struct Vertice {
        long id;
        T valor;
        std::list<long> listaDeAdyacencia;
    };
    std::vector<Vertice*> g;
public:
    UndirectedGraph(size_t cantidadVertices) {
        g.resize(cantidadVertices);
        for(int i = 0; i < cantidadVertices; ++i) {
            g[i] = new Vertice{i};
        }
    }
    void addAdyacencia(long v, long u){
        if(esUnVerticeValido(v) == false || esUnVerticeValido(u) == false)
            throw "Uno ambos vertices no son validos";
        // v -> u
        g[v]->listaDeAdyacencia.push_back(u);
        // v <- u
        g[u]->listaDeAdyacencia.push_back(v);
    }
    void addValor(long v,T valor) {
        g[v]->valor = valor;
    }
    void display() {
        for(Vertice* v: g) {
            std::cout << "\n " << v->id << ": ";
            for(long u: v->listaDeAdyacencia){
                std::cout << u << " ";
            }
            std::cout << "\n";
        }
    }
private:
    bool esUnVerticeValido(long v) {
        return v >= 0 && v <= g.size() - 1;
    }
};

#endif