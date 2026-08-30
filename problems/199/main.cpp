#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) { int j = pi[i - 1]; while (j && s[i] != s[j]) j = pi[j - 1]; if (s[i] == s[j]) j++; pi[i] = j; }
    vector<int> b;  // borders = chain pi[n-1], pi[pi[n-1]-1], ...
    int L = pi[n - 1];
    while (L > 0) { b.push_back(L); L = pi[L - 1]; }
    sort(b.begin(), b.end());
    for (size_t i = 0; i < b.size(); i++) cout << b[i] << " \n"[i + 1 == b.size()];
    if (b.empty()) cout << "\n";
}
