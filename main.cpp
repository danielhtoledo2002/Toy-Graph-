// Daniel Hernández Toledo
// ID 0243179 
#include<iostream>
#include <vector>
#include <map>
#include <iterator>

struct Node {
    Node * next;
    Node * prev;
    std::string dato;
};

struct List{
public:
    Node * head;
    Node * tail;
    Node * current;
    List();
    ~List();
    Node * new_node(std::string);
};

struct pointer_node{
    Node * node ;
    std::vector<Node *> conections;
    pointer_node * next;
    pointer_node * prev;
    uint cost ;
};

struct pointer_list{
public:
    pointer_node * pointer_head;
    pointer_node * pointer_tail;
    pointer_list();
    pointer_node * get_connection(Node *, Node *);
    void make_connection(Node *, Node *);
    /*
    std::map<Node *, std::vector<Node *>> getConnections(Node *);
    Node * getFromNode(Node *, Node *);
    Node * getToNode(Node *, Node *);
     */
    ~pointer_list();
    pointer_node * find(Node *);
    void travel_graph(Node *);
};

// --------------------Method-----------------
List::List() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

List::~List() {
    while (head != nullptr) {
        Node *ltem = head->next;
        delete head;
        head = ltem;
    }
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

Node * List::new_node(std::string x) {
    Node * ltem = new Node;
    if (ltem){
        ltem->next = nullptr;
        ltem->prev = nullptr;
        ltem->dato = x;
    }
    return ltem;
}

pointer_list::pointer_list(){

    pointer_head = nullptr;
    pointer_tail = nullptr;
}
pointer_list::~pointer_list() {
    while (pointer_head!= nullptr) {
        pointer_node * ltem = pointer_head->next;
        delete pointer_head;
        pointer_head  = ltem;
    }
    pointer_head = nullptr;
    pointer_tail = nullptr;

}
pointer_node * pointer_list::find(Node * node) {
        pointer_node * lTemp = pointer_head;
        while (lTemp) {
            if (node == lTemp->node)
                return lTemp;
            lTemp = lTemp->next;
        }
        return nullptr;
}

pointer_node * pointer_list::get_connection(Node * ltem, Node * next){
    auto * new_pointer_node = new pointer_node;
    if(new_pointer_node){

        new_pointer_node->node = ltem;
        new_pointer_node->cost =  1+(rand() % 10 );//Generate a random cost to any connection
        new_pointer_node->next = nullptr;
        new_pointer_node->prev = nullptr;
        new_pointer_node->conections.push_back(next);
        return new_pointer_node;
    }
    return new_pointer_node;
}
//push_back
void pointer_list::make_connection(Node * node1, Node * node2){
    if(pointer_head == nullptr){
        pointer_head = get_connection(node1, node2);
        pointer_tail = pointer_head;
    }
    else{
        pointer_node * prueba = find(node1);
        if (prueba == nullptr) {
            pointer_node *ltem = get_connection(node1, node2);
            pointer_tail->next = ltem;
            ltem->prev = pointer_tail;
            pointer_tail = ltem;
        } else{
            prueba->conections.push_back(node2);
        }
    }
}
void pointer_list::travel_graph(Node * head) {
    std::vector<pointer_node * > first_level;
    first_level.push_back(find(head));
    std::vector<pointer_node * > second_level;
    std::vector<pointer_node * > history;
    std::vector<pointer_node * >::iterator ite;
    std::vector<Node *>::iterator iter_node;
    while (true){
        if (first_level.empty()){
            std::cout<<"The node doesn't exist "<<std::endl;
            break;
        } else{

            for(ite = first_level.begin(); ite < first_level.end(); ite++){
                std::cout<<std::endl;
                std::cout<< (*ite)->node->dato <<" -> ";
                if(!(* ite)->conections.empty()) {
                    for (iter_node = (*ite)->conections.begin(); iter_node < (*ite)->conections.end(); iter_node++) {
                        if (find(*iter_node) != nullptr) {
                            second_level.push_back(find(*iter_node));
                        }
                        std::cout << (*iter_node)->dato << " -> ";
                    }
                }
            }
            std::cout<<std::endl;
            first_level.swap(second_level);
            second_level.clear();
        }
    }
}

// return a vector of the connection
/*
std::map<Node *, std::vector<Node *>> pointer_list::getConnections(Node * node ) {
    pointer_node * lTemp = pointer_head;
    std::map<Node *, std::vector<Node *>> conections;
    std::vector<Node *> tuple_connections;
    while (lTemp) {
        if (node == lTemp->node){
            tuple_connections.push_back(lTemp->next_node);
            tuple_connections.push_back(lTemp->prev_node);
            conections[node] = tuple_connections;
        }
        lTemp = lTemp->next;
    }
    return conections;
}

Node *  pointer_list::getFromNode(Node * node , Node *node2) {
    pointer_node * ltemp = pointer_head;
    Node * node3;
    std::vector<Node *> connections;
    while (ltemp){
        if (node ==  ltemp->next_node && node2 == ltemp->prev_node){
            node3 = ltemp->prev_node;
        }
        ltemp = ltemp->next;
    }

    return node3;
}

Node *pointer_list::getToNode(Node * node , Node *node2) {
    pointer_node * ltemp = pointer_head;
    Node * node3;
    std::vector<Node *> connections;
    while (ltemp){
        if (node ==  ltemp->next_node && node2 == ltemp->prev_node){
            node3 = ltemp->next_node;
        }
        ltemp = ltemp->next;
    }

    return node3;
}
*/
int main() {
    List list = List();
    Node * first_pointer = list.new_node("Arad");
    Node * second_pointer = list.new_node("Timisoara");
    Node * third = list.new_node("Zerid");
    Node * fouth = list.new_node("Sibiú");
    Node * fifth = list.new_node("Oradera");
    Node * six = list.new_node("Lugoj");
    Node *seven = list.new_node("Mehadia");
    Node * eight = list.new_node("Drobeta");
    Node * nine = list.new_node("Cravola");
    Node * ten = list.new_node("Rimnicu Viicea");
    Node * eleven = list.new_node("Fragaras");
    Node * twelve = list.new_node("Pitesti");
    Node * thirteen = list.new_node("Bucharest");
    Node * fourteen = list.new_node("Glurgiu");
    Node * fifteen = list.new_node("Urzicent");
    Node * sixteen = list.new_node("Hirsova");
    Node * seventeen = list.new_node("Eforic");
    Node * eighteen = list.new_node("Vaslui");
    Node * nineteen = list.new_node("Iasj");
    Node * twenty = list.new_node("Neamt");
    list.head = first_pointer;
    list.tail = twenty;
    pointer_list list2 = pointer_list();
    list2.make_connection(first_pointer, second_pointer);
    list2.make_connection(first_pointer, third);
    list2.make_connection(first_pointer, fouth );
    list2.make_connection(second_pointer, six);
    list2.make_connection(third, fifth);
    list2.make_connection(fouth, eleven);
    list2.make_connection(fouth, ten);
    list2.make_connection(fifth, fouth);
    list2.make_connection(six, seven);
    list2.make_connection(seven, eight);
    list2.make_connection(eight, nine);
    list2.make_connection(ten, nine);
    list2.make_connection(ten, twelve);
    list2.make_connection(nine, twelve);
    list2.make_connection(eleven, thirteen);
    list2.make_connection(twelve, thirteen);
    list2.make_connection(thirteen, fourteen);
    list2.make_connection(thirteen, fifteen);
    list2.make_connection(fifteen, sixteen);
    list2.make_connection(fifteen, eighteen);
    list2.make_connection(sixteen, seventeen);
    list2.make_connection(eighteen, nineteen);
    list2.make_connection(nineteen, twenty);
    list2.travel_graph(first_pointer);



    /*
    list2.make_connection(fifth, fouth);
    list2.make_connection(second_pointer, nullptr);
    list2.make_connection(second_pointer, nullptr);

    /*
 std::map<Node *, std::vector<Node *>> x = list2.getConnections(third);
 // l vector has all the connections from third node
 auto l = x[third];
 auto s = list2.getFromNode(fifth, first_pointer);
 auto  f = list2.getToNode(fifth, first_pointer);
 */
    return 0;
}