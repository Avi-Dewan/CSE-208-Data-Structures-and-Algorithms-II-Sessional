#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

class Node {
public:
    int at;
    double cost;

    Node(int at, double cost) {
        this->at = at;
        this->cost = cost;
    }
};

bool operator<(Node A, Node B) {
    return A.cost > B.cost;
}


class Edge {
public:
    int v;
    double w;
    Edge(int v, double w) {
        this->v = v;
        this->w = w;
    }
};


vector<Edge> adj[1000];
priority_queue<Node> PQ;

int n;

double dist[1000];
int visited[1000];
int p[1000];


void dijkstra(int s) {
    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        p[i] = -1;
    }

    dist[s] = 0;
    PQ.push(Node(s, 0));

    while(!PQ.empty()) {
        Node u = PQ.top();
        PQ.pop();

        if(visited[u.at]) continue;

        visited[u.at] = 1;

        for(Edge e: adj[u.at]) {
            if(dist[e.v] > u.cost + e.w) {
                dist[e.v] = u.cost + e.w;
                PQ.push(Node(e.v, dist[e.v]));
                p[e.v] = u.at;
            }
        }
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
        adj[u].push_back(Edge(v, w));
    }

    cin >> s >> d;

    dijkstra(s);


    cout << "Shortest path cost: " << dist[d] << endl;

    printPath(s, d);

}
