#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    long long tot = (long long)n * (n + 1) / 2;
    if (tot & 1) { cout << 0 << "\n"; return 0; }
    int half = tot / 2;
    vector<long long> dp(half + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int s = half; s >= i; s--) dp[s] = (dp[s] + dp[s - i]) % MOD;
    long long inv2 = (MOD + 1) / 2;     // each partition counted twice
    cout << dp[half] * inv2 % MOD << "\n";
}
