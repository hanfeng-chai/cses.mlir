#include <bits/stdc++.h>
using namespace std;
// Range update adds an arithmetic progression 1,2,3,... ; lazy stores the value
// added to a node's leftmost element (common difference is always 1).
int n, q;
struct Seg {
    vector<long long> sum, lazyB, lazyD;  // each position i gets lazyB + lazyD*(i - nodeLeft)
    int N;
    void init(int n_, vector<long long> &v) { N = n_; sum.assign(4 * N, 0); lazyB.assign(4 * N, 0); lazyD.assign(4 * N, 0); build(1, 1, N, v); }
    void build(int p, int l, int r, vector<long long> &v) {
        if (l == r) { sum[p] = v[l]; return; }
        int m = (l + r) / 2; build(2 * p, l, m, v); build(2 * p + 1, m + 1, r, v);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void put(int p, int l, int r, long long base, long long d) {  // add base + d*(i-l) over [l,r]
        long long len = r - l + 1;
        sum[p] += base * len + d * (len * (len - 1) / 2);
        lazyB[p] += base; lazyD[p] += d;
    }
    void push(int p, int l, int r) {
        if (lazyB[p] || lazyD[p]) {
            int m = (l + r) / 2;
            put(2 * p, l, m, lazyB[p], lazyD[p]);
            put(2 * p + 1, m + 1, r, lazyB[p] + lazyD[p] * (m - l + 1), lazyD[p]);
            lazyB[p] = lazyD[p] = 0;
        }
    }
    void upd(int p, int l, int r, int ql, int qr) {  // add (i-ql+1) at each i in [ql,qr]
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { put(p, l, r, (long long)(l - ql + 1), 1); return; }
        push(p, l, r); int m = (l + r) / 2;
        upd(2 * p, l, m, ql, qr); upd(2 * p + 1, m + 1, r, ql, qr);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    long long qry(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[p];
        push(p, l, r); int m = (l + r) / 2;
        return qry(2 * p, l, m, ql, qr) + qry(2 * p + 1, m + 1, r, ql, qr);
    }
} seg;
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    seg.init(n, v);
    while (q--) {
        int t, a, b; scanf("%d %d %d", &t, &a, &b);
        if (t == 1) seg.upd(1, 1, n, a, b);
        else printf("%lld\n", seg.qry(1, 1, n, a, b));
    }
}
