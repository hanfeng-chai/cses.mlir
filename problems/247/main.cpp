#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;
const int MAXX = 1000000;
struct Line { ll m, b; ll val(ll x) { return m * x + b; } };
vector<Line> seg;
void insert(int node, int lo, int hi, Line ln) {  // Li Chao min (arbitrary slopes)
    int mid = (lo + hi) / 2;
    bool l = ln.val(lo) < seg[node].val(lo);
    bool md = ln.val(mid) < seg[node].val(mid);
    if (md) swap(seg[node], ln);
    if (lo == hi) return;
    if (l != md) insert(2 * node, lo, mid, ln);
    else insert(2 * node + 1, mid + 1, hi, ln);
}
ll query(int node, int lo, int hi, int x) {
    ll r = seg[node].val(x);
    if (lo == hi) return r;
    int mid = (lo + hi) / 2;
    if (x <= mid) return min(r, query(2 * node, lo, mid, x));
    return min(r, query(2 * node + 1, mid + 1, hi, x));
}
int main() {
    int n; ll x; scanf("%d %lld", &n, &x);
    vector<ll> s(n + 1), f(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &s[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &f[i]);
    seg.assign(4 * (MAXX + 1), Line{0, INF});
    insert(1, 1, MAXX, Line{x, 0});
    ll dp = 0;
    for (int i = 1; i <= n; i++) {
        dp = query(1, 1, MAXX, (int)s[i]);
        insert(1, 1, MAXX, Line{f[i], dp});
    }
    printf("%lld\n", dp);
}
