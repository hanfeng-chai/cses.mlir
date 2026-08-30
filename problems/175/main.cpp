#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
int main() {
    int n; scanf("%d", &n);
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    // answer = lcm of cycle lengths mod p; track max exponent of each prime
    map<int, int> mx;
    vector<char> vis(n + 1, 0);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            int len = 0, j = i;
            while (!vis[j]) { vis[j] = 1; j = p[j]; len++; }
            int t = len;
            for (int d = 2; (long long)d * d <= t; d++)
                if (t % d == 0) { int e = 0; while (t % d == 0) { t /= d; e++; } mx[d] = max(mx[d], e); }
            if (t > 1) mx[t] = max(mx[t], 1);
        }
    long long ans = 1;
    for (auto [pr, e] : mx) ans = ans * pw(pr, e) % MOD;
    printf("%lld\n", ans);
}
