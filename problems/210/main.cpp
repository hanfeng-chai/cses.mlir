#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    vector<long long> dp(n + 1); dp[0] = 1;  // dp[i] = distinct subsequences of prefix (incl. empty)
    vector<int> last(26, -1);
    for (int i = 1; i <= n; i++) {
        int c = s[i - 1] - 'a';
        dp[i] = 2 * dp[i - 1] % MOD;
        if (last[c] != -1) dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
        last[c] = i;
    }
    cout << (dp[n] - 1 + MOD) % MOD << "\n";  // exclude the empty string
}
