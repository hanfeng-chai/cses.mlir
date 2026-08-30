#include <bits/stdc++.h>
using namespace std;
// k-th child eliminated when every 2nd is removed from a circle of n.
long long solve(long long n, long long k) {
    if (k <= n / 2) return 2 * k;
    long long kp = k - n / 2;
    if (n % 2 == 0) return 2 * solve(n / 2, kp) - 1;     // after removing n, count restarts at 1
    if (kp == 1) return 1;                                // n odd: first survivor-round removal is position 1
    return 2 * solve((n - 1) / 2, kp - 1) + 1;
}
int main() {
    int q; scanf("%d", &q);
    while (q--) { long long n, k; scanf("%lld %lld", &n, &k); printf("%lld\n", solve(n, k)); }
}
