#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int M = 2 * n + 1;
    vector<char> comp(M + 1, 0);
    for (int i = 2; (long long)i * i <= M; i++) if (!comp[i]) for (int j = i * i; j <= M; j += i) comp[j] = 1;
    auto isP = [&](int x) { return x >= 2 && !comp[x]; };
    vector<int> a(n), b(n);
    vector<char> sa(n + 1, 0), sb(n + 1, 0);
    for (int i = 0; i < n; i++) { a[i] = ouf.readInt(1, n, "a_i"); if (sa[a[i]]) quitf(_wa, "a not a permutation"); sa[a[i]] = 1; }
    for (int i = 0; i < n; i++) { b[i] = ouf.readInt(1, n, "b_i"); if (sb[b[i]]) quitf(_wa, "b not a permutation"); sb[b[i]] = 1; }
    for (int i = 0; i < n; i++) if (!isP(a[i] + b[i])) quitf(_wa, "a[%d]+b[%d]=%d not prime", i + 1, i + 1, a[i] + b[i]);
    quitf(_ok, "valid");
}
