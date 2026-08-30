#include <bits/stdc++.h>
using namespace std;
int n, q;
struct Seg {
    vector<long long> sum, add, asn;
    vector<char> hasA;
    int N;
    void init(int n_, vector<long long> &v) {
        N = n_; sum.assign(4 * N, 0); add.assign(4 * N, 0); asn.assign(4 * N, 0); hasA.assign(4 * N, 0);
        build(1, 1, N, v);
    }
    void build(int p, int l, int r, vector<long long> &v) {
        if (l == r) { sum[p] = v[l]; return; }
        int m = (l + r) / 2; build(2 * p, l, m, v); build(2 * p + 1, m + 1, r, v);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void putAsn(int p, int l, int r, long long v) { sum[p] = v * (r - l + 1); asn[p] = v; hasA[p] = 1; add[p] = 0; }
    void putAdd(int p, int l, int r, long long v) { sum[p] += v * (r - l + 1); add[p] += v; }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        if (hasA[p]) { putAsn(2 * p, l, m, asn[p]); putAsn(2 * p + 1, m + 1, r, asn[p]); hasA[p] = 0; }
        if (add[p]) { putAdd(2 * p, l, m, add[p]); putAdd(2 * p + 1, m + 1, r, add[p]); add[p] = 0; }
    }
    void uAdd(int p, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { putAdd(p, l, r, v); return; }
        push(p, l, r); int m = (l + r) / 2;
        uAdd(2 * p, l, m, ql, qr, v); uAdd(2 * p + 1, m + 1, r, ql, qr, v);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void uAsn(int p, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { putAsn(p, l, r, v); return; }
        push(p, l, r); int m = (l + r) / 2;
        uAsn(2 * p, l, m, ql, qr, v); uAsn(2 * p + 1, m + 1, r, ql, qr, v);
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
        int t; scanf("%d", &t);
        if (t == 1) { int a, b; long long x; scanf("%d %d %lld", &a, &b, &x); seg.uAdd(1, 1, n, a, b, x); }
        else if (t == 2) { int a, b; long long x; scanf("%d %d %lld", &a, &b, &x); seg.uAsn(1, 1, n, a, b, x); }
        else { int a, b; scanf("%d %d", &a, &b); printf("%lld\n", seg.qry(1, 1, n, a, b)); }
    }
}
