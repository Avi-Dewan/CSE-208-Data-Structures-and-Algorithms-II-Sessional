#include <iostream>
#include<vector>
#include<queue>
#include<utility>
#include<climits>
#include <algorithm>
using namespace std;

typedef pair<int, double> PII;
//weighted adjacency list

vector<PII> V[100];

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


bool operator<(Edge A, Edge B) {
    return A.w > B.w;
}

priority_queue<Edge> PQ;
vector <Edge> E, primEdge, krusEdge; // Edge list


int min_cost[1000]; //min_cost to include the node on MST(for PRIM)
int visited[1000]; // Whether the node is already visited or not
int p[100]; // array to keep track of parents for union find(for KRUSGAL)

double prim(int n, int s) {

    for(int i = 0; i < n; i++) {
        min_cost[i] = INT_MAX;
        visited[i] = 0;
    }

    min_cost[s] = 0;

    for(PII v: V[s]) {
        if(visited[v.first]) continue;

        if(v.second < min_cost[v.first]) {
            PQ.push(Edge(s, v.first, v.second));
            min_cost[v.first] = v.second;
        }
    }


    double ans = 0;

    while(!PQ.empty()) {
        Edge e = PQ.top();
        PQ.pop();

        if(visited[e.v]) {
            continue;
        }

        visited[e.v] = 1;

        ans += e.w;
        primEdge.push_back(e);

        for(PII v: V[e.v]) {
            if(visited[v.first]) continue;

            if(v.second < min_cost[v.first]) {
                PQ.push(Edge(e.v, v.first, v.second));
                min_cost[v.first] = v.second;
            }
        }

    }

    return ans;
}

int find(int x) {
    if(p[x] == x) return x;

    return p[x] = find(p[x]);

}

double kruskal() {
    sort(E.begin(), E.end());

    for(int i = 0; i < 100; i++) p[i] = i;

    int sz = E.size();
    double ans = 0;

    for(int i = sz-1; i >= 0 ; i--) {
        if(find(E[i].u)  != find(E[i].v)) {
            p[p[E[i].u]] = p[E[i].v];
            ans += E[i].w;
            krusEdge.push_back(E[i]);
         }
    }

    return ans;

}

int main() {

    freopen("mst.in", "r", stdin);

    int n, e, u, v;
    double w;

    cin >> n >> e;

//    for(int i = 0; i < 100; i++) p[i] = i;

    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;

        V[u].push_back(PII(v, w));
        V[v].push_back(PII(u,w));

        E.push_back(Edge(u, v, w));

    }

    double pCost = prim(n, 0) ;
    double kCost = kruskal();

    if(pCost == kCost) {
        cout << "Cost of minimum spanning tree: " << pCost << endl;
        cout << "List of edges selected by Prim's: {";

        for(int i = 0; i < primEdge.size(); i++) {
            cout << "(" << primEdge[i].u << "," << primEdge[i].v << ")";

            if(i != primEdge.size()-1) {
                cout << ",";
            }
        }

        cout << " }" << endl;


        cout << "List of edges selected by Kruskal's: {";

        for(int i = 0; i < krusEdge.size(); i++) {
            cout << "(" << krusEdge[i].u << "," << krusEdge[i].v << ")";

            if(i != krusEdge.size()-1) {
                cout << ",";
            }
        }

        cout << " }" << endl;
    }

    return 0;
}

