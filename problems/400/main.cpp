#include <bits/stdc++.h>
using namespace std;

struct RangeMinimum {
    static constexpr int INF = 1000000007;
    int size;
    vector<pair<int, int>> tree;
    explicit RangeMinimum(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, {INF, -1});
    }
    void update(int position, int value) {
        int node = position + size;
        tree[node] = {value, position};
        for (node >>= 1; node; node >>= 1) tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    pair<int, int> query(int left, int right) const {
        if (left > right) return {INF, -1};
        pair<int, int> result{INF, -1};
        for (left += size, right += size + 1; left < right; left >>= 1, right >>= 1) {
            if (left & 1) result = min(result, tree[left++]);
            if (right & 1) result = min(result, tree[--right]);
        }
        return result;
    }
};

struct ParityComponents {
    vector<int> parent;
    vector<set<pair<int, int>>> active;
    RangeMinimum &minimum;

    ParityComponents(int size, RangeMinimum &minimum)
        : parent(size), active(size), minimum(minimum) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    void hide_representative(int root) {
        if (!active[root].empty()) minimum.update(active[root].begin()->second, RangeMinimum::INF);
    }

    void show_representative(int root) {
        if (!active[root].empty()) minimum.update(active[root].begin()->second,
                                                   active[root].begin()->first);
    }

    void merge(int first, int second) {
        first = find(first);
        second = find(second);
        if (first == second) return;
        hide_representative(first);
        hide_representative(second);
        if (active[first].size() < active[second].size()) swap(first, second);
        parent[second] = first;
        active[first].insert(active[second].begin(), active[second].end());
        active[second].clear();
        show_representative(first);
    }

    void insert(int node, pair<int, int> item) {
        int root = find(node);
        hide_representative(root);
        active[root].insert(item);
        show_representative(root);
    }

    void erase(int node, pair<int, int> item) {
        int root = find(node);
        hide_representative(root);
        active[root].erase(item);
        show_representative(root);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> permutation(n);
    for (int &value : permutation) cin >> value;

    vector<int> suffix_minimum(n + 1, RangeMinimum::INF);
    for (int i = n - 1; i >= 0; --i) {
        suffix_minimum[i] = min(suffix_minimum[i + 1], permutation[i]);
    }

    vector<vector<int>> expires(n + 1);
    for (int i = 0; i < n; ++i) {
        int low = i + 1, high = n - 1, last = i;
        while (low <= high) {
            int middle = (low + high) / 2;
            if (suffix_minimum[middle] < permutation[i]) {
                last = middle;
                low = middle + 1;
            } else {
                high = middle - 1;
            }
        }
        expires[last + 1].push_back(i);
    }

    RangeMinimum minimum(n);
    ParityComponents components(2 * n, minimum);

    for (int j = 0; j < n; ++j) {
        for (int i : expires[j]) components.erase(i, {permutation[i], i});

        vector<int> conflicts;
        while (true) {
            auto [value, position] = minimum.query(0, j - 1);
            if (value >= permutation[j]) break;
            conflicts.push_back(position);
            minimum.update(position, RangeMinimum::INF);
        }

        components.insert(j, {permutation[j], j});
        for (int i : conflicts) {
            components.merge(j + n, i);
            components.merge(j, i + n);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (components.find(i) == components.find(i + n)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> root_color(2 * n, 0), color(n);
    for (int i = 0; i < n; ++i) {
        int root = components.find(i);
        int opposite = components.find(i + n);
        if (root_color[root] == 0) {
            root_color[root] = 1;
            root_color[opposite] = 2;
        }
        color[i] = root_color[root];
    }

    vector<int> stacks[2];
    int expected = 1;
    for (int i = 0; i < n; ++i) {
        stacks[color[i] - 1].push_back(permutation[i]);
        while (true) {
            if (!stacks[0].empty() && stacks[0].back() == expected) {
                stacks[0].pop_back();
                ++expected;
            } else if (!stacks[1].empty() && stacks[1].back() == expected) {
                stacks[1].pop_back();
                ++expected;
            } else {
                break;
            }
        }
    }
    if (expected != n + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << color[i];
    }
    cout << '\n';
}
