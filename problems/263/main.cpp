#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    vector<int> s(a); sort(s.begin(), s.end()); s.erase(unique(s.begin(), s.end()), s.end());
    for (auto &v : a) v = lower_bound(s.begin(), s.end(), v) - s.begin();
    vector<int> cnt(s.size(), 0); int distinct = 0; string out;
    for (int i = 0; i < n; i++) {
        if (cnt[a[i]]++ == 0) distinct++;
        if (i >= k) { if (--cnt[a[i - k]] == 0) distinct--; }
        if (i >= k - 1) { out += to_string(distinct); out += ' '; }
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
