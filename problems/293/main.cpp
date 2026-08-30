#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> id_;
int cnt;
// seed 5x9: each tromino's 3 (dr,dc)
int seed[15][3][2] = {
    {{0,0},{1,0},{1,1}}, {{0,1},{0,2},{1,2}}, {{0,3},{0,4},{1,3}}, {{0,5},{0,6},{1,5}},
    {{0,7},{0,8},{1,8}}, {{1,4},{2,4},{2,5}}, {{1,6},{1,7},{2,6}}, {{2,0},{2,1},{3,1}},
    {{2,2},{2,3},{3,3}}, {{2,7},{2,8},{3,8}}, {{3,0},{4,0},{4,1}}, {{3,2},{4,2},{4,3}},
    {{3,4},{4,4},{4,5}}, {{3,5},{3,6},{4,6}}, {{3,7},{4,7},{4,8}}
};
void put(int r0, int c0, vector<pair<int,int>> cells) { for (auto [r, c] : cells) id_[r0 + r][c0 + c] = cnt; cnt++; }
void block2x3(int r, int c) { put(r, c, {{0,0},{1,0},{1,1}}); put(r, c, {{0,1},{0,2},{1,2}}); }
void block3x2(int r, int c) { put(r, c, {{0,0},{0,1},{1,1}}); put(r, c, {{1,0},{2,0},{2,1}}); }
void seed5x9(int r0, int c0) { for (int t = 0; t < 15; t++) { for (int k = 0; k < 3; k++) id_[r0 + seed[t][k][0]][c0 + seed[t][k][1]] = cnt; cnt++; } }
void seed9x5(int r0, int c0) { for (int t = 0; t < 15; t++) { for (int k = 0; k < 3; k++) id_[r0 + seed[t][k][1]][c0 + seed[t][k][0]] = cnt; cnt++; } }
void fill5x6(int r0, int c0) { block2x3(r0, c0); block2x3(r0, c0 + 3); block3x2(r0 + 2, c0); block3x2(r0 + 2, c0 + 2); block3x2(r0 + 2, c0 + 4); }
void fill6x5(int r0, int c0) { block3x2(r0, c0); block3x2(r0 + 3, c0); block2x3(r0, c0 + 2); block2x3(r0 + 2, c0 + 2); block2x3(r0 + 4, c0 + 2); }
void fill5byM(int r0, int c0, int M) {  // 5 rows, M cols, 3|M, M>=6
    int c = c0;
    if (M % 6 == 3) { seed5x9(r0, c); c += 9; M -= 9; }
    for (; M > 0; M -= 6, c += 6) fill5x6(r0, c);
}
void fillNby5(int r0, int c0, int N) {  // N rows, 5 cols, 3|N, N>=6
    int r = r0;
    if (N % 6 == 3) { seed9x5(r, c0); r += 9; N -= 9; }
    for (; N > 0; N -= 6, r += 6) fill6x5(r, c0);
}
void fill(int r0, int c0, int N, int M) {
    if (N == 2) { for (int c = 0; c < M; c += 3) block2x3(r0, c0 + c); return; }
    if (M == 2) { for (int r = 0; r < N; r += 3) block3x2(r0 + r, c0); return; }
    if (N == 3) { for (int c = 0; c < M; c += 2) block3x2(r0, c0 + c); return; }
    if (M == 3) { for (int r = 0; r < N; r += 2) block2x3(r0 + r, c0); return; }
    if (N % 2 == 0 && M % 3 == 0) { for (int r = 0; r < N; r += 2) for (int c = 0; c < M; c += 3) block2x3(r0 + r, c0 + c); return; }
    if (M % 2 == 0 && N % 3 == 0) { for (int r = 0; r < N; r += 3) for (int c = 0; c < M; c += 2) block3x2(r0 + r, c0 + c); return; }
    if (N % 2 == 0) { for (int r = 0; r < N; r += 3) block3x2(r0 + r, c0); fill(r0, c0 + 2, N, M - 2); return; }  // n even, m odd, 3|n
    if (M % 2 == 0) { for (int c = 0; c < M; c += 3) block2x3(r0, c0 + c); fill(r0 + 2, c0, N - 2, M); return; }  // m even, n odd, 3|m
    // both odd
    if (M % 3 == 0) { fill5byM(r0, c0, M); if (N > 5) fill(r0 + 5, c0, N - 5, M); }
    else { fillNby5(r0, c0, N); if (M > 5) fill(r0, c0 + 5, N, M - 5); }
}
int main() {
    int t; scanf("%d", &t);
    string out;
    while (t--) {
        scanf("%d %d", &n, &m);
        bool ok = (n >= 2 && m >= 2 && (n * m) % 3 == 0 && !(n == 3 && m % 2 == 1) && !(m == 3 && n % 2 == 1));
        if (!ok) { out += "NO\n"; continue; }
        id_.assign(n, vector<int>(m, -1));
        cnt = 0;
        fill(0, 0, n, m);
        // greedy color trominoes so adjacent ones differ
        vector<vector<int>> adj(cnt);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            if (i + 1 < n && id_[i][j] != id_[i + 1][j]) { adj[id_[i][j]].push_back(id_[i + 1][j]); adj[id_[i + 1][j]].push_back(id_[i][j]); }
            if (j + 1 < m && id_[i][j] != id_[i][j + 1]) { adj[id_[i][j]].push_back(id_[i][j + 1]); adj[id_[i][j + 1]].push_back(id_[i][j]); }
        }
        vector<int> col(cnt, -1);
        for (int v = 0; v < cnt; v++) {
            bool usedc[26] = {false};
            for (int u : adj[v]) if (col[u] >= 0) usedc[col[u]] = true;
            int c = 0; while (usedc[c]) c++;
            col[v] = c;
        }
        out += "YES\n";
        for (int i = 0; i < n; i++) { for (int j = 0; j < m; j++) out += (char)('A' + col[id_[i][j]]); out += '\n'; }
    }
    cout << out;
}
