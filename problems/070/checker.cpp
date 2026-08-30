#include "testlib.h"
#include <vector>
using namespace std;

// SPJ for Longest Common Subsequence (multiple valid answers).
// Verifies the participant's length equals the official optimum AND the
// printed sequence is really a common subsequence of both input arrays.
static bool isSubseq(const vector<int> &s, const vector<int> &arr) {
    size_t k = 0;
    for (size_t i = 0; i < arr.size() && k < s.size(); i++)
        if (arr[i] == s[k]) k++;
    return k == s.size();
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) a[i] = inf.readInt();
    for (int i = 0; i < m; i++) b[i] = inf.readInt();

    int jlen = ans.readInt();           // official optimal length
    long long plen = ouf.readLong();    // participant's claimed length
    if (plen != jlen)
        quitf(_wa, "length mismatch: expected %d, found %lld", jlen, plen);

    vector<int> s;
    for (int i = 0; i < jlen; i++) s.push_back(ouf.readInt());
    if (!isSubseq(s, a)) quitf(_wa, "output is not a subsequence of array A");
    if (!isSubseq(s, b)) quitf(_wa, "output is not a subsequence of array B");
    quitf(_ok, "correct, length %d", jlen);
}
