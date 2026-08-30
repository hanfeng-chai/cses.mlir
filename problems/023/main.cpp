#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = (int)s.size();
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'A']++;
    for (int i = 0; i < 26; i++)
        if (cnt[i] > (n + 1) / 2) { cout << -1 << '\n'; return 0; }

    string res;
    res.reserve(n);
    int last = -1;
    for (int pos = 0; pos < n; pos++) {
        int rem = n - pos;
        // 若某字符剩余数 *2 > rem，它必须立刻放（否则之后必相邻）
        int forced = -1;
        for (int c = 0; c < 26; c++)
            if (cnt[c] * 2 > rem) { forced = c; break; }
        int pick;
        if (forced != -1) {
            pick = forced;  // forced != last 由频次上界保证
        } else {
            pick = 0;
            while (pick == last || cnt[pick] == 0) pick++;  // 最小可用且 != last
        }
        res += char('A' + pick);
        cnt[pick]--;
        last = pick;
    }
    cout << res << '\n';
}
