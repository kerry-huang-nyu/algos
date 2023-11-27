#include <vector>
#include <iostream>
using namespace std;

class Heap{
    friend ostream& operator<<(ostream& os, const Heap& heap){
        os << "[";
        for (int val: heap.values){
            os << val << ", ";
        }
        os << "]";

        return os;
    }
public:
    Heap(){
    }

    void heapifyForward(const vector<int>& rhs){
        
    }

    void heapifyBackward(const vector<int>& rhs){

    }

    vector<int> sort(){

    
        vector<int> lst(values.begin(), values.end());
        size_t loc_back = lst.size() - 1;

        while (loc_back > 0){ //at the zeroth the list won't be working
            swap(lst[0], lst[loc_back]);

            size_t loc = 0;
            
            while (2*loc < loc_back){ // 2 loc is a valid index within range
                int left = 2*loc, right = 2*loc + 1;

                int larger = (right < loc_back) ? (values[left] < values[right]) ? right : left : left;
                if (values[loc] < values[larger]){
                    swap(values[larger], values[loc]);
                    loc = larger;
                }
                else break;
            }
            loc_back--;
        }
    }

    int pop(){ //c++ doesn't believe that pop should return int 
        if (values.size() == 0){
            cerr << "cannot pop an empty list";
            exit(1);
        }

        int val = values[0];
        values[0] = values.back();
        values.pop_back();
        int loc = 0;

        while (2*loc < values.size()){ // 2 loc is a valid index within range
            int left = 2*loc, right = 2*loc + 1;

            int larger = (right < values.size()) ? (values[left] < values[right]) ? right : left : left;
            if (values[loc] < values[larger]){
                swap(values[larger], values[loc]);
                loc = larger;
            }
            else break;
        }

        return val;
    }

    int top() const {
        if (values.size() == 0){
            cerr << "cannot pop an empty list";
            exit(1);
        }
        return values[0];
    }

    /*     more readable code
            if (right < values.size()){ 
                if (values[left] > values[right] && values[left] > values[loc]) {
                    swap(values[left], values[right]);
                    loc = left;
                }
                else if (values[right] > values[left] && values[right] > values[loc]){
                    swap(values[right], values[loc]);
                    loc = right;
                }
            }

            else if (values[left] > values[loc]){
                swap(values[left], values[right]);
                loc = left;
            }

            else break;*/

    void push(int val){
        values.push_back(val);

        size_t loc = values.size() - 1;
        while (loc != 0){ //push into the right place 
            if (values[loc] > values[loc/2]){
                swap(values[loc], values[loc/2]);
                loc /= 2;
            }
            else break;
        }

    }




private:
    vector<int> values;
};


/*
int main(){
    Heap newHeap = Heap();

    vector<int> myvec = {2, 4, 5, 9, 3, 0, 6};
    for (int val : myvec){
        newHeap.push(val);
    }

    cout << newHeap << endl;
    cout << "largest: " << newHeap.pop() << endl;
    cout << newHeap;


    return 0;
}*/