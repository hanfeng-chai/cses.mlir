#include <bits/stdc++.h>
using namespace std;

int euclidean_length(int x, int y) {
    int length = 0;
    while (x != 1 || y != 1) {
        if (x > y) {
            if (y == 1) return length + x - 1;
            length += x / y;
            x %= y;
        } else {
            if (x == 1) return length + y - 1;
            length += y / x;
            y %= x;
        }
    }
    return length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int subsequences;
    cin >> subsequences;
    int target_sum = subsequences + 2;

    int best_x = 1;
    int best_length = numeric_limits<int>::max();
    for (int x = 1; x <= target_sum / 2; ++x) {
        if (gcd(x, target_sum) != 1) continue;
        int length = euclidean_length(x, target_sum - x);
        if (length < best_length) {
            best_length = length;
            best_x = x;
        }
    }

    int x = best_x, y = target_sum - best_x;
    string reversed;
    reversed.reserve(best_length);
    while (x != 1 || y != 1) {
        if (x > y) {
            int repeats = y == 1 ? x - 1 : x / y;
            reversed.append(repeats, '0');
            x -= repeats * y;
        } else {
            int repeats = x == 1 ? y - 1 : y / x;
            reversed.append(repeats, '1');
            y -= repeats * x;
        }
    }
    reverse(reversed.begin(), reversed.end());
    cout << reversed << '\n';
}
