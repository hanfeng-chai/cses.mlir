#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int bit[200005], N;
void upd(int i, int v) { for (i++; i <= N; i += i & -i) bit[i] += v; }
int qry(int i) { int s = 0; for (i++; i > 0; i -= i & -i) s += bit[i]; return s; }  // sum of ranks in [0,i]
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    vector<int> s(a); sort(s.begin(), s.end()); s.erase(unique(s.begin(), s.end()), s.end());
    N = s.size();
    for (auto &v : a) v = lower_bound(s.begin(), s.end(), v) - s.begin();
    ll inv = 0; string out;
    for (int j = 0; j < k; j++) { inv += j - qry(a[j]); upd(a[j], 1); }  // first window
    out += to_string(inv); out += ' ';
    for (int L = 0; L + k < n; L++) {
        int r = a[L + k];
        inv -= (a[L] > 0 ? qry(a[L] - 1) : 0);  // remove leftmost: pairs where it is the larger left element
        upd(a[L], -1);
        inv += (k - 1) - qry(r);                // add new rightmost: existing elements greater than it
        upd(r, 1);
        out += to_string(inv); out += ' ';
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
