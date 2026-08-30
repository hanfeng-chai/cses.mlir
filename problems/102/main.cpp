#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    const int LOG = 18;
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) up[0][i] = t[i];
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[j][i] = up[j - 1][up[j - 1][i]];
    // decompose functional graph into cycles + trees
    vector<int> state(n + 1, 0), onCyc(n + 1, 0), cid(n + 1, -1), idx(n + 1, 0);
    vector<int> cyclen;
    for (int i = 1; i <= n; i++) {
        if (state[i]) continue;
        vector<int> path;
        int u = i;
        while (state[u] == 0) { state[u] = 1; path.push_back(u); u = t[u]; }
        if (state[u] == 1) {  // a fresh cycle starts at u
            int c = cyclen.size(), len = 0, v = u;
            do { onCyc[v] = 1; cid[v] = c; idx[v] = len++; v = t[v]; } while (v != u);
            cyclen.push_back(len);
        }
        for (int x : path) state[x] = 2;
    }
    vector<int> depth(n + 1, -1), entry(n + 1, 0);
    for (int i = 1; i <= n; i++) if (onCyc[i]) { depth[i] = 0; entry[i] = i; }
    for (int i = 1; i <= n; i++) {
        if (depth[i] != -1) continue;
        vector<int> st;
        int u = i;
        while (depth[u] == -1) { st.push_back(u); u = t[u]; }
        int d = depth[u], e = entry[u];
        for (int k = (int)st.size() - 1; k >= 0; k--) { depth[st[k]] = ++d; entry[st[k]] = e; }
    }
    auto kth = [&](int v, long long k) { for (int j = 0; j < LOG && v; j++) if (k >> j & 1) v = up[j][v]; return v; };
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        long long ans = -1;
        if (!onCyc[b]) {
            if (depth[a] >= depth[b] && entry[a] == entry[b] && kth(a, depth[a] - depth[b]) == b)
                ans = depth[a] - depth[b];
        } else {
            int e = entry[a];
            if (cid[e] == cid[b]) {
                int len = cyclen[cid[b]];
                int diff = ((idx[b] - idx[e]) % len + len) % len;
                ans = (long long)depth[a] + diff;
            }
        }
        printf("%lld\n", ans);
    }
}
