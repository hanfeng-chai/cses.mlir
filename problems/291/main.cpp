#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<int> deg(n + 1);
    long long sum = 0;
    for (int i = 1; i <= n; i++) { scanf("%d", &deg[i]); sum += deg[i]; }
    if (sum % 2) { printf("IMPOSSIBLE\n"); return 0; }
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n; i++) if (deg[i] > 0) pq.push({deg[i], i});
    vector<pair<int, int>> edges;
    bool ok = true;
    while (!pq.empty() && ok) {
        auto [d, v] = pq.top(); pq.pop();
        if (d != deg[v]) continue;          // stale
        if (d == 0) continue;
        vector<pair<int, int>> taken;        // connect v to the d highest remaining
        while ((int)taken.size() < d) {
            if (pq.empty()) { ok = false; break; }
            auto [d2, u] = pq.top(); pq.pop();
            if (d2 != deg[u]) continue;      // stale
            if (d2 == 0) { ok = false; break; }
            taken.push_back({d2, u});
        }
        if (!ok) break;
        deg[v] = 0;
        for (auto [d2, u] : taken) { edges.push_back({v, u}); deg[u]--; }
        for (auto [d2, u] : taken) if (deg[u] > 0) pq.push({deg[u], u});
    }
    if (!ok) { printf("IMPOSSIBLE\n"); return 0; }
    string out = to_string(edges.size()) + "\n";
    for (auto [a, b] : edges) { out += to_string(a) + " " + to_string(b) + "\n"; }
    cout << out;
}
