#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int K;
vector<int> cnt_;
vector<ll> cov, ys;
void upd(int node, int lo, int hi, int ql, int qr, int v) {  // add v over [ql,qr) compressed y
    if (qr <= lo || hi <= ql) return;
    if (ql <= lo && hi <= qr) cnt_[node] += v;
    else { int mid = (lo + hi) / 2; upd(2 * node, lo, mid, ql, qr, v); upd(2 * node + 1, mid, hi, ql, qr, v); }
    if (cnt_[node] > 0) cov[node] = ys[hi] - ys[lo];
    else if (hi - lo == 1) cov[node] = 0;
    else cov[node] = cov[2 * node] + cov[2 * node + 1];
}
int main() {
    int n; scanf("%d", &n);
    vector<array<ll, 4>> ev;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2; scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        ev.push_back({x1, y1, y2, 1}); ev.push_back({x2, y1, y2, -1});
        ys.push_back(y1); ys.push_back(y2);
    }
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());
    K = ys.size() - 1;
    cnt_.assign(4 * (K + 1), 0); cov.assign(4 * (K + 1), 0);
    sort(ev.begin(), ev.end(), [](const array<ll, 4> &a, const array<ll, 4> &b) { return a[0] < b[0]; });
    ll area = 0, prevx = ev[0][0];
    for (int i = 0; i < (int)ev.size();) {
        ll x = ev[i][0];
        area += cov[1] * (x - prevx);
        while (i < (int)ev.size() && ev[i][0] == x) {
            int l = lower_bound(ys.begin(), ys.end(), ev[i][1]) - ys.begin();
            int r = lower_bound(ys.begin(), ys.end(), ev[i][2]) - ys.begin();
            upd(1, 0, K, l, r, ev[i][3]);
            i++;
        }
        prevx = x;
    }
    printf("%lld\n", area);
}
