#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

struct Node{
    friend ostream& operator<<(ostream&, const Node&);
    Node* parent;
    Node* left; //nullptrs for both left + right + being black means they are nill 
    Node* right;
    pair<int,int> val; //automatically make value INT_MIN but this won't be used to compare 

    bool red;
    int farRight = -1;
    //bool doubleblack = false;
    //ask thaison about using this outisde as a parameter? can this not be done? 
};
ostream& operator<<(ostream& os, const Node& node){
    if (node.red) os << "node: (" << node.val.first << ")";
    else os << "node: " << node.val.first << " ";
    os << "second: " << node.val.second << "   farRight:" << node.farRight<< endl;
    return os;
}


/*rules:
1. all leaves are nill black
2. root is black
3. red nodes have black parents 
4. black height always the same 
*/

class Redblack {
protected:
    friend ostream& operator<<(ostream& os, const Redblack&);
        virtual void leftRotate(Node* parent){
            Node* child = parent->right;
            Node* grandma = parent->parent;
            grandma->right = child;
            child->parent = grandma;
            parent->right = child->left;
            parent->right->parent = parent;
            child->left = parent;
            parent->parent = child;
        }

        virtual void rightRotate(Node* parent){//doesn't really work for the root!!! 
            Node* child = parent->left;
            Node* grandma = parent->parent;
            grandma->left = child;
            child->parent = grandma;
            parent->left = child->right;
            parent->left->parent = parent;
            child->right = parent;
            parent->parent = child;
        }
        //resolve color issues 
        void redred(Node* child){
            Node* mom = child->parent;
            Node* grandma = mom->parent;
            Node* aunt = (grandma->right == mom)? grandma->left: grandma->right;
            
            if (aunt->red){ //aunt is red so recolor 
                //self stays red 
                //cout << "case 1: aunt is red so recolor" << endl;
                mom->red = false; //color parent 
                grandma->red = true; //color grandparent
                aunt->red = false; //color aunt
                if (grandma == root) grandma->red = false;
                else if(grandma->parent->red) redred(grandma); //recurse when grandma has red red violation
            } 
            
            else{//case 2 and case 3 aunt is black 
                cout << "case 2,3: " << endl;
                if (grandma->left == mom && mom->right == child){ 
                    //swap if i am a left inner grandchild 
                    cout << "case2: left rotate" << endl;
                    leftRotate(mom);
                    cout << *this;
                    swap(child, mom);
                }
                else if(grandma->right == mom && mom->left == child){
                    //swap if i am a right inner grandchild 
                    //cout << "case2: right rotate" << endl;
                    rightRotate(mom);
                    //cout << *this;
                    swap(child, mom);
                }
                
                if (grandma->left->left == child){
                    //cout << "final case: right rotate" << endl;
                    rightRotate(grandma);
                    //cout << *this;
                }
                
                else if(grandma->right->right == child){
                    //cout << "final case left rotate" << endl;
                    //cout <<  "grandma in 3rd clase  " << *grandma;
                    leftRotate(grandma);
                }
                //recolor themselves 
                grandma->parent->red = false;
                grandma->red = true;
            }
        }

        Node* makeRedChild(int val, int second = 1, Node* mom = nullptr){ //make a new child on the heap with dummy children on the heap
            Node* answer = new Node{mom, 
                        new Node{nullptr, nullptr, nullptr, make_pair(INT_MIN,0), false}, 
                        new Node{nullptr, nullptr, nullptr, make_pair(INT_MIN,0), false}, 
                        make_pair(val, second), true}; //can't assign to answer when it don't exist 
            answer->left->parent = answer;
            answer->right->parent = answer;
            return answer;
        }

        int n;
        Node* root;

        /*found this online not my own code */
        void printBT(const string& prefix, Node* node, bool isLeft, ostream& os) const{
            if( node != nullptr )
            {
                os << prefix;

                os << (isLeft ? "├──" : "└──" );

                // print the value of the node
                if (node->red) os << '(' << node->val.first << ')';
                else os << node->val.first;
                os << "  s: " << node->val.second << "   right:" << node->farRight<< endl;

                // enter the next tree level - left and right branch
                printBT( prefix + (isLeft ? "│   " : "    "), node->left, true, os);
                printBT( prefix + (isLeft ? "│   " : "    "), node->right, false, os);
            }
        }

        Node* find(int val) const{ 
            //return the node itself or a dummy leaf if not found at the location to insert
            Node* prev = root;
            Node* curr = root;
            while (curr){
                if (curr->val.first == val) return curr;
                if (curr->val.first < val){
                    prev = curr;
                    curr = curr->right;
                }
                else{
                    prev = curr;
                    curr = curr->left;
                }
            }
            return prev;
        }

    public: 
        Redblack(){
            n = 0;
            root = nullptr;
        }

        int getSize() const{
            return n;
        }

        bool insert(int val, int second = 1){
            n++; //have another value always can insert
            if (!root){ //
                root = makeRedChild(val);
                //update self's root 
                root->parent = root;
                root->red = false;
                return true;
            }

            Node* loc = find(val);
            Node* parent = loc->parent;
            if (!loc->left && !loc->right){ //if location is a leaf 
                //insert a child first
                if (parent->right == loc){ //right child 
                    delete loc; //kill dummy
                    parent->right = makeRedChild(val, second, parent);
                    loc = parent->right;
                }
                else{                        
                    delete loc;
                    parent->left = makeRedChild(val, second, parent);
                    loc = parent->left;
                }
                //cout << parent->right->val;
                //cout << "loc->val "<<  loc->val << endl;
                if (parent->red){ //red parent 
                    redred(loc);
                }

                return true;
            }
            //cout << "node " << loc->val << " already exists";
            return false;
        }

