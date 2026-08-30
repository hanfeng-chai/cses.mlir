#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int bas[31] = {0}, r = 0;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        for (int b = 29; b >= 0; b--) if (x >> b & 1) { if (!bas[b]) { bas[b] = x; r++; break; } x ^= bas[b]; }
    }
    printf("%lld\n", 1LL << r);  // distinct subset xors = 2^rank
}
