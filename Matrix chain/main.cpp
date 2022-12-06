#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>


using namespace std;


typedef vector <int> dim;

typedef map <int,unsigned long> row;
typedef map <int, row> table;

void print(dim &);
void insert(int, dim &);
void matrixChain(dim &, table &, table &);
void optimalParents(table &, int, int);
int factorial(int);


int main(){

    srand((unsigned) time(nullptr));

    int n;
    printf("Entrada: ");
    cin >> n;

    unsigned long num_solutions = factorial((2 * n) - 2) / (factorial(n) * factorial(n - 1));

    dim p;
    table m;
    table s;

    printf("Salida:\n");
    insert(n + 1, p);

    printf("\nDim vector: ");
    print(p);

    matrixChain(p, m, s);
    cout << "Numbre of solutions: " << num_solutions <<endl;

    printf("\nOptimal parenthesizing:\n");
    optimalParents(s, 1, n);

    printf("\n\nCost of the solution: %i", m[1][n]);

    return 0;
}

void matrixChain(dim &p, table &m, table &s){

    int n = p.size();

    for(int i = 1; i <= n; i++) m[i][i] = 0;

    for(int len = 2; len <= n ; len++){
        
        for(int i = 1; i <= n - len + 1; i++){

            int j = i + len - 1;
            m[i][j] = -1;

            for(int k = i; k <= j - 1; k++){

                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);

                if(q < m[i][j] || m[i][j] == -1){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void optimalParents(table &s, int i, int j){

    if(i == j) printf(" A%i ", i);
    else{
        printf("(");
        optimalParents(s, i, s[i][j]);
        optimalParents(s, s[i][j] + 1, j);
        printf(")");
    }
}

void insert(int n, dim &p){

    for(int i = 0; i < n; i++)
        p.push_back(rand() % 10 + 1);
    
}

void print(dim &p){

    printf("\n< ");
    for(dim::iterator i = p.begin(); i != p.end(); i++)
        printf(" %i ", *i);
    printf(" >\n");
}

int factorial(int n){

    if(n < 2) return 1;
    else return factorial(n - 1) * n;
}