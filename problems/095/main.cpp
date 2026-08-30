#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
    }
    vector<int> cnt(n + 1, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 1});
    vector<long long> res;
    while (!pq.empty() && (int)res.size() < k) {
        auto [d, u] = pq.top(); pq.pop();
        if (cnt[u] >= k) continue;
        cnt[u]++;
        if (u == n) res.push_back(d);
        for (auto [v, w] : adj[u])
            if (cnt[v] < k) pq.push({d + w, v});
    }
    for (int i = 0; i < k; i++) printf("%lld%c", res[i], " \n"[i + 1 == k]);
}
