#include <iostream>
#include <vector>
#include <chrono>

#define M 500
#define N 500
#define X 500

using namespace std;

void multiplyColumnOrder(const vector<vector<double>> &A, const vector<vector<double>> &B, vector<vector<double>> &C) {
    for (int j = 0; j < X; j++) {
        for (int i = 0; i < M; i++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void initializeMatrices(vector<vector<double>> &A, vector<vector<double>> &B) {
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = rand() % 10;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < X; j++)
            B[i][j] = rand() % 10;
}

int main() {
    vector<vector<double>> A(M, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(X));
    vector<vector<double>> C(M, vector<double>(X));

    initializeMatrices(A, B);

    auto start = chrono::high_resolution_clock::now();
    multiplyColumnOrder(A, B, C);
    auto end = chrono::high_resolution_clock::now();

    cout << "Tempo (coluna por coluna): " 
         << chrono::duration<double>(end - start).count() 
         << " segundos\n";

    return 0;
}
