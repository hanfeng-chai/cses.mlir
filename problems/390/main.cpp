#include <bits/stdc++.h>
using namespace std;

// 390 Reversal Sorting: bring value i to position i for i=1..n via one reversal
// each (skipping i already in place), which uses at most n-1 <= n reversals.
// The naive "just reverse the array segment" simulation is O(n) per step in the
// worst case (e.g. rotating the array by n/2 makes ~n/2 steps each ~n/2 long),
// i.e. O(n^2) overall -- too slow for n up to 2*10^5. Instead we maintain the
// array in an implicit treap (order-statistics BST ordered by current position,
// with a lazy "reversed" flag per subtree) supporting:
//   - rankOf(node): the node's current 1-indexed position, found by first
//     pushing down every ancestor's rev flag along the root->node path (so
//     left/right pointers reflect the true current structure) and then doing
//     a simple bottom-up walk;
//   - split/merge by rank, used to cut out [i,pos], toggle its rev flag (lazy),
//     and splice it back -- this is the standard O(log n) treap range-reverse.
// Every value's node identity never changes, only its position in the treap,
// so nodeOf[value] pointers stay valid for the whole algorithm.
struct Node {
    int val;
    unsigned pri;
    int size;
    bool rev;
    Node *left, *right, *parent;
};

static Node pool[200005];
static int poolCnt = 0;
static mt19937 rng(12345);

Node* newNode(int val) {
    Node* t = &pool[poolCnt++];
    t->val = val;
    t->pri = rng();
    t->size = 1;
    t->rev = false;
    t->left = t->right = t->parent = nullptr;
    return t;
}

inline int getSize(Node* t) { return t ? t->size : 0; }
inline void updateSize(Node* t) { if (t) t->size = 1 + getSize(t->left) + getSize(t->right); }
inline void setParent(Node* t, Node* p) { if (t) t->parent = p; }

inline void pushDown(Node* t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->left, t->right);
        if (t->left) t->left->rev ^= true;
        if (t->right) t->right->rev ^= true;
    }
}

void split(Node* t, int k, Node*& outL, Node*& outR) {
    if (!t) { outL = outR = nullptr; return; }
    pushDown(t);
    int leftSize = getSize(t->left);
    if (leftSize < k) {
        Node *subL, *subR;
        split(t->right, k - leftSize - 1, subL, subR);
        t->right = subL;
        setParent(t->right, t);
        setParent(subR, nullptr);
        updateSize(t);
        outL = t;
        outR = subR;
    } else {
        Node *subL, *subR;
        split(t->left, k, subL, subR);
        t->left = subR;
        setParent(t->left, t);
        setParent(subL, nullptr);
        updateSize(t);
        outL = subL;
        outR = t;
    }
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    pushDown(l);
    pushDown(r);
    if (l->pri > r->pri) {
        l->right = merge(l->right, r);
        setParent(l->right, l);
        updateSize(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        setParent(r->left, r);
        updateSize(r);
        return r;
    }
}

// Rank query: push down along the root->x path first so every ancestor's rev
// flag is resolved (cleared) and its left/right pointers reflect the true
// current structure, then a simple bottom-up walk (no rev-flag juggling needed
// anymore) gives the exact 0-indexed rank. (An earlier version tried to skip
// the push-down and infer each ancestor's effective side purely from that
// ancestor's OWN rev flag -- this looked correct on small hand-checked
// examples but produced wrong ranks on deeper trees; always materializing the
// path first is simpler and provably correct.)
int rankOf(Node* x) {
    static vector<Node*> path;
    path.clear();
    for (Node* cur = x; cur; cur = cur->parent) path.push_back(cur);
    for (int idx = (int)path.size() - 1; idx >= 0; idx--) pushDown(path[idx]);
    int r = getSize(x->left);
    Node* cur = x;
    while (cur->parent) {
        Node* p = cur->parent;
        if (cur == p->right) r += getSize(p->left) + 1;
        cur = p;
    }
    return r; // 0-indexed rank
}

int main() {
    int n;
    scanf("%d", &n);
    vector<Node*> nodeOf(n + 1);
    Node* root = nullptr;
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        Node* nd = newNode(v);
        nodeOf[v] = nd;
        root = merge(root, nd);
    }
    setParent(root, nullptr);

    vector<pair<int,int>> ops;
    ops.reserve(n);
    for (int i = 1; i <= n; i++) {
        int pos = rankOf(nodeOf[i]) + 1;
        if (pos == i) continue;
        Node *A, *B, *C;
        split(root, i - 1, A, B);
        split(B, pos - i + 1, B, C);
        B->rev ^= true;
        Node* AB = merge(A, B);
        root = merge(AB, C);
        setParent(root, nullptr);
        ops.push_back({i, pos});
    }

    printf("%d\n", (int)ops.size());
    for (auto &p : ops) printf("%d %d\n", p.first, p.second);
}
