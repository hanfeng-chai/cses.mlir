#include "testlib.h"
using namespace std;

// 390 Reversal Sorting 是多解题：只要给出的反转序列（不超过 n 次）能把数组排好序，
// 具体方案不必和裁判一致。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = inf.readInt();

    int k = ouf.readInt(0, n, "number of reversals");
    for (int t = 0; t < k; t++) {
        int l = ouf.readInt(1, n, "l");
        int r = ouf.readInt(l, n, "r");
        reverse(a.begin() + l, a.begin() + r + 1);
    }
    for (int i = 1; i <= n; i++)
        if (a[i] != i) quitf(_wa, "array is not sorted after applying the reversals (a[%d]=%d)", i, a[i]);

    quitf(_ok, "sorted using %d <= %d reversals", k, n);
}
