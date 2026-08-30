#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

// 388 Grid Puzzle II: same row/column count constraints as 387, but now we must
// MAXIMIZE the sum of collected coin values. This is a transportation problem:
// source -> row_i (capacity a_i) -> column_j (capacity 1, cost -c_ij, negated so
// a min-cost flow maximizes the real value) -> sink (capacity b_j). Solved with
// classic MCMF (SPFA-based successive shortest augmenting paths); since every
// row-column edge has capacity 1, each augmentation pushes exactly one unit.
struct MCMF {
    struct Edge { int to; ll cap, cost; int rev; };
    int n;
    vector<vector<Edge>> g;
    MCMF(int n) : n(n), g(n) {}
    void addEdge(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, cap, cost, (int)g[v].size()});
        g[v].push_back({u, 0, -cost, (int)g[u].size() - 1});
    }
    pair<ll,ll> run(int s, int t) {
        ll totalFlow = 0, totalCost = 0;
        while (true) {
            vector<ll> dist(n, INF);
            vector<int> prevNode(n, -1), prevEdge(n, -1);
            vector<bool> inq(n, false);
            deque<int> q;
            dist[s] = 0; q.push_back(s); inq[s] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop_front(); inq[u] = false;
                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto &e = g[u][i];
                    if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        prevNode[e.to] = u;
                        prevEdge[e.to] = i;
                        if (!inq[e.to]) { inq[e.to] = true; q.push_back(e.to); }
                    }
                }
            }
            if (dist[t] >= INF) break; // no more augmenting path: whatever flow
                                        // we have is the max feasible (must
                                        // equal the required total, else -1)
            ll push = INF;
            for (int v = t; v != s; v = prevNode[v])
                push = min(push, g[prevNode[v]][prevEdge[v]].cap);
            for (int v = t; v != s; v = prevNode[v]) {
                auto &e = g[prevNode[v]][prevEdge[v]];
                e.cap -= push;
                g[v][e.rev].cap += push;
            }
            totalFlow += push;
            totalCost += push * dist[t];
        }
        return {totalFlow, totalCost};
    }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n), b(n);
    for (auto &v : a) scanf("%d", &v);
    for (auto &v : b) scanf("%d", &v);
    vector<vector<int>> c(n, vector<int>(n));
    for (auto &row : c) for (auto &v : row) scanf("%d", &v);

    int S = 2 * n, T = 2 * n + 1;
    MCMF mcmf(2 * n + 2);
    ll needFlow = 0;
    for (int i = 0; i < n; i++) { mcmf.addEdge(S, i, a[i], 0); needFlow += a[i]; }
    for (int j = 0; j < n; j++) mcmf.addEdge(n + j, T, b[j], 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mcmf.addEdge(i, n + j, 1, -c[i][j]);

    auto [flow, cost] = mcmf.run(S, T);
    if (flow != needFlow) {
        printf("-1\n");
        return 0;
    }
    printf("%lld\n", -cost);

    // Reconstruct the chosen cells from residual capacities (row->col edge used
    // iff its forward capacity dropped to 0, i.e. flow of 1 went through it).
    vector<string> grid(n, string(n, '.'));
    for (int i = 0; i < n; i++) {
        for (auto &e : mcmf.g[i]) {
            if (e.to >= n && e.to < 2 * n && e.cap == 0) {
                grid[i][e.to - n] = 'X';
            }
        }
    }
    for (auto &row : grid) printf("%s\n", row.c_str());
}
