#include <bits/stdc++.h>
using namespace std;
int n, m, k;
vector<vector<int>> adj;
vector<int> matchG;
vector<char> used;
bool tryK(int u) {
    for (int v : adj[u])
        if (!used[v]) {
            used[v] = 1;
            if (matchG[v] == 0 || tryK(matchG[v])) { matchG[v] = u; return true; }
        }
    return false;
}
int main() {
    scanf("%d %d %d", &n, &m, &k);
    adj.assign(n + 1, {});
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
    }
    matchG.assign(m + 1, 0);
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        used.assign(m + 1, 0);
        if (tryK(u)) cnt++;
    }
    printf("%d\n", cnt);
    for (int v = 1; v <= m; v++) if (matchG[v]) printf("%d %d\n", matchG[v], v);
}
