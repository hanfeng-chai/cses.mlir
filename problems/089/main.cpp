#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &r : g) cin >> r;
    const int INF = 1e9;
    vector<vector<int>> md(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    int sx = 0, sy = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'M') { md[i][j] = 0; q.push({i, j}); }
            if (g[i][j] == 'A') { sx = i; sy = j; }
        }
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    char dc[] = {'D', 'U', 'R', 'L'};
    while (!q.empty()) {  // multi-source BFS: monster arrival times
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#' || md[nx][ny] != INF) continue;
            md[nx][ny] = md[x][y] + 1; q.push({nx, ny});
        }
    }
    vector<vector<int>> yd(n, vector<int>(m, -1));
    vector<vector<char>> from(n, vector<char>(m, 0));
    auto boundary = [&](int x, int y) { return x == 0 || x == n - 1 || y == 0 || y == m - 1; };
    int ex = -1, ey = -1;
    yd[sx][sy] = 0;
    if (boundary(sx, sy)) { ex = sx; ey = sy; }
    q.push({sx, sy});
    while (!q.empty() && ex == -1) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#' || yd[nx][ny] != -1) continue;
            if (yd[x][y] + 1 >= md[nx][ny]) continue;  // a monster reaches it no later than you
            yd[nx][ny] = yd[x][y] + 1; from[nx][ny] = dc[d]; q.push({nx, ny});
            if (boundary(nx, ny)) { ex = nx; ey = ny; break; }
        }
    }
    if (ex == -1) { cout << "NO\n"; return 0; }
    string path;
    int x = ex, y = ey;
    while (!(x == sx && y == sy)) {
        char c = from[x][y]; path += c;
        if (c == 'D') x--; else if (c == 'U') x++; else if (c == 'R') y--; else y++;
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}
