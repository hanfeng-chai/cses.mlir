#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int bas[31] = {0};
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        for (int b = 29; b >= 0; b--) if (x >> b & 1) { if (!bas[b]) { bas[b] = x; break; } x ^= bas[b]; }
    }
    int ans = 0;  // greedily maximize using the linear basis
    for (int b = 29; b >= 0; b--) if ((ans ^ bas[b]) > ans) ans ^= bas[b];
    printf("%d\n", ans);
}
