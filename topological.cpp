#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int dfs(vector<int>& visit_time, int counter, const vector<vector<int>>& adjlst, int index){ //visit time must be within the range of 1 ~ v 

    for (int i: adjlst[index]){
        //cout << "visiting " << index << " using " << i << endl;
        if (visit_time[i] >= 0){ //already visited places and have their finish times 
            continue;
        }
        else{ //haven't visited yet visit them first 
            counter = dfs(visit_time, counter, adjlst, i);
            counter++;
            //cout <<" counter for " << index << " became "<< counter <<" after dfs through " << i << endl;
            /*
            for(int val : visit_time){
                cout << val << " ";
            }
            cout << endl;*/
        }
    }

    visit_time[index] = counter;

    return counter;
}

vector<int> topological(int v, const vector<vector<int>>& edges){
    
    vector<int> answer(v,0);

    //make adj list not adj matrix since then you don't know the neighbors 
    vector<vector<int>> adjlst(v);
    for(const auto& edge: edges){
        adjlst[edge[0]].push_back(edge[1]);
    }

    vector<int> visit_time(v, -1); //never visited 
    int counter = 0; 

    

    for (int i = 0; i < v; ++i){
        if (visit_time[i] == -1){ //haven't been dfs through 
            counter = dfs(visit_time, counter, adjlst, i);
        }
    }

    for (int i = 0; i < visit_time.size(); ++i){
        answer[visit_time[i]] = i;
    }

    reverse(answer.begin(), answer.end());

    return answer;
}

int main(){

    vector<vector<int>> edges = {{0, 1, 70}, {1, 2, 8}, {1, 3, 20}, {2, 3, 13}, {2, 4, 17}, {1, 4, 31}, 
     {3, 4, 15}, {3, 5, 18}, {5, 6, 4}, {6, 7, 5}, {5, 7, 10}};
    int n = 8;

    vector<int> answer = topological(n, edges);

    for(int val : answer){
        cout << val << " ";
    }
    cout << endl;

}