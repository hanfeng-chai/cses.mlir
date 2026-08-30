#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> sa(n);
    for (auto &x : sa) { cin >> x; x--; }
    vector<int> rnk(n);
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;
    auto nxtrank = [&](int p) { return p + 1 < n ? rnk[p + 1] : -1; };
    string s(n, 'a'); int cur = 0;  // greedily assign smallest letters
    for (int i = 1; i < n; i++) {
        if (!(nxtrank(sa[i - 1]) < nxtrank(sa[i]))) cur++;  // must increase the letter
        if (cur > 25) { cout << -1 << "\n"; return 0; }
        s[sa[i]] = 'a' + cur;
    }
    cout << s << "\n";
}
