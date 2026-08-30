#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n; scanf("%lld", &n);
    long long tot = 0;
    for (int b = 0; (1LL << b) <= n; b++) {  // count integers in [1,n] with bit b set
        long long cyc = 1LL << (b + 1), half = 1LL << b;
        tot += (n + 1) / cyc * half + max(0LL, (n + 1) % cyc - half);
    }
    printf("%lld\n", tot);
}
