#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int main() {
    int n; scanf("%d", &n);
    vector<vector<ll>> a(n + 1, vector<ll>(n + 1));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%lld", &a[i][j]);
    // Hungarian algorithm (min cost perfect matching)
    vector<ll> u(n + 1, 0), v(n + 1, 0);
    vector<int> p(n + 1, 0), way(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        p[0] = i; int j0 = 0;
        vector<ll> minv(n + 1, INF); vector<char> used(n + 1, false);
        do {
            used[j0] = true; int i0 = p[j0], j1 = -1; ll delta = INF;
            for (int j = 1; j <= n; j++) if (!used[j]) {
                ll cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j = 0; j <= n; j++) if (used[j]) { u[p[j]] += delta; v[j] -= delta; } else minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do { int j1 = way[j0]; p[j0] = p[j1]; j0 = j1; } while (j0);
    }
    ll cost = 0;
    for (int j = 1; j <= n; j++) cost += a[p[j]][j];
    printf("%lld\n", cost);
    string out;
    for (int j = 1; j <= n; j++) { out += to_string(p[j]); out += ' '; out += to_string(j); out += '\n'; }
    printf("%s", out.c_str());
}
