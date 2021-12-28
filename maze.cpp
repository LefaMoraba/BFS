#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

class Maze{
    private:

    int numRows;
    int numColumns;
    vector<vector<char>> grid;
    pair<int,int> start;
    pair<int,int> goal;

    public:

        Maze(int row, int col, vector<vector<char>>g, pair<int,int> G, pair<int,int> S){
            this->numRows = row;
            this->numColumns = col;
            this->grid = g;
            this->start = S;
            this->goal = G;
        }

        bool validMove(int r, int c){
            if(grid[r][c] != 'x'){
                return true;
            }
            else{
                return false;
            }
        }

        void PrintMaze(){
            for(int r = 0; r < numRows; r++){
                for(int c = 0; c <numColumns; c++){
                    cout<<grid[r][c];
                }
                cout<<endl;
            }
        }

        void UpdateMaze(int r,int c,char symbol){
            if(this->grid[r][c]!='G' && this->grid[r][c]!='S' ){
                this->grid[r][c] = symbol;
            }
        }

        vector<pair<int,int>>neighbours(int r,int c){
            vector<pair<int,int>>neighbours;
            int down = r + 1;
            if(down<this->numRows){
                neighbours.push_back({down,c});
            }
            int left = c - 1;
            if(left>=0){
                neighbours.push_back({r,left});
            }
            int up = r - 1;
            if(up>=0){
                 neighbours.push_back({up,c});
            }
            int right = c + 1;
            if(right<this->numColumns){
                neighbours.push_back({r,right});
            }
            return neighbours;
        }

};


int main(){
    int rows, cols;
    cin >> rows >> cols;

    vector<vector<char>>maze(rows,vector<char>(cols));

    string x;
    int r = 0;
    getline(cin , x);

    while(r < rows){
        getline(cin, x);
        for(int c = 0; c < cols; c++){
             maze[r][c] = x[c];
         }
         r = r+1;
     }

    pair<int,int> start;
    pair<int,int> goal;

    for(int x = 0; x < rows; x++){
        for(int y = 0; y < cols; y++){
            if(maze[x][y]=='S'){
                start ={x,y};
            }
            else
                if(maze[x][y]=='G'){
                    goal ={x,y};
            }
        }
    }

    Maze puzzel(rows, cols, maze, start, goal);
    //initialising an empty queue
    queue<pair<int,int>>q;

    //initialising a 2D parent array with values {-2,-2} everywhere
    vector<vector<pair<int,int>>>parent(rows,vector<pair<int,int>>(cols));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            parent[i][j]={-2,-2};
        }
    }

    //initialising a 2D distance array
    vector<vector<int>>distance(rows,vector<int>(cols));

    //initialising a set to store all the visited cells
    set<pair<int,int>> travelled;

    //pushing the coordinates of the starting point to the queue
    q.push(start);

    //pushing the coordinates of the starting point to the queue
    travelled.insert(start);

    //while loop to traverse through the maze till we find the shortest path to the goal
    while(!q.empty() && travelled.find(goal)==travelled.end()){
        pair<int,int> curr = q.front();
        q.pop();

        int a, b;
        a = curr.first;
        b = curr.second;

        vector<pair<int,int>>neighbour = puzzel.neighbours(a,b);
        for(int i=0; i < neighbour.size(); i++){
            if(travelled.find(neighbour[i])==travelled.end()){
                if(puzzel.validMove(neighbour[i].first,neighbour[i].second)==true){
                distance[neighbour[i].first][neighbour[i].second] = distance[a][b]+1;
                if(parent[neighbour[i].first][neighbour[i].second].first == -2){
                    parent[neighbour[i].first][neighbour[i].second] = curr;
                }
                q.push(neighbour[i]);
                travelled.insert(neighbour[i]);
            }
        }
        }
    }

    cout << endl;

    //print out "No Path" if no path was found
    if(q.empty()){
        if(travelled.find(goal) == travelled.end()){
        cout << "No Path" << endl;
        }
    }

    else{
        pair<int,int>curr = goal;
        while(!(curr.first == start.first && curr.second == start.second)){
            puzzel.UpdateMaze(curr.first, curr.second,'*');
            curr = parent[curr.first][curr.second];

        }
        //print out the maze with the shortest path from start to goal
        puzzel.PrintMaze();
    }


    return 0;
}
