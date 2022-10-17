#include <iostream>
#include <string>
#include <unordered_map>
#include "HashTable.hpp"

struct Persona {
    int dni;
    Persona(int dni): dni(dni) {}
    Persona() {}
};

int main() {
    /*std::unordered_map<std::string, int> ht;
    ht.insert(std::pair<std::string,int>("estaEsUnaKey",10));
    ht["nvjfvnjfv"] = 67;
    for(auto [k, v]: ht) {
        std::cout << v << "\n";
    }*/
    HashTable<Persona> ht(10);
    ht.insert("estaEsUnaKey",Persona(5066));
    ht["key"] = Persona(545646);
    ht.display([](Persona v) -> void { std::cout << v.dni;});
    std::cout << "\nGetting a copy: " << ht.getCopy("key").dni;
    return 0;
}