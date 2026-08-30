#include <bits/stdc++.h>
using namespace std;
struct BIT {
    vector<int> t; int n;
    void init(int n_) { n = n_; t.assign(n + 1, 0); }
    void add(int i, int v) { for (i++; i <= n; i += i & -i) t[i] += v; }
    int sum(int i) { int s = 0; for (i++; i > 0; i -= i & -i) s += t[i]; return s; }
    int range(int l, int r) { if (l > r) return 0; return sum(r) - sum(l - 1); }
};
int main() {
    int n; scanf("%d", &n);
    const int SH = 1000000;
    vector<array<int, 4>> ev;  // (x, type, a, b): type 0=add horiz, 1=vertical query, 2=remove horiz
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (y1 == y2) { int xL = min(x1, x2), xR = max(x1, x2); ev.push_back({xL, 0, y1 + SH, 0}); ev.push_back({xR, 2, y1 + SH, 0}); }
        else { int yL = min(y1, y2), yR = max(y1, y2); ev.push_back({x1, 1, yL + SH, yR + SH}); }
    }
    sort(ev.begin(), ev.end(), [](const array<int, 4> &a, const array<int, 4> &b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); });
    BIT bit; bit.init(2 * SH + 2);
    long long ans = 0;
    for (auto &e : ev) {
        if (e[1] == 0) bit.add(e[2], 1);
        else if (e[1] == 2) bit.add(e[2], -1);
        else ans += bit.range(e[2], e[3]);
    }
    printf("%lld\n", ans);
}
