#include <bits/stdc++.h>
using namespace std;
const int BITS = 30;
struct Node { int nxt[2]; };
vector<Node> t;
void ins(int x) {
    int u = 0;
    for (int b = BITS - 1; b >= 0; b--) { int c = (x >> b) & 1; if (t[u].nxt[c] < 0) { t[u].nxt[c] = t.size(); t.push_back({-1, -1}); } u = t[u].nxt[c]; }
}
int qry(int x) {  // max xor of x with a stored value
    int u = 0, r = 0;
    for (int b = BITS - 1; b >= 0; b--) { int c = (x >> b) & 1; if (t[u].nxt[c ^ 1] >= 0) { r |= 1 << b; u = t[u].nxt[c ^ 1]; } else u = t[u].nxt[c]; }
    return r;
}
int main() {
    int n; scanf("%d", &n);
    t.push_back({-1, -1});
    ins(0); int px = 0, ans = 0;
    for (int i = 0; i < n; i++) { int x; scanf("%d", &x); px ^= x; ans = max(ans, qry(px)); ins(px); }
    printf("%d\n", ans);  // max subarray xor = max over prefix-xor pairs
}
