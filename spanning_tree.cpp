#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node;

struct Repr{
    Node* first;
    Node* last;
    int size = 1;

    friend ostream& operator<<(ostream& os, const Repr& repr);
};

struct Node{
    int numbr;
    Repr* repr = nullptr;
    Node* next = nullptr;

    friend ostream& operator<<(ostream& os, const Node& node);

    Node(int num){
        numbr = num;
        repr = new Repr{this, this};
    }

    void merge(Node* rhs);


    ~Node(){
        //cout << " destructor " << endl;
        delete repr;
        repr = nullptr;
    }
    
    Node(const Node& rhs): numbr(rhs.numbr), next(rhs.next){
        //cout << "copy constructor" << endl;
        repr = new Repr{rhs.repr->first, rhs.repr->last, rhs.repr->size};//can simplify 
        //cout << "thsi is what i have become " << repr->first->numbr << endl;
    }

    Node& operator=(const Node& rhs){
        //cout << "assignment operator";
        if (this != &rhs){ ///not correct 
            delete repr;
            numbr = rhs.numbr;
            next = rhs.next;
        }
        return *this; 
    }
};

ostream& operator<<(ostream& os, const Repr& repr){
    Node* cursor = repr.first;
    while (cursor){
        os << cursor->numbr << " -> ";
        cursor = cursor->next;
    }
    return os;
}

ostream& operator<<(ostream& os, const Node& node){
    os << "numbr: " << node.numbr;
    return os;
}

void Node::merge(Node* rhs){
    Repr* repr2 = rhs->repr;
    Node* junction1 = repr->last;
    Node* junction2 = repr2->first;
    
    //connect the 2 chains + update the size 
    junction1->next = junction2;
    repr->size += repr2->size;
    repr->last = repr2->last;

    //update the repr for all nodes in rhs
    Node* cursor = junction2; 
    while (cursor){ 
        cursor->repr = this->repr;
        cursor = cursor->next;
    }
    delete repr2;
}

bool sortbythird(const tuple<int, int, int>& a,  
               const tuple<int, int, int>& b) 
{ 
    return (get<2>(a) < get<2>(b)); 
} 

vector<tuple<int,int,int>> kruskal(int n, vector<tuple<int,int,int>>& edges){
    /*
    1. sort the edges by weight 
    2. add in the smallest by connecting things if they are good. remember in a list 
    return the 
    return the list 
    
    */
    vector<tuple<int,int,int>> answer;

    vector<Node*> nodes;
    for (int i = 0; i < n; i ++) nodes.push_back(new Node(i));

    /*

    for (Node* node: nodes){
        cout << *node << "  " << *node->repr << endl;
    }*/
    sort(edges.begin(), edges.end(), sortbythird);

    
    cout << endl << "sorted edges" << endl;
    for (const auto& val: edges){
        cout << "(" << get<0>(val) << " " << get<1>(val) << " " << get<2>(val) << ")" << endl;
    }


    for (const auto& edge : edges){
        //cout << " i can get here" << endl;
        int node1 = get<0>(edge);
        int node2 = get<1>(edge);
        //cout << "after node1,2" << endl;
        if (nodes[node1]->repr == nodes[node2]->repr){
            //cout << "found a repeating cycle ";
            //cout << "(" << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << ")" << endl;
            continue;
        }
        if (nodes[node1]->repr->size >= nodes[node2]->repr->size){
            nodes[node1]->merge(nodes[node2]);
        }
        else{
            nodes[node2]->merge(nodes[node1]);
        }
        answer.push_back(edge);
        //cout << "i reached here" << endl;
    }
    return answer;
}

/*
vector<vector<int>> prim(vector<vector<int>>& edges){

}*/

int main(){
    vector<tuple<int,int,int>> edges = {{0, 1, 70}, {1, 2, 8}, {1, 3, 20}, {2, 4, 17}, {1, 4, 31}, 
    {2, 3, 13}, {3, 4, 15}, {3, 5, 18}, {5, 6, 4}, {6, 7, 5}, {5, 7, 10}};
    int n = 8;

    
    auto answer = kruskal(n, edges);

    cout << endl << "final answer " << endl;
    for (const auto& val: answer){
        cout << "(" << get<0>(val) << " " << get<1>(val) << " " << get<2>(val) << ")" << endl;
    }

    return 0;


    

}
