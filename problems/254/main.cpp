#include <bits/stdc++.h>
using namespace std;
int dsu[200005];
int find(int x) { while (dsu[x] != x) x = dsu[x] = dsu[dsu[x]]; return x; }
int main() {
    int n, m, q; scanf("%d %d %d", &n, &m, &q);
    int mx = 2 * n + 5;
    vector<int> label(mx, 0), root(mx, 0);
    vector<vector<int>> ch(mx);
    for (int i = 1; i <= n; i++) { dsu[i] = i; root[i] = i; }
    int cnt = n;
    for (int day = 1; day <= m; day++) {  // Kruskal reconstruction tree
        int a, b; scanf("%d %d", &a, &b);
        int ra = find(a), rb = find(b);
        if (ra != rb) {
            int node = ++cnt; label[node] = day;
            ch[node].push_back(root[ra]); ch[node].push_back(root[rb]);
            dsu[ra] = rb; root[rb] = node;
        }
    }
    int LOG = 1; while ((1 << LOG) < cnt) LOG++;
    vector<vector<int>> up(LOG + 1, vector<int>(cnt + 1, 0));
    vector<int> depth(cnt + 1, 0), comp(cnt + 1, -1), par_(cnt + 1, 0);
    for (int v = 1; v <= cnt; v++) for (int c : ch[v]) par_[c] = v;
    int compId = 0;
    for (int v = 1; v <= cnt; v++) if (par_[v] == 0) {
        compId++; stack<int> stk; stk.push(v); comp[v] = compId; up[0][v] = 0; depth[v] = 0;
        while (!stk.empty()) { int u = stk.top(); stk.pop(); for (int c : ch[u]) { depth[c] = depth[u] + 1; up[0][c] = u; comp[c] = compId; stk.push(c); } }
    }
    for (int k = 1; k <= LOG; k++) for (int v = 1; v <= cnt; v++) up[k][v] = up[k - 1][up[k - 1][v]];
    auto lca = [&](int a, int b) -> int {
        if (comp[a] != comp[b]) return -1;
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        for (int k = 0; k <= LOG; k++) if (d >> k & 1) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG; k >= 0; k--) if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
        return up[0][a];
    };
    string out;
    while (q--) { int a, b; scanf("%d %d", &a, &b); int l = lca(a, b); out += (l == -1 ? string("-1") : to_string(label[l])); out += '\n'; }
    cout << out;
}
