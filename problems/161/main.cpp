#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b, long long m) { a %= m; long long r = 1; while (b) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; } return r; }
int main() {
    int n; scanf("%d", &n);
    while (n--) { long long a, b; scanf("%lld %lld", &a, &b); printf("%lld\n", pw(a, b, MOD)); }
}
