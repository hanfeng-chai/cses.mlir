#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> radj(n);  // predecessors, 0-indexed
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        radj[b - 1].push_back(a - 1);
    }
    int FULL = 1 << n;
    vector<int> dp((size_t)FULL * n, 0);
    dp[(1 << 0) * n + 0] = 1;  // start at city 0 having visited only {0}
    for (int mask = 1; mask < FULL; mask++) {
        if (!(mask & 1) || mask == 1) continue;  // must contain start; base set
        for (int v = 1; v < n; v++) {  // city 0 only appears as the start
            if (!(mask >> v & 1)) continue;
            int pm = mask ^ (1 << v);
            long long s = 0;
            for (int u : radj[v]) if (pm >> u & 1) s += dp[(size_t)pm * n + u];
            dp[(size_t)mask * n + v] = s % MOD;
        }
    }
    printf("%lld\n", (long long)dp[(size_t)(FULL - 1) * n + (n - 1)]);
}
