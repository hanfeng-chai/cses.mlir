#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    char buf[40];
    for (int i = 0; i < n; i++) { scanf("%s", buf); int v = 0; for (int j = 0; j < k; j++) v = v * 2 + (buf[j] - '0'); a[i] = v; }
    int best = k;
    for (int i = 0; i < n; i++) {
        int ai = a[i];
        for (int j = i + 1; j < n; j++) { int d = __builtin_popcount(ai ^ a[j]); if (d < best) best = d; }
        if (best == 0) break;
    }
    printf("%d\n", best);
}
