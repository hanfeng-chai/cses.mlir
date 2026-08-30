#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (auto &v : w) cin >> v;
    // dp[mask] = {min rides, min weight used in the last ride}
    vector<pair<int, int>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                auto pr = dp[mask ^ (1 << i)];
                pair<int, int> cand;
                if (pr.second + w[i] <= x) cand = {pr.first, pr.second + w[i]};
                else cand = {pr.first + 1, w[i]};
                dp[mask] = min(dp[mask], cand);
            }
    cout << dp[(1 << n) - 1].first << "\n";
}
