#include<cmath>  
#include <vector>
#include <iostream>
using namespace std;


struct Node{
    public:
    friend ostream& operator<<(ostream& os, const Node& node){
        os << "order: " << node.order << "   value: " << node.value;
        return os;
    }

    Node(int order = 0, int value = 0){
        this->order = order;
        this->value = value;
    }

    int order;
    int value;

};
/*
void countSort(vector<Node>& val, int k, int min_order){ //how does this sort work again? 
    vector<int> counter(k, 0);

    for (const Node& node : val){
        counter[node.order - min_order]++;
    }

    vector<Node> answer(k);

    for(size_t i = val.size(); i > 0; --i){

        //i - 1 
    }
}*/


void stableCount(vector<Node>& val, int k, int min_order){ //k is the counter base system, min order is the starting number for the base system
    //cout << " i got in?" << endl;
    vector<int> counter(k, 0); //k size
    //cout << "here"; 

    for (const Node& node : val){   //n time 
        counter[node.order - min_order]++;
    }

    for (size_t i = 1; i < counter.size(); ++i){ //k time 
        counter[i] += counter[i-1];
    }
    //cout << "hello";

    vector<Node> answer(val.size()); //n size 

    for(size_t i = val.size(); i > 0; --i){
        //val[i].order the value at the place 
        int curr_order = val[i-1].order;

        int index = counter[curr_order - min_order] - 1; //index of the place you should place the value 
        answer[index] = val[i-1]; //copy over the object itself 
        counter[curr_order - min_order] --; //update the order 


        /*
        for (const Node& thing: answer){
            cout << thing << " ";
        }
        cout << endl;*/
    }


    val = answer;
}


struct chainNode{
    Node node;
    Node* next;
};

/*
void stableCountChain(vector<Node>& val, int k, int min_order){
    vector<chainNode> chain(k);
    vector<Node*> lastval(k, nullptr);

    for(Node& node: val){
        int index = node.order - min_order;
        
        if (!lastval[index]){ //if it is nullptr 
            chain[index] = chainNode{node, nullptr};
            lastval[index] = &node;
        }
        else {
            lastval[index].next = chainNode{node, nullptr};
            lastval[index] = chain
        }
    }
}*/


void radixSort(vector<int>& values, int k, int l){
    // take the values and then make them into node. after sorting them, put them back in. 
    vector<Node> intermediate;

    for(int number : values){
        intermediate.emplace_back(0, number);
    }
    
    for (int i = 0; i < l; i ++){ //for l times 
        for (Node& node: intermediate){ 
            node.order = (node.value/ int(pow(10,i))) % 10; //find the order at this pt costs n 
            cout << node.order << " ";
        }
        cout << endl;

        stableCount(intermediate, k, 0); //costs n + k 


    }

    for (size_t i = 0; i < intermediate.size(); ++i){ //update this 
        values[i] = intermediate[i].value;
    }
}




/*
int main(){
    //vector<Node> vect= {Node(1,10), Node(1,1), Node(4,900), Node(2,0), Node(0,90)};
    
    for(const Node& val : vect){
        cout << val << endl;
    }
    
    cout << "line break" << endl;

    stableCount(vect, 10, 0);
    cout << "exited value" << endl;


    for(const Node& val : vect){
        cout << val << endl;
    }

    vector<int> vect= {1, 0, 90, 22, 99, 80, 90, 1000};
    for(int val : vect){
        cout << val << " ";
    }
    cout << endl;

    radixSort(vect, 10, 4);

     for(int val : vect){
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

*/