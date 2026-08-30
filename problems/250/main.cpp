#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll pre[5005];
static ll dp[5005][5005];
static short opt[5005][5005];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) { ll v; scanf("%lld", &v); pre[i] = pre[i - 1] + v; }
    for (int i = 1; i <= n; i++) { dp[i][i] = 0; opt[i][i] = i; }
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            ll w = pre[j] - pre[i - 1], best = LLONG_MAX; int bo = i;
            int lo = max((int)opt[i][j - 1], i), hi = min((int)opt[i + 1][j], j - 1);  // Knuth bounds
            for (int kk = lo; kk <= hi; kk++) {
                ll v = dp[i][kk] + dp[kk + 1][j];
                if (v < best) { best = v; bo = kk; }
            }
            dp[i][j] = best + w; opt[i][j] = bo;
        }
    printf("%lld\n", dp[1][n]);
}
