#include <bits/stdc++.h>
using namespace std;
// distinct colors per subtree = distinct values in the Euler-tour range [tin,tout];
// answered offline with a Fenwick keeping each color's last occurrence (as in problem 135).
int n;
int bit[200005];
void upd(int i, int d) { for (; i <= n; i += i & -i) bit[i] += d; }
int qsum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d", &n);
    vector<int> col(n + 1), vals;
    for (int i = 1; i <= n; i++) { scanf("%d", &col[i]); vals.push_back(col[i]); }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= n; i++) col[i] = lower_bound(vals.begin(), vals.end(), col[i]) - vals.begin() + 1;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> tin(n + 1), tout(n + 1), ptr(n + 1, 0), ecol(n + 1);
    int timer = 0;
    {
        vector<char> vis(n + 1, 0); vis[1] = 1; tin[1] = ++timer; ecol[1] = col[1];
        vector<int> st = {1};
        while (!st.empty()) {
            int u = st.back();
            if (ptr[u] < (int)adj[u].size()) {
                int v = adj[u][ptr[u]++];
                if (!vis[v]) { vis[v] = 1; tin[v] = ++timer; ecol[tin[v]] = col[v]; st.push_back(v); }
            } else { tout[u] = timer; st.pop_back(); }
        }
    }
    // queries: subtree u = range [tin[u], tout[u]]; sort by right end, sweep
    vector<int> orderByOut(n);
    for (int i = 1; i <= n; i++) orderByOut[i - 1] = i;
    sort(orderByOut.begin(), orderByOut.end(), [&](int a, int b) { return tout[a] < tout[b]; });
    vector<int> last(n + 1, 0), ans(n + 1);
    int pos = 1;
    for (int u : orderByOut) {
        while (pos <= tout[u]) {
            int c = ecol[pos];
            if (last[c]) upd(last[c], -1);
            upd(pos, 1); last[c] = pos; pos++;
        }
        ans[u] = qsum(tout[u]) - qsum(tin[u] - 1);
    }
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
}
