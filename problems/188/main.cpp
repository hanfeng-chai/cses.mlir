#include <bits/stdc++.h>
using namespace std;
int main() {
    int k; scanf("%d", &k);
    auto id = [](int r, int c) { return r * 8 + c; };
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    int deg[64]; vector<int> nb[64];
    for (int r = 0; r < 8; r++) for (int c = 0; c < 8; c++) {
        int d = 0;
        for (int t = 0; t < 4; t++) { int nr = r + dr[t], nc = c + dc[t]; if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) { nb[id(r, c)].push_back(id(nr, nc)); d++; } }
        deg[id(r, c)] = d;
    }
    static double P[64][64];  // P[p][s] = prob robot starting at p is on s after k steps
    for (int p = 0; p < 64; p++) {
        vector<double> dp(64, 0); dp[p] = 1;
        for (int step = 0; step < k; step++) {
            vector<double> nd(64, 0);
            for (int cell = 0; cell < 64; cell++) if (dp[cell] > 0) { double sh = dp[cell] / deg[cell]; for (int to : nb[cell]) nd[to] += sh; }
            dp = nd;
        }
        for (int s = 0; s < 64; s++) P[p][s] = dp[s];
    }
    double ans = 0;
    for (int s = 0; s < 64; s++) { double empty = 1; for (int p = 0; p < 64; p++) empty *= (1 - P[p][s]); ans += empty; }
    printf("%.6f\n", ans);
}
