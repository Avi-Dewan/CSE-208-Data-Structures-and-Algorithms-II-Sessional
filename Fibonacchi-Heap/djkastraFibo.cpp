#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<cmath>
#include<chrono>
#include <ctime>


using namespace std;
using namespace std::chrono;

class NodeF{
public:
    int degree;
    bool mark;
    NodeF *p, *child, *left, *right;
    int key, at;

    NodeF() {

    }

    NodeF(int at, int key) {
        this->at = at;
        this->key = key;
    }

};

class fibonacciHeap{
public:
    NodeF *min;
    int n;

    fibonacciHeap() {
        n = 0;
        min = NULL;
    }

    void addLeft(NodeF *m,  NodeF *x) { //adding x node on left of Node m
        m->left->right = x;
        x->right = m;
        x->left = m->left;
        m->left = x;
    }

    void delNode(NodeF *x) {
        x->left->right = x->right;
        x->right->left = x->left;
    }

    void insert(NodeF *x) {
        x->degree = 0;
        x->p = NULL;
        x->child = x->left = x->right = NULL;
        x->mark = false;

        if(min == NULL) {
            min = x;
            min->right = min->left = min;
        } else {

            addLeft(min, x);

            if(x->key < min->key) min = x;
        }

        n++;
    }

    void fib_heap_link(NodeF *y, NodeF *x) {

        delNode(y);

        if(x->child == NULL) {
            x->child = y;
            y->left = y->right = y;
        } else {
            addLeft(x->child, y);
        }

        y->p = x;

        x->degree++;

        y->mark = false;

    }

    void consolidate() {

        int D = log2(n) + 2;


        NodeF *A[D];

        for(int i = 0; i < D; i++) A[i] = NULL;

        NodeF *x = min;
        NodeF *m = min->left;



        while(true) {

            int d = x->degree;


            while(A[d] != NULL) {
                NodeF *y = A[d];



                if(x->key > y->key) {


                    int tempAt = x->at, tempK = x->key;
                    NodeF *tempC = x->child;

                    x->at = y->at;
                    x->key = y->key;
                    x->child = y->child;

                    y->at = tempAt;
                    y->key = tempK;
                    y->child = tempC;
                }


                fib_heap_link(y, x);
                A[d] = NULL;
                d++;

            }

            A[d] = x;

            if(x == m)
                break;

            x = x->right;
        }

        min = NULL;

        for(int i = 0; i < D; i++) {
            if(A[i] != NULL)  {
                if(min == NULL) {
                    min = A[i];
                    min->right = min->left = min;
                } else {
                    addLeft(min, A[i]);

                    if(A[i]->key < min->key) min = A[i];
                }
            }
        }
    }

    NodeF* extract_min() {
        NodeF *z = min;

        if(z != NULL) {

            NodeF *x = z->child;

            for(int i = 0; i < z->degree; i++) {

                NodeF *y = x->right;

                addLeft(min, x);

                x->p = NULL;
                x = y;
            }

            delNode(z);

            if(n == 1) {

                min = NULL;
            } else {
                min = z->right;
                consolidate();
            }

            n--;

        }

        return z;

    }

};

class Node {
public:
    int at, cost;

    Node(int at, int cost) {
        this->at = at;
        this->cost = cost;
    }
};

bool operator<(Node A, Node B) {
    return A.cost > B.cost;
}


class Edge {
public:
    int v, w;
    Edge(int v, int w) {
        this->v = v;
        this->w = w;
    }
};


vector<Edge> adj[100000];
int n;


priority_queue<Node> PQ;

int dist[100000];
int visited[100000];
int p[100000];
int length[100000];


void dijkstra(int s) {
    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        length[i] = INT_MAX;
        visited[i] = 0;
        p[i] = -1;
    }

    dist[s] = 0;
    length[s] = 0;
    PQ.push(Node(s, 0));

    while(!PQ.empty()) {
        Node u = PQ.top();
        PQ.pop();

        if(visited[u.at]) continue;

        visited[u.at] = 1;

        for(Edge e: adj[u.at]) {
            if(dist[e.v] > u.cost + e.w) {
                dist[e.v] = u.cost + e.w;
                length[e.v] = length[u.at] + 1;
                PQ.push(Node(e.v, dist[e.v]));
                p[e.v] = u.at;
            }
        }
    }

}

void printPath(int s, int d) {
    vector<int> path;

    path.push_back(d);

    cout << "Bin : ";

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


int distF[100000];
int lengthF[100000];
int visitedF[100000];
int pF[100000];


void dijkstraFibo(int s) {
    for(int i = 0; i < n; i++) {
        distF[i] = INT_MAX;
        lengthF[i] = INT_MAX;
        visitedF[i] = 0;
        pF[i] = -1;
    }

    fibonacciHeap H;
    int i = 0;

    NodeF a[n+10];

    a[i] = NodeF(s, 0);

    distF[s] = 0;
    lengthF[s] = 0;

    H.insert(&a[i]);
    i++;

    while(H.n != 0) {
        NodeF *u = H.extract_min();

        if(visitedF[u->at]) continue;

        visitedF[u->at] = 1;

        for(Edge e: adj[u->at]) {
            if(distF[e.v] > u->key + e.w) {
                distF[e.v] = u->key + e.w;
                lengthF[e.v] = lengthF[u->at] + 1;
                a[i] = NodeF(e.v, distF[e.v]);
                H.insert(&a[i]);
                i++;
                pF[e.v] = u->at;
            }
        }
    }

}

void printPathF(int s, int d) {
    vector<int> path;

    path.push_back(d);

    cout << "Fibo: " ;

    while(d != s) {
        d = pF[d];
        path.push_back(d);
    }

    for(int i = path.size()-1; i >= 0; i--) {
        cout << path[i];

        if(i != 0) cout << " -> ";
    }

    cout << endl;
}





int main() {

    int e, u, v, w, k, s, d;

    freopen("in1.txt", "r", stdin);

    cin >> n >> e;

    for(int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        adj[u].push_back(Edge(v, w));
        adj[v].push_back(Edge(u, w));
    }

    fclose(stdin);

//
//    cin >> s >> d;
//
//    dijkstra(s);
//    dijkstraFibo(s);
//
//    cout << "Shortest path cost(Bin) : " << dist[d] << " " << length[d] << endl;
//    cout << "Shortest path cost(Fibo): " << distF[d] << " " << lengthF[d] << endl;
//    printPath(s, d);
//    printPathF(s, d);


    freopen("in2.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin >> k;

    for(int i = 0; i < k; i++) {
        cin >> s >> d;

        double tDjk = 0, tFib = 0;

        //Start
        auto start = high_resolution_clock::now();
        dijkstra(s);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop-start);
        tDjk = duration.count();



        start = high_resolution_clock::now();
        dijkstraFibo(s);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop-start);
        tDjk = duration.count();

//        clock_t insertion = clock();
//        dijkstra(s);
//        tDjk = double((clock() - insertion ) / CLOCKS_PER_SEC);
//
//        insertion = clock();
//        dijkstraFibo(s);
//        tFib = double((clock() - insertion) / CLOCKS_PER_SEC);

        cout << lengthF[d] << "\t" << distF[d] << "\t" << tDjk << "\t" << tFib << endl;
    }

    fclose(stdin);
    fclose(stdout);


    return 0;

}
