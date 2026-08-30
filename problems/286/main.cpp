#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
int main() {
    int n; scanf("%d", &n);
    int LOG = 1; while ((1 << LOG) <= n) LOG++;
    int M = 1 << LOG;
    vector<long long> c(M, 0);
    for (int i = 0; i < n; i++) { int a; scanf("%d", &a); c[a]++; }
    for (int b = 0; b < LOG; b++) for (int m = 0; m < M; m++) if (!(m >> b & 1)) c[m] += c[m | (1 << b)];  // c[k] = #elements that are supermasks of k
    vector<long long> g(M);
    for (int m = 0; m < M; m++) g[m] = (pw(2, c[m]) - 1 + MOD) % MOD;  // non-empty subsets whose AND is a supermask of m
    for (int b = 0; b < LOG; b++) for (int m = 0; m < M; m++) if (!(m >> b & 1)) g[m] = (g[m] - g[m | (1 << b)] + MOD) % MOD;  // superset Mobius -> exact AND == m
    string out;
    for (int k = 0; k <= n; k++) { out += to_string(g[k]); out += " \n"[k == n]; }
    cout << out;
}
