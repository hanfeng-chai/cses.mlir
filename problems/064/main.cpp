#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t) {
            int d = t % 10;
            if (d) dp[i] = min(dp[i], dp[i - d] + 1);
            t /= 10;
        }
    }
    cout << dp[n] << "\n";
}
