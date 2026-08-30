#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (auto &v : h) cin >> v;
    for (auto &v : s) cin >> v;
    vector<int> dp(x + 1, 0);  // dp[price] = max pages with budget price
    for (int i = 0; i < n; i++)
        for (int p = x; p >= h[i]; p--) dp[p] = max(dp[p], dp[p - h[i]] + s[i]);
    cout << dp[x] << "\n";
}
