#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<array<int, 4>> cl(n);  // a, x, b, y with sign 0='+',1='-'
    for (int i = 0; i < n; i++) {
        string s1 = inf.readWord(); int x1 = inf.readInt();
        string s2 = inf.readWord(); int x2 = inf.readInt();
        cl[i] = {s1 == "+" ? 0 : 1, x1, s2 == "+" ? 0 : 1, x2};
    }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    vector<int> val(m + 1);  // 0 = included (+), 1 = excluded (-)
    for (int i = 1; i <= m; i++) {
        string s = ouf.readWord();
        if (s != "+" && s != "-") quitf(_wa, "bad symbol %s", s.c_str());
        val[i] = (s == "+") ? 0 : 1;
    }
    for (int i = 0; i < n; i++) {
        auto [a, x, b, y] = cl[i];
        if (!((val[x] == a) || (val[y] == b))) quitf(_wa, "wish %d not satisfied", i + 1);
    }
    quitf(_ok, "all %d family wishes satisfied", n);
}
