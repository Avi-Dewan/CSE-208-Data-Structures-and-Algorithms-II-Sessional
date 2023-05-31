#include<iostream>
#include<climits>
#include<cmath>

#define ll long long
#define INF INT_MAX

using namespace std;

int n;
ll W[100][100];

void init() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            i == j ? W[i][j] = 0: W[i][j] = INF;
}

void print2D() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(W[i][j] < INF) cout << W[i][j] << " ";
            else cout << "INF ";
        }


        cout << endl;
    }

}


void extend_shortest_paths() {
  for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
            }
        }
    }
}

void fast_APSP() {
    int m = 1;

    while(m < n-1) {
        extend_shortest_paths();
        m *= 2;
    }
}


int main() {
    int t = 1000;

    while( t != 0) {
        int m;
        ll a, b, w;
        cin >> n >> m;

        init();


        for(int i = 0; i < m; i++) {
            cin >> a >> b >> w;

            W[a-1][b-1] = w;
        }

        fast_APSP();

        cout << "Shortest distance matrix: " << endl;

        print2D();

    }





    return 0;
}
