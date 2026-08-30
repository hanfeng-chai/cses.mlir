#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
pair<long long, long long> fib(long long n) {  // returns (F(n), F(n+1)) via fast doubling
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n / 2);
    long long c = a * ((2 * b % MOD - a + MOD) % MOD) % MOD;
    long long d = (a * a % MOD + b * b % MOD) % MOD;
    if (n & 1) return {d, (c + d) % MOD};
    return {c, d};
}
int main() {
    long long n; scanf("%lld", &n);
    printf("%lld\n", fib(n).first);
}
