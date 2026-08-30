#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    string s = ouf.readWord();
    long long need = (1LL << n) + n - 1;
    if ((long long)s.size() != need) quitf(_wa, "length %d != minimal %lld", (int)s.size(), need);
    for (char c : s) if (c != '0' && c != '1') quitf(_wa, "non-binary character");
    int total = 1 << n;
    vector<char> seen(total, 0);
    int cnt = 0;
    for (int i = 0; i + n <= (int)s.size(); i++) {
        int v = 0;
        for (int j = 0; j < n; j++) v = (v << 1) | (s[i + j] - '0');
        if (!seen[v]) { seen[v] = 1; cnt++; }
    }
    if (cnt != total) quitf(_wa, "only %d of %d substrings present", cnt, total);
    quitf(_ok, "valid De Bruijn sequence");
}
