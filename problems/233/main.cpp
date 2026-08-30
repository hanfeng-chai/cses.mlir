#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

// Segment tree over a compressed coordinate. Range-insert a value into all leaves of
// an index range; point-query the nearest stored value to c within a directed window.
struct SegTree {
    int n; vector<multiset<ll>> ms;
    void init(int n_) { n = n_; ms.assign(4 * n, {}); }
    void insert(int node, int lo, int hi, int ql, int qr, ll val) {
        if (qr < lo || hi < ql) return;
        if (ql <= lo && hi <= qr) { ms[node].insert(val); return; }
        int mid = (lo + hi) / 2;
        insert(2 * node, lo, mid, ql, qr, val);
        insert(2 * node + 1, mid + 1, hi, ql, qr, val);
    }
    ll best, C, LIM; bool up;
    void go(int node, int lo, int hi, int pos) {
        auto &S = ms[node];
        if (!S.empty()) {
            if (up) { auto it = S.upper_bound(C); if (it != S.end() && *it <= LIM) best = min(best, *it - C); }
            else { auto it = S.lower_bound(C); if (it != S.begin()) { --it; if (*it >= LIM) best = min(best, C - *it); } }
        }
        if (lo == hi) return;
        int mid = (lo + hi) / 2;
        if (pos <= mid) go(2 * node, lo, mid, pos); else go(2 * node + 1, mid + 1, hi, pos);
    }
    ll nearest(int pos, ll c, ll lim, bool up_) { best = INF; C = c; LIM = lim; up = up_; go(1, 0, n - 1, pos); return best; }
};

// Collinear storage: for each line coordinate keep merged disjoint intervals.
struct Lines {
    map<ll, set<pair<ll, ll>>> mp;
    void add(ll key, ll a, ll b) {
        auto &S = mp[key];
        ll lo = a, hi = b;
        auto it = S.lower_bound({a, LLONG_MIN});
        if (it != S.begin()) { auto p = prev(it); if (p->second >= a) { lo = min(lo, p->first); hi = max(hi, p->second); S.erase(p); } }
        it = S.lower_bound({lo, LLONG_MIN});
        while (it != S.end() && it->first <= hi) { hi = max(hi, it->second); lo = min(lo, it->first); it = S.erase(it); }
        S.insert({lo, hi});
    }
    ll nearest(ll key, ll c, ll lim, bool up) {
        auto mit = mp.find(key); if (mit == mp.end()) return INF;
        auto &S = mit->second;
        auto it = S.upper_bound({c, LLONG_MAX});  // first interval with lo > c
        if (up) {
            if (it != S.begin()) { auto p = prev(it); if (p->first <= c && p->second > c) return 0; }
            if (it != S.end() && it->first <= lim) return it->first - c;
            return INF;
        } else {
            if (it != S.begin()) { auto p = prev(it); if (p->first < c && p->second >= c) return 0; if (p->second < c && p->second >= lim) return c - p->second; }
            return INF;
        }
    }
};

int main() {
    int n; scanf("%d", &n);
    vector<ll> px(n + 1), py(n + 1); px[0] = py[0] = 0;
    vector<ll> dlen(n); vector<char> dch(n);
    for (int i = 0; i < n; i++) {
        char d; ll x; scanf(" %c %lld", &d, &x); dch[i] = d; dlen[i] = x;
        ll dx = 0, dy = 0;
        if (d == 'U') dy = x; else if (d == 'D') dy = -x; else if (d == 'R') dx = x; else dx = -x;
        px[i + 1] = px[i] + dx; py[i + 1] = py[i] + dy;
    }
    vector<ll> xs(px.begin(), px.end()), ys(py.begin(), py.end());
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto xi = [&](ll v) { return (int)(lower_bound(xs.begin(), xs.end(), v) - xs.begin()); };
    auto yi = [&](ll v) { return (int)(lower_bound(ys.begin(), ys.end(), v) - ys.begin()); };
    SegTree segX, segY;  // segX: horizontals' y over x-range; segY: verticals' x over y-range
    segX.init(xs.size()); segY.init(ys.size());
    Lines vlines, hlines;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        ll sx = px[i], sy = py[i], ex = px[i + 1], ey = py[i + 1], len = dlen[i], stop = INF;
        if (sx == ex) {  // vertical move
            bool up = ey > sy;
            stop = min(segX.nearest(xi(sx), sy, ey, up), vlines.nearest(sx, sy, ey, up));
        } else {         // horizontal move
            bool up = ex > sx;
            stop = min(segY.nearest(yi(sy), sx, ex, up), hlines.nearest(sy, sx, ex, up));
        }
        if (stop <= len) { total += stop; printf("%lld\n", total); return 0; }
        total += len;
        if (sx == ex) { ll a = min(sy, ey), b = max(sy, ey); segY.insert(1, 0, segY.n - 1, yi(a), yi(b), sx); vlines.add(sx, a, b); }
        else { ll a = min(sx, ex), b = max(sx, ex); segX.insert(1, 0, segX.n - 1, xi(a), xi(b), sy); hlines.add(sy, a, b); }
    }
    printf("%lld\n", total);
}
