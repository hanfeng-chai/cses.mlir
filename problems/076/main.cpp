#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> seg;
void upd(int nd, int l, int r, int pos, int val) {
    if (l == r) { seg[nd] = max(seg[nd], val); return; }
    int m = (l + r) / 2;
    if (pos <= m) upd(2 * nd, l, m, pos, val);
    else upd(2 * nd + 1, m + 1, r, pos, val);
    seg[nd] = max(seg[2 * nd], seg[2 * nd + 1]);
}
int qry(int nd, int l, int r, int ql, int qr) {
    if (ql > qr || qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return seg[nd];
    int m = (l + r) / 2;
    return max(qry(2 * nd, l, m, ql, qr), qry(2 * nd + 1, m + 1, r, ql, qr));
}
int main() {
    cin >> n;
    vector<int> h(n);
    for (auto &v : h) cin >> v;
    // f[i] = longest route starting at i. i can glide to any j inside the
    // maximal span where i is the strict maximum, i.e. the open interval
    // bounded by the nearest mountain of height >= h[i] on each side.
    vector<int> L(n), R(n), stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && h[stk.back()] < h[i]) stk.pop_back();
        L[i] = stk.empty() ? -1 : stk.back();
        stk.push_back(i);
    }
    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && h[stk.back()] < h[i]) stk.pop_back();
        R[i] = stk.empty() ? n : stk.back();
        stk.push_back(i);
    }
    // Process by increasing height so every reachable (strictly lower) mountain
    // is already in the segment tree. Equal heights never lie strictly inside
    // each other's window, so they are correctly excluded.
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return h[a] < h[b]; });
    seg.assign(4 * n, 0);
    int ans = 1;
    for (int i : order) {
        int best = qry(1, 0, n - 1, L[i] + 1, R[i] - 1);  // i itself is still 0
        int fi = 1 + best;
        upd(1, 0, n - 1, i, fi);
        ans = max(ans, fi);
    }
    cout << ans << "\n";
}
