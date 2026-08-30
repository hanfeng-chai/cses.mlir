#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    while (true) {
        cout << n;
        if (n == 1) break;
        cout << ' ';
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
    }
    cout << '\n';
}
