#include <bits/stdc++.h>
using namespace std;
int n;
int bit[1001][1001];
void upd(int y, int x, int d) { for (int i = y; i <= n; i += i & -i) for (int j = x; j <= n; j += j & -j) bit[i][j] += d; }
int qs(int y, int x) { int s = 0; for (int i = y; i > 0; i -= i & -i) for (int j = x; j > 0; j -= j & -j) s += bit[i][j]; return s; }
int rect(int y1, int x1, int y2, int x2) { return qs(y2, x2) - qs(y1 - 1, x2) - qs(y2, x1 - 1) + qs(y1 - 1, x1 - 1); }
int main() {
    int q;
    scanf("%d %d", &n, &q);
    vector<vector<int>> cur(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        char buf[1005]; scanf("%s", buf);
        for (int j = 1; j <= n; j++) if (buf[j - 1] == '*') { cur[i][j] = 1; upd(i, j, 1); }
    }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int y, x; scanf("%d %d", &y, &x);
            if (cur[y][x]) { upd(y, x, -1); cur[y][x] = 0; }
            else { upd(y, x, 1); cur[y][x] = 1; }
        } else {
            int y1, x1, y2, x2; scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
            printf("%d\n", rect(y1, x1, y2, x2));
        }
    }
}
