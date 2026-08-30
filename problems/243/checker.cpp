#include "testlib.h"
#include <set>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int jk = ans.readInt();
    set<pair<int, int>> js;
    for (int i = 0; i < jk; i++) { int a = ans.readInt(), b = ans.readInt(); if (a > b) swap(a, b); js.insert({a, b}); }
    int pk = ouf.readInt();
    if (pk != jk) quitf(_wa, "expected %d necessary roads, got %d", jk, pk);
    set<pair<int, int>> ps;
    for (int i = 0; i < pk; i++) { int a = ouf.readInt(), b = ouf.readInt(); if (a > b) swap(a, b); ps.insert({a, b}); }
    if ((int)ps.size() != pk) quitf(_wa, "duplicate roads in output");
    if (ps != js) quitf(_wa, "set of necessary roads differs from jury");
    quitf(_ok, "%d necessary roads", jk);
}
