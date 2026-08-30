#include "testlib.h"
using namespace std;

// SPJ for 031 Sum of Two Values: 任意一对合法下标都接受
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    long long x = inf.readLong();
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = inf.readLong();

    string j = ans.readWord();
    string p = ouf.readWord();
    bool jImp = (j == "IMPOSSIBLE"), pImp = (p == "IMPOSSIBLE");
    if (jImp) {
        if (pImp) quitf(_ok, "both IMPOSSIBLE");
        quitf(_wa, "jury IMPOSSIBLE but participant printed a pair");
    }
    if (pImp) quitf(_wa, "participant IMPOSSIBLE but a solution exists");
    long long i = atoll(p.c_str());
    long long jj = ouf.readLong();
    if (i < 1 || i > n || jj < 1 || jj > n) quitf(_wa, "index out of range: %lld %lld", i, jj);
    if (i == jj) quitf(_wa, "indices must be distinct");
    if (a[i] + a[jj] != x) quitf(_wa, "a[%lld]+a[%lld]=%lld != %lld", i, jj, a[i] + a[jj], x);
    quitf(_ok, "valid pair");
}
