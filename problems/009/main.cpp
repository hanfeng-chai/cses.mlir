#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    const long long MOD = 1000000007;
    long long r = 1, b = 2;  // 快速幂求 2^n
    while (n) {
        if (n & 1) r = r * b % MOD;
        b = b * b % MOD;
        n >>= 1;
    }
    cout << r << '\n';
}
