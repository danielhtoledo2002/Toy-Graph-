#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <time.h>

struct Conections {
    std::string son_name;
    int coste;
};

struct Step {
    Conections name;
    std::shared_ptr<Step> dad;
    int suma;
    Step(std::string);
    Step(std::string, std::shared_ptr<Step>, int );
};

Step::Step(std::string head) {
    dad = nullptr;
    name.son_name = head;
    suma = 0;
}

Step::Step(std::string head, std::shared_ptr<Step> papa, int x) {
    dad = papa;
    name.son_name = head;
    suma = x ;
}

std::vector<std::string> clone_vector(std::vector<std::string> copy_vector) {
    std::vector<std::string> copy;
    std::vector<std::string>::iterator iter;
    for (iter = copy_vector.begin(); iter < copy_vector.end(); iter++) {
        copy.push_back(*iter);
    }
    return copy;
}

std::shared_ptr<Step> busqueda_ancho (std::string head,std::map<std::string , std::vector<Conections >> graph, std::string arrival){
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string>history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()){
        general_level.push_back(nodo);
    }

    while(!general_level.empty()){
        nodo = general_level.front();
        general_level.pop_front();
        if (nodo->name.son_name == arrival){
            std::cout<<"Nodo encontrado"<< std::endl;
            return nodo;
        } else{

            auto hijos = graph[nodo->name.son_name];
            for(auto & hijo: hijos ){
                if (!history.contains( hijo.son_name)) {
                    history.insert(hijo.son_name);
                    general_level.push_back(std::make_shared<Step>(hijo.son_name, nodo,hijo.coste));
                }
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Step>djkstrap(std::string head, std::map<std::string, std::vector<Conections>> graph,std::string arrival) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true) {
        std::shared_ptr<Step> nod ;
        nod = nullptr;
        for (auto &i : general_level) {
            if (!graph[(i)->name.son_name].empty() || i->name.son_name == arrival) {

                if(nod == nullptr){
                    nod = i;
                }else{
                    if(i->suma < nod->suma){
                        nod = i;
                    }
                }
            }
        }
        if(nod == nullptr){
            return nullptr;
        }

        nodo = nod;
        general_level.remove(nod);
        // general_level.push_back(std::make_shared<Step>(nod->name, nod, nod->suma));

        auto hijos = graph[nodo->name.son_name];

        for (auto &hijo : hijos) {

            general_level.push_back(std::make_shared<Step>(hijo.son_name, nodo, (hijo.coste + nodo->suma)));
        }

        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        }
    }
    return nullptr;
}

std::shared_ptr<Step> busqueda_profundo (std::string head,std::map<std::string , std::vector<Conections >> graph, std::string arrival){
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string>history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()){
        general_level.push_back(nodo);
    }

    while(!general_level.empty()){

        nodo = general_level.back();
        general_level.pop_back();
        if (nodo->name.son_name == arrival){
            std::cout<<"Nodo encontrado"<< std::endl;
            return nodo;
        } else{

            auto hijos = graph[nodo->name.son_name];
            for(auto & hijo: hijos ){
                general_level.push_back(std::make_shared<Step>(hijo.son_name, nodo,hijo.coste));

            }
        }
    }
    return nullptr;
}

