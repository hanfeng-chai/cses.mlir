#include "testlib.h"
using namespace std;

// 361 Two Array Average 是多解题：只要求出的前缀长度对应的平均值与裁判最优平均值
// 相差不超过 1e-6 即可，具体前缀长度不必完全一致。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<long long> a(n + 1), b(n + 1), PA(n + 1, 0), PB(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = inf.readLong();
    for (int i = 1; i <= n; i++) b[i] = inf.readLong();
    for (int i = 1; i <= n; i++) { PA[i] = PA[i-1] + a[i]; PB[i] = PB[i-1] + b[i]; }

    int ji = ans.readInt(), jj = ans.readInt();
    double juryAvg = (double)(PA[ji] + PB[jj]) / (ji + jj);

    int pi = ouf.readInt(1, n, "i");
    int pj = ouf.readInt(1, n, "j");
    double pAvg = (double)(PA[pi] + PB[pj]) / (pi + pj);

    double diff = fabs(pAvg - juryAvg);
    double rel = diff / max(1.0, fabs(juryAvg));
    if (diff > 1e-6 && rel > 1e-6)
        quitf(_wa, "average %.9f, but optimal is %.9f", pAvg, juryAvg);

    quitf(_ok, "average %.9f (optimal %.9f)", pAvg, juryAvg);
}
