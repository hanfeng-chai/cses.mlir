#include <bits/stdc++.h>
using namespace std;
bool isSq(long long x) {
    if (x < 0) return false;
    long long s = sqrtl(x);
    for (long long i = max(0LL, s - 2); i <= s + 2; i++) if (i * i == x) return true;
    return false;
}
bool sumTwoSq(long long x) {  // x is sum of two squares iff every prime p%4==3 has even exponent
    for (long long p = 2; p * p <= x; p++)
        if (x % p == 0) { int e = 0; while (x % p == 0) { x /= p; e++; } if (p % 4 == 3 && (e & 1)) return false; }
    if (x > 1 && x % 4 == 3) return false;
    return true;
}
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        long long n; scanf("%lld", &n);
        // Gauss: every n is a sum of at most 3 triangular numbers
        if (isSq(8 * n + 1)) printf("1\n");
        else if (sumTwoSq(4 * n + 1)) printf("2\n");
        else printf("3\n");
    }
}
