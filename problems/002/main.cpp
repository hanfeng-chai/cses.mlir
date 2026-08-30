#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long sum = n * (n + 1) / 2;
    for (long long i = 0, x; i < n - 1; i++) {
        cin >> x;
        sum -= x;
    }
    cout << sum << '\n';
}
