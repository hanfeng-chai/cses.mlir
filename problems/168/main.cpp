#include <bits/stdc++.h>
using namespace std;
const int MX = 1000001;
int mu[MX], freq[MX];
int main() {
    vector<int> primes; vector<char> comp(MX, 0); mu[1] = 1;
    for (int i = 2; i < MX; i++) {
        if (!comp[i]) { primes.push_back(i); mu[i] = -1; }
        for (int p : primes) {
            if ((long long)i * p >= MX) break;
            comp[i * p] = 1;
            if (i % p == 0) { mu[i * p] = 0; break; }
            mu[i * p] = -mu[i];
        }
    }
    int n; scanf("%d", &n);
    int mx = 0;
    for (int i = 0; i < n; i++) { int x; scanf("%d", &x); freq[x]++; mx = max(mx, x); }
    long long ans = 0;
    for (int d = 1; d <= mx; d++) {  // Mobius: sum mu(d) * C(#multiples of d, 2)
        if (mu[d] == 0) continue;
        long long c = 0;
        for (int m = d; m <= mx; m += d) c += freq[m];
        ans += (long long)mu[d] * (c * (c - 1) / 2);
    }
    printf("%lld\n", ans);
}
