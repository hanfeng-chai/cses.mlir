#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int par[100005], rnk[100005];
int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
int main() {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) { par[i] = i; rnk[i] = 0; }
    int comp = n;
    for (int i = 0; i < m; i++) {
        int a, b; scanf("%d %d", &a, &b);
        int ra = find(a), rb = find(b);
        if (ra != rb) { if (rnk[ra] < rnk[rb]) swap(ra, rb); par[rb] = ra; if (rnk[ra] == rnk[rb]) rnk[ra]++; comp--; }
    }
    // # Eulerian subgraphs = 2^(m - n + c), c = number of connected components
    printf("%lld\n", pw(2, (long long)m - n + comp));
}
