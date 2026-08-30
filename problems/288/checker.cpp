#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int tc = 0; tc < t; tc++) {
        long long n = inf.readLong(), k = inf.readLong();
        bool feasible = (k * k >= n);
        string first = ouf.readToken();
        if (first == "IMPOSSIBLE") {
            if (feasible) quitf(_wa, "test %d: said IMPOSSIBLE but k^2>=n", tc + 1);
            continue;
        }
        if (!feasible) quitf(_wa, "test %d: gave a permutation but none exists", tc + 1);
        vector<int> p(n);
        vector<char> seen(n + 1, 0);
        p[0] = atoi(first.c_str());
        for (int i = 1; i < n; i++) p[i] = ouf.readInt(1, (int)n, "p_i");
        for (int i = 0; i < n; i++) {
            if (p[i] < 1 || p[i] > n || seen[p[i]]) quitf(_wa, "test %d: not a permutation", tc + 1);
            seen[p[i]] = 1;
        }
        // longest monotone subsequence (n <= 100) via O(n^2) LIS and LDS
        vector<int> up(n, 1), dn(n, 1); int best = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (p[j] < p[i]) up[i] = max(up[i], up[j] + 1);
                if (p[j] > p[i]) dn[i] = max(dn[i], dn[j] + 1);
            }
            best = max({best, up[i], dn[i]});
        }
        if (best != k) quitf(_wa, "test %d: longest monotone %d != %lld", tc + 1, best, k);
    }
    quitf(_ok, "all tests valid");
}
