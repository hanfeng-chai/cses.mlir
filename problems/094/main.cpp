#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<array<int, 3>> e(m);
    for (auto &E : e) { int a, b, c; scanf("%d %d %d", &a, &b, &c); E = {a, b, c}; }
    vector<long long> dist(n + 1, 0);
    vector<int> par(n + 1, -1);
    int x = -1;
    for (int it = 0; it < n; it++) {
        x = -1;
        for (auto &[a, b, c] : e)
            if (dist[a] + c < dist[b]) { dist[b] = dist[a] + c; par[b] = a; x = b; }
    }
    if (x == -1) { printf("NO\n"); return 0; }
    for (int i = 0; i < n; i++) x = par[x];  // walk into the cycle
    vector<int> cyc;
    for (int v = x;; v = par[v]) {
        cyc.push_back(v);
        if (v == x && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());
    printf("YES\n");
    for (size_t i = 0; i < cyc.size(); i++) printf("%d%c", cyc[i], " \n"[i + 1 == cyc.size()]);
}
