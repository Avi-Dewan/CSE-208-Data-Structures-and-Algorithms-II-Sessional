
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> g[(int)1e5+5] ;
bool used[(int)1e5+5] ;

vector<int> comp ;

void dfs(int v) {
    used[v] = true ;
    comp.push_back(v);
    for (size_t i = 0; i < (int) g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs(to);
    }
}

void find_comps() {
    for (int i = 0; i < n ; ++i)
        used [i] = false;

    int countComp = 0;

    for (int i = 0; i < n ; ++i)
        if (!used[i]) {
            comp.clear();
            dfs(i);
            countComp++;
//            cout << "Component:" ;
//            for (size_t j = 0; j < comp.size(); ++j)
//                cout << ' ' << comp[j];
//            cout << endl ;
        }

        cout  << countComp << endl;
}

int main() {
    int t = 1, e, a, b;

    //cin >> t;

    while(t--) {
        cin >> n >> e;

        for(int i = 0; i < e; i++) {
            cin >> a >> b;
            g[a].push_back(b);
        }

        find_comps();
    }



    return 0;
}
