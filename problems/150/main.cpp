#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    const int LOG = 18;
    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    vector<int> depth(n + 1, 0);
    for (int i = 2; i <= n; i++) { scanf("%d", &up[0][i]); depth[i] = depth[up[0][i]] + 1; }
    up[0][1] = 0;
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[j][i] = up[j - 1][up[j - 1][i]];
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        for (int j = 0; j < LOG; j++) if (d >> j & 1) a = up[j][a];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--) if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
        return up[0][a];
    };
    while (q--) { int a, b; scanf("%d %d", &a, &b); printf("%d\n", lca(a, b)); }
}
