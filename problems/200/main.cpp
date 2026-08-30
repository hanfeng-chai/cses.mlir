#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) { int j = pi[i - 1]; while (j && s[i] != s[j]) j = pi[j - 1]; if (s[i] == s[j]) j++; pi[i] = j; }
    vector<int> per;  // period = n - border, for every border length (chain) and 0
    int L = pi[n - 1];
    while (L > 0) { per.push_back(n - L); L = pi[L - 1]; }
    per.push_back(n);
    sort(per.begin(), per.end());
    for (size_t i = 0; i < per.size(); i++) cout << per[i] << " \n"[i + 1 == per.size()];
}
