#include <bits/stdc++.h>
using namespace std;

namespace {
constexpr int DY[4] = {1, 0, -1, 0};
constexpr int DX[4] = {0, 1, 0, -1};
constexpr char STEP[4] = {'D', 'R', 'U', 'L'};
int dir_id[256];

bool feasible(int n, int m, int sy, int sx, int ty, int tx) {
    if (n == 1 && m == 1) return true;
    if (sy == ty && sx == tx) return false;
    if (n > m) {
        swap(n, m);
        swap(sy, sx);
        swap(ty, tx);
    }
    if (sx > tx) {
        swap(sx, tx);
        swap(sy, ty);
    }

    if (n == 1) return sx == 0 && tx == m - 1;
    if (n == 2) {
        if (sx == tx) return sx == 0 || sx == m - 1;
        return ((sy + sx) & 1) != ((ty + tx) & 1);
    }
    if (n * m & 1) {
        return ((sy + sx) & 1) == 0 && ((ty + tx) & 1) == 0;
    }
    if (n == 3) {
        if (((sy + sx) & 1) == ((ty + tx) & 1)) return false;
        if (((sy + sx) & 1) && (sx < tx - 1 || (sy == 1 && sx < tx))) return false;
        if (((ty + tx) & 1) && (tx < sx - 1 || (ty == 1 && tx < sx))) return false;
        return true;
    }
    return ((sy + sx) & 1) != ((ty + tx) & 1);
}

struct TinyBoard {
    int n, m, cells, source, target;
    vector<vector<pair<int, char>>> adj;
    vector<char> used;
    string answer, path;

    int id(int y, int x) const { return y * m + x; }

    bool remaining_connected(int current, int used_count) {
        if (used_count == cells) return true;
        int first = -1;
        for (int v = 0; v < cells; ++v) {
            if (!used[v]) {
                first = v;
                break;
            }
        }
        vector<char> seen(cells, false);
        vector<int> queue = {first};
        seen[first] = true;
        for (int head = 0; head < (int)queue.size(); ++head) {
            int u = queue[head];
            for (auto [v, step] : adj[u]) {
                (void)step;
                if (!used[v] && !seen[v]) {
                    seen[v] = true;
                    queue.push_back(v);
                }
            }
        }
        int remaining = 0;
        for (int v = 0; v < cells; ++v) remaining += !used[v];
        if ((int)queue.size() != remaining) return false;
        for (auto [v, step] : adj[current]) {
            (void)step;
            if (!used[v]) return true;
        }
        return false;
    }

    int onward_degree(int v) const {
        int degree = 0;
        for (auto [to, step] : adj[v]) {
            (void)step;
            degree += !used[to];
        }
        return degree;
    }

    bool dfs(int current, int used_count) {
        if (used_count == cells) {
            if (current == target) {
                answer = path;
                return true;
            }
            return false;
        }
        if (current == target || !remaining_connected(current, used_count)) return false;

        vector<tuple<int, int, char>> candidates;
        for (auto [to, step] : adj[current]) {
            if (!used[to]) candidates.push_back({onward_degree(to), to, step});
        }
        sort(candidates.begin(), candidates.end());
        for (auto [degree, to, step] : candidates) {
            (void)degree;
            used[to] = true;
            path.push_back(step);
            if (dfs(to, used_count + 1)) return true;
            path.pop_back();
            used[to] = false;
        }
        return false;
    }

    string solve(int rows, int cols, int sy, int sx, int ty, int tx) {
        n = rows;
        m = cols;
        cells = n * m;
        source = id(sy, sx);
        target = id(ty, tx);
        adj.assign(cells, {});
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < m; ++x) {
                int u = id(y, x);
                for (int d = 0; d < 4; ++d) {
                    int ny = y + DY[d], nx = x + DX[d];
                    if (0 <= ny && ny < n && 0 <= nx && nx < m) {
                        adj[u].push_back({id(ny, nx), STEP[d]});
                    }
                }
            }
        }
        used.assign(cells, false);
        used[source] = true;
        answer.clear();
        path.clear();
        dfs(source, 1);
        return answer;
    }
} tiny;

