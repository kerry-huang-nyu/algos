#include<cmath>  
#include <vector>
#include <iostream>
using namespace std;

void partition(vector<int>& vec){ //assuming that the vector is random 
    int pivot = vec[0];

    int i = 1; 
    int j = vec.size() - 1;

    while (i < j){ //this will take n to partitition 
        if (vec[i] < pivot) i ++;
        else if (vec[j] > pivot) j --;
        else {
            swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }
    vec[0] = vec[i];
    vec[i] = pivot;

}

void stablePartition(vector<int>& vec){ //assuming that the vector is random 
    vector<int> answer; //uses n space 
    int pivot = vec[0];

    int i = 1; 
    int j = vec.size() - 1;

    while (i < j){ //this will take n to partitition 
        if (vec[i] < pivot) {
            answer[i-1] = vec[i];
            i ++;
        }
        else if (vec[j] > pivot) {
            answer[j] = vec[j];
            j --;
        }
        else {
            answer[i-1] = vec[j];
            answer[j] = answer[i];
            i++;
            j--;
        }
    }
    answer[i] = pivot;
    vec = answer;
}


int main(){
    cout << "here";
    vector<int> vec={2, 9, 300, 202, 39, 58, 1};
    cout << "bello";
    stablePartition(vec);
    cout << "hello";

    for(int val: vec){
        cout << "inside";
        cout << val << " ";
    } cout << endl;

    return 0;
}