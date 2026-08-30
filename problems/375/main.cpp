#include <bits/stdc++.h>
using namespace std;

struct State {
    long long sum;
    int hole;
    int moving;
    int limit;

    bool operator>(const State &other) const {
        if (sum != other.sum) return sum > other.sum;
        if (hole != other.hole) return hole > other.hole;
        if (moving != other.moving) return moving > other.moving;
        return limit > other.limit;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, subset_size, count;
    cin >> n >> subset_size >> count;
    vector<long long> values(n);
    for (long long &value : values) cin >> value;
    sort(values.begin(), values.end());

    long long minimum_sum = accumulate(values.begin(), values.begin() + subset_size, 0LL);
    vector<long long> answer;
    answer.reserve(count);
    answer.push_back(minimum_sum);

    priority_queue<State, vector<State>, greater<State>> queue;
    if (count > 1) {
        queue.push({minimum_sum - values[subset_size - 1] + values[subset_size],
                    subset_size - 1, subset_size, n});
    }

    while ((int)answer.size() < count) {
        State state = queue.top();
        queue.pop();
        answer.push_back(state.sum);

        if (state.hole > 0) {
            queue.push({state.sum - values[state.hole - 1] + values[state.hole],
                        state.hole - 1, state.hole, state.moving});
        }
        if (state.moving + 1 < state.limit) {
            queue.push({state.sum - values[state.moving] + values[state.moving + 1],
                        state.hole, state.moving + 1, state.limit});
        }
    }

    for (int i = 0; i < count; ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
}
