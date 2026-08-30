#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    // E[max] = sum_{v=1..k} P(max >= v) = sum_{v=1..k} (1 - ((v-1)/k)^n)
    long double ans = 0;
    for (int v = 1; v <= k; v++) ans += 1.0L - powl((long double)(v - 1) / k, n);
    printf("%.6Lf\n", ans);
}
