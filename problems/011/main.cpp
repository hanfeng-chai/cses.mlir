#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        // 设操作 x 次(左1右2)、y 次(左2右1)：x+2y=a, 2x+y=b
        // 有非负整数解 <=> (a+b)%3==0 且 a<=2b 且 b<=2a
        bool ok = (a + b) % 3 == 0 && a <= 2 * b && b <= 2 * a;
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
