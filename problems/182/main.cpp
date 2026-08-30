#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
typedef vector<vector<long long>> Mat;
Mat mul(Mat &A, Mat &B) {
    int n = A.size();
    Mat C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) for (int k = 0; k < n; k++) if (A[i][k]) for (int j = 0; j < n; j++) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}
Mat mpow(Mat A, long long e) {
    int n = A.size();
    Mat R(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (e) { if (e & 1) R = mul(R, A); A = mul(A, A); e >>= 1; }
    return R;
}
int main() {
    int n, m; long long k;
    scanf("%d %d %lld", &n, &m, &k);
    Mat A(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); A[a - 1][b - 1] = (A[a - 1][b - 1] + 1) % MOD; }
    Mat P = mpow(A, k);  // paths of exactly k edges from 1 to n
    printf("%lld\n", P[0][n - 1]);
}
