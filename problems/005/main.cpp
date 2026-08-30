#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 1) { cout << "1\n"; return 0; }
    if (n <= 3) { cout << "NO SOLUTION\n"; return 0; }
    vector<int> p;
    for (int i = 2; i <= n; i += 2) p.push_back(i);  // 先偶数
    for (int i = 1; i <= n; i += 2) p.push_back(i);  // 再奇数
    for (size_t i = 0; i < p.size(); i++)
        cout << p[i] << " \n"[i + 1 == p.size()];
}
