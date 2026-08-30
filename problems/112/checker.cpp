#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    multiset<pair<int, int>> es;
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); es.insert({a, b}); }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    vector<int> path;
    while (!ouf.seekEof()) path.push_back(ouf.readInt(1, n));
    if ((int)path.size() != m + 1) quitf(_wa, "path length %d != %d", (int)path.size(), m + 1);
    if (path.front() != 1) quitf(_wa, "path must start at level 1");
    if (path.back() != n) quitf(_wa, "path must end at level n");
    multiset<pair<int, int>> used = es;
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        auto it = used.find({path[i], path[i + 1]});
        if (it == used.end()) quitf(_wa, "teleporter %d->%d missing or reused", path[i], path[i + 1]);
        used.erase(it);
    }
    quitf(_ok, "valid teleporters path");
}
