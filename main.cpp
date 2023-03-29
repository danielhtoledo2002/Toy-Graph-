#include "lib.hpp"

int main() {


    std::vector<Conections> connections;
    std::map<std::string, std::vector<Conections>> graph;
    std::list<std::shared_ptr<Step>> list;
    std::map<std::string, std::vector<float>> heuristic;
    heuristic["Arad"] = {-8, 3};
    heuristic["Zerind"] = {-7.5, 4.8};
    heuristic["Oradera"] = {-6.5, 6.2};
    heuristic["Sibiu"] = {-3.5, 1.8};
    heuristic["Fragaras"] = {0.3, 1.5};
    heuristic["Timisoara"] = {-8, 0};
    heuristic["Lugoj"] = {-5.2, -1.2};
    heuristic["Mehadia"] = {-5.1, -3.};
    heuristic["Drobeta"] = {-5.4, -4.4};
    heuristic["Craiova"] = {-2, -5};
    heuristic["Pitesti"] = {1, 2};
    heuristic["Rimnicu Viicea"] = {-2.5, 0};
    heuristic["Bucharest"] = {4, -3};
    heuristic["Giurgiu"] = {3, -5.5};
    heuristic["Urziceni"] = {6, -2.3};
    heuristic["Hirsova"] = {9, -2.2};
    heuristic["Eforie"] = {10, -4.4};
    heuristic["Vasiui"] = {8.2, 1.3};
    heuristic["Iasi"] = {6.9, 3.9};
    heuristic["Neamt"] = {4.1, 5};
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
    connections = {{"Pitesti", 97}, {"Craiova", 146}};
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

    list.clear();
    std::cout << "" << std::endl;
    auto u = greddy_search("Arad", graph, "Bucharest", heuristic);

    while (u != nullptr) {
        list.push_front(u);
        u = u->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> " << resultado->suma << " ";
    }
    list.clear();
    std::cout << "" << std::endl;

    auto ww = a_star_method("Arad", graph, "Bucharest", heuristic);

    while (ww != nullptr) {
        list.push_front(ww);
        ww = ww->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> " << resultado->suma << " ";
    }

    
    list.clear();
    std::cout << "" << std::endl;

    
    list.clear();
    std::cout << "" << std::endl;

    auto www = weight_a_star_method("Arad", graph, "Bucharest", heuristic, 1.3);

    while (www != nullptr) {
        list.push_front(www);
        www = www->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> " << resultado->suma << " ";
    }

    
    list.clear();
    std::cout << "" << std::endl;


    auto wwww = beam_search("Arad", graph, "Bucharest", heuristic, 2);

    while (wwww != nullptr) {
        list.push_front(wwww);
        wwww = wwww->dad;
    }
    for (auto &resultado : list) {
        std::cout << resultado->name.son_name << " -> " ;
    }

    
    list.clear();
    std::cout << "" << std::endl;
}

