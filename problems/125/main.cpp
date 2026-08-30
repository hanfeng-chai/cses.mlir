#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<vector<int>> p(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        char buf[1005];
        scanf("%s", buf);
        for (int j = 1; j <= n; j++)
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + (buf[j - 1] == '*');
    }
    while (q--) {
        int y1, x1, y2, x2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", p[y2][x2] - p[y1 - 1][x2] - p[y2][x1 - 1] + p[y1 - 1][x1 - 1]);
    }
}
