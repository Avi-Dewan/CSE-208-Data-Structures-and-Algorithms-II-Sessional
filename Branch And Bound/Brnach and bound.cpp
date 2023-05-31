#include <iostream>
#include <vector>
#include <queue>

using namespace std;


void printMatrix(vector<vector<int>> &m) {

    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < m.size(); j++)
                if(m[i][j]) cout << "X "; else cout << "0 ";


        cout << endl;
    }

}


int lowerBound(vector<vector<int>> &m , int fixCol, int fixRow) {

    vector<vector<int>> matrix = m;
    vector<vector<int>> matrix2 = m;

    int n = matrix.size();

    int unFixed = 0, fixed = 0, x = 0;

    //unfixed area

    for(int i = fixCol + 1; i < n; i++) {
        x = 0;
        for(int j = fixRow + 1; j < n; j++ ) {
            if(matrix[j][i]) x++;
        }

        x = (x + 1) / 2;

        unFixed = max(x, unFixed);
    }

    for(int i = fixRow + 1; i < n; i++) {
        x = 0;
        for(int j = fixCol + 1; j < n; j++ ) {
            if(matrix[i][j]) x++;
        }

        x = (x + 1) / 2;

        unFixed = max(x, unFixed);
    }

    //fixed area

    int up, down, left, right;

    //for columns

    for(int i = 0; i <= fixCol; i++) {

        int c = -1 ;
        for(int j = fixRow + 1; j < n; j++) {
            if(matrix[j][i] == 1 && c != j && c!= -1) {
                matrix[c++][i] = 1;
                matrix[j][i] = 0;
            } else if(matrix[j][i] == 0 && c == -1) {
                c = j;
            }
        }


        up = -1, down = 1;

        for(int j = 0; j < n; j++) {
            if(j < i) {
                if(up == - 1 && matrix[j][i] == 1) {
                    up = i - j + 1;
                }
            } else {
                if(matrix[j][i]) down = j - i + 1;
            }
        }

        fixed = max(fixed, max(up, down));

    }


    //for rows

    for(int i = 0; i <= fixRow; i++) {

        int c = -1;
        for(int j = fixCol + 1; j < n; j++) {
            if(matrix2[i][j] && c != j && c!= -1) {
                matrix2[i][c++] = 1;
                matrix2[i][j] = 0;
            } else if(matrix2[i][j] == 0 && c == -1) {
                c = j;
            }
        }


        left = -1, right = 1;

        for(int j = 0; j < n; j++) {
            if(j < i) {
                if(left == - 1 && matrix2[i][j] == 1) {
                    left = i - j + 1;
                }
            } else {
                if(matrix2[i][j]) right = j - i + 1;
            }
        }

        fixed = max(fixed, max(left, right));

    }


    return max(unFixed, fixed);

}


int bandWidth(vector <vector <int>> matrix) {
    int n = matrix.size();

    int band = 0, left, right, up, down;

    for(int i = 0; i < n; i++) {

        left = -1, right = 1;

        for(int j = 0; j < n; j++) {
            if(j < i) {
                if(left == - 1 && matrix[i][j] == 1) {
                    left = i - j + 1;
                }
            } else {
                if(matrix[i][j]) right = j - i + 1;
            }
        }

        if(left == -1) left = 1;



        band = max(band, max(left, right));

        up = -1, down = 1;



        for(int j = 0; j < n; j++) {
            if(j < i) {
                if(up == - 1 && matrix[j][i] == 1) {
                    up = i - j + 1;
                }
            } else {
                if(matrix[j][i]) down = j - i + 1;
            }
        }

        band = max(band, max(up, down));
    }

    return band;
}


class bandMatrix{
public:
    vector<vector<int>> matrix;
    int bound, level, order, fxCol, fxRow;

    bandMatrix(vector<vector<int>> matrix, int level, int order, int fxCol, int fxRow) {
        this->matrix = matrix;
        this->level = level;
        this->order = order;
        this->fxCol = fxCol;
        this->fxRow = fxRow;

        this->bound = lowerBound(matrix, fxCol, fxRow);
    }
};


bool operator<(bandMatrix  A, bandMatrix B) {

    if(A.bound == B.bound) {
        if(A.level == B.level) {
            return A.order < B.order;
        } else {
            return A.level < B.level;
        }
    } else {
        return A.bound > B.bound;
    }
}


vector<vector<int>> minBand(vector<vector<int>> &matrix) {

    vector<vector<int>> A = matrix;

    int n = matrix.size(), order = 0;

    priority_queue <bandMatrix> PQ;

    PQ.push(bandMatrix(A, 0, order++, -1, -1));

    while(!PQ.empty()) {
        bandMatrix b = PQ.top();
        PQ.pop();

        if(b.fxCol ==  n-1 && b.fxRow == n-1) {
            return b.matrix;
            break;
        }

        if(b.fxCol == b.fxRow) {

            for(int i = b.fxCol + 1; i < n; i++) {

                vector<vector<int>> m = b.matrix;
                int temp[n];

                for(int j = 0; j < n; j++) {
                    temp[j] = m[j][i];

                }


                for(int j = i; j > b.fxCol + 1; j-- ) {
                   for(int k = 0; k < n; k++) {
                        m[k][j] = m[k][j-1];
                   }

                }

                for(int j = 0; j < n; j++) {
                    m[j][b.fxCol + 1] = temp[j];
                }

                PQ.push(bandMatrix(m, b.level+1, order++, b.fxCol + 1, b.fxRow ));
            }

        } else {

            for(int i = b.fxRow + 1; i < n; i++) {

                vector<vector<int>> m = b.matrix;
                int temp[n];

                for(int j = 0; j < n; j++) {
                    temp[j] = m[i][j];
                }

                for(int j = i; j > b.fxRow + 1; j-- ) {
                   for(int k = 0; k < n; k++) {
                        m[j][k] = m[j-1][k];
                   }
                }

                for(int j = 0; j < n; j++) {
                    m[b.fxRow+1][j] = temp[j];
                }

                PQ.push(bandMatrix(m, b.level+1, order++, b.fxCol, b.fxRow + 1 ));
            }
        }
    }

}


int main()  {
    int n;
    char c;

    cin >> n;

    vector <vector <int>> matrix(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> c;

            if(c == 'X') matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }
    }

    vector <vector <int>> minMatrix = minBand(matrix);

    cout << bandWidth(minMatrix) << endl;

    printMatrix(minMatrix);



    return 0;
}


/*
4
X 0 0 X
0 0 X 0
X 0 0 X
0 X X X

4
X 0 0 0
X X X 0
0 0 X X
0 0 X X

4
X X 0 0
0 0 0 X
X X 0 0
X 0 X X

4
0X0X
X000
0X0X
X0XX

4
X000
0X0X
0X0X
X0XX

4
0X0X
0X0X
X000
0XXX

4
X0XX
0X0X
X000
0X0X

4
X000
00XX
00XX
XX0X

4
X000
XX0X
00XX
00XX

4
X000
XXX0
00XX
00XX
*/




