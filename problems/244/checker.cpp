#include "testlib.h"
#include <set>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int jk = ans.readInt();
    set<int> js;
    for (int i = 0; i < jk; i++) js.insert(ans.readInt());
    int pk = ouf.readInt();
    if (pk != jk) quitf(_wa, "expected %d necessary cities, got %d", jk, pk);
    set<int> ps;
    for (int i = 0; i < pk; i++) ps.insert(ouf.readInt());
    if ((int)ps.size() != pk) quitf(_wa, "duplicate cities in output");
    if (ps != js) quitf(_wa, "set of necessary cities differs from jury");
    quitf(_ok, "%d necessary cities", jk);
}
