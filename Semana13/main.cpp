#include <iostream>
//#define WEIGHTED
//#include "UndirectedGraph.hpp"
#include "GraphUndirected.hpp"
#include "GraphDirected.hpp"
#include "UndirectedWeightedGraph.hpp"
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

void readFile() {
    DirectedGraph<int> graph(4);
    std::ifstream arch("input.txt");
    std::string line;
    for(int i = 0;std::getline(arch,line);++i) {
        std::stringstream s(line);
        std::string aux;
        while(s >> aux) {
            long v = i;
            long u = std::stol(aux);
            graph.addAdyacencia(v,u);
        }
    }
    graph.display();
    arch.close();
}

int main() {
    /*UndirectedGraph<> g(10);
    g.add(0,1,5);
    g.display();
    g.dfs(0);*/

    // Grafo no dirigido
    UndirectedGraph<int> graph(4);
    graph.addAdyacencia(0,1);
    graph.addAdyacencia(0,2);
    graph.addAdyacencia(1,2);
    graph.addAdyacencia(1,3);
    //graph.display();
    readFile();

    UndirectedAndWeightedGraph<int> g(4);
    g.addAdyacencia(0,1,3);
    g.addAdyacencia(0,2,5);
    g.addAdyacencia(1,2,8);
    g.addAdyacencia(1,3,4);
    g.display();
    return 0;
}