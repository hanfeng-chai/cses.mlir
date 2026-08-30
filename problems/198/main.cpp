#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s, p; cin >> s >> p;
    int n = s.size(), m = p.size();
    vector<int> pi(m, 0);  // KMP prefix function of pattern
    for (int i = 1; i < m; i++) { int j = pi[i - 1]; while (j && p[i] != p[j]) j = pi[j - 1]; if (p[i] == p[j]) j++; pi[i] = j; }
    int cnt = 0, j = 0;
    for (int i = 0; i < n; i++) {
        while (j && s[i] != p[j]) j = pi[j - 1];
        if (s[i] == p[j]) j++;
        if (j == m) { cnt++; j = pi[j - 1]; }
    }
    cout << cnt << "\n";
}
