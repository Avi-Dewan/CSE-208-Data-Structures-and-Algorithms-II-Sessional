#include <iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;

bool visited[1000000];

int parent[1000000]; //if you want to record parent

int timer;
int sTime[1000000]; // starting time
int fTime[1000000]; //finishing time
int distance[1000000]; //distance from root

vector<int> comp; //for finding out connected components



class Graph {
private:
    bool **adjMatrix;
    int nVertices;

public:
    Graph(int n) {
        nVertices = n;
        adjMatrix = new bool*[n+1];

        for(int i = 0; i <= n; i++) {
            adjMatrix[i] = new bool[n+1];

            for(int j = 0; j <= n; j++) {
                adjMatrix[i][j] = false;
            }
        }
    }

    int totalVertices() {
        return nVertices;
    }

    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
    }

    void deleteEdge(int i, int j) {
        adjMatrix[i][j] = false;
    }

    bool hasEdge(int i,int j) {
        return adjMatrix[i][j];
    }

    void toString() {
        for (int i = 0; i <= nVertices; i++) {
          cout << i << " : ";
          for (int j = 0; j <= nVertices; j++)
            cout << adjMatrix[i][j] << " ";
          cout << "\n";
        }
    }

    ~Graph() {
        for(int i = 0; i <= nVertices; i++)
            delete[] adjMatrix[i];

        delete[] adjMatrix;
    }




*/

};

void falsifyVisited(int n) {
    for(int i = 0; i <= n; i++) visited[i] = false;
}


void bfs(Graph &g, int start) {

        queue<int> q;

        int n = g.totalVertices();

        //making all the visited false
        falsifyVisited(n);

        q.push(start);

        cout << "BFS: " ;

        distance[start] = 0;

        while(!q.empty()) {
            int curr = q.front();

            if(!visited[curr]) {
                cout << curr << " ";
                visited[curr] = true;
            }

            q.pop();

            for(int i = 0; i <= n; i++) {
                if(g.hasEdge(curr,i) && !visited[i]) {
                        q.push(i);
                        parent[i] = start;
                        distance[i] = distance[start]  + 1;
                }
            }
        }

        cout << endl;

}


 void dfs(Graph &g, int start) {

        stack<int> S;

        int n = g.totalVertices();

        //if not done beofore, call falisfyVisited;

        S.push(start);


        while(!S.empty()) {
            int curr = S.top();

            if(!visited[curr]) {
//                cout << curr << " ";
                comp.push_back(curr);
                visited[curr] = true;
            }

            S.pop();

            for (int i = 0; i <= n; i++) {
                if (g.hasEdge(curr, i) && !visited[i]) {
                    S.push(i);
                }
            }
        }
}

//DFS using recursion
void dfsR(Graph &g, int start) {

     cout << start << " ";

     visited[start] = true;

     timer++;
     sTime[start] = timer;

     for (int i = 1; i <= nVertices; i++) {

        if ( hasEdge(start, i) && (!visited[i])) {
            parent[i] = start;
            dfsR(g, i);
        }
    }

    timer++;
    fTime[start] = timer;
}


// number of connected component using DFS

int connectedComponent(Graph &g) {

    int n = g.totalVertices();


    falsifyVisited(n);

    int countCC = 0;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            comp.clear();

            dfs(g, i);

            countCC++;

            cout << "Component-" << countCC << " : " ;

            for(int j = 0; j < comp.size(); j++)
                cout << comp[j] << " ";

            cout << endl;
        }
    }

    return countCC;

}




int main() {

    int t, n, e, a, b;

    cin >> t;

    while(t--) {
        cin >> n >> e;

        Graph g(n);

        for(int i = 0; i < e; i++) {
            cin >> a >> b;
            g.addEdge(a, b);
        }


        bfs(g, 0);

        connectedComponent(g);

    }

    return 0;
}


/*

10
10
0 1
0 3
1 2
1 4
3 6
6 3
4 5
4 7
6 5
6 8



*/