int main() {

    std::vector<Conections> connections;
    std::map<std::string, std::vector<Conections>> graph;
    std::list<std::shared_ptr<Step>> list;

    // First level
    connections = {{"Timisoara", 118}, {"Zerind", 100}, {"Sibiu", 140}};
    graph["Arad"] = connections;
    connections.clear();
    // Second level
    connections = {{"Lugoj", 111}};
    graph["Timisoara"] = connections;
    connections.clear();
    connections = {{"Oradera", 71}};
    graph["Zerind"] = connections;
    connections.clear();
    connections = {{"Fragaras", 99}, {"Rimnicu Viicea", 80}};
    graph["Sibiu"] = connections;
    connections.clear();
    // Third level
    connections = {{"Mehadia", 70}};
    graph["Lugoj"] = connections;
    connections.clear();
    connections = {{"Sibiu", 151}};
    graph["Oradera"] = connections;
    connections.clear();
    connections = {{"Bucharest", 211}};
    graph["Fragaras"] = connections;
    connections.clear();
    connections = {{"Pitesti",97}, {"Craiova", 146}};
    graph["Rimnicu Viicea"] = connections;
    connections.clear();
    // Four level
    connections = {{"Drobeta", 75}};
    graph["Mehadia"] = connections;
    connections.clear();
    connections = {{"Glurgiu", 90}, {"Urziceni", 85}};
    graph["Bucharest"] = connections;
    connections.clear();
    connections = {{"Bucharest", 101}};
    graph["Pitesti"] = connections;
    connections.clear();
    connections = {{"Pitesti", 138}};
    graph["Craiova"] = connections;
    connections.clear();
    // Five level
    connections = {{"Craiova", 120}};
    graph["Drobeta"] = connections;
    connections.clear();
    connections = {};
    graph["Glurgiu"] = connections;
    connections.clear();
    connections = {{"Hirsova", 98}, {"Vaslui", 142}};
    graph["Urziceni"] = connections;
    connections.clear();
    // Six Level

    connections = {{"Iasi", 92}};
    graph["Vaslui"] = connections;
    connections.clear();
    // Seven Level
    connections = {{"Eforie", 86}};
    graph["Hirsova"] = connections;
    connections.clear();
    connections = {{"Neamt", 87}};
    graph["Iasi"] = connections;
    connections.clear();
    // Nine Level
    connections = {};
    graph["Neamt"] = connections;
    connections.clear();
    auto x = busqueda_ancho("Sibiu", graph, "Bucharest");
    while (x != nullptr) {
        list.push_front(x);
        x = x->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> "<<resultado->suma<<" ";
    }
    list.clear();
    std::cout<<""<<std::endl;
    auto z = djkstrap("Arad",graph, "Neamt");
    while (z != nullptr){
        list.push_front(z);
        z = z->dad;
    }
    for (auto & resultado:list) {
        std::cout<<resultado->name.son_name<<" ->";
    }

    list.clear();
    std::cout<<""<<std::endl;
    std::cout<<"Last method"<<std::endl;
    auto s = busqueda_profundo("Arad",graph, "Neamt");
    if (s == nullptr){
        std::cout<<"el resultado no existe"<<std::endl;

    } else {
        while (s != nullptr) {
            list.push_front(s);
            s = s->dad;
        }
        for (auto &resultado: list) {
            std::cout << resultado->name.son_name << " ->";
        }
    }
}
























/*
 * beta method
std::shared_ptr<Step>find_the_first_path(std::string head, std::string aririval, std::map<std::string, std::vector<Conections>> graph){
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));

    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true){
        nodo = general_level.back();
        srand ( time(NULL) );
        if(graph[nodo->name.son_name].empty() && nodo->name.son_name != aririval){
            while(graph[nodo->dad->name.son_name].size() > 1){
                nodo = nodo->dad;
            }

        }

        general_level.pop_back();

        if (nodo->name.son_name == aririval){
            return nodo;
        }
        else{
            auto hijos = graph[nodo->name.son_name];
            if(hijos.size() > 1){

                auto hijo = hijos[(rand() % hijos.size())];

                general_level.push_back(std::make_shared<Step>(hijo.son_name, nodo,hijo.coste));
            }else{
                if (!hijos.empty()){
                    general_level.push_back(std::make_shared<Step>(hijos[0].son_name, nodo,hijos[0].coste));
                } else{
                    if(graph[nodo->name.son_name].empty() && nodo->name.son_name != aririval){
                        while(graph[nodo->dad->name.son_name].size() > 1){
                            nodo = nodo->dad;
                        }

                    }
                }

            }
        }

    }
    return nullptr;

}
 */
