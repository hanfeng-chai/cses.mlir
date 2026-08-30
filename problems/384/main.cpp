#include <bits/stdc++.h>
using namespace std;

struct Result {
    long long steps;
    long long remainder;
};

array<unordered_map<long long, Result>, 10> memo;

Result reduce_block(long long value, int outside_maximum) {
    if (value < 10) {
        int digit = value;
        int subtract = max(digit, outside_maximum);
        if (subtract == 0) return {0, 0};
        return {1, value - subtract};
    }

    auto &table = memo[outside_maximum];
    auto found = table.find(value);
    if (found != table.end()) return found->second;

    long long power = 1;
    while (power <= value / 10) power *= 10;

    long long current = value;
    long long steps = 0;
    while (current >= power) {
        int leading_digit = current / power;
        Result suffix = reduce_block(current % power,
                                     max(outside_maximum, leading_digit));
        steps += suffix.steps;
        current = leading_digit * power + suffix.remainder;
    }

    Result tail = reduce_block(current, outside_maximum);
    Result result{steps + tail.steps, tail.remainder};
    table.emplace(value, result);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    cout << reduce_block(n, 0).steps << '\n';
}
