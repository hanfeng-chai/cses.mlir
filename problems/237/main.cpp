#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef unsigned long long u64;
const int W = 47;  // ceil(3000/64)
static u64 bits[3000][W];
int main() {
    int n; scanf("%d", &n);
    char buf[3005];
    int w = (n + 63) / 64;
    for (int i = 0; i < n; i++) { scanf("%s", buf); for (int j = 0; j < n; j++) if (buf[j] == '1') bits[i][j >> 6] |= (u64)1 << (j & 63); }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        const u64 *bi = bits[i];
        for (int j = i + 1; j < n; j++) {
            const u64 *bj = bits[j];
            long long c = 0;
            for (int t = 0; t < w; t++) c += __builtin_popcountll(bi[t] & bj[t]);  // common black columns
            ans += c * (c - 1) / 2;
        }
    }
    printf("%lld\n", ans);
}
