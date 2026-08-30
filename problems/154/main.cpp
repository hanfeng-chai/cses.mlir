#include <bits/stdc++.h>
using namespace std;
int n, q;
long long bit[200007];
void upd(int i, long long d) { for (; i <= n + 1; i += i & -i) bit[i] += d; }
long long qsum(int i) { long long s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &val[i]);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> tin(n + 1), tout(n + 1), par(n + 1, 0), ptr(n + 1, 0);
    int timer = 0;
    {
        vector<char> vis(n + 1, 0); vis[1] = 1; tin[1] = ++timer;
        vector<int> st = {1};
        while (!st.empty()) {
            int u = st.back();
            if (ptr[u] < (int)adj[u].size()) {
                int v = adj[u][ptr[u]++];
                if (!vis[v]) { vis[v] = 1; par[v] = u; tin[v] = ++timer; st.push_back(v); }
            } else { tout[u] = timer; st.pop_back(); }
        }
    }
    // value at a node contributes to root-paths of its whole subtree: +v at tin, -v at tout+1
    for (int i = 1; i <= n; i++) { upd(tin[i], val[i]); upd(tout[i] + 1, -val[i]); }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int s; long long x; scanf("%d %lld", &s, &x);
            long long d = x - val[s]; val[s] = x;
            upd(tin[s], d); upd(tout[s] + 1, -d);
        } else {
            int s; scanf("%d", &s);
            printf("%lld\n", qsum(tin[s]));  // prefix sum = sum on path root..s
        }
    }
}
