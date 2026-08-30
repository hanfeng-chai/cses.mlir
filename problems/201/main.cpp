#include <bits/stdc++.h>
using namespace std;
// Booth's algorithm: index of the lexicographically minimal rotation
int booth(const string &S) {
    string s = S + S; int n = s.size();
    vector<int> f(n, -1); int k = 0;
    for (int j = 1; j < n; j++) {
        char sj = s[j]; int i = f[j - k - 1];
        while (i != -1 && sj != s[k + i + 1]) { if (sj < s[k + i + 1]) k = j - i - 1; i = f[i]; }
        if (sj != s[k + i + 1]) { if (sj < s[k]) k = j; f[j - k] = -1; }
        else f[j - k] = i + 1;
    }
    return k;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int k = booth(s);
    cout << s.substr(k) + s.substr(0, k) << "\n";
}
