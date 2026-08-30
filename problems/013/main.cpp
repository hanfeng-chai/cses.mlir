#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int total = 1 << n;
    string out;
    out.reserve((size_t)total * (n + 1));
    for (int i = 0; i < total; i++) {
        int g = i ^ (i >> 1);  // 标准反射格雷码
        for (int b = n - 1; b >= 0; b--) out += char('0' + ((g >> b) & 1));
        out += '\n';
    }
    cout << out;
}
