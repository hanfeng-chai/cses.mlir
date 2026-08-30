#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    const long long INF = 1e18;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b; long long c;
        scanf("%d %d %lld", &a, &b, &c);
        d[a][b] = min(d[a][b], c); d[b][a] = min(d[b][a], c);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
        }
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld\n", d[a][b] >= INF ? -1 : d[a][b]);
    }
}
