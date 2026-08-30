#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int tc = 0; tc < t; tc++) {
        int n = inf.readInt(), m = inf.readInt();
        bool feasible = (n >= 2 && m >= 2 && (n * m) % 3 == 0 && !(n == 3 && m % 2 == 1) && !(m == 3 && n % 2 == 1));
        string verdict = ouf.readToken();
        if (verdict == "NO") {
            if (feasible) quitf(_wa, "test %d: said NO but tiling exists", tc + 1);
            continue;
        }
        if (verdict != "YES") quitf(_wa, "test %d: expected YES/NO, got %s", tc + 1, verdict.c_str());
        if (!feasible) quitf(_wa, "test %d: said YES but no tiling exists", tc + 1);
        vector<string> g(n);
        for (int i = 0; i < n; i++) {
            g[i] = ouf.readToken();
            if ((int)g[i].size() != m) quitf(_wa, "test %d: row %d wrong length", tc + 1, i + 1);
        }
        vector<vector<char>> vis(n, vector<char>(m, 0));
        int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (!vis[i][j]) {
            // flood fill same letter
            vector<pair<int,int>> comp;
            vector<pair<int,int>> st = {{i, j}}; vis[i][j] = 1;
            while (!st.empty()) {
                auto [r, c] = st.back(); st.pop_back(); comp.push_back({r, c});
                for (int d = 0; d < 4; d++) { int nr = r + dr[d], nc = c + dc[d]; if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && g[nr][nc] == g[i][j]) { vis[nr][nc] = 1; st.push_back({nr, nc}); } }
            }
            if ((int)comp.size() != 3) quitf(_wa, "test %d: a region of letter %c has size %d, not 3", tc + 1, g[i][j], (int)comp.size());
            int mnr = n, mxr = -1, mnc = m, mxc = -1;
            for (auto [r, c] : comp) { mnr = min(mnr, r); mxr = max(mxr, r); mnc = min(mnc, c); mxc = max(mxc, c); }
            if (mxr - mnr != 1 || mxc - mnc != 1) quitf(_wa, "test %d: region not an L-tromino (not in a 2x2)", tc + 1);
        }
    }
    quitf(_ok, "all tilings valid");
}
