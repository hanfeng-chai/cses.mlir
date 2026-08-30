#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;
int n, k;
vector<ll> c, costArr, dpPrev, dpCur;
inline ll COST(int a, int b) { return costArr[(ll)a * (n + 1) + b]; }
void solve(int iL, int iR, int pL, int pR) {  // divide & conquer optimization
    if (iL > iR) return;
    int mid = (iL + iR) / 2;
    ll best = INF; int bestp = pL, up = min(pR, mid - 1);
    for (int p = pL; p <= up; p++) {
        if (dpPrev[p] >= INF) continue;
        ll v = dpPrev[p] + COST(p + 1, mid);
        if (v < best) { best = v; bestp = p; }
    }
    dpCur[mid] = best;
    solve(iL, mid - 1, pL, bestp);
    solve(mid + 1, iR, bestp, pR);
}
int main() {
    scanf("%d %d", &n, &k);
    c.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
    costArr.assign((ll)(n + 1) * (n + 1), 0);
    for (int a = 1; a <= n; a++) {  // 1-median cost via incremental weighted median
        ll med = a, Lw = c[a], W = c[a], cost = 0;
        for (int b = a + 1; b <= n; b++) {
            cost += c[b] * (b - med); W += c[b];
            while (true) { ll Rw = W - Lw; if (Rw > Lw) { cost += Lw - Rw; med++; Lw += c[med]; } else break; }
            costArr[(ll)a * (n + 1) + b] = cost;
        }
    }
    dpPrev.assign(n + 1, INF); dpCur.assign(n + 1, INF);
    dpPrev[0] = 0;
    for (int j = 1; j <= k; j++) {
        fill(dpCur.begin(), dpCur.end(), INF);
        solve(j, n, j - 1, n - 1);
        swap(dpPrev, dpCur);
    }
    printf("%lld\n", dpPrev[n]);
}
