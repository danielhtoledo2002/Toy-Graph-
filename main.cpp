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
  float x1;
  float y1;
  float x2;
  float y2;

  if (graph.find(nodo) != graph.end() && graph.find(goal) != graph.end() &&
      heuristic.find(nodo) != heuristic.end() &&
      heuristic.find(goal) != heuristic.end()) {

    x1 = heuristic[nodo][0];
    y1 = heuristic[nodo][1];
    x2 = heuristic[nodo][0];
    y2 = heuristic[nodo][1];
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
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

int main() {

  std::vector<Conections> connections;
  std::map<std::string, std::vector<Conections>> graph;
  std::list<std::shared_ptr<Step>> list;
  std::map<std::string, std::vector<float>> heuristic;
  heuristic["Arad"] = {-8, 3};
  heuristic["Zerind"] = {-7.5, 4.8};
  heuristic["Oradea"] = {-6.5, 6.2};
  heuristic["Sibiu"] = {-3.5, 1.8};
  heuristic["Fagaras"] = {0.3, 1.5};
  heuristic["Timisoara"] = {-8, 0};
  heuristic["Lugoj"] = {-5.2, -1.2};
  heuristic["Mehadia"] = {-5.1, -3.};
  heuristic["Drobeta"] = {-5.4, -4.4};
  heuristic["Craiova"] = {-2, -5};
  heuristic["Pitesti"] = {1, 2};
  heuristic["Rimnieu Vilcea"] = {-2.5, 0};
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
  auto x = busqueda_ancho("Sibiu", graph, "Bucharest");
  while (x != nullptr) {
    list.push_front(x);
    x = x->dad;
  }
  for (auto &resultado : list) {
    std::cout << resultado->name.son_name << " -> " << resultado->suma << " ";
  }
  list.clear();
  std::cout << "" << std::endl;
  auto z = djkstrap("Arad", graph, "Neamt");
  while (z != nullptr) {
    list.push_front(z);
    z = z->dad;
  }
  for (auto &resultado : list) {
    std::cout << resultado->name.son_name << " ->";
  }

  list.clear();
  std::cout << "" << std::endl;
  std::cout << "Last method" << std::endl;
  auto s = busqueda_profundo("Arad", graph, "Neamt");
  if (s == nullptr) {
    std::cout << "el resultado no existe" << std::endl;

  } else {
    while (s != nullptr) {
      list.push_front(s);
      s = s->dad;
    }
    for (auto &resultado : list) {
      std::cout << resultado->name.son_name << " ->";
    }
  }

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
  list.clear();
  std::cout << "" << std::endl;
}

