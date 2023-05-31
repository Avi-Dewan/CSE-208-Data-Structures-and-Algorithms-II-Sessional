#include<iostream>
#include<climits>
#include<cmath>
#include<vector>

#define ll long long
#define INF INT_MAX

using namespace std;



void init(vector<vector<ll>> &v) {

    int n = v.size();

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            i == j ? v[i][j] = 0: v[i][j] = INF;
}

void print2D(vector<vector<ll>> &v) {

    int n = v.size();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(v[i][j] < INF) cout << v[i][j] << " ";
            else cout << "INF ";
        }


        cout << endl;
    }

}


void extend_shortest_paths(vector<vector<ll>> &l, vector<vector<ll>> &w) {

    int n = l.size();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                l[i][j] = min(l[i][j], l[i][k] + w[k][j]);
            }
        }
    }
}

void fast_APSP(vector<vector<ll>> &W) {

    int m = 1, n = W.size();
    while(m < n-1) {
        vector<vector<ll>> temp(W);
        extend_shortest_paths(W, temp);
        m *= 2;
    }
}


int main() {

    int m, n;
    ll a, b, w;
    cin >> n >> m;

    vector<vector <ll>> W(n, vector<ll>(n));

    init(W);

    for(int i = 0; i < m; i++) {
        cin >> a >> b >> w;

        W[a-1][b-1] = w;
    }

    fast_APSP(W);

    cout << "Shortest distance matrix" << endl;

    print2D(W);

    return 0;
}