        ~Redblack(){ //destructor using a breadth first search 
            deque<Node*> ptrs;
            ptrs.push_back(root);
            while (ptrs.size() > 0){
                const int n = ptrs.size();
                for (int i = 0; i < n; ++i){
                    Node* val = ptrs.front();
                    ptrs.pop_front();
                    if (val->right) ptrs.push_back(val->right);
                    if (val->left) ptrs.push_back(val->left);
                    delete val;
                }
            }
        }
        //I don't wanna implement copy control bite me
};



ostream& operator<<(ostream& os, const Redblack& tree){
    tree.printBT("", tree.root, false, os);
    return os;
}


/*implement the children and the two other stuff



*/

class Interval : public Redblack{ //itnerval tree 
protected:
    void leftRotate(Node* parent){
        Redblack::leftRotate(parent);

        Node* child = parent->parent;
        Node* A = parent->left;
        Node* B = parent->right;
        Node* C = child->right;
        parent->farRight = max(A->val.second, B->val.second);
        child->farRight = max(C->val.second, parent->val.second);
    }

    void rightRotate(Node* parent){
        Redblack::rightRotate(parent);

        Node* child = parent->parent;
        Node* A = parent->right;
        Node* B = parent->left;
        Node* C = child->left;
        parent->farRight = max(A->val.second, B->val.second);
        child->farRight = max(C->val.second, parent->val.second);
    }

public:
    using Redblack::Redblack;

    bool insert(int val, int second){
        Node* curr = Redblack::find(val);
        //check if curr is nullptr. will be when tree has no values
        while (curr && curr->parent != curr){ //update the parents size first
            curr = curr->parent;
            curr->farRight = max(curr->farRight, second);
        }
        Redblack::insert(val);
        curr = Redblack::find(val);
        curr->farRight = curr->val.second;
        return true;
        //incorrect interval tree. it shouldn't be far right compared here!!!
    }
private:
};

class Dynamic : public Redblack{ //itnerval tree 
protected:
    void leftRotate(Node* parent){
        Redblack::leftRotate(parent);
        cout << "leftrotate " << endl;

        Node* child = parent->parent;
        Node* A = parent->left;
        Node* B = parent->right;
        Node* C = child->right;
        parent->val.second = A->val.second + B->val.second + 1;
        child->val.second = C->val.second + parent->val.second + 1;
    }

    void rightRotate(Node* parent){
        Redblack::rightRotate(parent);

        Node* child = parent->parent;
        Node* A = parent->right;
        Node* B = parent->left;
        Node* C = child->left;
        parent->val.second = A->val.second + B->val.second + 1;
        child->val.second = C->val.second + parent->val.second + 1;
    }

public:
    using Redblack::Redblack;

    bool insert(int val){
        Node* curr = Redblack::find(val);
        //check if curr is nullptr. will be when tree has no values
        while (curr && curr->parent != curr){ //update the parents size first
            curr = curr->parent;
            curr->val.second ++;
        }
        Redblack::insert(val);
        return true;
    }

    int rank(int k){ 
        if (k <= 0 || k > Redblack::n ){
            cout << "Error: cannot find rank" << endl;
            return -1;
        }
        Node* curr = Redblack::root;
        int totalRank = 0;
        while(curr){
            int currRank = curr->left->val.second + 1;
            totalRank += currRank;
            if (totalRank == k) return curr->val.first;
            if (totalRank > k) {
                totalRank -= currRank;
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        return -1;
    }

    int getRankOf(int val) const{
        Node* node = find(val);
        if (!(node->right) || !(node->left)){ //if its a fake child 
            cout << "value not found in tree";
            return -1;
        }
        
        int rank = 0;
        bool wentleft = true;
        node = node->right; //just to avoid the edge cases. 
        //start on invalid node then go to parent, add parent, then check if they are root 
        while (node->parent != node){ //while it isn't root 
            node = node->parent;
            if (wentleft) rank += node->left->val.second + 1;
            
            if (node->parent->left == node) wentleft = false;
            else wentleft = true;
        }
        return rank;
    }

    vector<int> range(int i, int j){ //indices inclusive. enumerate the values within the ranges
        return {1, 2};
    }
    //have not finished implementing this one yet!!! 

private:
};

int main(){
    vector<int> i = {8, 11, 0, 3, 9, 22, 33, 109};
    vector<int> j = {9, 1000, 1, 4, 10, 29, 200, 101};
    Interval tree;
 
    for (int _ = 0; _ < i.size(); ++_){
        tree.insert(i[_], j[_]);
        cout << tree;
    }
    
    /*
    vector<int> inorder;
    for (int i = 1; i <= tree.getSize(); ++i){
        cout << tree.rank(i) << " ";
        inorder.push_back(tree.rank(i));
    }
    cout << endl;

    for (int val : inorder){
        cout << tree.getRankOf(val) << " ";
    }
    cout << endl;*/


    return 0;
}




/*
int main(){
    vector<int> values = {8, 11, 0, 3, 9, 22, 33, 109};
    Redblack tree;
    for (int val: values){
        tree.insert(val);
        cout << tree;
    }
    return 0;
}*/





/*
1. insert red leaf to replace nill 
2. 2 possibities:
    1. no red red violation then we are all set 
    2. if red red violation 
case 1: you recolor if aunt is also red 
case 2/3: you need to rotate:
    case 2: you first swap with parent. then converts to case 3 
    case 3: you rotate (left child of left parent, right child of right )
*/

