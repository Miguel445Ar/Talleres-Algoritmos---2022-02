#ifndef __GRAPUW_HPP__
#define __GRAPUW_HPP__

#include <iostream>
#include <vector>
#include <list>

template<class T = int>
class UndirectedAndWeightedGraph {
    struct Vertice {
        long id;
        T valor;
        std::list<std::pair<long,long>> listaDeAdyacencia;
    };
    std::vector<Vertice*> g;
public:
    UndirectedAndWeightedGraph(size_t cantidadVertices) {
        g.resize(cantidadVertices);
        for(int i = 0; i < cantidadVertices; ++i) {
            g[i] = new Vertice{i};
        }
    }
    void addAdyacencia(long v, long u, long w){
        if(esUnVerticeValido(v) == false || esUnVerticeValido(u) == false)
            throw "Uno ambos vertices no son validos";
        // v -> u
        g[v]->listaDeAdyacencia.push_back(std::pair<long,long>(u,w));
        // v <- u
        g[u]->listaDeAdyacencia.push_back(std::pair<long,long>(v,w));
    }
    void addValor(long v,T valor) {
        g[v]->valor = valor;
    }
    void display() {
        for(Vertice* v: g) {
            std::cout << "\n " << v->id << ": ";
            for(auto u: v->listaDeAdyacencia){
                std::cout << "(" << u.first << ", " << u.second << ") ";
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