#include <bits/stdc++.h>
using namespace std;
multiset<int> lo, hi;  // lo: lower half (median = max of lo), hi: upper half
void rebalance(int cnt) {
    int target = (cnt + 1) / 2;
    while ((int)lo.size() > target) { hi.insert(*lo.rbegin()); lo.erase(prev(lo.end())); }
    while ((int)lo.size() < target) { lo.insert(*hi.begin()); hi.erase(hi.begin()); }
}
void addv(int x) { if (lo.empty() || x <= *lo.rbegin()) lo.insert(x); else hi.insert(x); }
void remv(int x) { auto it = lo.find(x); if (it != lo.end()) lo.erase(it); else hi.erase(hi.find(x)); }
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    string out;
    for (int i = 0; i < n; i++) {
        addv(a[i]);
        if (i >= k) remv(a[i - k]);
        int cnt = min(i + 1, k);
        rebalance(cnt);
        if (i >= k - 1) { out += to_string(*lo.rbegin()); out += ' '; }
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
