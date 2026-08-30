#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; if (a < 0) a += MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
long long inv(long long a) { return pw(a, MOD - 2); }
int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<long long>> A(n, vector<long long>(m + 1));
    for (int i = 0; i < n; i++) for (int j = 0; j <= m; j++) scanf("%lld", &A[i][j]);
    vector<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; col++) {  // Gauss-Jordan mod p
        int sel = -1;
        for (int i = row; i < n; i++) if (A[i][col] % MOD != 0) { sel = i; break; }
        if (sel == -1) continue;
        swap(A[sel], A[row]);
        long long iv = inv(A[row][col]);
        for (int j = col; j <= m; j++) A[row][j] = A[row][j] * iv % MOD;
        for (int i = 0; i < n; i++) if (i != row) {
            long long f = A[i][col] % MOD;
            if (f) for (int j = col; j <= m; j++) A[i][j] = ((A[i][j] - f * A[row][j]) % MOD + MOD) % MOD;
        }
        where[col] = row; row++;
    }
    for (int i = row; i < n; i++) if (((A[i][m] % MOD) + MOD) % MOD != 0) { printf("-1\n"); return 0; }
    vector<long long> x(m, 0);
    for (int j = 0; j < m; j++) if (where[j] != -1) x[j] = ((A[where[j]][m] % MOD) + MOD) % MOD;  // free vars = 0
    for (int j = 0; j < m; j++) printf("%lld%c", x[j], " \n"[j == m - 1]);
}
