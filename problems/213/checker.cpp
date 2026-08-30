#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// suffix array O(n log n)
vector<int> suffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) { sa[i] = i; rnk[i] = s[i]; }
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
            int ra = a + k < n ? rnk[a + k] : -1, rb = b + k < n ? rnk[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> given(n);
    for (int i = 0; i < n; i++) given[i] = inf.readInt() - 1;  // 0-indexed
    string jt = ans.readToken();
    bool juryNo = (jt == "-1");
    string o = ouf.readToken();
    if (o == "-1") {
        if (juryNo) quitf(_ok, "no string (confirmed)");
        quitf(_wa, "participant says -1 but a string exists");
    }
    if ((int)o.size() != n) quitf(_wa, "length %d != %d", (int)o.size(), n);
    for (char c : o) if (c < 'a' || c > 'z') quitf(_wa, "non-lowercase character");
    vector<int> sa = suffixArray(o);
    for (int i = 0; i < n; i++) if (sa[i] != given[i]) quitf(_wa, "suffix array mismatch at position %d", i + 1);
    quitf(_ok, "valid string of length %d", n);
}
