#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) a[i] = inf.readInt();
    for (int i = 1; i <= n; i++) b[i] = inf.readInt();
    string jt = ans.readToken();
    bool juryImp = (jt == "IMPOSSIBLE");
    string pt = ouf.readToken();
    if (pt == "IMPOSSIBLE") {
        if (juryImp) quitf(_ok, "IMPOSSIBLE confirmed");
        quitf(_wa, "said IMPOSSIBLE but a solution exists");
    }
    if (juryImp) quitf(_wa, "gave a permutation but it is IMPOSSIBLE");
    vector<int> c(n + 1);
    vector<char> seen(n + 1, 0);
    c[1] = atoi(pt.c_str());
    for (int i = 2; i <= n; i++) c[i] = ouf.readInt(1, n, "c_i");
    for (int i = 1; i <= n; i++) {
        if (c[i] < 1 || c[i] > n || seen[c[i]]) quitf(_wa, "not a permutation at %d", i);
        seen[c[i]] = 1;
        if (c[i] == a[i] || c[i] == b[i]) quitf(_wa, "c[%d]=%d conflicts with a or b", i, c[i]);
    }
    quitf(_ok, "valid third permutation");
}
