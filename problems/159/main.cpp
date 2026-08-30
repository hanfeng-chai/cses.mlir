#include <bits/stdc++.h>
using namespace std;
// Centroid decomposition: count paths with between K1 and K2 edges.
// Per centroid count pairs whose depth-sum lies in [K1,K2] over all subtrees,
// minus same-subtree pairs (inclusion-exclusion). Counting via sort + two pointers.
int n, K1, K2;
vector<vector<int>> adj;
vector<char> removed;
vector<int> sz, par, ordBuf, dval, allD;
long long ans = 0;
int findCentroid(int u) {
    ordBuf.clear(); ordBuf.push_back(u); par[u] = 0;
    for (size_t i = 0; i < ordBuf.size(); i++) { int x = ordBuf[i]; for (int v : adj[x]) if (!removed[v] && v != par[x]) { par[v] = x; ordBuf.push_back(v); } }
    int total = ordBuf.size();
    for (int i = (int)ordBuf.size() - 1; i >= 0; i--) { int x = ordBuf[i]; sz[x] = 1; for (int v : adj[x]) if (!removed[v] && v != par[x]) sz[x] += sz[v]; }
    for (int x : ordBuf) {
        int mx = total - sz[x];
        for (int v : adj[x]) if (!removed[v] && v != par[x]) mx = max(mx, sz[v]);
        if (mx <= total / 2) return x;
    }
    return u;
}
long long pairsLE(int lo, int hi, int X) {  // allD[lo..hi) sorted; count i<j with sum<=X
    if (X < 0) return 0;
    long long res = 0;
    int l = lo, r = hi - 1;
    while (l < r) { if (allD[l] + allD[r] <= X) { res += r - l; l++; } else r--; }
    return res;
}
long long rangeCnt(int lo, int hi) { return pairsLE(lo, hi, K2) - pairsLE(lo, hi, K1 - 1); }
void process(int c) {
    allD.clear(); allD.push_back(0);  // the centroid itself at depth 0
    for (int w : adj[c]) if (!removed[w]) {
        int start = allD.size();
        ordBuf.clear(); ordBuf.push_back(w); par[w] = c; dval[w] = 1; allD.push_back(1);
        for (size_t i = 0; i < ordBuf.size(); i++) {
            int x = ordBuf[i];
            for (int v : adj[x]) if (!removed[v] && v != par[x]) { par[v] = x; dval[v] = dval[x] + 1; ordBuf.push_back(v); allD.push_back(dval[v]); }
        }
        sort(allD.begin() + start, allD.end());
        ans -= rangeCnt(start, allD.size());  // remove same-subtree pairs
    }
    sort(allD.begin(), allD.end());
    ans += rangeCnt(0, allD.size());
}
void decompose(int u) {
    int c = findCentroid(u);
    process(c);
    removed[c] = 1;
    for (int v : adj[c]) if (!removed[v]) decompose(v);
}
int main() {
    scanf("%d %d %d", &n, &K1, &K2);
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    removed.assign(n + 1, 0); sz.assign(n + 1, 0); par.assign(n + 1, 0); dval.assign(n + 1, 0);
    decompose(1);
    printf("%lld\n", ans);
}
