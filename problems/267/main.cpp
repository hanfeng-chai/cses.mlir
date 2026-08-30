#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
multiset<int> lo, hi;
ll sumLo = 0, sumHi = 0;
void rebalance(int cnt) {
    int target = (cnt + 1) / 2;
    while ((int)lo.size() > target) { int v = *lo.rbegin(); sumLo -= v; lo.erase(prev(lo.end())); hi.insert(v); sumHi += v; }
    while ((int)lo.size() < target) { int v = *hi.begin(); sumHi -= v; hi.erase(hi.begin()); lo.insert(v); sumLo += v; }
}
void addv(int x) { if (lo.empty() || x <= *lo.rbegin()) { lo.insert(x); sumLo += x; } else { hi.insert(x); sumHi += x; } }
void remv(int x) { auto it = lo.find(x); if (it != lo.end()) { lo.erase(it); sumLo -= x; } else { hi.erase(hi.find(x)); sumHi -= x; } }
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
        if (i >= k - 1) {
            ll med = *lo.rbegin();
            ll cost = (med * (ll)lo.size() - sumLo) + (sumHi - med * (ll)hi.size());
            out += to_string(cost); out += ' ';
        }
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
