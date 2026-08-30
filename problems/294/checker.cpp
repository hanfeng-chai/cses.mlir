#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int tests = inf.readInt();
    const string directions = "UDLR";
    const int dy[4] = {-1, 1, 0, 0};
    const int dx[4] = {0, 0, -1, 1};

    for (int tc = 1; tc <= tests; ++tc) {
        int n = inf.readInt();
        int m = inf.readInt();
        int sy = inf.readInt() - 1;
        int sx = inf.readInt() - 1;
        int ty = inf.readInt() - 1;
        int tx = inf.readInt() - 1;

        string juryVerdict = upperCase(ans.readWord());
        if (juryVerdict == "YES") ans.readWord();
        string participantVerdict = upperCase(ouf.readWord());
        if (participantVerdict != "YES" && participantVerdict != "NO")
            quitf(_pe, "test %d: expected YES or NO, got '%s'", tc, participantVerdict.c_str());
        if (participantVerdict != juryVerdict)
            quitf(_wa, "test %d: jury says %s, participant says %s", tc,
                  juryVerdict.c_str(), participantVerdict.c_str());
        if (participantVerdict == "NO") continue;

        string path = ouf.readWord();
        if ((int)path.size() != n * m - 1)
            quitf(_wa, "test %d: path length %d, expected %d", tc,
                  (int)path.size(), n * m - 1);
        vector<vector<bool>> seen(n, vector<bool>(m, false));
        int y = sy, x = sx;
        seen[y][x] = true;
        for (int step = 0; step < (int)path.size(); ++step) {
            size_t d = directions.find(path[step]);
            if (d == string::npos)
                quitf(_pe, "test %d: invalid direction '%c' at step %d", tc, path[step], step + 1);
            y += dy[d];
            x += dx[d];
            if (y < 0 || y >= n || x < 0 || x >= m)
                quitf(_wa, "test %d: path leaves the grid at step %d", tc, step + 1);
            if (seen[y][x])
                quitf(_wa, "test %d: cell (%d,%d) is visited twice", tc, y + 1, x + 1);
            seen[y][x] = true;
        }
        if (y != ty || x != tx)
            quitf(_wa, "test %d: path ends at (%d,%d), expected (%d,%d)",
                  tc, y + 1, x + 1, ty + 1, tx + 1);
    }
    quitf(_ok, "all paths are valid");
}
