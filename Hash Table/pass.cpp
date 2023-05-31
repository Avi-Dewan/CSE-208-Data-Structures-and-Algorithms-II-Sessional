#include<iostream>
#include<string>

using namespace std;

class Node{
public:
    int value;
    string key;
    Node *left, *right;

    Node() {
        left = right = NULL;
    }

    Node(string key, int value) {
        this->key = key;
        this->value = value;
        left = right = NULL;
    }

};


class LinkedList{
public:

    Node *head;

    LinkedList(Node *n = NULL) {
        head = n;
    }

    void addNode(Node *n) {
        if(head == NULL) {
            head = n;
        } else {
            n->right = head;
            head->left =n;
            head = n;
        }

    }

    void deleteNodeHelp(Node *n) {

        //should we delete here ?

        if(n == head) {
            n->right->left = NULL;
            head = n->right;
        } else if(n->right == NULL) {
            n->left->right = NULL;
        } else {
            n->left->right = n->right;
            n->right->left = n->left;
        }

    }

    bool deleteNode(string key) {

        Node *n = head;

        while(n != NULL) {
            if(n->key == key) {
                deleteNodeHelp(n);
                return true;
            }

            n = n->right;
        }

        return false;

    }

    int searchNode(string key) {
        Node *s = head;

        while(s != NULL) {
            if(s->key == key) return s->value;

            s = s->right;
        }


        return -1;
    }

    ~LinkedList() {

        Node *temp = NULL;

        while(head = NULL) {
            temp = head;
            head = head->right;

            delete temp;
        }
    }

};


string randWord(int n) {

    int r;
    char c;
    string s = "";
    for (int i = 0; i < n; i++) {
          r = rand() % 26;   // generate a random number
          c = 'a' + r;            // Convert to a character from a-z

          //c = (r % 2 == 0)? 'a' + r : 'A' + r;
          s += c;
    }

    return s;
}

int h1(string key, int n) {

    int s = key.size();

    long long int result = 0;

    for(int i = 0; i < s; i++){
        result = (result + key[i])* 1234567891;
        result = result % n;
    }
    return (result % n);
}



int h2(string key, int n)
{
    int s = key.size();

    long long int result = 0;

    for(int i = 0; i < s; i++){
        result += 31 * result + key[i];
        result = result % n;
    }
    return (result % n);
}

class HashTableSC{


public:

    LinkedList *T;
    int n;

    HashTableSC(int n) {
        this->n = n;
        T = new LinkedList[n];
    }

    bool insertHT(Node *p) {

        int i = h1(p->key, n);

        if(T[i].searchNode(p->key) != -1) return false;

        T[i].addNode(p);

        return true;
    }

    int searchHT(string key){
        int i = h1(key, n);

        return T[i].searchNode(key);
    }

    bool deleteHT(string key) {
        int i = h1(key, n);

        return T[i].deleteNode(key);


    }

};

class NodeP{
public:
    string key;
    int value;

    NodeP() {

    }

    NodeP(string key, int value) {
        this->key = key;
        this->value = value;
    }
};

class HashTableProb{


public:

    NodeP **T;
    int n;
    int prob;
    NodeP *nil, *deleted;

//    int null = 0, deleted = -1, filled = 1;

    HashTableProb(int n, int prob) {
        this->n = n;
        this->prob = prob;
        T = new NodeP*[n];

        nil = NULL;
        deleted = new NodeP("deleted", -1);

        for(int i = 0; i < n; i++) {
            T[i] = nil;
        }

    }


    bool linearProb(NodeP *p) {

        int j = h1(p->key, n);

        for(int i= 0; i < n; i++) {
            j = (j + i) % n;
            NodeP *t = T[j];
            if(t == nil || t == deleted) {
                T[j] = p;
                return true;
            }
        }

        return false;
    }

