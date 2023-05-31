#include<iostream>
#include<climits>
#include<cmath>

#define ll long long
#define INF 10000000007

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

void floyd_warshell() {
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
            }
        }
    }
}


int main() {

    int m;
    ll a, b, w;
    cin >> n >> m;

    init();


    for(int i = 0; i < m; i++) {
        cin >> a >> b >> w;

        W[a-1][b-1] = w;
    }

    floyd_warshell();
    cout << "Shortest distance matrix" << endl;
    print2D();

    return 0;
}

