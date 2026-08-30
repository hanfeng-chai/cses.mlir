#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int best = 0, cur = 0;
    for (size_t i = 0; i < s.size(); i++) {
        cur = (i > 0 && s[i] == s[i - 1]) ? cur + 1 : 1;
        best = max(best, cur);
    }
    cout << best << '\n';
}
