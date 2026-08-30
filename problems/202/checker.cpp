#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;
int manacherMax(const string &s) {
    string t = "^";
    for (char c : s) { t += '#'; t += c; }
    t += "#$";
    int m = t.size(); vector<int> p(m, 0); int c = 0, r = 0, best = 0;
    for (int i = 1; i < m - 1; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
        best = max(best, p[i]);
    }
    return best;
}
bool occurs(const string &s, const string &o) {
    int n = s.size(), m = o.size();
    if (m == 0) return true;
    if (m > n) return false;
    const u64 M1 = 1000000007ULL, M2 = 998244353ULL, B1 = 131, B2 = 137;
    u64 h1 = 0, h2 = 0, p1 = 1, p2 = 1;
    for (int i = 0; i < m; i++) { h1 = (h1 * B1 + o[i]) % M1; h2 = (h2 * B2 + o[i]) % M2; if (i) { p1 = p1 * B1 % M1; p2 = p2 * B2 % M2; } }
    u64 w1 = 0, w2 = 0;
    for (int i = 0; i < n; i++) {
        w1 = (w1 * B1 + s[i]) % M1; w2 = (w2 * B2 + s[i]) % M2;
        if (i >= m) { w1 = (w1 + M1 * M1 - p1 * B1 % M1 * s[i - m]) % M1; w2 = (w2 + M2 * M2 - p2 * B2 % M2 * s[i - m]) % M2; }
        if (i >= m - 1 && w1 == h1 && w2 == h2) return true;
    }
    return false;
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    string s = inf.readString();
    string o = ouf.readString();
    int maxlen = manacherMax(s);
    if ((int)o.size() != maxlen) quitf(_wa, "length %d != max palindrome %d", (int)o.size(), maxlen);
    string r = o; reverse(r.begin(), r.end());
    if (r != o) quitf(_wa, "answer is not a palindrome");
    if (!occurs(s, o)) quitf(_wa, "answer is not a substring");
    quitf(_ok, "longest palindrome length %d", maxlen);
}
