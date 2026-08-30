#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> adj, radj;
vector<int> comp;
void kosaraju() {
    vector<int> order; order.reserve(n);
    vector<char> vis(n + 1, 0);
    vector<int> idx(n + 1, 0);
    for (int s = 1; s <= n; s++)
        if (!vis[s]) {
            vector<int> st = {s}; vis[s] = 1;
            while (!st.empty()) {
                int u = st.back();
                if (idx[u] < (int)adj[u].size()) { int v = adj[u][idx[u]++]; if (!vis[v]) { vis[v] = 1; st.push_back(v); } }
                else { order.push_back(u); st.pop_back(); }
            }
        }
    comp.assign(n + 1, -1);
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s] == -1) {
            vector<int> st = {s}; comp[s] = k;
            while (!st.empty()) { int u = st.back(); st.pop_back(); for (int v : radj[u]) if (comp[v] == -1) { comp[v] = k; st.push_back(v); } }
            k++;
        }
    }
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt(); m = inf.readInt();
    adj.assign(n + 1, {}); radj.assign(n + 1, {});
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); adj[a].push_back(b); radj[b].push_back(a); }
    kosaraju();
    int trueK = *max_element(comp.begin() + 1, comp.end()) + 1;
    ans.readLong();  // official k (consume)
    long long pk = ouf.readLong();
    if (pk != trueK) quitf(_wa, "wrong number of kingdoms: expected %d, got %lld", trueK, pk);
    vector<int> lab(n + 1);
    for (int i = 1; i <= n; i++) lab[i] = ouf.readInt(1, (int)pk);
    vector<int> c2l(trueK, -1), l2c(pk + 1, -1);
    for (int i = 1; i <= n; i++) {
        int c = comp[i], L = lab[i];
        if (c2l[c] == -1) c2l[c] = L; else if (c2l[c] != L) quitf(_wa, "same kingdom got different labels");
        if (l2c[L] == -1) l2c[L] = c; else if (l2c[L] != c) quitf(_wa, "same label spans different kingdoms");
    }
    quitf(_ok, "correct, %d kingdoms", trueK);
}
