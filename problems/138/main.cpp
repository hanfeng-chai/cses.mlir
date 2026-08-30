#include <bits/stdc++.h>
using namespace std;
const int T = 1000000;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<int> minEnd(T + 2, INT_MAX);
    for (int i = 0; i < n; i++) { int a, b; scanf("%d %d", &a, &b); minEnd[a] = min(minEnd[a], b); }
    vector<int> go(T + 2, INT_MAX);  // min end among movies starting at time >= t
    for (int t = T; t >= 0; t--) go[t] = min(go[t + 1], minEnd[t]);
    const int LOG = 20;
    vector<vector<int>> up(LOG, vector<int>(T + 2));
    for (int t = 0; t <= T + 1; t++) up[0][t] = (go[t] == INT_MAX) ? T + 1 : go[t];
    up[0][T + 1] = T + 1;
    for (int j = 1; j < LOG; j++)
        for (int t = 0; t <= T + 1; t++) up[j][t] = up[j - 1][up[j - 1][t]];
    while (q--) {
        int a, b; scanf("%d %d", &a, &b);
        int t = a, cnt = 0;
        for (int j = LOG - 1; j >= 0; j--)
            if (up[j][t] <= b) { cnt += 1 << j; t = up[j][t]; }
        printf("%d\n", cnt);
    }
}
