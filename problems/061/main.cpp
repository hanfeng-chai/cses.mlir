#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &v : c) cin >> v;
    const int INF = 1e9;
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int s = 1; s <= x; s++)
        for (int v : c)
            if (v <= s) dp[s] = min(dp[s], dp[s - v] + 1);
    cout << (dp[x] >= INF ? -1 : dp[x]) << "\n";
}
