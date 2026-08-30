#include <bits/stdc++.h>
using namespace std;

vector<long long> enumerate_half(const vector<long long> &values) {
    int size = 1 << values.size();
    vector<long long> sums(size, 0);
    for (int mask = 1; mask < size; ++mask) {
        int bit = __builtin_ctz(mask);
        sums[mask] = sums[mask & (mask - 1)] + values[bit];
    }
    return sums;
}

long long count_at_most(const vector<long long> &left,
                        const vector<long long> &right,
                        long long bound) {
    long long count = 0;
    int j = (int)right.size() - 1;
    for (long long a : left) {
        while (j >= 0 && a + right[j] > bound) --j;
        if (j < 0) break;
        count += j + 1;
        if (count > bound + 1) return count;
    }
    return count;
}

vector<uint32_t> find_masks(const vector<long long> &raw,
                            long long target, int needed) {
    vector<uint32_t> result;
    for (uint32_t mask = 0; mask < raw.size() && (int)result.size() < needed; ++mask) {
        if (raw[mask] == target) result.push_back(mask);
    }
    return result;
}

struct SumGroup {
    long long left_sum, right_sum;
    int left_count, right_count;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> values(n);
    long long total = 0;
    for (long long &value : values) {
        cin >> value;
        total += value;
    }

    int left_size = n / 2;
    vector<long long> left_values(values.begin(), values.begin() + left_size);
    vector<long long> right_values(values.begin() + left_size, values.end());
    vector<long long> left_raw = enumerate_half(left_values);
    vector<long long> right_raw = enumerate_half(right_values);
    vector<long long> left = left_raw;
    vector<long long> right = right_raw;
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    long long low = -1;
    long long high = total;
    while (high - low > 1) {
        long long middle = low + (high - low) / 2;
        long long count = count_at_most(left, right, middle);
        if (count > middle + 1) high = middle;
        else low = middle;
    }
    long long target = high;

    vector<SumGroup> groups;
    int i = 0, j = (int)right.size() - 1;
    long long represented = 0;
    while (i < (int)left.size() && j >= 0 && represented < 2) {
        long long sum = left[i] + right[j];
        if (sum < target) {
            long long value = left[i];
            while (i < (int)left.size() && left[i] == value) ++i;
        } else if (sum > target) {
            long long value = right[j];
            while (j >= 0 && right[j] == value) --j;
        } else {
            int next_i = i + 1;
            while (next_i < (int)left.size() && left[next_i] == left[i]) ++next_i;
            int first_j = j - 1;
            while (first_j >= 0 && right[first_j] == right[j]) --first_j;
            int left_count = next_i - i;
            int right_count = j - first_j;
            groups.push_back({left[i], right[j], left_count, right_count});
            represented += 1LL * left_count * right_count;
            i = next_i;
            j = first_j;
        }
    }

    const SumGroup &first_group = groups[0];
    vector<uint32_t> left_masks = find_masks(left_raw, first_group.left_sum,
                                             first_group.left_count >= 2 ? 2 : 1);
    vector<uint32_t> right_masks = find_masks(right_raw, first_group.right_sum,
                                               first_group.right_count >= 2 ? 2 : 1);
    uint64_t first_mask = left_masks[0] | (uint64_t(right_masks[0]) << left_size);
    uint64_t second_mask;
    if (1LL * first_group.left_count * first_group.right_count >= 2) {
        if (left_masks.size() >= 2) {
            second_mask = left_masks[1] | (uint64_t(right_masks[0]) << left_size);
        } else {
            second_mask = left_masks[0] | (uint64_t(right_masks[1]) << left_size);
        }
    } else {
        const SumGroup &second_group = groups[1];
        uint32_t left_mask = find_masks(left_raw, second_group.left_sum, 1)[0];
        uint32_t right_mask = find_masks(right_raw, second_group.right_sum, 1)[0];
        second_mask = left_mask | (uint64_t(right_mask) << left_size);
    }

    uint64_t common = first_mask & second_mask;
    uint64_t first = first_mask ^ common;
    uint64_t second = second_mask ^ common;

    cout << __builtin_popcountll(first) << '\n';
    for (int i = 0; i < n; ++i) {
        if (first >> i & 1ULL) cout << values[i] << ' ';
    }
    cout << '\n';
    cout << __builtin_popcountll(second) << '\n';
    for (int i = 0; i < n; ++i) {
        if (second >> i & 1ULL) cout << values[i] << ' ';
    }
    cout << '\n';
}
