#include "testlib.h"
using namespace std;

// 005 Permutations 是多解题：构造任意满足"相邻元素差不为 1"的 1..n 排列。
// 当 n==2 或 n==3 时无解，应输出 "NO SOLUTION"；n==1 时输出单个 1。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    long long n = inf.readLong();
    bool possible = (n == 1 || n >= 4);

    if (!possible) {
        string a = ouf.readWord(), b = ouf.readWord();
        if (upperCase(a) == "NO" && upperCase(b) == "SOLUTION")
            quitf(_ok, "NO SOLUTION");
        quitf(_wa, "expected 'NO SOLUTION', got '%s %s'", a.c_str(), b.c_str());
    }

    vector<long long> p(n);
    for (long long i = 0; i < n; i++) p[i] = ouf.readLong(1, n, "p_i");

    vector<char> seen(n + 1, 0);
    for (long long x : p) {
        if (seen[x]) quitf(_wa, "duplicate value %lld", x);
        seen[x] = 1;
    }
    for (long long i = 1; i < n; i++) {
        long long d = p[i] - p[i - 1];
        if (d == 1 || d == -1)
            quitf(_wa, "adjacent %lld and %lld differ by 1", p[i - 1], p[i]);
    }
    quitf(_ok, "valid beautiful permutation (n=%lld)", n);
}
