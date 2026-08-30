#include <bits/stdc++.h>
using namespace std;
int n;
map<pair<int, int>, bool> cache;
bool less_(int i, int j) {  // a_i < a_j ?
    auto key = make_pair(i, j);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    printf("? %d %d\n", i, j); fflush(stdout);
    char buf[8]; scanf("%s", buf);
    bool r = (buf[0] == 'Y');
    cache[key] = r; cache[{j, i}] = !r;
    return r;
}
vector<int> tmp;
void mergesort(vector<int> &v, int l, int r) {  // merge sort (<= n*ceil(log n) comparisons)
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergesort(v, l, m); mergesort(v, m, r);
    int i = l, j = m, t = l;
    while (i < m && j < r) { if (less_(v[i], v[j])) tmp[t++] = v[i++]; else tmp[t++] = v[j++]; }
    while (i < m) tmp[t++] = v[i++];
    while (j < r) tmp[t++] = v[j++];
    for (int k = l; k < r; k++) v[k] = tmp[k];
}
int main() {
    scanf("%d", &n);
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i + 1;
    tmp.assign(n, 0);
    mergesort(idx, 0, n);  // idx sorted by value ascending
    vector<int> a(n + 1);
    for (int p = 0; p < n; p++) a[idx[p]] = p + 1;  // rank = value
    printf("!");
    for (int i = 1; i <= n; i++) printf(" %d", a[i]);
    printf("\n"); fflush(stdout);
}
