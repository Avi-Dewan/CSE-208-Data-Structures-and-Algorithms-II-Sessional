#include<iostream>
#include<cmath>

using namespace std;

class NodeF;
void showList(NodeF *x);

class NodeF{
public:
    int degree;
    bool mark;
    NodeF *p, *child, *left, *right;
    int key;

    NodeF() {

    }

    NodeF(int key) {
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

//    void exchange(NodeF *x, NodeF *y) {
//        NodeF *tempL = x->left , *tempR = x->right;
//
//        x->left = y->left;
//        x->right = y->right;
//        y->left = tempL;
//        y->right = tempR;
//
//        cout << "f3.5: " << x->key << " " << y->key   << endl;
//    }

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

//        cout << "f1" << endl;

        NodeF *A[D];
//        cout << "f2" << endl;

        for(int i = 0; i < D; i++) A[i] = NULL;

        NodeF *x = min;
        NodeF *m = min->left;



        while(true) {

            int d = x->degree;

//            cout << "f2.5: "  << d << " " << A[d] << endl;

            while(A[d] != NULL) {
                NodeF *y = A[d];

//                cout << "f3: " << x->key << " " << y->key << endl;

                if(x->key > y->key) {
//                    exchange(x, y);

                    int temp = x->key;
                    NodeF *tempC = x->child;

                    x->key = y->key;
                    x->child = y->child;

                    y->key = temp;
                    y->child = tempC;
                }

//                cout << "f4: " << x->key << " " << y->key  << endl;

                fib_heap_link(y, x);
                A[d] = NULL;
                d++;

//                cout << "f5: " << x->key <<  " " << x->degree << " " << y->key << endl;
//                cout << y->p->key << " " << x->child->key << endl;
            }

            A[d] = x;

            if(x == m)
                break;

            x = x->right;

//            cout << "f6 " << x->key <<endl;



        }

//        cout << "f7" << endl;

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

//        cout << "f8" << endl;

    }

    NodeF* extract_min() {
        NodeF *z = min;

        if(z != NULL) {

//            cout << "e1: " << z->degree << endl;

            NodeF *x = z->child;

            for(int i = 0; i < z->degree; i++) {

                NodeF *y = x->right;
//                cout << x->key << endl;

                addLeft(min, x);

                x->p = NULL;
                x = y;
            }

//            cout << "e2: "<< z->right->key <<  endl;

//            showList(min);

            delNode(z);

            if(n == 1) {
//                cout << "e3" << endl;
                min = NULL;
            } else {
                min = z->right;

//                cout << "e4: " << min->key << endl;

                consolidate();
//                cout << "h" << endl;
            }

            n--;

        }

        return z;

    }

};





//void showList(int n, NodeF *x) {
//    for(int i = 0; i < n; i++) {
//        cout << x->key << " ";
//        x = x->right;
//    }
//    cout << endl;
//    x = x->right;
//}

void showList(NodeF *x) {
    NodeF *e = x;

    while(true) {
        cout << x->key << " ";

        if(x->degree > 0) {
            cout <<  "\n{ c: \n";
            showList(x->child);
            cout << "}" << endl;
        }

        x = x->right;

        if(x == e) break;
    }

    cout << endl;
}


int main()
{
    fibonacciHeap H;


    NodeF n(5), m(3), n2(7), n4(2), n5(1), n3(8);


    int x = 1, i = 0;

    NodeF a[50];

    while(x > 0) {

        cin >> x;

        a[i] = NodeF(x);


        H.insert(&a[i]);

        showList( H.min);

        i++;
    }


     NodeF *z = NULL;

     while(H.n != 0) {

        z = H.extract_min();

         cout << z->key << endl;

         cout << H.n << endl;

         showList( H.min);

         cout << "--------------------" << endl;

         cin >> x;
         a[i] = NodeF(x);
         if(x != 0) {
            H.insert(&a[i]);
         }
         i++;

     }





/*


    H.insert(&n);
    H.insert(&m);
    H.insert(&n2);

    showList(H.n, H.min);

    H.insert(&n4);

    showList(H.n, H.min);

    showList(H.n, H.min);
    H.insert(&n5);
    showList(H.n, H.min);
    H.insert(&n3);
    showList(H.n, H.min);

*/
    return 0;
}


/*

#include<chrono>
...
Using namespace std::chrono

//Start
Auto start = high_resolution_clock::now()
...
Auto end .... Same as the line before
Auto duration = duration_cast<microseconds>(stop-start)
Cout << duration.count()

*/
