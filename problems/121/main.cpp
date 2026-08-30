#include <bits/stdc++.h>
using namespace std;
int n, q;
long long bit[200005];
void upd(int i, long long d) { for (; i <= n; i += i & -i) bit[i] += d; }
long long qsum(int i) { long long s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) { scanf("%lld", &a[i]); upd(i, a[i]); }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) { int k; long long u; scanf("%d %lld", &k, &u); upd(k, u - a[k]); a[k] = u; }
        else { int x, y; scanf("%d %d", &x, &y); printf("%lld\n", qsum(y) - qsum(x - 1)); }
    }
}
