#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
int main() {
    char buf[1000006];
    scanf("%s", buf);
    int len = strlen(buf);
    vector<long long> f(len + 1);
    f[0] = 1;
    for (int i = 1; i <= len; i++) f[i] = f[i - 1] * i % MOD;
    int cnt[26] = {0};
    for (int i = 0; i < len; i++) cnt[buf[i] - 'a']++;
    long long ans = f[len];  // multinomial = len! / prod(cnt!)
    for (int c = 0; c < 26; c++) ans = ans * pw(f[cnt[c]], MOD - 2) % MOD;
    printf("%lld\n", ans);
}
