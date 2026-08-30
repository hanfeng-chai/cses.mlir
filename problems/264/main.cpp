#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (auto &v : a) scanf("%d", &v);
    vector<int> s(a); sort(s.begin(), s.end()); s.erase(unique(s.begin(), s.end()), s.end());
    for (auto &v : a) v = lower_bound(s.begin(), s.end(), v) - s.begin();
    vector<int> freq(s.size(), 0);
    vector<set<int>> byFreq(k + 2);  // byFreq[f] = ranks with frequency f
    int maxFreq = 0; string out;
    auto add = [&](int r) { if (freq[r]) byFreq[freq[r]].erase(r); freq[r]++; byFreq[freq[r]].insert(r); maxFreq = max(maxFreq, freq[r]); };
    auto rem = [&](int r) { byFreq[freq[r]].erase(r); freq[r]--; if (freq[r]) byFreq[freq[r]].insert(r); while (maxFreq > 0 && byFreq[maxFreq].empty()) maxFreq--; };
    for (int i = 0; i < n; i++) {
        add(a[i]);
        if (i >= k) rem(a[i - k]);
        if (i >= k - 1) { out += to_string(s[*byFreq[maxFreq].begin()]); out += ' '; }  // smallest value among the most frequent
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
