#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <system_error>
#include <time.h>
#include <vector>

struct Conections {
    std::string son_name;
    int coste;
};

struct Step {
    Conections name;
    std::shared_ptr<Step> dad;
    float suma;
    Step(std::string);
    Step(std::string, std::shared_ptr<Step>, float);
};

Step::Step(std::string head) {
    dad = nullptr;
    name.son_name = head;
    suma = 0;
}

Step::Step(std::string head, std::shared_ptr<Step> papa, float x) {
    dad = papa;
    name.son_name = head;
    suma = x;
}


std::shared_ptr<Step>busqueda_ancho(std::string head,
               std::map<std::string, std::vector<Conections>> graph,
               std::string arrival) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (!general_level.empty()) {
        nodo = general_level.front();
        general_level.pop_front();
        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        } else {

            auto hijos = graph[nodo->name.son_name];
            for (auto &hijo : hijos) {
                if (!history.contains(hijo.son_name)) {
                    history.insert(hijo.son_name);
                    general_level.push_back(
                            std::make_shared<Step>(hijo.son_name, nodo, hijo.coste));
                }
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Step>
djkstrap(std::string head, std::map<std::string, std::vector<Conections>> graph,
         std::string arrival) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true) {
        std::shared_ptr<Step> nod;
        nod = nullptr;
        for (auto &i : general_level) {
            if (!graph[(i)->name.son_name].empty() || i->name.son_name == arrival) {

                if (nod == nullptr) {
                    nod = i;
                } else {
                    if (i->suma < nod->suma) {
                        nod = i;
                    }
                }
            }
        }
        if (nod == nullptr) {
            return nullptr;
        }

        nodo = nod;
        general_level.remove(nod);
        // general_level.push_back(std::make_shared<Step>(nod->name, nod,
        // nod->suma));

        auto hijos = graph[nodo->name.son_name];

        for (auto &hijo : hijos) {

            general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo, (hijo.coste + nodo->suma)));
        }

        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        }
    }
    return nullptr;
}

std::shared_ptr<Step>
busqueda_profundo(std::string head,
                  std::map<std::string, std::vector<Conections>> graph,
                  std::string arrival) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (!general_level.empty()) {

        nodo = general_level.back();
        general_level.pop_back();
        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        } else {

            auto hijos = graph[nodo->name.son_name];
            for (auto &hijo : hijos) {
                general_level.push_back(
                        std::make_shared<Step>(hijo.son_name, nodo, hijo.coste));
            }
        }
    }
    return nullptr;
}

float make_heuristic(std::map<std::string, std::vector<Conections>> &graph,
                     std::string nodo, std::string goal,
                     std::map<std::string, std::vector<float>> &heuristic) {
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;

    if (graph.find(nodo) != graph.end() && graph.find(goal) != graph.end() &&
        heuristic.find(nodo) != heuristic.end() &&
        heuristic.find(goal) != heuristic.end()) {

        x1 = heuristic[nodo][0];
        y1 = heuristic[nodo][1];
        x2 = heuristic[goal][0];
        y2 = heuristic[goal][1];
        auto z = std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2);
        return std::sqrt(z);
    }

    return 0.;
}

std::shared_ptr<Step>
greddy_search(std::string head,
              std::map<std::string, std::vector<Conections>> &graph,
              std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true) {
        std::shared_ptr<Step> nod;
        nod = nullptr;
        for (auto &i : general_level) {
            if (!graph[(i)->name.son_name].empty() || i->name.son_name == arrival) {

                if (nod == nullptr) {
                    nod = i;
                } else {
                    if (i->suma < nod->suma) {
                        nod = i;
                    }
                }
            }
        }
        if (nod == nullptr) {
            return nullptr;
        }

        nodo = nod;
        general_level.remove(nod);

        auto hijos = graph[nodo->name.son_name];

        for (auto &hijo : hijos) {

            general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo,
                    (make_heuristic(graph, hijo.son_name, arrival, heuristica) +
                     nodo->suma)));
        }

        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        }
    }
    return nullptr;
}

std::shared_ptr<Step>
a_star_method(std::string head,
              std::map<std::string, std::vector<Conections>> &graph,
              std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true) {
        std::shared_ptr<Step> nod;
        nod = nullptr;
        for (auto &i : general_level) {
            if (!graph[(i)->name.son_name].empty() || i->name.son_name == arrival) {

                if (nod == nullptr) {
                    nod = i;
                } else {
                    if (i->suma < nod->suma) {
                        nod = i;
                    }
                }
            }
        }
        if (nod == nullptr) {
            return nullptr;
        }

        nodo = nod;
        general_level.remove(nod);
        // general_level.push_back(std::make_shared<Step>(nod->name, nod,
        // nod->suma));

        auto hijos = graph[nodo->name.son_name];

        for (auto &hijo : hijos) {

            general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo,
                    (make_heuristic(graph, hijo.son_name, arrival, heuristica) +
                     nodo->suma + hijo.coste)));
        }

        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        }
    }
    return nullptr;
}



