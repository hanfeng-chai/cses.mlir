#include "testlib.h"
#include <vector>
using namespace std;
typedef long long ll;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<vector<ll>> c(n + 1, vector<ll>(n + 1));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) c[i][j] = inf.readLong();
    ll jcost = ans.readLong();
    ll pcost = ouf.readLong();
    if (pcost != jcost) quitf(_wa, "cost %lld != optimal %lld", pcost, jcost);
    vector<int> usedE(n + 1, 0), usedT(n + 1, 0);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int a = ouf.readInt(1, n, "employee"), b = ouf.readInt(1, n, "task");
        if (usedE[a]++) quitf(_wa, "employee %d assigned twice", a);
        if (usedT[b]++) quitf(_wa, "task %d assigned twice", b);
        sum += c[a][b];
    }
    if (sum != jcost) quitf(_wa, "assignment cost %lld != stated %lld", sum, jcost);
    quitf(_ok, "optimal cost %lld", jcost);
}
