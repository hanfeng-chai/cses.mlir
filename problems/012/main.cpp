#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'A']++;
    int odd = 0;
    char mid = 0;
    for (int i = 0; i < 26; i++)
        if (cnt[i] & 1) { odd++; mid = 'A' + i; }
    if (odd > 1) { cout << "NO SOLUTION\n"; return 0; }
    // 前半按字母序，每字符取一半；中间放唯一的奇数字符；后半镜像
    string half;
    for (int i = 0; i < 26; i++) half += string(cnt[i] / 2, 'A' + i);
    string res = half;
    if (odd) res += mid;
    res += string(half.rbegin(), half.rend());
    cout << res << '\n';
}
