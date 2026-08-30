#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &v : c) cin >> v;
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    // ordered count: sum position outer, coin inner -> sequences
    for (int s = 1; s <= x; s++) {
        long long t = 0;
        for (int v : c)
            if (v <= s) t += dp[s - v];
        dp[s] = t % MOD;
    }
    cout << dp[x] << "\n";
}
