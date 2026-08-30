#include <bits/stdc++.h>
using namespace std;
const long long INF = 4e18;  // real paths <= k*c <= 1e18, so keep INF strictly above
typedef vector<vector<long long>> Mat;
Mat mul(Mat &A, Mat &B) {  // min-plus product
    int n = A.size();
    Mat C(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) for (int k = 0; k < n; k++) if (A[i][k] < INF) for (int j = 0; j < n; j++) if (B[k][j] < INF) C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
    return C;
}
Mat mpow(Mat A, long long e) {
    int n = A.size();
    Mat R(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) R[i][i] = 0;  // min-plus identity
    while (e) { if (e & 1) R = mul(R, A); A = mul(A, A); e >>= 1; }
    return R;
}
int main() {
    int n, m; long long k;
    scanf("%d %d %lld", &n, &m, &k);
    Mat A(n, vector<long long>(n, INF));
    for (int i = 0; i < m; i++) { int a, b; long long c; scanf("%d %d %lld", &a, &b, &c); A[a - 1][b - 1] = min(A[a - 1][b - 1], c); }
    Mat P = mpow(A, k);  // min path of exactly k edges from 1 to n
    long long ans = P[0][n - 1];
    printf("%lld\n", ans >= INF ? -1 : ans);
}
