#ifndef __UNDIRECTED_GRAPH__
#define __UNDIRECTED_GRAPH__

#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include <array>

template<class T = int>
class UndirectedGraph {
public:
    UndirectedGraph(size_t size) {
        _arr.resize(size);
        for(long i = 0; i < size; ++i)
            _arr[i] = new Vertex{i};
    }
    #ifndef WEIGHTED
        void add(long v, long u) {
            Vertex* v_i = _arr[v];
            Vertex* v_u = _arr[u];
            v_i->adjl.push_back(v_u);
            v_u->adjl.push_back(v_i);
        }
    #endif
    #ifdef WEIGHTED
        void add(long v, long u, long w) {
            Vertex* v_i = _arr[v];
            Vertex* v_u = _arr[u];
            v_i->adjl.push_back(typename Vertex::Adj(v_u,w));
            v_u->adjl.push_back(typename Vertex::Adj(v_i,w));
        }
    #endif
    #ifndef WEIGHTED
        void display() {
            for(long i = 0; i < _arr.size(); ++i) {
                std::cout << "\n" << i << "\n";
                std::cout << "Adj: ";
                for(typename Vertex::Adj a: _arr[i]->adjl)
                    std::cout << a->id << " ";
                std::cout << "\n";
            }
        }
    #endif
    #ifdef WEIGHTED
        void display() {
            for(long i = 0; i < _arr.size(); ++i) {
                std::cout << "\n" << i << "\n";
                std::cout << "Adj: ";
                for(typename Vertex::Adj a: _arr[i]->adjl)
                    std::cout << "(" << a.first->id << ", " << a.second << ") ";
                std::cout << "\n";
            }
        }
    #endif
    void dfs(long start) {
        std::stack<Vertex*> s;
        std::vector<bool> visited(_arr.size(),false);
        s.push(_arr[start]);
        while (s.empty() == false) {
            Vertex* v = s.top();
            s.pop();
            if(visited[v->id])
                continue;
            visited[v->id] = true;
            #ifndef WEIGHTED
                for(Vertex* u: v->adjl)
                    s.push(v);
            #endif
            #ifdef WEIGHTED
                for(auto p: v->adjl)
                    s.push(p.first);
            #endif
        }
    }
private:
    struct Vertex {
        #ifdef WEIGHTED
            using Adj = std::pair<Vertex*,long>;
        #endif
        #ifndef WEIGHTED
            using Adj = Vertex*;
        #endif
        long id;
        T value;
        std::list<Adj> adjl;
    };
    std::vector<Vertex*> _arr;
};

#endif