std::shared_ptr<Step>
weight_a_star_method(std::string head,
              std::map<std::string, std::vector<Conections>> &graph,
              std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica, float weight) {
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }
    while (true) {
        std::shared_ptr<Step> nod;
        nod = nullptr;
        for (auto &i : general_level) {
            if (!graph[(i)->name.son_name].empty() || i->name.son_name == arrival) {

                if (nod == nullptr) {
                    nod = i;
                } else {
                    if (i->suma < nod->suma) {
                        nod = i;
                    }
                }
            }
        }
        if (nod == nullptr) {
            return nullptr;
        }

        nodo = nod;
        general_level.remove(nod);
        // general_level.push_back(std::make_shared<Step>(nod->name, nod,
        // nod->suma));

        auto hijos = graph[nodo->name.son_name];

        for (auto &hijo : hijos) {

            general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo,
                    (make_heuristic(graph, hijo.son_name, arrival, heuristica) +
                     nodo->suma + weight * hijo.coste )));
        }

        if (nodo->name.son_name == arrival) {
            std::cout << "Nodo encontrado" << std::endl;
            return nodo;
        }
    }
    return nullptr;
}

std::shared_ptr<Step>beam_search(std::string head,std::map<std::string, std::vector<Conections>> &graph,std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica, int number_nodes) {

    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (true) {
        std::vector<std::shared_ptr<Step>> nodoss;
        for (auto &i : general_level) {
            nodoss.push_back(i);
        }
        std::sort(nodoss.begin(), nodoss.end());

        if (nodoss.empty()){
            std::cout<<"ERROR"<<std::endl;
            return nullptr; 
        }
        while ( nodoss.size() == number_nodes){           
            nodoss.pop_back();
         }
        for (auto i: nodoss){
            nodo = i; 
            general_level.remove(i);

            auto hijos = graph[nodo->name.son_name];

            for (auto &hijo : hijos) {

                general_level.push_back(std::make_shared<Step>(
                        hijo.son_name, nodo, hijo.coste));
            }
            if (nodo->name.son_name == arrival) {
                std::cout << "Nodo encontrado" << std::endl;
                return nodo;
            }
        }

    }
    return nullptr;
}

std::shared_ptr<Step>hight_climbing(std::string head,std::map<std::string, std::vector<Conections>> &graph,std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica) {

    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (true) {
        std::vector<std::shared_ptr<Step>> nodoss;
        for (auto &i : general_level) {
            nodoss.push_back(i);
            if (i->name.son_name == arrival){

                return i;
            }
        }
        std::sort(nodoss.begin(), nodoss.end(),std::greater<std::shared_ptr<Step>>());
        if (nodoss.empty()){
            std::cout<<"ERROR"<<std::endl;
            return nullptr; 
        }
        for (auto i: nodoss){
            nodo = i; 
            general_level.remove(i);

            auto hijos = graph[nodo->name.son_name];

            for (auto &hijo : hijos) {


                 general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo,make_heuristic(graph, hijo.son_name, arrival, heuristica)));
                
            }
        }

    }
    return nullptr;
}

std::shared_ptr<Step>hight_climbing_variation(std::string head,std::map<std::string, std::vector<Conections>> &graph,std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica) {

    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (true) {
        std::vector<std::shared_ptr<Step>> nodoss;
        for (auto &i : general_level) {
            i->suma+= i->suma * (std::rand() % 100);
            nodoss.push_back(i);
            if (i->name.son_name == arrival){

                return i;
            }
        }

        
        std::sort(nodoss.begin(), nodoss.end(),std::greater<std::shared_ptr<Step>>());
        if (nodoss.empty()){
            std::cout<<"ERROR"<<std::endl;
            return nullptr; 
        }
        for (auto i: nodoss){
            nodo = i; 
            general_level.remove(i);
            auto hijos = graph[nodo->name.son_name];
            for (auto &hijo : hijos) {

                 general_level.push_back(std::make_shared<Step>(
                    hijo.son_name, nodo,make_heuristic(graph, hijo.son_name, arrival, heuristica)));
            }
        }
    }
    return nullptr;
}


std::shared_ptr<Step>simulated_annealing(std::string head,std::map<std::string, std::vector<Conections>> &graph,std::string arrival,
              std::map<std::string, std::vector<float>> &heuristica, int temperature, int max_temperature, float percentage) {
    
    std::list<std::shared_ptr<Step>> general_level;
    std::set<std::string> history;
    std::shared_ptr<Step> nodo = std::make_shared<Step>(Step(head));
    if (graph.find(head) != graph.end()) {
        general_level.push_back(nodo);
    }

    while (true) {
        std::vector<std::shared_ptr<Step>> nodoss;
        for (auto &i : general_level) {
            nodoss.push_back(i);
        }
        std::sort(nodoss.begin(), nodoss.end());

        if (nodoss.empty()){
            std::cout<<"ERROR"<<std::endl;
            return nullptr; 
        }
        while ( nodoss.size() == temperature){           
            nodoss.pop_back();
         }
        for (auto i: nodoss){
            nodo = i; 
            general_level.remove(i);

            auto hijos = graph[nodo->name.son_name];

            for (auto &hijo : hijos) {

                general_level.push_back(std::make_shared<Step>(
                        hijo.son_name, nodo, hijo.coste));
            }
            if (nodo->name.son_name == arrival) {
                std::cout << "Nodo encontrado" << std::endl;
                return nodo;
            }
        }

    }
    return nullptr;
}
