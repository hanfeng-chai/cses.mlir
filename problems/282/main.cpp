#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    int m = n - 1, ans = 0;
    for (int i = 0; i < n; i++) if ((i & m) == i) ans ^= a[i];  // C(n-1,i) odd iff i submask of n-1
    printf("%d\n", ans);
}
