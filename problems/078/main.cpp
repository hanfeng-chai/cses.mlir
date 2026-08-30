#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> p(n);  // {end, start, reward}
    for (auto &e : p) {
        long long a, b, w;
        cin >> a >> b >> w;
        e = {b, a, w};
    }
    sort(p.begin(), p.end());
    vector<long long> ends(n);
    for (int i = 0; i < n; i++) ends[i] = p[i][0];
    vector<long long> dp(n + 1, 0);  // dp[i] = best money using first i projects (by end)
    for (int i = 0; i < n; i++) {
        long long a = p[i][1], w = p[i][2];
        // number of earlier projects whose end day < start day a
        int lo = lower_bound(ends.begin(), ends.begin() + i, a) - ends.begin();
        dp[i + 1] = max(dp[i], w + dp[lo]);
    }
    cout << dp[n] << "\n";
}
