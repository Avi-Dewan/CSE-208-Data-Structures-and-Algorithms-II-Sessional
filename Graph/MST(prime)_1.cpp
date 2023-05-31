#include <iostream>
#include<vector>
#include<queue>
#include<utility>
#include<climits>

using namespace std;

typedef pair<int, double> PII;
//weighted adjacency list

vector<PII> V[100];


class Node {
public:
    int u;
    double cost;

    Node() {

    }

    Node(int u, double cost) {
        this->u = u;
        this->cost = cost;
    }
};

bool operator<(Node A, Node B) {
    return A.cost > B.cost;
}

priority_queue<Node> PQ;

int min_cost[1000];

int visited[1000];


double prim(int n, int s) {

    for(int i = 0; i < n; i++) {
        min_cost[i] = INT_MAX;
        visited[i] = 0;
    }

    min_cost[s] = 0;
    PQ.push(Node(s, 0));

    double ans = 0;

    while(!PQ.empty()) {
        Node x = PQ.top();
        PQ.pop();

        if(visited[x.u]) {
            continue;
        }

        visited[x.u] = 1;

        ans += x.cost;

//        cout << "Selected node and the cost: "  << x.u << ", " << x.cost << endl;

        for(PII v: V[x.u]) {
            if(visited[v.first]) continue;

            if(v.second < min_cost[v.first]) {
                PQ.push(Node(v.first, v.second));
                min_cost[v.first] = v.second;
            }
        }

    }

    return ans;


}

int main() {

    int n, e, u, v;
    double w;

    cin >> n >> e;

//    for(int i = 0; i < 100; i++) p[i] = i;

    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;

        PII p = PII(v, w);

        V[u].push_back(p);
        V[v].push_back(PII(u,w));

        for(PII t: V[u]) {
            cout << "| " << t.first << " " << t.second ;
        }

        cout << endl;
    }

    cout << prim(n, 0);

    return 0;
}







