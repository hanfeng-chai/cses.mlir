#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<int, 3>> c(n);  // 到达, 离开, 原始下标
    for (int i = 0; i < n; i++) { cin >> c[i][0] >> c[i][1]; c[i][2] = i; }
    sort(c.begin(), c.end());    // 按到达时间
    vector<int> room(n);
    // 小根堆：(离开时间, 房间号)，堆顶最早空出
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    int rooms = 0;
    for (auto &[a, b, idx] : c) {
        if (!pq.empty() && pq.top().first < a) {   // 该房间已空出可复用
            int rm = pq.top().second; pq.pop();
            room[idx] = rm;
            pq.push({b, rm});
        } else {                                    // 开新房间
            room[idx] = ++rooms;
            pq.push({b, rooms});
        }
    }
    cout << rooms << '\n';
    for (int i = 0; i < n; i++) cout << room[i] << " \n"[i == n - 1];
}
