#include <iostream>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

bool visited[1000000];

int parent[1000000]; //if you want to record parent

int sTime[1000000]; // starting time
int fTime[1000000]; //finishing time
int distance[1000000]; //distance from root

vector<int> order, comp; //for finding out connected components



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
};

void falsifyVisited(int n) {
    for(int i = 0; i <= n; i++) visited[i] = false;
}


void dfs1(Graph &g, int start) {

     visited[start] = true;

     int n = g.totalVertices();

     for (int i = 1; i <= n; i++) {
        if ( g.hasEdge(start, i) && (!visited[i])) {
            dfs1(g, i);
        }
    }
    order.push_back(start);
}


void dfs2(Graph &g, int start) {

        stack<int> S;

        int n = g.totalVertices();

        //if not done before, call falisfyVisited;

        S.push(start);


        while(!S.empty()) {
            int curr = S.top();

            if(!visited[curr]) {
                comp.push_back(curr);
                visited[curr] = true;
            }

            S.pop();

            for (int i = 1; i <= n; i++) {
                if (g.hasEdge(curr, i) && !visited[i]) {
                    S.push(i);
                }
            }
        }
}


int main() {

    int t, n, e, a, b;

    cin >> t;

    while(t--) {
        cin >> n >> e;

        Graph g(n), revG(n);

        for(int i = 0; i < e; i++) {
            cin >> a >> b;
            g.addEdge(a, b);
            revG.addEdge(b, a);
        }

        falsifyVisited(n);

        for(int i = 1; i <= n; i++) {
            if(!visited[i]) {
                dfs1(g, i);
            }
        }

        reverse(order.begin(), order.end());

        falsifyVisited(n);

        cout << endl;



        for(int v: order) {


            if(!visited[v]) {


                dfs2(revG, v);

                for(int i = 0; i < comp.size(); i++)
                    cout << comp[i] << " ";

                cout << endl;

                comp.clear();
            }

        }

    }

    return 0;

}

