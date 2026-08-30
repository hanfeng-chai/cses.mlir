#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        long long s = 0;
        for (int j = 1; j <= 6 && j <= i; j++) s += dp[i - j];
        dp[i] = s % MOD;
    }
    cout << dp[n] << "\n";
}
