#include "testlib.h"
using namespace std;

// 008 Two Sets 是多解题：把 1..n 划分为两个和相等的集合。
// 当 1+2+...+n = n(n+1)/2 为奇数时无解，应输出 "NO"。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    long long n = inf.readLong();
    long long S = n * (n + 1) / 2;
    bool possible = (S % 2 == 0);

    string v = upperCase(ouf.readWord());
    if (v == "NO") {
        if (possible) quitf(_wa, "answered NO but a division exists (n=%lld)", n);
        quitf(_ok, "correctly NO");
    }
    if (v != "YES") quitf(_wa, "expected YES or NO, got '%s'", v.c_str());
    if (!possible) quitf(_wa, "answered YES but no division exists (n=%lld)", n);

    vector<char> seen(n + 1, 0);
    long long c1 = ouf.readLong(0, n, "c1"), sum1 = 0;
    for (long long i = 0; i < c1; i++) {
        long long x = ouf.readLong(1, n, "x");
        if (seen[x]) quitf(_wa, "value %lld repeated", x);
        seen[x] = 1; sum1 += x;
    }
    long long c2 = ouf.readLong(0, n, "c2"), sum2 = 0;
    for (long long i = 0; i < c2; i++) {
        long long x = ouf.readLong(1, n, "x");
        if (seen[x]) quitf(_wa, "value %lld repeated", x);
        seen[x] = 1; sum2 += x;
    }
    if (c1 + c2 != n) quitf(_wa, "counts %lld+%lld != %lld", c1, c2, n);
    for (long long i = 1; i <= n; i++)
        if (!seen[i]) quitf(_wa, "value %lld missing", i);
    if (sum1 != sum2) quitf(_wa, "sums differ: %lld vs %lld", sum1, sum2);
    quitf(_ok, "valid division, each sum=%lld", sum1);
}
