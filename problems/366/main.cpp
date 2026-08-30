#include <bits/stdc++.h>
using namespace std;

namespace {
unordered_map<string, string> parent_state;
vector<string> states;
vector<string> output_states;
string current;

void build_window_graph(int length, bool small_board) {
    parent_state.clear();
    states.clear();
    for (int a_count = 0; a_count <= length - 2; ++a_count) {
        string letters(a_count, 'A');
        letters += string(length - 2 - a_count, 'B');

        string goal = ".." + letters;
        if (parent_state.emplace(goal, "").second) states.push_back(goal);
        if (small_board) {
            goal = letters;
            goal.insert(1, "..");
            if (parent_state.emplace(goal, "").second) states.push_back(goal);
        }
    }

    for (int head = 0; head < (int)states.size(); ++head) {
        const string state = states[head];
        int empty = state.find('.');
        for (int source = 0; source + 1 < length; ++source) {
            if (state[source] == '.' || state[source + 1] == '.') continue;
            string next = state;
            swap(next[empty], next[source]);
            swap(next[empty + 1], next[source + 1]);
            if (parent_state.emplace(next, state).second) states.push_back(next);
        }
    }
}

void move_pair(int empty, int source) {
    swap(current[empty], current[source]);
    swap(current[empty + 1], current[source + 1]);
    output_states.push_back(current);
}

bool solve_window(int left, int right) {
    string state = current.substr(left, right - left);
    auto it = parent_state.find(state);
    if (it == parent_state.end()) return false;
    while (!it->second.empty()) {
        state = it->second;
        current.replace(left, right - left, state);
        output_states.push_back(current);
        it = parent_state.find(state);
    }
    return true;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> current;
    int length = 2 * n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    if (length < 8) {
        build_window_graph(length, true);
        if (!solve_window(0, length)) {
            cout << -1 << '\n';
            return 0;
        }
    } else {
        int empty = current.find('.');
        if (empty > 1) {
            move_pair(empty, 0);
        } else if (empty == 1) {
            move_pair(1, 3);
            move_pair(3, 0);
        }

        int cursor = 0;
        build_window_graph(8, false);
        bool possible = true;
        while (cursor + 8 < length) {
            if (current[cursor + 2] == 'A' && current[cursor + 3] == 'A') {
                move_pair(cursor, cursor + 2);
                cursor += 2;
                continue;
            }

            int first_b = current.find('B', cursor);
            int later_a = current.find('A', first_b + 2);
            bool last_cell = false;
            if (later_a == (int)string::npos) {
                possible = solve_window(cursor, cursor + 8);
                break;
            }
            if (later_a == length - 1) {
                --later_a;
                last_cell = true;
            }

            move_pair(cursor, first_b);
            move_pair(first_b, later_a);
            move_pair(later_a, cursor);
            if (last_cell && !solve_window(cursor, cursor + 8)) {
                possible = false;
                break;
            }
        }
        if (possible) possible = solve_window(cursor, cursor + 8);
        if (!possible) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << output_states.size() << '\n';
    for (const string &state : output_states) cout << state << '\n';
}
