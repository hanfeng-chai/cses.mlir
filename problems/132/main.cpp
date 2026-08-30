#include <bits/stdc++.h>
using namespace std;
// count i in [a,b] with c <= x_i <= d. Offline: 2 prefix events per query, sweep index.
int B;
int bit[200005];
void upd(int i, int d) { for (; i <= B; i += i & -i) bit[i] += d; }
int qsum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<int> x(n + 1);
    vector<int> vals;
    for (int i = 1; i <= n; i++) { scanf("%d", &x[i]); vals.push_back(x[i]); }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    B = vals.size();
    auto cidx = [&](int v) { return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; };
    // events: (prefix index p, c, d, sign, query id)
    vector<array<int, 5>> ev;
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int lo = lower_bound(vals.begin(), vals.end(), c) - vals.begin() + 1;  // first >= c
        int hi = upper_bound(vals.begin(), vals.end(), d) - vals.begin();      // last <= d
        ev.push_back({b, lo, hi, 1, i});
        ev.push_back({a - 1, lo, hi, -1, i});
    }
    sort(ev.begin(), ev.end());  // by prefix index p ascending
    vector<long long> ans(q, 0);
    int pos = 1;
    for (auto &e : ev) {
        int p = e[0], lo = e[1], hi = e[2], sgn = e[3], id = e[4];
        while (pos <= p) { upd(cidx(x[pos]), 1); pos++; }
        ans[id] += (long long)sgn * (qsum(hi) - qsum(lo - 1));
    }
    for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
}
