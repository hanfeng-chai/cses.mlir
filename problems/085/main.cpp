#include <bits/stdc++.h>
using namespace std;
int p[100005];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        p[find(a)] = find(b);
    }
    vector<int> reps;
    for (int i = 1; i <= n; i++)
        if (find(i) == i) reps.push_back(i);
    printf("%d\n", (int)reps.size() - 1);
    for (size_t i = 1; i < reps.size(); i++) printf("%d %d\n", reps[0], reps[i]);
}
