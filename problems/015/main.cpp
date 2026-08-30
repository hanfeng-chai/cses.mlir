#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<string> res;
    do {
        res.push_back(s);
    } while (next_permutation(s.begin(), s.end()));  // 自动跳过重复排列
    cout << res.size() << '\n';
    for (auto &r : res) cout << r << '\n';
}
