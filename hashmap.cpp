#include<cmath>  
#include <vector>
#include <iostream>
using namespace std;


class Direct_Access_Hash {
public:
    Direct_Access_Hash(){
    }

    void add(int val){ //insert(T,k) -> T[k] = k 
        if (hash(val) < table.size()){
            //create a new table of that size
            //copy over the values
            //that's the new size
        }
        table[val] = val;
    }

    /*
    int get(int val){   //get(T,k) -> T[k]
        if (hash(val) < table.size()){
            if (table[hash(val)] != empty) return hash(val);
        } 
        exit(1);
    }*/



private:
    int hash(int val){
        return val;
    }
    
    vector<int> table;

};


class Other_Hash {
public:
    Other_Hash(){
    }

    void add(int val){ //insert(T,k) -> T[k] = k 
        if (hash(val) < table.size()){
            //create a new table of that size
            //copy over the values
            //that's the new size
        }
        table[val] = val;
    }

    /*
    int get(int val){   //get(T,k) -> T[k]
        if (hash(val) < table.size()){
            if (table[hash(val)] != empty) return hash(val);
        } 
        exit(1);
    }*/

    

private:
    //
    void delete_me(int val){
        for (int i = 0; i < table.size(); ++i){
            int index = probe_linear(val, i);
            if (index == del) continue;
            if (index == null) exit(1)
            if (table[index] = val) table[index] = del;
        }
        exit(1); //not found 

    }
    
    int linear_hash(char first_letter, int grade){
        return 10* first_letter + grade;
    }

    int probe_linear(int value, int iteration){
        //generate a permutation of sudo random values with no repeats 

        int index = (linear_hash(value, 0) + iteration) % table.size(); //generate m probe sequences
        return index;
    }

    int probe_quadratic(int value, int iteration){
        //generate a permutation of sudo random values with no repeats 
        int c = prime;
        int d = prime;
        int index = (linear_hash(value, 0) + c * iteration + d * i * i) % table.size(); //generate m probe sequences
        return index;
    }

    int double_hashing(int value, int iteration){
        int index = (linear_hash(value, iteration) + linear_hash2(value,iteration) * i) % tables.size();
        return index; //can generate up to m^2 probe sequences? 
    } //uniform hashing wants us to get m! sequences. m^2 is good but not even close to this m! sequence 


    
    vector<int> table;

};