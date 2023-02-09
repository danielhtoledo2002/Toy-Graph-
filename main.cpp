#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stack>
#include <vector>

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

std::shared_ptr<Step> find_path (std::string head,std::map<std::string , std::vector<Conections >> graph, std::string arrival){
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

std::shared_ptr<Step>search_by_cost(std::string head, std::map<std::string, std::vector<Conections>> graph,std::string arrival) {
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
std::shared_ptr<Step>find_the_first_path(std::string head, std::string aririval, std::map<std::string, std::vector<Conections>> graph){
    
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }



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
    connections = {{"Eforie", 98}};
    graph["Hirsova"] = connections;
    connections.clear();
    connections = {{"Iasi", 92}};
    graph["Vaslui"] = connections;
    connections.clear();
    // Seven Level
    connections = {};
    graph["Hirsova"] = connections;
    connections.clear();
    connections = {{"Neamt", 87}};
    graph["Iasi"] = connections;
    connections.clear();
    // Nine Level
    connections = {};
    graph["Neamt"] = connections;
    connections.clear();
    auto x = search_by_cost("Sibiu", graph, "Bucharest");
    while (x != nullptr) {
        list.push_front(x);
        x = x->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> "<<resultado->suma<<" ";
    }
    list.clear();
    std::cout<<""<<std::endl;
    auto z = find_path("Arad",graph, "Neamt");
    while (z != nullptr){
        list.push_front(z);
        z = z->dad;
    }
    for (auto & resultado:list) {
        std::cout<<resultado->name.son_name<<" ->";
    }
}
