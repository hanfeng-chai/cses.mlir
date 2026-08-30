#include "testlib.h"
#include <vector>
using namespace std;
typedef long long ll;
int bit_[1000006], N;
void upd(int i) { for (i++; i <= N; i += i & -i) bit_[i]++; }
int qry(int i) { int s = 0; for (i++; i > 0; i -= i & -i) s += bit_[i]; return s; }
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(); ll k = inf.readLong();
    vector<int> p(n);
    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; i++) {
        p[i] = ouf.readInt(1, n, "p_i");
        if (seen[p[i]]) quitf(_wa, "value %d repeated", p[i]);
        seen[p[i]] = 1;
    }
    N = n; ll inv = 0;
    for (int i = n - 1; i >= 0; i--) { inv += qry(p[i] - 1); upd(p[i]); }  // count inversions
    if (inv != k) quitf(_wa, "got %lld inversions, expected %lld", inv, k);
    quitf(_ok, "valid permutation with %lld inversions", k);
}
