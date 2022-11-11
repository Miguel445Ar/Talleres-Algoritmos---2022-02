#include <iostream>
#define WEIGHTED
#include "UndirectedGraph.hpp"

int main() {
    UndirectedGraph<int> g(10);
    g.add(0,1,5);
    g.display();
    g.dfs(0);
    return 0;
}