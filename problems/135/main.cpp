#include <bits/stdc++.h>
using namespace std;
int n, q;
int bit[200005];
void upd(int i, int d) { for (; i <= n; i += i & -i) bit[i] += d; }
int qsum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d %d", &n, &q);
    vector<int> x(n + 1), vals;
    for (int i = 1; i <= n; i++) { scanf("%d", &x[i]); vals.push_back(x[i]); }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= n; i++) x[i] = lower_bound(vals.begin(), vals.end(), x[i]) - vals.begin() + 1;
    vector<array<int, 3>> qs(q);
    for (int i = 0; i < q; i++) { int a, b; scanf("%d %d", &a, &b); qs[i] = {b, a, i}; }
    sort(qs.begin(), qs.end());  // by right endpoint b
    vector<int> last((int)vals.size() + 1, 0), ans(q);
    int pos = 1;
    for (auto &qq : qs) {
        int b = qq[0], a = qq[1], id = qq[2];
        while (pos <= b) {
            int v = x[pos];
            if (last[v]) upd(last[v], -1);
            upd(pos, 1); last[v] = pos; pos++;
        }
        ans[id] = qsum(b) - qsum(a - 1);
    }
    for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
