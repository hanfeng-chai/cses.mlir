#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, a, b; scanf("%d %d %d", &n, &a, &b);
    vector<double> dp(6 * n + 1, 0); dp[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<double> nd(6 * n + 1, 0);
        for (int s = 0; s <= 6 * i; s++) if (dp[s] > 0) for (int f = 1; f <= 6; f++) nd[s + f] += dp[s] / 6;
        dp = nd;
    }
    double ans = 0;
    for (int s = a; s <= b; s++) ans += dp[s];
    printf("%.6f\n", ans);
}
