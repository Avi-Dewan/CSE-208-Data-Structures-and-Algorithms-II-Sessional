#include<iostream>

using namespace std;



class Node{
public:
    Node *p, *left, *right;
    int key, color;


    Node() {
    }


    Node(int key, int color = 1) {
        this->key = key;
        this->color = color;

    }

};

class RED_BLACK_TREE{
public:
    Node *root, *nil;
    const int red = 1, black = 2;

    RED_BLACK_TREE() {

        nil = new Node();
        nil->color = black;

        root = nil;



    }

/*
            y          <---- LEFT Rotate(x)           x
        x       b      RIGHT Rotate(y)---->        a      y
      a   c                                              c  b

*/

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;

        if(y->left != nil) y->left->p = x;
        y->p = x->p;

        if(x->p == nil) root = y;
        else if(x == x->p->left) x->p->left = y;
        else x->p->right = y;

        y->left = x;
        x->p = y;
    }


    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;

        if(x->right != nil) x->right->p = y;
        x->p = y->p;

        if(y->p == nil) root = x;
        else if(y == y->p->left) y->p->left = x;
        else y->p->right = x;

        x->right = y;
        y->p = x;
    }

    //INSERT

    void RBinsert_fixup(Node *z) {
        while(z->p->color == red) {
            if(z->p == z->p->p->left) {

                Node *y = z->p->p->right;

                if(y->color == red) {           //case 1 : z's uncle y is red
                    z->p->color = black;
                    y->color = black;
                    z->p->p->color = red;
                    z = z->p->p;
                } else {
                    if(z == z->p->right) {      //case 2: z's uncle y is black and z is a right child
                        z = z->p;
                        leftRotate(z);
                    }

                    z->p->color = black;         //case 2: z's uncle y is black and z is a left child
                    z->p->p->color = red;
                    rightRotate(z->p->p);

                }
            } else {

                Node *y = z->p->p->left;

                if(y->color == red) {           //case 1 : z's uncle y is red
                    z->p->color = black;
                    y->color = black;
                    z->p->p->color = red;
                    z = z->p->p;
                } else {
                    if(z == z->p->left) {      //case 2: z's uncle y is black and z is a left child
                        z = z->p;
                        rightRotate(z);
                    }

                    z->p->color = black;         //case 2: z's uncle y is black and z is a right child
                    z->p->p->color = red;
                    leftRotate(z->p->p);

                }

            }
        }


        root->color = black;
    }


    bool RBinsert(int k) {

        Node *z = new Node(k);

        Node *y = nil;
        Node *x = root;

//        cout << nil->color << endl;

        while(x != nil) {

            y = x;
            if(z->key < x->key) x = x->left;
            else if(z->key > x->key) x = x->right;
            else return false;
        }

        z->p = y;

//        cout << nil->color << endl;

        if(y == nil) root = z;
        else if(z->key < y->key) y->left = z;
        else y->right = z;

        z->left = z->right = nil;
//        cout << nil->color << endl;
        z->color = red;

        RBinsert_fixup(z);


        return true;

    }

    //SEARCHING FROM KEY

    Node* searchHelp(Node *n, int key) {
        if(n == nil) return nil;

        if(key < n->key) return searchHelp(n->left, key);
        else if(key > n->key) return searchHelp(n->right, key);
        else return n;

    }

    bool RBsearch(const int key) {

        if(searchHelp(root, key) == nil) return false;

        return true;
    }

    Node* searchNode(const int key) {
        Node *z = searchHelp(root, key);

        return z;
    }



    //DELETION


    void transplant(Node *u, Node *v) {
        if(u->p == nil) root = v;
        else if( u == u->p->left) u->p->left = v;
        else u->p->right = v;

        v->p = u->p;

    }


    Node* treeMin(Node *z) {
        if(z->left == nil) return z;
        else return treeMin(z->left);
    }

    void RBdeleteFixUP(Node *x) {
        cout << x->color <<endl;
        while(x != root && x->color == black) {



            if(x == x->p->left) {

                Node *w = x->p->right;

                if(w->color == red) {       //  case 1: x's sibling w is red
//                    cout << "case 1" << endl;
                    w->color = black;
                    x->p->color = red;
                    leftRotate(x->p);
                    w = x->p->right;
                }

                if(w->left->color  == black && w->right->color == black) {  // case 2: x's sibling w is black, and both of w's children black
//                    cout << "case 2" << endl;
                    w->color = red;
                    x = x->p;
                } else {

                    if(w->right->color == black) {  // case 3:  x's sibling w is black, w's left child is red and w's right child is black
//                        cout << "case 3" << endl;
                        w->left->color = black;
                        w->color = red;
                        rightRotate(w);
                        w = x->p->right;
                    }

                                                //case 4:  x's sibling w is black, and w's right child is black
//                    cout << "case 4" << endl;
                    w->color = x->p->color;
                    x->p->color = black;
                    w->right->color = black;
                    leftRotate(x->p);
                    x = root;

                }


            } else {

                Node *w = x->p->left;

                if(w->color == red) {       //  case 1: x's sibling w is red
//                    cout << "case 5" << endl;
                    w->color = black;
                    x->p->color = red;
                    rightRotate(x->p);
                    w = x->p->left;
                }

                if(w->right->color  == black && w->left->color == black) {  // case 2: x's sibling w is black, and both of w's children black
//                    cout << "case 6" << endl;
                    w->color = red;
                    x = x->p;
                } else {

                    if(w->left->color == black) {  //case 3: x's sibling w is black, w's right child is red and w's left child is black
//                        cout << "case 7" << endl;
                        w->right->color = black;
                        w->color = red;
                        leftRotate(w);
                        w = x->p->left;
                    }

                                                //case 4: x's sibling w is black, and w's left child is black
//                    cout << "case 8" << endl;
                    w->color = x->p->color;
                    x->p->color = black;
                    w->left->color = black;
                    rightRotate(x->p);
                    x = root;

                }
            }

        }


        x->color = black;
    }


    bool RBdelete(int key) {

        Node *z = searchNode(key);



        if(z == nil) return false;



        Node *y = z, *x = nil;
        int y_original_color = y->color;

        if(z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if(z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = treeMin(z->right);
            y_original_color = y->color;
            x = y->right;

            if(y->p == z) {
                x->p = y;
            }
            else {

                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;

        }

        if(y_original_color == black) RBdeleteFixUP(x);

        return true;

    }



    int countNodeTree(Node *a) {
        if(a == nil)
            return 0;
        else
            return 1 + countNodeTree(a->left) + countNodeTree(a->right);
    }

    int lessKeyHelp(Node *z, int p) {
        if(z == nil) return 0;

        if(z-> key < p) return 1 + lessKeyHelp(z->left, p) + lessKeyHelp(z->right, p);
        else return lessKeyHelp(z->left, p);
    }

    int lessKey(int p) {

        return lessKeyHelp(root, p);

    }






    void printTree(Node *x) {
        if(x == nil) return;

        cout << "(" ;

        printTree(x->left);

        cout << ") " << x->key << "[" << x->color << "] " << " (";

        printTree(x->right);

        cout << ")";
    }







};

int main()
{

    RED_BLACK_TREE T;

/*

    int k = 3, i = 0;;


    cout << "inserting...." << T.nil->color << endl;

    while (true) {
        cin >> k;

        if(k < 0) break;

        T.RBinsert(k);

        i++;

        T.printTree(T.root);

        cout << endl;
    }

    cout << "finding...." << endl;

    while (true) {
        cin >> k;

        if(k < 0) break;


        cout << T.RBsearch(k) << endl;
    }

    cout << "Deleting...." << endl;


    while (true) {
        cin >> k;

        if(k < 0) break;


        T.RBdelete(k);

        T.printTree(T.root);

        cout << endl;
    }
*/




    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n, e, x;

    cin >> n;

    cout << n << endl;

    for(int i = 0; i < n; i++) {
        cin >> e >> x;

        switch(e)
        {
            case 0:
                cout << e << " " << x << " " << (int)T.RBdelete(x) << endl;
                break;
            case 1:
                cout << e << " " << x << " " << (int)T.RBinsert(x) << endl;
                break;
            case 2:
                cout << e << " " << x << " " << (int)T.RBsearch(x) << endl;
                break;
            case 3:
                cout << e << " " << x << " " << T.lessKey(x) << endl;

        }
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}

// 7 2 11 1 8 14 15 5 4

/*
11
1 1
1 2
1 3
1 1
0 1
0 4
2 3
2 5
1 1
3 3
3 6
*/
