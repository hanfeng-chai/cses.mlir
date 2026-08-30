#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    const int LOG = 30;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) up[0][i] = t[i];
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[j][i] = up[j - 1][up[j - 1][i]];
    while (q--) {
        int x; long long k;
        scanf("%d %lld", &x, &k);
        for (int j = 0; j < LOG; j++)
            if (k >> j & 1) x = up[j][x];
        printf("%d\n", x);
    }
}
