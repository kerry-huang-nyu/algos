#include <vector>
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

void print(const vector<int>& answer){
    if (!answer.size()) cout << "No Solution";
    else {
        for (int val : answer){
            cout << val << " ";
        }
    } 
    cout << endl;
}

vector<int> bfs(const vector<vector<int>>& edges, int v, bool uselist, int start, int end){

    /* adjacency list */
    if (uselist){
        cout<< "BFS Adjacency List: ";
        vector<vector<int>> list(v); //Space = Theta(v + e)
        for (const vector<int>& edge : edges){ //Time = Theta(e)
            list[edge[0]].push_back(edge[1]); 
            //list may not have vertices in sorted order 
        }
        
        //keeps track of the parents of these lists. 
        //if they have a parent then they are visited 
        //bfs also has a consequence of getting the shortest path 
        int parent[v];  //Space: Theta(v) 
        for (int i = 0; i < v; i ++){ //Time: Theta(v)
            parent[i] = -1; //no parent is -1
        }
        parent[start] = start; //add start avoid start added into possible. 
        //also works for edge cases where start = end 
        
        deque<int> possible; 
        possible.push_back(start);
        while (possible.size()){ 
            //possible deque will have v values at most. 
            //we will never traverse through the same vertex twice
            int vertex = possible.front();
            possible.pop_front();

            if (vertex == end) break; //end the program early. no need 

            for (int i = 0; i < list[vertex].size(); i ++){ //Theta(v)
                int reach = list[vertex][i]; //the vertices we can get to
                if (parent[reach] == -1) { 
                    //if the vertex can be traversed and haven't been visited
                    parent[reach] = vertex;
                    possible.push_back(reach); //put in the vertex we found 
                }
            }
        }

        if (parent[end] == -1) return {}; //no solution 

        vector<int> answer; //build the answer backwards, then reverse 
        answer.push_back(end);
        int curr = end;
        while (curr != start){
            answer.push_back(parent[curr]);
            curr = parent[curr];
        }
        reverse(answer.begin(), answer.end());
        return answer;
    }

    /* adjacency matrix */
    else{
        cout << "BFS Adjacency Matrix: ";
        bool matrix[v][v]; //Space = Theta(v^2)
        for (int i = 0; i < v; ++i){ //Time = Theta(v^2) to falsify everything
            for (int j = 0; j < v; ++j){
                matrix[i][j] = false;
            }
        }
        for (const vector<int>& edge : edges){ //Time = Theta(e)
            matrix[edge[0]][edge[1]] = true;
        }

        //keeps track of the parents of these lists. 
        //if they have a parent then they are visited 
        //bfs also has a consequence of getting the shortest path 
        int parent[v];  //Space: Theta(v) 
        for (int i = 0; i < v; i ++){ //Time: Theta(v)
            parent[i] = -1;
        }
        parent[start] = start; //add start avoid start added into possible. 
        //also works for edge cases where start = end 
        
        deque<int> possible; 
        possible.push_back(start);
        while (possible.size()){ 
            //possible deque will have v values at most. 
            //we will never traverse through the same vertex twice
            int vertex = possible.front();
            possible.pop_front();

            if (vertex == end) break; //end the program early. no need 

            for (int i = 0; i < v; i ++){ //Theta(v)
                if (matrix[vertex][i] && parent[i] == -1) { 
                    //if the vertex can be traversed and haven't been visited
                    parent[i] = vertex;
                    possible.push_back(i); //put in the vertex we found 
                }
            }
        }

        if (parent[end] == -1) return {}; //no solution 
        vector<int> answer; //build the answer backwards, then reverse 
        answer.push_back(end);
        int curr = end;
        while (curr != start){
            answer.push_back(parent[curr]);
            curr = parent[curr];
        }
        reverse(answer.begin(), answer.end());
        return answer;
    }
}

bool dfsHelper(bool* matrix, bool* visited, vector<int>& answer, int v, int start, int end){ //helper gets matrix, and visited 
    visited[start] = true;
    if (start == end) return true;
    for (int i = 0; i < v; i ++){ //Theta(v)
        if (matrix[start * v + i] && !visited[i]){ //access the 
            bool status = dfsHelper(matrix, visited, answer, v, i, end);
            if (status){
                answer.push_back(i);
                return true;
            }
        }
    }
    return false;
}

vector<int> dfs(const vector<vector<int>>& edges, int v, bool uselist, int start, int end){
    //dfs may not be able to find the shortest path but is still the same runtime as bfs 
    /* adjacency list */
    if (uselist){
        
    }

    /* adjacency matrix */
    else{
        cout << "DFS Adjacency Matrix: ";
        bool matrix[v][v]; //Space = Theta(v^2)
        for (int i = 0; i < v; ++i){ //Time = Theta(v^2) to falsify everything
            for (int j = 0; j < v; ++j){
                matrix[i][j] = false;
            }
        }
        for (const vector<int>& edge : edges){ //Time = Theta(e)
            matrix[edge[0]][edge[1]] = true;
        }

        bool visited[v];
        for (int i = 0; i < v; ++i){
            visited[i] = false;
        }

        vector<int> answer;
        if(!dfsHelper((bool*)matrix, visited, answer, v, start, end)){
            return {};
        };
        answer.push_back(start);
        reverse(answer.begin(), answer.end());
        return answer;
    }

    return {};
}



int main() {
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 1}, {2, 2}, {3, 0}, {0, 3}, {3, 1}};
    /*
    n is the number of vertices that we have 
    let 0 ~ n-1 be all the vertices within the graph 
    */

    //runtime analysis of these algos 
    print(bfs(edges, 4, true, 2, 3)); 
    print(bfs(edges, 4, false, 2, 3));

    //cout << hello
    //runtime analysis of these algos 
    //print(dfs(edges, 4, true, 1, 2));
    print(dfs(edges, 4, false, 2, 3));
}


