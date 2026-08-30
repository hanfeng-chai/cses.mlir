#include <bits/stdc++.h>
using namespace std;
int cnt[1000001];
int main() {
    int n; scanf("%d", &n);
    int mx = 0;
    for (int i = 0; i < n; i++) { int x; scanf("%d", &x); cnt[x]++; mx = max(mx, x); }
    for (int d = mx; d >= 1; d--) {  // largest d dividing at least two values
        int c = 0;
        for (int m = d; m <= mx; m += d) c += cnt[m];
        if (c >= 2) { printf("%d\n", d); return 0; }
    }
}
