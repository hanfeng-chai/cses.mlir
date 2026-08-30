#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;
int M;
struct Line { ll a, b; ll val(ll x) { return a * x + b; } };
vector<Line> seg;
void insert(int node, int lo, int hi, Line ln) {
    int mid = (lo + hi) / 2;
    bool l = ln.val(lo) > seg[node].val(lo);
    bool m = ln.val(mid) > seg[node].val(mid);
    if (m) swap(seg[node], ln);
    if (lo == hi) return;
    if (l != m) insert(2 * node, lo, mid, ln);
    else insert(2 * node + 1, mid + 1, hi, ln);
}
void insertSeg(int node, int lo, int hi, int ql, int qr, Line ln) {
    if (qr < lo || hi < ql) return;
    if (ql <= lo && hi <= qr) { insert(node, lo, hi, ln); return; }
    int mid = (lo + hi) / 2;
    insertSeg(2 * node, lo, mid, ql, qr, ln);
    insertSeg(2 * node + 1, mid + 1, hi, ql, qr, ln);
}
ll query(int node, int lo, int hi, int x) {
    ll r = seg[node].val(x);
    if (lo == hi) return r;
    int mid = (lo + hi) / 2;
    if (x <= mid) return max(r, query(2 * node, lo, mid, x));
    return max(r, query(2 * node + 1, mid + 1, hi, x));
}
int main() {
    int n; scanf("%d", &n); M = 100000;
    seg.assign(4 * (M + 1), Line{0, NEG});
    string out;
    while (n--) {
        int type; scanf("%d", &type);
        if (type == 1) { ll a, b, l, r; scanf("%lld %lld %lld %lld", &a, &b, &l, &r); insertSeg(1, 0, M, l, r, Line{a, b}); }
        else { int x; scanf("%d", &x); ll q = query(1, 0, M, x); out += (q < NEG / 2 ? string("NO") : to_string(q)); out += '\n'; }
    }
    cout << out;
}
