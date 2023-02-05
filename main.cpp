#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <memory>
struct Step{
    std::string name;
    std::shared_ptr<Step>dad;
    Step(std::string);
    Step(std::string,std::shared_ptr<Step>);
};

Step::Step(std::string head) {
    dad = nullptr;
    name = head;
}

Step::Step(std::string head, std::shared_ptr<Step> papa) {
    dad = papa;
    name = head;
}

std::vector<std::string> clone_vector (std::vector<std::string>copy_vector){
    std::vector<std::string> copy;
    std::vector<std::string>::iterator iter;
    for (iter = copy_vector.begin(); iter < copy_vector.end() ; iter++) {
        copy.push_back(* iter);
    }
    return copy;
}
std::shared_ptr<Step> find_path (std::string head,std::map<std::string , std::vector<std::string >> graph, std::string arrival){
    std::list<std::shared_ptr<Step>> general_level;
    std::map<std::string , std::vector<std::string >>::iterator ite_map ;
    std::vector<std::string>::iterator ite_sec_vec;
    std::vector<std::string>::iterator iter;
    std::set<std::string>history;

    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()){
        general_level.push_back(nodo);
    }

    while(!general_level.empty()){
        nodo = general_level.front();
        general_level.pop_front();
        if (nodo->name == arrival){
            std::cout<<"Nodo encontrado"<< std::endl;
            return nodo;
        } else{

            auto hijos = graph[nodo->name];
            for(auto & hijo: hijos ){
                if (!history.contains( hijo)) {
                    history.insert(hijo);
                    general_level.push_back(std::make_shared<Step>(hijo, nodo));
                }
            }
        }
    }
    return nullptr;
}
int main() {
    std::vector<std::string>connections;
    std::map<std::string , std::vector<std::string >> graph;
    std::list<std::shared_ptr<Step>> list;
    // First level
    connections = {"Timisorta", "Zerid", "Sibiu"};
    graph["Arad"] = connections;
    connections.clear();
    // Second level
    connections = {"Lugoj"};
    graph["Timisorta"] = connections;
    connections.clear();
    connections = {"Oradera"};
    graph["Zerid"] = connections;
    connections.clear();
    connections = {"Fragaras", "Rimnicu Viicea"};
    graph["Sibiu"] = connections;
    connections.clear();
    // Third level
    connections = {"Mehadia"};
    graph["Lugoj"] = connections;
    connections.clear();
    connections = {"Sibiu"};
    graph["Oradera"] = connections;
    connections.clear();
    connections = {"Bucharest"};
    graph["Fragaras"] = connections;
    connections.clear();
    connections = {"Pitesti", "Craiova"};
    graph["Rimnicu Viicea"] = connections;
    connections.clear();
    // Four level
    connections = {"Drobeta"};
    graph["Mehadia"] = connections;
    connections.clear();
    connections = {"Glurgiu", "Urziceni"};
    graph["Bucharest"] = connections;
    connections.clear();
    connections = {"Bucharest"};
    graph["Pitesti"] = connections;
    connections.clear();
    connections = {"Pitesti"};
    graph["Craiova"] = connections;
    connections.clear();
    // Five level
    connections = {"Craiova"};
    graph["Drobeta"] = connections;
    connections.clear();
    connections = {};
    graph["Glurgiu"] = connections;
    connections.clear();
    connections = {"Hirsova", "Vaslui"};
    graph["Urziceni"] = connections;
    connections.clear();
    // Six Level
    connections = {"Eforie"};
    graph["Hirsova"] = connections;
    connections.clear();
    connections = {"Iasi"};
    graph["Vaslui"] = connections;
    connections.clear();
    // Seven Level
    connections = {};
    graph["Hirsova"] = connections;
    connections.clear();
    connections = {"Neamt"};
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
        std::cout<<resultado->name<<" ->";
    }
}
