#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

class Node {
public:
    int at, cost;

    Node(int at, int cost) {
        this->at = at;
        this->cost = cost;
    }
};

bool operator<(Node A, Node B) {
    return A.cost > B.cost;
}


class Edge {
public:
    int v, w;
    Edge(int v, int w) {
        this->v = v;
        this->w = w;
    }
};


vector<Edge> adj[1000];
priority_queue<Node> PQ;
int dist[1000];
int n;
int p[1000];


void dijkstra(int s) {
    for(int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }

    dist[s] = 0;
    PQ.push(Node(s, 0));

    while(!PQ.empty()) {
        Node u = PQ.top();
        PQ.pop();

        cout << "u: " << u.at << " " << u.cost << " " << dist[u.at] << endl;

        if(u.cost != dist[u.at]) continue;

        for(Edge e: adj[u.at]) {
            if(dist[e.v] > u.cost + e.w) {
                dist[e.v] = u.cost + e.w;
                PQ.push(Node(e.v, dist[e.v]));
                p[e.v] = u.at;
                cout << "v: " << e.v << " " << dist[e.v] << " || ";
            }
        }

        cout << endl;
    }

}

void printPath(int s, int d) {
    vector<int> path;

    path.push_back(d);

    while(d != s) {
        d = p[d];
        path.push_back(d);
    }

    for(int i = path.size()-1; i >= 0; i--) {
        cout << path[i] << " -> " ;
    }

    cout << endl;
}

int main() {

    int e, u, v, w, s, d;

    cin >> n >> e;

    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        adj[u].push_back(Edge(v, w));
    }

    cin >> s >> d;

    dijkstra(s);


    for(int i = 0; i < n; i++) {
        cout << dist[i] << endl;
    }

    printPath(s, d);

}
