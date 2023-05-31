#include<iostream>
#include<algorithm>

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


bool operator<(Edge A, Edge B) {
    return A.w > B.w;
}

vector <Edge> E; // Edge list

int p[100]; // array to keep track of parents for union find


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
         }
    }

    return ans;

}

int main() {

    int n, e, u, v;
    double w;

    cin >> n >> e;



    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        E.push_back(Edge(u, v, w));
    }

    cout << kruskal();


    return 0;
}
