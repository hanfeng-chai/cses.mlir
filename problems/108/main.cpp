#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int N = 2 * m;
    vector<vector<int>> adj(N), radj(N);
    auto addImpl = [&](int u, int v) { adj[u].push_back(v); radj[v].push_back(u); };
    // node 2v = var v true, 2v+1 = var v false; negation = ^1
    auto lit = [&](char s, int x) { int v = x - 1; return s == '+' ? 2 * v : 2 * v + 1; };
    for (int i = 0; i < n; i++) {
        char s1, s2; int x1, x2;
        scanf(" %c %d %c %d", &s1, &x1, &s2, &x2);
        int a = lit(s1, x1), b = lit(s2, x2);
        addImpl(a ^ 1, b);  // (a OR b): ¬a -> b
        addImpl(b ^ 1, a);  //           ¬b -> a
    }
    vector<int> order; order.reserve(N);
    vector<char> vis(N, 0);
    vector<int> idx(N, 0);
    for (int s = 0; s < N; s++)
        if (!vis[s]) {
            vector<int> st = {s}; vis[s] = 1;
            while (!st.empty()) {
                int u = st.back();
                if (idx[u] < (int)adj[u].size()) {
                    int v = adj[u][idx[u]++];
                    if (!vis[v]) { vis[v] = 1; st.push_back(v); }
                } else { order.push_back(u); st.pop_back(); }
            }
        }
    vector<int> comp(N, -1);
    int k = 0;
    for (int i = N - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s] == -1) {
            vector<int> st = {s}; comp[s] = k;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (int v : radj[u]) if (comp[v] == -1) { comp[v] = k; st.push_back(v); }
            }
            k++;
        }
    }
    // comp increases source->sink; var true iff true-node is more sink-ward
    string res(m, '-');
    for (int v = 0; v < m; v++) {
        if (comp[2 * v] == comp[2 * v + 1]) { printf("IMPOSSIBLE\n"); return 0; }
        res[v] = comp[2 * v] > comp[2 * v + 1] ? '+' : '-';
    }
    for (int v = 0; v < m; v++) printf("%c%c", res[v], " \n"[v == m - 1]);
}
