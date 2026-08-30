#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &r : g) cin >> r;
    int sx = 0, sy = 0, ex = 0, ey = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'A') { sx = i; sy = j; }
            if (g[i][j] == 'B') { ex = i; ey = j; }
        }
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<char>> from(n, vector<char>(m, 0));
    queue<pair<int, int>> q;
    q.push({sx, sy}); dist[sx][sy] = 0;
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    char dc[] = {'D', 'U', 'R', 'L'};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || dist[nx][ny] != -1 || g[nx][ny] == '#') continue;
            dist[nx][ny] = dist[x][y] + 1; from[nx][ny] = dc[d]; q.push({nx, ny});
        }
    }
    if (dist[ex][ey] == -1) { cout << "NO\n"; return 0; }
    string path;
    int x = ex, y = ey;
    while (!(x == sx && y == sy)) {
        char c = from[x][y]; path += c;
        if (c == 'D') x--; else if (c == 'U') x++; else if (c == 'R') y--; else y++;
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << dist[ex][ey] << "\n" << path << "\n";
}
