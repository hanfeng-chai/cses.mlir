#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    vector<int> cnt(k + 2, 0);
    set<int> missing;  // values in [0,k] absent from the window; mex <= k
    for (int v = 0; v <= k; v++) missing.insert(v);
    string out;
    for (int i = 0; i < n; i++) {
        int v = a[i]; if (v <= k) { if (cnt[v]++ == 0) missing.erase(v); }
        if (i >= k) { int u = a[i - k]; if (u <= k) { if (--cnt[u] == 0) missing.insert(u); } }
        if (i >= k - 1) { out += to_string(*missing.begin()); out += ' '; }
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
