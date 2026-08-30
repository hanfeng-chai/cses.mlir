#include "testlib.h"
using namespace std;

// 378 Swap Round Sorting 是多解题：只要求出最少轮数、且每轮内的交换两两不相交、
// 交换后确实排好序即可，具体怎么配对不必和裁判一致。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = inf.readInt();

    int jk = ans.readInt();

    int pk = ouf.readInt(0, n, "k");
    if (pk != jk) quitf(_wa, "used %d rounds, but optimal is %d", pk, jk);

    vector<char> usedThisRound(n + 1, 0);
    for (int r = 0; r < pk; r++) {
        int cnt = ouf.readInt(0, n / 2, "cnt");
        fill(usedThisRound.begin(), usedThisRound.end(), 0);
        for (int i = 0; i < cnt; i++) {
            int a = ouf.readInt(1, n, "a");
            int b = ouf.readInt(1, n, "b");
            if (a == b) quitf(_wa, "round %d: swap of a position with itself", r + 1);
            if (usedThisRound[a] || usedThisRound[b])
                quitf(_wa, "round %d: position used in more than one swap", r + 1);
            usedThisRound[a] = usedThisRound[b] = 1;
            swap(p[a], p[b]);
        }
    }

    for (int i = 1; i <= n; i++)
        if (p[i] != i) quitf(_wa, "array is not sorted after all rounds");

    quitf(_ok, "sorted in %d rounds", pk);
}
