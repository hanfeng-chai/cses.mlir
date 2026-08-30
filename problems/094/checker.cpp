#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Cycle Finding: a directed cycle of strictly negative total weight.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    map<pair<int, int>, long long> w;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(), b = inf.readInt();
        long long c = inf.readLong();
        auto key = make_pair(a, b);
        auto it = w.find(key);
        if (it == w.end() || c < it->second) w[key] = c;
    }
    string jw = ans.readWord(), pw = ouf.readWord();
    if (jw == "NO") {
        if (pw != "NO") quitf(_wa, "expected NO, found %s", pw.c_str());
        quitf(_ok, "NO");
    }
    if (pw != "YES") quitf(_wa, "expected YES, found %s", pw.c_str());
    vector<int> cyc;
    while (!ouf.seekEof()) cyc.push_back(ouf.readInt(1, n));
    if ((int)cyc.size() < 2) quitf(_wa, "cycle too short");
    if (cyc.front() != cyc.back()) quitf(_wa, "cycle must start and end at the same node");
    long long sum = 0;
    for (int i = 0; i + 1 < (int)cyc.size(); i++) {
        auto it = w.find({cyc[i], cyc[i + 1]});
        if (it == w.end()) quitf(_wa, "no edge %d->%d", cyc[i], cyc[i + 1]);
        sum += it->second;
    }
    if (sum >= 0) quitf(_wa, "cycle weight %lld is not negative", sum);
    quitf(_ok, "negative cycle of weight %lld", sum);
}
