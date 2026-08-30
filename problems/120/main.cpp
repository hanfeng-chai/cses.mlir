#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    vector<vector<int>> sp(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) scanf("%d", &sp[0][i]);
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            sp[j][i] = min(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        int k = 31 - __builtin_clz(b - a + 1);
        printf("%d\n", min(sp[k][a], sp[k][b - (1 << k) + 1]));
    }
}
