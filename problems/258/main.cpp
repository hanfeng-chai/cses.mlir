#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
struct MCMF {
    struct E { int to, cap, cost, flow; };
    vector<E> es; vector<vector<int>> g; int n, s, t;
    vector<ll> dist; vector<int> inq, pe;
    void init(int n_) { n = n_; g.assign(n, {}); }
    void ae(int a, int b, int cap, int cost) {
        g[a].push_back(es.size()); es.push_back({b, cap, cost, 0});
        g[b].push_back(es.size()); es.push_back({a, 0, -cost, 0});
    }
    bool spfa() {
        dist.assign(n, INF); inq.assign(n, 0); pe.assign(n, -1);
        deque<int> q; dist[s] = 0; q.push_back(s);
        while (!q.empty()) {
            int u = q.front(); q.pop_front(); inq[u] = 0;
            for (int id : g[u]) { auto &e = es[id]; if (e.cap - e.flow > 0 && dist[u] + e.cost < dist[e.to]) { dist[e.to] = dist[u] + e.cost; pe[e.to] = id; if (!inq[e.to]) { inq[e.to] = 1; q.push_back(e.to); } } }
        }
        return dist[t] < INF;
    }
    pair<ll, ll> run(int s_, int t_, ll maxf) {
        s = s_; t = t_; ll flow = 0, cost = 0;
        while (flow < maxf && spfa()) {
            ll push = maxf - flow;
            for (int v = t; v != s;) { int id = pe[v]; push = min(push, (ll)(es[id].cap - es[id].flow)); v = es[id ^ 1].to; }
            for (int v = t; v != s;) { int id = pe[v]; es[id].flow += push; es[id ^ 1].flow -= push; v = es[id ^ 1].to; }
            flow += push; cost += push * dist[t];
        }
        return {flow, cost};
    }
};
int main() {
    int n, m, k; scanf("%d %d %d", &n, &m, &k);
    MCMF f; f.init(n + 1);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); f.ae(a, b, 1, 1); }
    auto [flow, cost] = f.run(1, n, k);
    if (flow < k) { printf("-1\n"); return 0; }
    printf("%lld\n", cost);
    string out;
    for (int p = 0; p < k; p++) {  // decompose flow into k routes
        vector<int> path; int u = 1; path.push_back(1);
        while (u != n) {
            for (int id : f.g[u]) if ((id % 2 == 0) && f.es[id].flow > 0) { f.es[id].flow--; u = f.es[id].to; path.push_back(u); break; }
        }
        out += to_string(path.size()); out += '\n';
        for (int i = 0; i < (int)path.size(); i++) { out += to_string(path[i]); out += " \n"[i + 1 == (int)path.size()]; }
    }
    printf("%s", out.c_str());
}
