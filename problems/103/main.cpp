#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    // decompose functional graph into cycles + trees
    vector<int> state(n + 1, 0), onCyc(n + 1, 0), cid(n + 1, -1);
    vector<int> cyclen;
    for (int i = 1; i <= n; i++) {
        if (state[i]) continue;
        vector<int> path;
        int u = i;
        while (state[u] == 0) { state[u] = 1; path.push_back(u); u = t[u]; }
        if (state[u] == 1) {
            int c = cyclen.size(), len = 0, v = u;
            do { onCyc[v] = 1; cid[v] = c; len++; v = t[v]; } while (v != u);
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
    // answer = steps in tail + length of the cycle finally entered
    for (int i = 1; i <= n; i++)
        printf("%d%c", depth[i] + cyclen[cid[entry[i]]], " \n"[i == n]);
}
