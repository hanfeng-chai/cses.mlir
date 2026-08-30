#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) { long long x; scanf("%lld", &x); pre[i] = pre[i - 1] + x; }
    while (q--) { int a, b; scanf("%d %d", &a, &b); printf("%lld\n", pre[b] - pre[a - 1]); }
}
