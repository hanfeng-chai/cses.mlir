#include <bits/stdc++.h>
using namespace std;
int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2}, dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int board[8][8];
bool inb(int r, int c) { return r >= 0 && r < 8 && c >= 0 && c < 8; }
int onward(int r, int c) {
    int cnt = 0;
    for (int e = 0; e < 8; e++) {
        int ar = r + dr[e], ac = c + dc[e];
        if (inb(ar, ac) && board[ar][ac] == 0) cnt++;
    }
    return cnt;
}
bool dfs(int r, int c, int step) {
    board[r][c] = step;
    if (step == 64) return true;
    // Warnsdorff ordering: try moves with fewest onward options first
    vector<array<int, 3>> mv;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inb(nr, nc) && board[nr][nc] == 0) mv.push_back({onward(nr, nc), nr, nc});
    }
    sort(mv.begin(), mv.end());
    for (auto &[cnt, nr, nc] : mv)
        if (dfs(nr, nc, step + 1)) return true;
    board[r][c] = 0;
    return false;
}
int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    memset(board, 0, sizeof(board));
    dfs(y - 1, x - 1, 1);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) printf("%d%c", board[i][j], " \n"[j == 7]);
}
