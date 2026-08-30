#include "testlib.h"
using namespace std;

// SPJ for 046 Room Allocation: 校验房间数最优、分配合法（同房间区间不重叠）
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) { a[i] = inf.readLong(); b[i] = inf.readLong(); }
    long long kj = ans.readLong();
    long long kp = ouf.readLong();
    if (kp != kj) quitf(_wa, "room count: expected %lld, got %lld", kj, kp);
    vector<int> room(n);
    for (int i = 0; i < n; i++) {
        room[i] = ouf.readInt();
        if (room[i] < 1 || room[i] > kp) quitf(_wa, "room %d out of [1,%lld]", room[i], kp);
    }
    vector<vector<int>> g(kp + 1);
    for (int i = 0; i < n; i++) g[room[i]].push_back(i);
    for (int r = 1; r <= kp; r++) {
        auto &v = g[r];
        sort(v.begin(), v.end(), [&](int x, int y) { return a[x] < a[y]; });
        for (size_t i = 1; i < v.size(); i++)
            if (!(b[v[i - 1]] < a[v[i]]))
                quitf(_wa, "room %d: customers %d and %d overlap", r, v[i - 1] + 1, v[i] + 1);
    }
    quitf(_ok, "k=%lld valid", kp);
}