string construct_path(int n, int m, int sy, int sx, int ty, int tx) {
    if (n > m) {
        string path = construct_path(m, n, m - sx - 1, sy, m - tx - 1, ty);
        for (char &step : path) step = STEP[(dir_id[(unsigned char)step] + 3) % 4];
        return path;
    }
    if (sx > tx) {
        string path = construct_path(n, m, sy, m - sx - 1, ty, m - tx - 1);
        for (char &step : path) {
            if (step == 'L') step = 'R';
            else if (step == 'R') step = 'L';
        }
        return path;
    }
    if (sy > ty) {
        string path = construct_path(n, m, n - sy - 1, sx, n - ty - 1, tx);
        for (char &step : path) {
            if (step == 'U') step = 'D';
            else if (step == 'D') step = 'U';
        }
        return path;
    }

    if (n == 1) return string(m - 1, 'R');

    if (n == 2 && sy == ty && sx + 1 == tx) {
        string path(sx, 'L');
        char vertical = sy == 0 ? 'D' : 'U';
        path.push_back(vertical);
        path += string(m - 1, 'R');
        path.push_back(vertical == 'D' ? 'U' : 'D');
        path += string(m - 1 - tx, 'L');
        return path;
    }

    if (n <= 4 && m <= 5) return tiny.solve(n, m, sy, sx, ty, tx);

    if (sx >= 2 && feasible(n, m - 2, sy, sx - 2, ty, tx - 2)) {
        string core = construct_path(n, m - 2, sy, sx - 2, ty, tx - 2);
        int y = sy, x = sx - 2;
        for (int i = 0; i < (int)core.size(); ++i) {
            int d = dir_id[(unsigned char)core[i]];
            int ny = y + DY[d], nx = x + DX[d];
            if (x == 0 && nx == 0) {
                return core.substr(0, i) + "L" +
                       construct_path(n, 2, y, 1, ny, 1) + "R" +
                       core.substr(i + 1);
            }
            y = ny;
            x = nx;
        }
    }

    if (tx <= m - 3 && feasible(n, m - 2, sy, sx, ty, tx)) {
        string core = construct_path(n, m - 2, sy, sx, ty, tx);
        int y = sy, x = sx;
        for (int i = 0; i < (int)core.size(); ++i) {
            int d = dir_id[(unsigned char)core[i]];
            int ny = y + DY[d], nx = x + DX[d];
            if (x == m - 3 && nx == m - 3) {
                return core.substr(0, i) + "R" +
                       construct_path(n, 2, y, 0, ny, 0) + "L" +
                       core.substr(i + 1);
            }
            y = ny;
            x = nx;
        }
    }

    for (int cut = sy; cut < ty; ++cut) {
        for (int x = 0; x < m; ++x) {
            if (!feasible(cut + 1, m, sy, sx, cut, x)) continue;
            if (!feasible(n - cut - 1, m, 0, x, ty - cut - 1, tx)) continue;
            return construct_path(cut + 1, m, sy, sx, cut, x) + "D" +
                   construct_path(n - cut - 1, m, 0, x, ty - cut - 1, tx);
        }
    }

    for (int cut = sx; cut < tx; ++cut) {
        for (int y = 0; y < n; ++y) {
            if (!feasible(n, cut + 1, sy, sx, y, cut)) continue;
            if (!feasible(n, m - cut - 1, y, 0, ty, tx - cut - 1)) continue;
            return construct_path(n, cut + 1, sy, sx, y, cut) + "R" +
                   construct_path(n, m - cut - 1, y, 0, ty, tx - cut - 1);
        }
    }

    return {};
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    dir_id[(unsigned char)'D'] = 0;
    dir_id[(unsigned char)'R'] = 1;
    dir_id[(unsigned char)'U'] = 2;
    dir_id[(unsigned char)'L'] = 3;

    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, sy, sx, ty, tx;
        cin >> n >> m >> sy >> sx >> ty >> tx;
        --sy; --sx; --ty; --tx;
        if (!feasible(n, m, sy, sx, ty, tx)) {
            cout << "NO\n";
            continue;
        }
        string path = construct_path(n, m, sy, sx, ty, tx);
        if ((int)path.size() != n * m - 1) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n" << path << '\n';
    }
}
