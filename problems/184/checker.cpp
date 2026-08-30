#include "testlib.h"
#include <vector>
using namespace std;
const long long MOD = 1e9 + 7;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<vector<long long>> A(n, vector<long long>(m + 1));
    for (int i = 0; i < n; i++) for (int j = 0; j <= m; j++) A[i][j] = inf.readLong();
    string jtok = ans.readToken();
    bool juryNo = (jtok == "-1");
    string ptok = ouf.readToken();
    if (ptok == "-1") {
        if (juryNo) quitf(_ok, "no solution");
        quitf(_wa, "participant reports no solution but one exists");
    }
    vector<long long> x(m);
    x[0] = atoll(ptok.c_str());
    for (int j = 1; j < m; j++) x[j] = ouf.readLong();
    for (int j = 0; j < m; j++) if (x[j] < 0 || x[j] >= MOD) quitf(_wa, "x[%d]=%lld out of range", j + 1, x[j]);
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = 0; j < m; j++) s = (s + (__int128)A[i][j] * x[j]) % MOD;
        if (s != A[i][m] % MOD) quitf(_wa, "equation %d not satisfied (got %lld, want %lld)", i + 1, s, A[i][m] % MOD);
    }
    quitf(_ok, "valid solution");
}
