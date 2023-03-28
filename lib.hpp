
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
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

std::vector<std::string> clone_vector(std::vector<std::string> copy_vector) {
    std::vector<std::string> copy;
    std::vector<std::string>::iterator iter;
    for (iter = copy_vector.begin(); iter < copy_vector.end(); iter++) {
        copy.push_back(*iter);
    }
    return copy;
}

std::shared_ptr<Step>
busqueda_ancho(std::string head,
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
    std::cout << "Nodos no encontrados" << std::endl;

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
        // general_level.push_back(std::make_shared<Step>(nod->name, nod,
        // nod->suma));

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
