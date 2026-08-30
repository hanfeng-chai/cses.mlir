#include <bits/stdc++.h>
using namespace std;
// min over a of p_a + |a-k|: for a<=k use (p_a - a)+k, for a>=k use (p_a + a)-k.
int n, q;
const long long INF = 4e18;
struct Seg {
    vector<long long> t;
    int n;
    void init(int n_) { n = n_; t.assign(2 * n, INF); }
    void upd(int p, long long v) { for (t[p += n] = v, p >>= 1; p >= 1; p >>= 1) t[p] = min(t[2 * p], t[2 * p + 1]); }
    long long qry(int l, int r) {  // inclusive 0-indexed
        long long res = INF;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }
} segL, segR;
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> p(n + 1);
    segL.init(n); segR.init(n);  // segL stores p_a - a, segR stores p_a + a
    for (int i = 1; i <= n; i++) { scanf("%lld", &p[i]); segL.upd(i - 1, p[i] - i); segR.upd(i - 1, p[i] + i); }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) { int k; long long x; scanf("%d %lld", &k, &x); p[k] = x; segL.upd(k - 1, x - k); segR.upd(k - 1, x + k); }
        else {
            int k; scanf("%d", &k);
            long long ans = INF;
            ans = min(ans, segL.qry(0, k - 1) + k);          // a <= k
            ans = min(ans, segR.qry(k - 1, n - 1) - k);      // a >= k
            printf("%lld\n", ans);
        }
    }
}
