#include <bits/stdc++.h>
using namespace std;

struct MaxState {
    long long maximum_piece;
    long long minimum_piece;
    int index;
    bool operator<(const MaxState &other) const {
        if (maximum_piece != other.maximum_piece)
            return maximum_piece < other.maximum_piece;
        if (minimum_piece != other.minimum_piece)
            return minimum_piece < other.minimum_piece;
        return index < other.index;
    }
};

struct RangeMinimum {
    int size;
    vector<long long> tree;
    explicit RangeMinimum(const vector<long long> &values) {
        size = 1;
        while (size < (int)values.size()) size <<= 1;
        tree.assign(2 * size, (1LL << 60));
        copy(values.begin(), values.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; --i) tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }
    long long query(int left, int right) const {
        long long result = 1LL << 60;
        for (left += size, right += size + 1; left < right; left >>= 1, right >>= 1) {
            if (left & 1) result = min(result, tree[left++]);
            if (right & 1) result = min(result, tree[--right]);
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cuts;
    cin >> n >> cuts;
    vector<long long> length(n);
    for (long long &value : length) cin >> value;

    vector<long long> best_maximum(cuts + 1), associated_minimum(cuts + 1);
    vector<int> pieces(n, 1);
    multiset<long long> minimum_pieces(length.begin(), length.end());
    priority_queue<MaxState> maximum_queue;
    for (int i = 0; i < n; ++i) maximum_queue.push({length[i], length[i], i});
    best_maximum[0] = maximum_queue.top().maximum_piece;
    associated_minimum[0] = *minimum_pieces.begin();

    for (int used = 1; used <= cuts; ++used) {
        MaxState state = maximum_queue.top();
        maximum_queue.pop();
        int i = state.index;
        minimum_pieces.erase(minimum_pieces.find(state.minimum_piece));
        ++pieces[i];
        long long new_maximum = (length[i] + pieces[i] - 1) / pieces[i];
        long long new_minimum = length[i] / pieces[i];
        minimum_pieces.insert(new_minimum);
        maximum_queue.push({new_maximum, new_minimum, i});
        best_maximum[used] = maximum_queue.top().maximum_piece;
        associated_minimum[used] = *minimum_pieces.begin();
    }

    vector<long long> best_minimum(cuts + 1);
    fill(pieces.begin(), pieces.end(), 1);
    minimum_pieces = multiset<long long>(length.begin(), length.end());
    priority_queue<pair<long long, int>> minimum_queue;
    for (int i = 0; i < n; ++i) minimum_queue.push({length[i] / 2, i});
    best_minimum[0] = *minimum_pieces.begin();

    for (int used = 1; used <= cuts; ++used) {
        auto [next_minimum, i] = minimum_queue.top();
        minimum_queue.pop();
        (void)next_minimum;
        long long old_minimum = length[i] / pieces[i];
        minimum_pieces.erase(minimum_pieces.find(old_minimum));
        ++pieces[i];
        long long new_minimum = length[i] / pieces[i];
        minimum_pieces.insert(new_minimum);
        minimum_queue.push({length[i] / (pieces[i] + 1), i});
        best_minimum[used] = *minimum_pieces.begin();
    }

    vector<long long> direct_range(cuts + 1);
    for (int used = 0; used <= cuts; ++used) {
        direct_range[used] = best_maximum[used] - associated_minimum[used];
    }
    RangeMinimum range_minimum(direct_range);

    for (int k = 1; k <= cuts; ++k) {
        long long target_minimum = best_minimum[k];
        int low = 0, high = k;
        while (low < high) {
            int middle = (low + high + 1) / 2;
            if (associated_minimum[middle] >= target_minimum) low = middle;
            else high = middle - 1;
        }
        int split = low;
        long long answer = best_maximum[split] - target_minimum;
        if (split < k) answer = min(answer, range_minimum.query(split + 1, k));
        if (k > 1) cout << ' ';
        cout << answer;
    }
    cout << '\n';
}
