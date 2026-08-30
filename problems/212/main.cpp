#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    vector<int> z(n, 0);  // Z-algorithm
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    z[0] = 0;  // problem defines z(1)=0
    vector<int> pi(n, 0);  // prefix function (KMP)
    for (int i = 1; i < n; i++) { int j = pi[i - 1]; while (j && s[i] != s[j]) j = pi[j - 1]; if (s[i] == s[j]) j++; pi[i] = j; }
    string out;
    for (int i = 0; i < n; i++) { out += to_string(z[i]); out += " \n"[i == n - 1]; }
    for (int i = 0; i < n; i++) { out += to_string(pi[i]); out += " \n"[i == n - 1]; }
    cout << out;
}
