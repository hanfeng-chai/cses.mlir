#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long prev, moves = 0;
    cin >> prev;
    for (int i = 1; i < n; i++) {
        long long x;
        cin >> x;
        if (x < prev) moves += prev - x;  // 把 x 抬高到 prev
        else prev = x;
    }
    cout << moves << '\n';
}
