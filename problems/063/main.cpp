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
    // unordered count: coin outer, sum inner -> each coin used as a "layer"
    for (int v : c)
        for (int s = v; s <= x; s++) dp[s] = (dp[s] + dp[s - v]) % MOD;
    cout << dp[x] << "\n";
}
