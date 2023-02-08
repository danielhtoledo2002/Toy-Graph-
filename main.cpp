#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <memory>

struct Conections{
    std::string son_name;
    int coste ;
};

struct Step{
    Conections name;
    std::shared_ptr<Step>dad;
    Step(std::string);
    Step(std::string,std::shared_ptr<Step>);
};

Step::Step(std::string head) {
    dad = nullptr;
    name.son_name = head;
}

Step::Step(std::string head, std::shared_ptr<Step> papa) {
    dad = papa;
    name.son_name = head;
}

std::vector<std::string> clone_vector (std::vector<std::string>copy_vector){
    std::vector<std::string> copy;
    std::vector<std::string>::iterator iter;
    for (iter = copy_vector.begin(); iter < copy_vector.end() ; iter++) {
        copy.push_back(* iter);
    }
    return copy;
}
std::shared_ptr<Step> find_path (std::string head,std::map<std::string , std::vector<Conections >> graph, std::string arrival){
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string>history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    std::vector<int>valores;
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
            int x = 0;
            for (auto & hijo:hijos){
                valores.push_back(hijo.coste);
                if(hijo.coste > x){
                    x = hijo.coste;
                }
            }
            
            for(auto & hijo: hijos ){
                if (!history.contains( hijo.son_name)) {
                    history.insert(hijo.son_name);
                    general_level.push_back(std::make_shared<Step>(hijo.son_name, nodo));
                }
            }
        }
    }
    return nullptr;
}
int main() {

    std::vector<Conections>connections;
    std::map<std::string , std::vector<Conections >> graph;
    std::list<std::shared_ptr<Step>> list;
    // First level
    connections = {{"Timisoara",118}, {"Zerind", 100}, {"Sibiu", 140}};
    graph["Arad"] = connections;
    connections.clear();
    // Second level
    connections = {{"Lugoj", 111}};
    graph["Timisorta"] = connections;
    connections.clear();
    connections = {{"Oradera", 71}};
    graph["Zerid"] = connections;
    connections.clear();
    connections = {{"Fragaras", 99}, {"Rimnicu Viicea",97 }};
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
    connections = {{"Pitesti", 97}, {"Craiova",146}};
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
    connections = {{"Craiova",120}};
    graph["Drobeta"] = connections;
    connections.clear();
    connections = {};
    graph["Glurgiu"] = connections;
    connections.clear();
    connections = {{"Hirsova", 98}, {"Vaslui",142 }};
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
    auto x = find_path("Arad",graph, "Neamt");
    while (x != nullptr){
        list.push_front(x);
        x = x->dad;
    }
    for (auto & resultado:list) {
        std::cout<<resultado->name.son_name<<" ->";
    }
}
