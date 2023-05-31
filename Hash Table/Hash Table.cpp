#include<iostream>
#include<string>
#include<chrono>
#include <ctime>
#include<vector>

using namespace std;
using namespace std::chrono;

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

        Node *temp = n;

        if(n == head) {
            if(n->right != NULL)
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


string randWordGenerator(int n) {

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

    ~HashTableSC() {
        delete T;
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
    int prob;

    NodeP() {

    }

    NodeP(string key, int value) {
        this->key = key;
        this->value = value;
        prob = 0;
    }
};

class HashTableProb{


public:

    NodeP **T;
    int n;
    int prob;
    NodeP *nil, *deleted;


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

    ~HashTableProb() {


        delete T;
        delete deleted;
    }


    bool linearProb(NodeP *p) {

        int j = h1(p->key, n);

        for(int i= 0; i < n; i++) {
            j = (j + i) % n;

            p->prob++;
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
            p->prob++;
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
            p->prob++;
            NodeP *t = T[j];
            if(t == nil || t == deleted) {
                T[j] = p;
                return true;
            }

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

    NodeP* searchHT(string key) {
        int j = searchIndexHT(key);

        if(j == -1) return NULL;
        else return T[j];

    }


    bool deleteHT(string key) {

        int j = searchIndexHT(key);

        if(j == -1) return false;

        NodeP *temp = T[j];

        T[j] = deleted;
        delete temp;

        return true;

    }

};




int main(){

//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);

    int N;

    double load[6] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    cin >> N;

    vector<string> randomWord(N);

    for(int i = 0; i < N; i++) randomWord[i] = randWordGenerator(7);

    double bDelSC[6][2], bDelLP[6][2], bDelQP[6][2], bDelDH[6][2], aDelSC[6][2], aDelLP[6][2], aDelQP[6][2], aDelDH[6][2];

    for(int l = 0; l < 6; l++) {
        HashTableSC H1(N);
        HashTableProb H2(N, 1);
        HashTableProb H3(N, 2);
        HashTableProb H4(N, 3);

        int n = (int)N*load[l];

        int value = 1;

        for(int i = 0; i < n; i++) {

            Node *a = new Node(randomWord[i], value);
            NodeP *b = new NodeP(randomWord[i], value);
            NodeP *c = new NodeP(randomWord[i], value);
            NodeP *d = new NodeP(randomWord[i], value);

            H1.insertHT(a);
            H2.insertHT(b);
            H3.insertHT(c);
            if(H4.insertHT(d)) {
                value++;
            }
        }

        //search


        double totalTime1 = 0, totalTime2 = 0, totalTime3 = 0, totalTime4 = 0;
        double totalProb1 = -1, totalProb2 = 0, totalProb3 = 0, totalProb4 = 0;

        int tenthN = n/10;

        int searchN = tenthN;




        while(searchN--) {

            int x = rand() % n;

            auto start = high_resolution_clock::now();
            H1.searchHT(randomWord[x]);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop-start);
            totalTime1 += duration.count();


            start = high_resolution_clock::now();
            NodeP* a = H2.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime2 += duration.count();
            if(a != NULL) {
                totalProb2 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H3.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime3 += duration.count();
            if(a != NULL) {
                totalProb3 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H4.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime4 += duration.count();
            if(a != NULL) {
                totalProb4 += a->prob;
            }

        }

        // avgTime and avgProb updating

        double avg0 = totalTime1*1.00 / tenthN, avg1 = -1 ;

        bDelSC[l][0] = avg0, bDelSC[l][1] = avg1;



        avg0 = totalTime2*1.00 / tenthN, avg1 = totalProb2/tenthN ;

        bDelLP[l][0] = avg0, bDelLP[l][1] = avg1;



        avg0 = totalTime3*1.00 / tenthN, avg1 = totalProb3/tenthN  ;

        bDelQP[l][0] = avg0, bDelQP[l][1] = avg1;



        avg0 = totalTime4*1.00 / tenthN, avg1 = totalProb4/tenthN  ;

        bDelDH[l][0] = avg0, bDelDH[l][1] = avg1;




        //delete

        int deleteN = tenthN;

        int idxDeleted[deleteN];

        int d = 0;

        while(deleteN--) {

            int x = rand() % n;

            idxDeleted[d++] = x;

            H1.deleteHT(randomWord[x]);

            H2.deleteHT(randomWord[x]);

            H3.deleteHT(randomWord[x]);

            H4.deleteHT(randomWord[x]);
        }




        //Again search after delete

        totalTime1 = 0, totalTime2 = 0, totalTime3 = 0, totalTime4 = 0;
        totalProb1 = -1, totalProb2 = 0, totalProb3 = 0, totalProb4 = 0;

        int searchHalf = tenthN/2;


        while(searchHalf--) {

            int x = rand() % n;

            auto start = high_resolution_clock::now();
            H1.searchHT(randomWord[x]);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop-start);
            totalTime1 += duration.count();


            start = high_resolution_clock::now();
            NodeP* a = H2.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime2 += duration.count();
            if(a != NULL) {
                totalProb2 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H3.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime3 += duration.count();
            if(a != NULL) {
                totalProb3 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H4.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime4 += duration.count();
            if(a != NULL) {
                totalProb4 += a->prob;
            }

        }



        searchHalf = tenthN / 2;

         while(searchHalf--) {

            d = rand() % tenthN;

            int x = (idxDeleted[d] % n);


            auto start = high_resolution_clock::now();
            H1.searchHT(randomWord[x]);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop-start);
            totalTime1 += duration.count();


            start = high_resolution_clock::now();
            NodeP* a = H2.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime2 += duration.count();
            if(a != NULL) {
                totalProb2 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H3.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime3 += duration.count();
            if(a != NULL) {
                totalProb3 += a->prob;
            }

            start = high_resolution_clock::now();
            a = H4.searchHT(randomWord[x]);
            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop-start);
            totalTime4 += duration.count();
            if(a != NULL) {
                totalProb4 += a->prob;
            }

        }




        avg0 = totalTime1*1.00 / tenthN, avg1 = -1 ;

        aDelSC[l][0] = avg0, aDelSC[l][1] = avg1;



        avg0 = totalTime2*1.00 / tenthN, avg1 = totalProb2/tenthN ;

        aDelLP[l][0] = avg0, aDelLP[l][1] = avg1;



        avg0 = totalTime3*1.00 / tenthN, avg1 = totalProb3/tenthN  ;

        aDelQP[l][0] = avg0, aDelQP[l][1] = avg1;



        avg0 = totalTime4*1.00 / tenthN, avg1 = totalProb4/tenthN  ;

        aDelDH[l][0] = avg0, aDelDH[l][1] = avg1;



    }

    cout << "\n\nTable 1: Performance of separate chaining in various load factors \n" <<endl;

    cout << "\t\t Before Deletion \t After Deletion" <<endl;
    cout << "Load factor \t Avg search time \t Avg search time "<< endl;

    for(int i =0; i < 6; i++) {
        cout << load[i] << "\t\t\t" << bDelSC[i][0] << "\t\t\t" << aDelSC[i][0] << endl;
    }

    cout << "\n\n\n\nTable 2: Performance of linear probing in various load factors \n" <<endl;

    cout << "\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Load factor \t Avg searchTime \t Avg prob \t Avg searchTime \t Avg prob "<< endl;

    for(int i =0; i < 6; i++) {
        cout << "   " << load[i] << "\t\t " << bDelLP[i][0] << "\t\t\t" << bDelLP[i][1] << "\t\t\t" << aDelLP[i][0] << "\t\t\t" << aDelLP[i][1] << endl;
    }

    cout << "\n\n\n\nTable 3: Performance of Quadric probing in various load factors \n" <<endl;

    cout << "\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Load factor \t Avg searchTime \t Avg prob \t Avg searchTime \t Avg prob "<< endl;

    for(int i =0; i < 6; i++) {
        cout << "   " << load[i] << "\t\t " << bDelQP[i][0] << "\t\t\t" << bDelQP[i][1] << "\t\t\t" << aDelQP[i][0] << "\t\t\t" << aDelQP[i][1] << endl;
    }

    cout << "\n\n\n\nTable 4: Performance of Double Hashing in various load factors \n" <<endl;

    cout << "\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Load factor \t Avg searchTime \t Avg prob \t Avg searchTime \t Avg prob "<< endl;

    for(int i =0; i < 6; i++) {
        cout << "   " << load[i] << "\t\t " << bDelDH[i][0] << "\t\t\t" << bDelDH[i][1] << "\t\t\t" << aDelDH[i][0] << "\t\t\t" << aDelDH[i][1] << endl;
    }


    cout << "\n\n\n\nTable 5: Performance of various collision resolution methods in load factor 0.4\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[0][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[0][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[0][0] << "\t\t\t" << bDelLP[0][1] << "\t\t\t" << aDelLP[0][0] << "\t\t\t" << aDelLP[0][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[0][0] << "\t\t\t" << bDelQP[0][1] << "\t\t\t" << aDelQP[0][0] << "\t\t\t" << aDelQP[0][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[0][0] << "\t\t\t" << bDelDH[0][1] << "\t\t\t" << aDelDH[0][0] << "\t\t\t" << aDelDH[0][1] << endl;



    cout << "\n\n\n\nTable 6: Performance of various collision resolution methods in load factor 0.5\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[1][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[1][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[1][0] << "\t\t\t" << bDelLP[1][1] << "\t\t\t" << aDelLP[1][0] << "\t\t\t" << aDelLP[1][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[1][0] << "\t\t\t" << bDelQP[1][1] << "\t\t\t" << aDelQP[1][0] << "\t\t\t" << aDelQP[1][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[1][0] << "\t\t\t" << bDelDH[1][1] << "\t\t\t" << aDelDH[1][0] << "\t\t\t" << aDelDH[1][1] << endl;


    cout << "\n\n\n\nTable 7: Performance of various collision resolution methods in load factor 0.6\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[2][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[2][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[2][0] << "\t\t\t" << bDelLP[2][1] << "\t\t\t" << aDelLP[2][0] << "\t\t\t" << aDelLP[2][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[2][0] << "\t\t\t" << bDelQP[2][1] << "\t\t\t" << aDelQP[2][0] << "\t\t\t" << aDelQP[2][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[2][0] << "\t\t\t" << bDelDH[2][1] << "\t\t\t" << aDelDH[2][0] << "\t\t\t" << aDelDH[2][1] << endl;


    cout << "\n\n\n\nTable 8: Performance of various collision resolution methods in load factor 0.7\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[3][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[3][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[3][0] << "\t\t\t" << bDelLP[3][1] << "\t\t\t" << aDelLP[3][0] << "\t\t\t" << aDelLP[0][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[3][0] << "\t\t\t" << bDelQP[3][1] << "\t\t\t" << aDelQP[3][0] << "\t\t\t" << aDelQP[0][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[3][0] << "\t\t\t" << bDelDH[3][1] << "\t\t\t" << aDelDH[3][0] << "\t\t\t" << aDelDH[0][1] << endl;

    cout << "\n\n\n\nTable 9: Performance of various collision resolution methods in load factor 0.8\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[4][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[4][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[4][0] << "\t\t\t" << bDelLP[4][1] << "\t\t\t" << aDelLP[4][0] << "\t\t\t" << aDelLP[4][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[4][0] << "\t\t\t" << bDelQP[4][1] << "\t\t\t" << aDelQP[4][0] << "\t\t\t" << aDelQP[4][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[4][0] << "\t\t\t" << bDelDH[4][1] << "\t\t\t" << aDelDH[4][0] << "\t\t\t" << aDelDH[4][1] << endl;


    cout << "\n\n\n\nTable 10: Performance of various collision resolution methods in load factor 0.9\n" <<endl;
    cout << "\t\t\t\t Before Deletion \t\t\t After Deletion" <<endl;
    cout << "Method \t\t\t Avg searchTime \t Avg prob \t Avg searchTime \t\t  Avg prob "<< endl;
    cout << "Separate Chaining  " << " \t " << bDelSC[5][0] << "\t\t\t" << "N/A" << "\t\t\t" << aDelSC[5][0] << "\t\t\t" << "N/A" << endl;
    cout << "Linear Probing  " << " \t " << bDelLP[5][0] << "\t\t\t" << bDelLP[5][1] << "\t\t\t" << aDelLP[5][0] << "\t\t\t" << aDelLP[0][1] << endl;
    cout << "Quadric Probing   " << " \t " << bDelQP[5][0] << "\t\t\t" << bDelQP[5][1] << "\t\t\t" << aDelQP[5][0] << "\t\t\t" << aDelQP[0][1] << endl;
    cout << "Double Hashing  " << " \t " << bDelDH[5][0] << "\t\t\t" << bDelDH[5][1] << "\t\t\t" << aDelDH[5][0] << "\t\t\t" << aDelDH[0][1] << endl;

    return 0;
}


