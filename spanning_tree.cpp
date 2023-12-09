#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
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

struct Node2{
    int vertex;
    int distance;
    const tuple<int,int,int>* came_from = nullptr;    //this is used so that when they are added into the thing, they have a length we are using and their origns 
    
    friend ostream& operator<<(ostream& os, const Node2& node){
        os << "(" << node.vertex << ")" << "  dist" << node.distance;
        return os;
    }


    class Node_Iter{
        friend bool operator<(Node2::Node_Iter lhs, Node2::Node_Iter rhs);
    public:
        Node_Iter(Node2& loc){
            where = &loc;
        }

        Node2& operator*() const{
            return *where;
        }
        
    private:
        Node2* where;
    };

    Node2(int vert, int dist = INT_MAX){
        vertex = vert;
        distance = dist;
    }

    bool operator<(const Node2& rhs) const{
        return distance < rhs.distance;
    }
};

bool operator<(Node2::Node_Iter lhs, Node2::Node_Iter rhs){
    return *lhs < *rhs;
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

vector<tuple<int,int,int>> prim(int n, const vector<tuple<int,int,int>>& edges){ //no need to modify 
    /*
    1. the idea is to add each edge sequentially. so we want to add each edge that is accessible from the current tree 
    2. put all nodes into the heap and mark their distance 
    3. then go through the adjacency list of edges to find the weights 
    4. then process the node that is the min val 
    5. then add mroe weights 
    */

    vector<vector<const tuple<int,int,int>*>> adjlst(n); //no changes to the ptrs 
    for (auto edge: edges){
        int origin = get<0>(edge);
        adjlst[origin].push_back(&edge);
    } //make the adjacency list. Space = O(e), Time = O(e)


    vector<tuple<int,int,int>> answer;
    vector<bool> added(n,false);
    priority_queue<Node2::Node_Iter, vector<Node2::Node_Iter>, less<Node2::Node_Iter>> heap;
    vector<Node2*> nodes;

    for (int i = 0; i < n; ++i){ //make the nodes for the priority queue 
        nodes.push_back(new Node2(i, INT_MAX));
    }// Space = O(v), Time = O(v)

    for (auto val : nodes){ //add the nodes into the priority queue 
        heap.push(Node2::Node_Iter(*val));
    }// Space = O(v), Time = O(vlogv) //can reduce to O(v) for time if heapify an array 

    while (heap.size()){ //prim's algo might make forest of trees? wait kruskal's algo might as well! adsfsafd
        Node2::Node_Iter currNode = heap.top();
        /*
        int vert = (*currNode).vertex;
        int dist = (*currNode).distance;
        const tuple<int,int,int>* camefrom = (*currNode).came_from; //edge that we came from
        */

        if ((*currNode).distance == INT_MAX){ //not vaid
            (*currNode).distance = 0;
        } 
        else{ //add the edge that made them 
            answer.push_back(*(*currNode).came_from); //the copy of the value we have 
        }
        heap.pop();
        added[(*currNode).vertex] = true; //put in the added list 
        
        for (const tuple<int,int,int>* edge: adjlst[(*currNode).vertex]){
            /*get the node, delete the node, input new weight, insert the node*/
            int dest = get<1>(*edge);
            int weight = get<2>(*edge);
            if (!added[dest]){ //not added already 
                int currdistance = nodes[dest]->distance;
                if (currdistance > weight){
                    nodes[dest]->distance = weight;
                    nodes[dest]->came_from = edge; //edge is on the stack 
                    //how t odelete the value from the heap?!!! 



                    //not gonna need this! do not do this anymore! stop this deal. heapify this thing 
                    //don't worry about this too much just analyze the runtime at this point
                }
            }
        }
    }
    


/*
    while (heap.size()){
        const Node2::Node_Iter itr = heap.top();
        cout << *itr << endl;
        heap.pop(); 
    }*/



    return answer;
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




int main(){
    vector<tuple<int,int,int>> edges = {{0, 1, 70}, {1, 2, 8}, {1, 3, 20}, {2, 4, 17}, {1, 4, 31}, 
    {2, 3, 13}, {3, 4, 15}, {3, 5, 18}, {5, 6, 4}, {6, 7, 5}, {5, 7, 10}};
    int n = 8;

    

    prim(n, edges);

    /*
    auto answer = kruskal(n, edges);

    cout << endl << "final answer " << endl;
    for (const auto& val: answer){
        cout << "(" << get<0>(val) << " " << get<1>(val) << " " << get<2>(val) << ")" << endl;
    }*/



    return 0;
}
