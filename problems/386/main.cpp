#include <bits/stdc++.h>
using namespace std;

namespace {
constexpr int MAX_TARGET = 500000;
bitset<MAX_TARGET + 1> possible[1001];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> values(n);
    long long total = 0;
    for (int &value : values) {
        cin >> value;
        total += value;
    }
    if (total & 1) {
        cout << -1 << '\n';
        return 0;
    }

    int target = total / 2;
    possible[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        possible[i] = possible[i - 1] | (possible[i - 1] << values[i - 1]);
    }
    if (!possible[n][target]) {
        cout << -1 << '\n';
        return 0;
    }

    multiset<int> left, right;
    int remaining = target;
    for (int i = n; i >= 1; --i) {
        int value = values[i - 1];
        if (remaining >= value && possible[i - 1][remaining - value]) {
            left.insert(value);
            remaining -= value;
        } else {
            right.insert(value);
        }
    }

    for (int step = 0; step < n - 1; ++step) {
        if (left.empty()) {
            auto first = right.begin();
            int a = *first;
            right.erase(first);
            auto second = right.begin();
            int b = *second;
            right.erase(second);
            cout << a << ' ' << b << '\n';
            right.insert(abs(a - b));
        } else if (right.empty()) {
            auto first = left.begin();
            int a = *first;
            left.erase(first);
            auto second = left.begin();
            int b = *second;
            left.erase(second);
            cout << a << ' ' << b << '\n';
            left.insert(abs(a - b));
        } else if (*left.rbegin() > *right.rbegin()) {
            auto large = prev(left.end());
            auto small = right.begin();
            int a = *large, b = *small;
            left.erase(large);
            right.erase(small);
            cout << a << ' ' << b << '\n';
            left.insert(a - b);
        } else {
            auto large = prev(right.end());
            auto small = left.begin();
            int a = *large, b = *small;
            right.erase(large);
            left.erase(small);
            cout << a << ' ' << b << '\n';
            right.insert(a - b);
        }
    }
}
