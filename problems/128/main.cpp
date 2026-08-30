#include <bits/stdc++.h>
using namespace std;
int B;
int bit[400005];
void upd(int i, int d) { for (; i <= B; i += i & -i) bit[i] += d; }
int qsum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<long long> p(n + 1);
    vector<long long> vals;
    for (int i = 1; i <= n; i++) { scanf("%lld", &p[i]); vals.push_back(p[i]); }
    vector<array<long long, 3>> ops(q);
    for (int i = 0; i < q; i++) {
        char c; long long a, b;
        scanf(" %c %lld %lld", &c, &a, &b);
        ops[i] = {c == '!' ? 1 : 2, a, b};
        if (c == '!') vals.push_back(b);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    B = vals.size();
    auto idx = [&](long long v) { return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; };
    for (int i = 1; i <= n; i++) upd(idx(p[i]), 1);
    for (auto &o : ops) {
        if (o[0] == 1) {
            int k = o[1]; long long x = o[2];
            upd(idx(p[k]), -1); p[k] = x; upd(idx(x), 1);
        } else {
            long long a = o[1], b = o[2];
            int lo = lower_bound(vals.begin(), vals.end(), a) - vals.begin();      // # vals < a
            int hi = upper_bound(vals.begin(), vals.end(), b) - vals.begin();      // # vals <= b
            printf("%d\n", qsum(hi) - qsum(lo));
        }
    }
}
