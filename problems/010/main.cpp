#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long z = 0;
    for (long long p = 5; p <= n; p *= 5) z += n / p;  // Legendre 公式数因子 5
    cout << z << '\n';
}
