#include "testlib.h"
#include <string>
#include <vector>
#include <cstring>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1;
long long cnt[MX];
void ext(int c) {
    int cur = ++sz; len_[cur] = len_[last] + 1; cnt[cur] = 1; int p = last;
    while (p && !to[p][c]) { to[p][c] = cur; p = link_[p]; }
    if (!p) link_[cur] = 1;
    else {
        int q = to[p][c];
        if (len_[q] == len_[p] + 1) link_[cur] = q;
        else {
            int cl = ++sz; len_[cl] = len_[p] + 1; link_[cl] = link_[q]; cnt[cl] = 0;
            memcpy(to[cl], to[q], sizeof(to[q]));
            while (p && to[p][c] == q) { to[p][c] = cl; p = link_[p]; }
            link_[q] = cl; link_[cur] = cl;
        }
    }
    last = cur;
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    string s = inf.readString(); int n = s.size();
    for (char ch : s) ext(ch - 'a');
    vector<int> ord(sz + 1), bk(n + 2, 0);
    for (int v = 1; v <= sz; v++) bk[len_[v]]++;
    for (int i = 1; i <= n; i++) bk[i] += bk[i - 1];
    for (int v = 1; v <= sz; v++) ord[bk[len_[v]]--] = v;
    for (int i = sz; i >= 1; i--) { int v = ord[i]; if (link_[v]) cnt[link_[v]] += cnt[v]; }
    int maxRep = 0;
    for (int v = 2; v <= sz; v++) if (cnt[v] >= 2) maxRep = max(maxRep, len_[v]);
    string o = ouf.readString();
    if (maxRep == 0) {
        if (o == "-1") quitf(_ok, "no repeating substring");
        quitf(_wa, "expected -1 (no repeating substring)");
    }
    if ((int)o.size() != maxRep) quitf(_wa, "length %d != longest repeating %d", (int)o.size(), maxRep);
    int u = 1;  // verify o occurs at least twice
    for (char ch : o) { int c = ch - 'a'; if (c < 0 || c >= 26 || !to[u][c]) quitf(_wa, "answer is not a substring"); u = to[u][c]; }
    if (cnt[u] < 2) quitf(_wa, "answer occurs only once");
    quitf(_ok, "longest repeating length %d", maxRep);
}
