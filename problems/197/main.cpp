#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
static int nxt[1000006][26];
static bool term[1000006];
int cnt = 1;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    int k; cin >> k;
    for (int i = 0; i < k; i++) {  // build trie of dictionary words
        string w; cin >> w; int u = 0;
        for (char c : w) { int d = c - 'a'; if (!nxt[u][d]) nxt[u][d] = cnt++; u = nxt[u][d]; }
        term[u] = true;
    }
    vector<long long> dp(n + 1, 0); dp[0] = 1;
    for (int i = 0; i < n; i++) {  // dp[i] = ways to build prefix of length i
        if (!dp[i]) continue;
        int u = 0;
        for (int j = i; j < n; j++) {
            int d = s[j] - 'a';
            if (!nxt[u][d]) break;
            u = nxt[u][d];
            if (term[u]) dp[j + 1] = (dp[j + 1] + dp[i]) % MOD;
        }
    }
    cout << dp[n] << "\n";
}
