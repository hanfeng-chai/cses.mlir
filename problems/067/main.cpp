#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (auto &v : x) cin >> v;
    vector<long long> dp(m + 2, 0);
    if (x[0] == 0)
        for (int v = 1; v <= m; v++) dp[v] = 1;
    else
        dp[x[0]] = 1;
    for (int i = 1; i < n; i++) {
        vector<long long> nd(m + 2, 0);
        for (int v = 1; v <= m; v++) {
            if (x[i] != 0 && x[i] != v) continue;
            nd[v] = (dp[v] + dp[v - 1] + dp[v + 1]) % MOD;
        }
        dp = move(nd);
    }
    long long ans = 0;
    for (int v = 1; v <= m; v++) ans = (ans + dp[v]) % MOD;
    cout << ans << "\n";
}
