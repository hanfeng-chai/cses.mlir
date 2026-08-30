#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n; scanf("%d", &n);
    // derangements: D(n) = (n-1)(D(n-1)+D(n-2))
    vector<long long> d(max(2, n + 1));
    d[0] = 1; if (n >= 1) d[1] = 0;
    for (int i = 2; i <= n; i++) d[i] = (long long)(i - 1) * ((d[i - 1] + d[i - 2]) % MOD) % MOD;
    printf("%lld\n", d[n]);
}
