#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Monsters: a path that escapes to the boundary, never caught.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<string> g(n);
    for (int i = 0; i < n; i++) g[i] = inf.readWord();
    int sx = 0, sy = 0;
    const int INF = 1e9;
    vector<vector<int>> md(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'M') { md[i][j] = 0; q.push({i, j}); }
            if (g[i][j] == 'A') { sx = i; sy = j; }
        }
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#' || md[nx][ny] != INF) continue;
            md[nx][ny] = md[x][y] + 1; q.push({nx, ny});
        }
    }
    string jw = ans.readWord(), pw = ouf.readWord();
    if (jw == "NO") {
        if (pw != "NO") quitf(_wa, "expected NO, found %s", pw.c_str());
        quitf(_ok, "NO");
    }
    if (pw != "YES") quitf(_wa, "expected YES, found %s", pw.c_str());
    long long plen = ouf.readLong();
    if (plen > (long long)n * m) quitf(_wa, "path too long");
    auto edge = [&](int x, int y) { return x == 0 || x == n - 1 || y == 0 || y == m - 1; };
    int x = sx, y = sy;
    string path = plen > 0 ? ouf.readWord() : "";
    if ((long long)path.size() != plen) quitf(_wa, "path length mismatch");
    int t = 0;
    for (char ch : path) {
        if (ch == 'U') x--; else if (ch == 'D') x++; else if (ch == 'L') y--; else if (ch == 'R') y++;
        else quitf(_wa, "bad move char %c", ch);
        t++;
        if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#') quitf(_wa, "step into wall/outside at (%d,%d)", x, y);
        if (t >= md[x][y]) quitf(_wa, "caught at (%d,%d): t=%d, monster md=%d", x, y, t, md[x][y]);
    }
    if (!edge(x, y)) quitf(_wa, "path does not end on the boundary");
    quitf(_ok, "escaped in %lld steps", plen);
}
