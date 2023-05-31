#include<iostream>
#include<vector>

using namespace std;

class Edge {
public:
    int u, v;
    double w;

    Edge(int u, int v, double w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};


vector <Edge> E; //weighted Adjacency list
double dist[1000];
int p[1000];
int n;

bool bellmanFord(int s) {

    for(int i = 0; i < n; i++) {
        dist[i] = 100000000;
        p[i] = -1;
    }

    dist[s] = 1;

    for(int i = 0; i < n; i++) {
        for(Edge e: E) {
            if(dist[e.v] > dist[e.u] * e.w) {
                dist[e.v] = dist[e.u] * e.w;
                p[e.v] = e.u;
            }
        }
    }
//
//    for(int i = 0; i < n; i++) {
//        cout << dist[i] << endl;
//    }

//    for(Edge e: E) {
//        if(dist[e.v] > dist[e.u] + e.w) {
//            return false;
//        }
//    }

    return true;
}

void printPath(int s, int d) {
    vector<int> path;

    path.push_back(d);

    while(d != s) {
        d = p[d];
        path.push_back(d);
    }

    for(int i = path.size()-1; i >= 0; i--) {
        cout << path[i];

        if(i != 0) cout << " -> ";
    }

    cout << endl;
}

int main() {

    int e, u, v, s, d;
    double w;

    cin >> n >> e;

    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        E.push_back(Edge(u, v, w));
    }

    cin >> s >> d;

    bool noNegCycle = bellmanFord(s);

    if(noNegCycle) {
        cout << "The graph does not contain a negative cycle" << endl;
        cout << "Shortest path cost: " << dist[d] << endl;
        printPath(s, d);
    } else {
        cout << "The graph contains a negative cycle";
    }


    return 0;


}



