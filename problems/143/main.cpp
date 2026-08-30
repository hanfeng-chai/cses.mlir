#include <bits/stdc++.h>
using namespace std;
// Persistent segment tree over coin values: version i adds coin i. To answer a query,
// repeatedly add the sum of coins with value <= reach+1 in index range [a,b].
struct Node { long long sum; int l, r; };
vector<Node> t;
int B;
int update(int prev, int lo, int hi, int pos, long long val) {
    int id = t.size(); t.push_back(t[prev]); t[id].sum += val;
    if (lo == hi) return id;
    int m = (lo + hi) / 2;
    if (pos <= m) t[id].l = update(t[prev].l, lo, m, pos, val);
    else t[id].r = update(t[prev].r, m + 1, hi, pos, val);
    return id;
}
long long query(int ia, int ib, int lo, int hi, int k) {  // sum of coords [lo, k] over version diff
    if (hi <= k) return t[ib].sum - t[ia].sum;
    int m = (lo + hi) / 2;
    long long res = query(t[ia].l, t[ib].l, lo, m, k);
    if (k > m) res += query(t[ia].r, t[ib].r, m + 1, hi, k);
    return res;
}
int main() {
    int n, q; scanf("%d %d", &n, &q);
    vector<long long> x(n + 1), vals;
    for (int i = 1; i <= n; i++) { scanf("%lld", &x[i]); vals.push_back(x[i]); }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    B = vals.size();
    auto cidx = [&](long long v) { return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()); };
    t.reserve((size_t)(n + 1) * 20 + 10);
    t.push_back({0, 0, 0});  // null node 0
    vector<int> root(n + 1);
    root[0] = 0;
    for (int i = 1; i <= n; i++) root[i] = update(root[i - 1], 0, B - 1, cidx(x[i]), x[i]);
    while (q--) {
        int a, b; scanf("%d %d", &a, &b);
        long long reach = 0;
        while (true) {
            long long V = reach + 1;
            int hi = upper_bound(vals.begin(), vals.end(), V) - vals.begin() - 1;  // largest coord <= V
            long long s = (hi < 0) ? 0 : query(root[a - 1], root[b], 0, B - 1, hi);
            if (s > reach) reach = s; else break;
        }
        printf("%lld\n", reach + 1);
    }
}
