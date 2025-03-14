#include <iostream>
#include <vector>
#include <chrono>

#define M 500
#define N 500
#define X 500
#define BLOCK_SIZE 50  // Tamanho do bloco para otimizar cache

using namespace std;

void multiplyBlocked(const vector<vector<double>> &A, const vector<vector<double>> &B, vector<vector<double>> &C) {
    for (int i = 0; i < M; i += BLOCK_SIZE) {
        for (int j = 0; j < X; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                for (int ii = i; ii < min(i + BLOCK_SIZE, M); ii++) {
                    for (int jj = j; jj < min(j + BLOCK_SIZE, X); jj++) {
                        for (int kk = k; kk < min(k + BLOCK_SIZE, N); kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
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
    vector<vector<double>> C(M, vector<double>(X, 0));

    initializeMatrices(A, B);

    auto start = chrono::high_resolution_clock::now();
    multiplyBlocked(A, B, C);
    auto end = chrono::high_resolution_clock::now();

    cout << "Tempo (com blocagem): " 
         << chrono::duration<double>(end - start).count() 
         << " segundos\n";

    return 0;
}
