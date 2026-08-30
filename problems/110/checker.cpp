#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    multiset<pair<int, int>> es;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(), b = inf.readInt();
        if (a > b) swap(a, b);
        es.insert({a, b});
    }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    vector<int> route;
    while (!ouf.seekEof()) route.push_back(ouf.readInt(1, n));
    if ((int)route.size() != m + 1) quitf(_wa, "route length %d != %d", (int)route.size(), m + 1);
    if (route.front() != 1 || route.back() != 1) quitf(_wa, "route must start and end at crossing 1");
    multiset<pair<int, int>> used = es;
    for (int i = 0; i + 1 < (int)route.size(); i++) {
        int a = route[i], b = route[i + 1];
        if (a > b) swap(a, b);
        auto it = used.find({a, b});
        if (it == used.end()) quitf(_wa, "street %d-%d missing or reused", route[i], route[i + 1]);
        used.erase(it);
    }
    quitf(_ok, "valid mail route through all streets");
}
