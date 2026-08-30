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
    long long n; scanf("%lld", &n);
    // ways to sum n with dice (1..6): f[i]=sum_{j=1..6} f[i-j], f[0]=1
    long long f[6]; f[0] = 1;
    for (int i = 1; i < 6; i++) { f[i] = 0; for (int j = 1; j <= i; j++) f[i] += f[i - j]; }
    if (n <= 5) { printf("%lld\n", f[n] % MOD); return 0; }
    Mat M(6, vector<long long>(6, 0));
    for (int j = 0; j < 6; j++) M[0][j] = 1;
    for (int i = 1; i < 6; i++) M[i][i - 1] = 1;
    Mat P = mpow(M, n - 5);
    long long st[6] = {f[5], f[4], f[3], f[2], f[1], f[0]};
    long long ans = 0;
    for (int j = 0; j < 6; j++) ans = (ans + P[0][j] * st[j]) % MOD;
    printf("%lld\n", ans);
}
