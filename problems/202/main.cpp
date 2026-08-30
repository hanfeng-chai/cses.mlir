#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    string t = "^";  // Manacher on transformed string
    for (char c : s) { t += '#'; t += c; }
    t += "#$";
    int m = t.size();
    vector<int> p(m, 0); int c = 0, r = 0;
    for (int i = 1; i < m - 1; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
    }
    int best = 0, center = 0;
    for (int i = 1; i < m - 1; i++) if (p[i] > best) { best = p[i]; center = i; }
    cout << s.substr((center - best) / 2, best) << "\n";
}
