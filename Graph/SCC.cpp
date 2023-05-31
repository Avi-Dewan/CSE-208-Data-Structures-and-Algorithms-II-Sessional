#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj(100000), adj_rev(100000);
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {

    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);
    cout << v << " ";
    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

int main() {
    int n, e, a, b;

    cin >> n >> e;

    for (int i = 0; i < e; i++) {

        cin >> a >> b;

        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }

    used.assign(n, false);

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs1(i);

    cout << endl;
    used.assign(n, false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
        cout << (int)v << endl;
        if (!used[v]) {
            dfs2 (v);

            // ... processing next component ...

            for(int i = 0; i < component.size(); i++)
                cout << component[i] << " ";


            cout << endl;

            component.clear();
        }
    }


    return 0;
}