    bool quadricProb(NodeP *p) {

        int j = h1(p->key, n);

        for(int i= 0; i < n; i++) {
            j = (j + i) % n;
            NodeP *t = T[j];
            if(t == nil || t == deleted) {
                T[j] = p;
                return true;
            }
        }

        return false;
    }

    bool doubleHash(NodeP *p) {

        int j = h1(p->key, n), k = h2(p->key, n);

        for(int i= 0; i < n; i++) {
            j = (j + k*i) % n;

            NodeP *t = T[j];
            if(t == nil || t == deleted) {
                T[j] = p;
                return true;
            }


//            if(check[j] == null || check[j] == deleted) {
//                T[j] = *p;
//                check[j] = filled;
//                return true;
//            }



        }

        return false;
    }

    bool insertHT(NodeP *p) {

        if(searchIndexHT(p->key) != -1) return false;

        switch(prob) {
        case  1:
            return linearProb(p);
            break;

        case 2:
            return quadricProb(p);
            break;
        case 3:
            return doubleHash(p);
        }
    }

    int linearProbSearch(string key) {

        int j = h1(key, n);

        for(int i= 0; i < n; i++) {

            j = (j + i) % n;

            NodeP *t = T[j];

            if(t == deleted) {
                continue;
            }

            if(t == nil) {
                break;
            }

            if(t->key == key) {
                return j;
            }
        }

        return -1;
    }

    int quadricProbSearch(string key) {

        int j = h1(key, n);

        for(int i= 0; i < n; i++) {

            j = (j + i) % n;

            NodeP *t = T[j];

            if(t == deleted) {
                continue;
            }

            if(t == nil) {
                break;
            }

            if(t->key == key) {
                return j;
            }

//           if(T[j].key == key) {
//                return j;
//            }
//
//            if(check[j] == null) break;
        }

        return -1;
    }

    int doubleHashSearch(string key) {

        int j = h1(key, n), k = h2(key, n);

        for(int i= 0; i < n; i++) {

            j = ( j + k*i ) % n;

            NodeP *t = T[j];

            if(t == deleted) {
                continue;
            }

            if(t == nil) {
                break;
            }

            if(t->key == key) {
                return j;
            }
        }

        return -1;
    }

    int searchIndexHT(string key){

        switch(prob) {
        case  1:
            return linearProbSearch(key);
            break;

        case 2:
            return quadricProbSearch(key);
            break;
        case 3:
            return doubleHashSearch(key);
        }
    }

    int searchHT(string key) {
        int j = searchIndexHT(key);



        if(j == -1) return -1;

        else {
            cout << j << " " << T[j]->key  << " " << T[j]->value << endl;
            return T[j]->value;
        }
    }


    bool deleteHT(string key) {

        int j = searchIndexHT(key);

        if(j == -1) return false;

        else T[j] = deleted;
        return true;

//        switch(prob) {
//        case  1:
//            return deleteProb(key);
//            break;
//
//        case 2:
//            return deleteProb(key);
//            break;
//        case 3:
//            return deleteHash(key);
//        }


    }

};




int main(){

    int n, t;

    string s;


    cin >> n >> t;

    HashTableProb H(n, 3);
    NodeP *a[t+5];

    for(int i = 0; i < t; i++) {
//        s = randWord(7);

        cin >> s;

        a[i] = new NodeP(s, i+1);

        cout  << H.insertHT(a[i]) << endl;
    }

    int k, c;

    cin >> k;

    while(k--) {
        cin >> c >> s;
        if(c == 1) {
            cout << H.deleteHT(s) << endl;
        } else if(c == 2) {

            NodeP *m = H.searchHT(s);
            if( m != NULL) {
                cout << m->value << " " << m->prob << endl;
            }
        } else if(c == 3) {

            a[t] = new NodeP(s, t+1);

            cout << H.insertHT(a[t]) << endl;
            t++;
        }
    }
}


/*

10 9
ancient
pazzled
zigzags
benefit
asdfe
zigzags
ancient
aidsuf
bendsf

*/

