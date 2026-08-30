#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<string> g(n);
    for (auto &r : g) { char buf[1005]; scanf("%s", buf); r = buf; }
    vector<vector<char>> vis(n, vector<char>(m, 0));
    int rooms = 0, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '#' || vis[i][j]) continue;
            rooms++;
            queue<pair<int, int>> q;
            q.push({i, j}); vis[i][j] = 1;
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] || g[nx][ny] == '#') continue;
                    vis[nx][ny] = 1; q.push({nx, ny});
                }
            }
        }
    printf("%d\n", rooms);
}
