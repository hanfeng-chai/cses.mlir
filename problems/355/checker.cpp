#include "testlib.h"
using namespace std;

// 355 Subarray Sum Constraints 是多解题：只要满足全部区间和约束即可，构造方式不唯一。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    vector<array<long long,3>> cons(m);
    for (auto &c : cons) {
        c[0] = inf.readLong();
        c[1] = inf.readLong();
        c[2] = inf.readLong();
    }

    string jAns = upperCase(ans.readToken());
    string pAns = upperCase(ouf.readToken());
    if (pAns != "YES" && pAns != "NO")
        quitf(_pe, "expected YES or NO, got '%s'", pAns.c_str());

    bool jYes = (jAns == "YES");
    bool pYes = (pAns == "YES");
    if (jYes != pYes)
        quitf(_wa, "jury says %s but participant says %s", jAns.c_str(), pAns.c_str());

    if (!pYes) quitf(_ok, "correctly NO");

    vector<long long> x(n + 1), P(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        x[i] = ouf.readLong(-1000000000000000LL, 1000000000000000LL, "x_i");
        P[i] = P[i - 1] + x[i];
    }

    for (auto &c : cons) {
        int l = (int)c[0], r = (int)c[1];
        long long s = c[2];
        long long sum = P[r] - P[l - 1];
        if (sum != s)
            quitf(_wa, "constraint (%d,%d,%lld) violated: got sum %lld", l, r, s, sum);
    }

    quitf(_ok, "valid array satisfying all %d constraints", m);
}
