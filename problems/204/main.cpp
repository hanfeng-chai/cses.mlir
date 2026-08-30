#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; string p; cin >> n >> p; int m = p.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) { int j = pi[i - 1]; while (j && p[i] != p[j]) j = pi[j - 1]; if (p[i] == p[j]) j++; pi[i] = j; }
    // KMP automaton over states 0..m-1; state m means "pattern found" (absorbing)
    vector<array<int, 26>> aut(m);
    for (int st = 0; st < m; st++)
        for (int c = 0; c < 26; c++) {
            int j = st;
            while (j && p[j] != 'A' + c) j = pi[j - 1];
            if (p[j] == 'A' + c) j++;
            aut[st][c] = j;
        }
    vector<long long> dp(m, 0); dp[0] = 1;  // count strings that have NOT yet matched
    for (int i = 0; i < n; i++) {
        vector<long long> nd(m, 0);
        for (int st = 0; st < m; st++) if (dp[st])
            for (int c = 0; c < 26; c++) { int ns = aut[st][c]; if (ns < m) nd[ns] = (nd[ns] + dp[st]) % MOD; }
        dp = nd;
    }
    long long avoid = 0;
    for (int st = 0; st < m; st++) avoid = (avoid + dp[st]) % MOD;
    long long tot = 1;
    for (int i = 0; i < n; i++) tot = tot * 26 % MOD;
    cout << ((tot - avoid) % MOD + MOD) % MOD << "\n";
}
