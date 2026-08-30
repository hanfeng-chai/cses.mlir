#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        // d 位数共有 cnt=9*10^(d-1) 个，占 d*cnt 位；逐段扣除定位
        long long d = 1, cnt = 9, start = 1;
        while (k > d * cnt) {
            k -= d * cnt;
            d++;
            cnt *= 10;
            start *= 10;
        }
        long long num = start + (k - 1) / d;  // 段内第几个数
        int pos = (int)((k - 1) % d);          // 数内第几位
        cout << to_string(num)[pos] << '\n';
    }
}
