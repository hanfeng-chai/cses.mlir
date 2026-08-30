#include "testlib.h"
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int i = 0; i < t; i++) {
        long long n = inf.readLong();
        long long a = ouf.readLong(), b = ouf.readLong(), c = ouf.readLong(), d = ouf.readLong();
        if (a < 0 || b < 0 || c < 0 || d < 0) quitf(_wa, "test %d: negative value", i + 1);
        if (a * a + b * b + c * c + d * d != n)
            quitf(_wa, "test %d: %lld^2+%lld^2+%lld^2+%lld^2 != %lld", i + 1, a, b, c, d, n);
    }
    quitf(_ok, "correct (%d tests)", t);
}
