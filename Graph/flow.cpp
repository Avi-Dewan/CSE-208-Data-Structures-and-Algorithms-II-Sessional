#include<vector>
#include<iostream>
#include<queue>

#define INF INT_MAX

using namespace std;

vector<vector< pair<int, int>>> createGraph(int idx, int n, vector<int> &win, vector<int> &remain, vector<vector<int>> &matches ) {

    vector<vector< pair<int, int>>> ad(n+2);

    for(int i = 0; i < n; i++) {

        ad[i].push_back({n+1, win[idx] + remain[idx] - win[i]});
    }

    vector<vector<int>> gameNodes;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i < j && i != idx && j!= idx) {
                ad.push_back(vector<pair<int,int>>());
                ad[n].push_back({ad.size()-1, matches[i][j]});
                ad[ad.size()-1].push_back({i, INF});
                ad[ad.size()-1].push_back({j, INF});
            }
        }
    }

    return ad;
}

//
//vector<vector<int>> capacity;
//vector<vector<int>> adj;

int bfs(int s, int t, int n,  vector<int>& parent, vector<vector<int>> &adj, vector<vector<int>> &capacity) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

bool maxflow(int s, int t, int n, vector<vector<int>> &adj, vector<vector<int>> &capacity) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, n,  parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

//    return flow;



    for(int node : adj[s]) {
        if(capacity[s][node] != 0 ) {
            return false;
        }
    }

    return true;
}



int main() {

    int n;
    cin >> n;

    vector<string> names(n);
    vector<int> win(n), lose(n), remain(n);

    vector<vector<int>> matches(n, vector<int>(n));

    for(int i = 0; i < n ; i++) {
        cin >> names[i] >> win[i] >> lose[i] >> remain[i];

        for(int j = 0; j < n; j++) {
            cin >> matches[i][j];
        }

    }

    for(int x = 0; x < n; x++) {
        vector<vector< pair<int, int>>> ad = createGraph(x, n, win, remain, matches);

        vector<vector<int>> capacity(ad.size(), vector<int>(ad.size(), 0));
        vector<vector<int>> adj(ad.size());

        for(int i = 0; i < ad.size(); i++) {
            for(int j = 0; j < ad[i].size(); j++) {
                adj[i].push_back(ad[i][j].first);
                capacity[i][ad[i][j].first] = ad[i][j].second;
            }
        }

        if(!maxflow(n, n+1, ad.size(), adj, capacity)) {
            cout << names[x] <<  " eliminated " << endl;
        }

    }



    return 0;
}

/*
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0
*/
