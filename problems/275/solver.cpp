#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, LOG;
int bit_[1005];
void upd(int i, int v) { for (; i <= n; i += i & -i) bit_[i] += v; }
int kth(int k) {  // index of k-th smallest available value
    int pos = 0;
    for (int j = LOG; j >= 0; j--) { int nx = pos + (1 << j); if (nx <= n && bit_[nx] < k) { pos = nx; k -= bit_[nx]; } }
    return pos + 1;
}
ll doOp(int i, int j) {
    printf("%d %d\n", i, j); fflush(stdout);
    ll inv; scanf("%lld", &inv);
    if (inv == 0) exit(0);  // permutation sorted -> we win
    return inv;
}
int main() {
    scanf("%d", &n);
    LOG = 1; while ((1 << LOG) <= n) LOG++;
    if (n == 1) { printf("1 1\n"); fflush(stdout); ll inv; scanf("%lld", &inv); return 0; }
    ll oldInv = doOp(1, 1);  // single-element reversal: reports current inversion count
    vector<ll> invSuf(n + 2, 0);
    for (int i = 1; i <= n - 1; i++) {
        ll L = n - i + 1, Cn = L * (L - 1) / 2;
        ll inv1 = doOp(i, n);
        invSuf[i] = (oldInv + Cn - inv1) / 2;  // inversions inside [i,n]
        doOp(i, n);                            // reverse back to restore
    }
    invSuf[n] = 0;
    for (int i = 1; i <= n; i++) upd(i, 1);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {  // Lehmer-code reconstruction (left to right)
        ll R = invSuf[i] - invSuf[i + 1];  // # to the right smaller than a_i
        int val = kth((int)R + 1);
        a[i] = val; upd(val, -1);
    }
    vector<int> posOf(n + 1);
    for (int i = 1; i <= n; i++) posOf[a[i]] = i;
    for (int pos = n; pos >= 2; pos--) {  // selection sort by reversal
        int p = posOf[pos];
        if (p == pos) continue;
        doOp(p, pos);
        int l = p, r = pos;
        while (l < r) { swap(a[l], a[r]); posOf[a[l]] = l; posOf[a[r]] = r; l++; r--; }
    }
    printf("1 1\n"); fflush(stdout); ll inv; scanf("%lld", &inv);  // safety (unreachable if sorted earlier)
    return 0;
}
