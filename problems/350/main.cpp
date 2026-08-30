#include <bits/stdc++.h>
using namespace std;

struct Pt{ int x,y; };
static vector<Pt> pts;
static vector<int> idxArr;
struct Node{ int pt, axis, left, right; int minX,maxX,minY,maxY; };
static vector<Node> nodes;

int build(int l, int r, int depth){
    if(l>=r) return -1;
    int axis = depth&1;
    int mid=(l+r)/2;
    nth_element(idxArr.begin()+l, idxArr.begin()+mid, idxArr.begin()+r, [&](int a,int b){
        return axis==0 ? pts[a].x<pts[b].x : pts[a].y<pts[b].y;
    });
    int cur=(int)nodes.size();
    const Pt& self = pts[idxArr[mid]];
    nodes.push_back({idxArr[mid], axis, -1, -1, self.x, self.x, self.y, self.y});
    int lc = build(l, mid, depth+1);
    int rc = build(mid+1, r, depth+1);
    nodes[cur].left=lc; nodes[cur].right=rc;
    if(lc!=-1){
        nodes[cur].minX=min(nodes[cur].minX, nodes[lc].minX); nodes[cur].maxX=max(nodes[cur].maxX, nodes[lc].maxX);
        nodes[cur].minY=min(nodes[cur].minY, nodes[lc].minY); nodes[cur].maxY=max(nodes[cur].maxY, nodes[lc].maxY);
    }
    if(rc!=-1){
        nodes[cur].minX=min(nodes[cur].minX, nodes[rc].minX); nodes[cur].maxX=max(nodes[cur].maxX, nodes[rc].maxX);
        nodes[cur].minY=min(nodes[cur].minY, nodes[rc].minY); nodes[cur].maxY=max(nodes[cur].maxY, nodes[rc].maxY);
    }
    return cur;
}

long long bestDist;
long long boxDist(int node, const Pt& q){
    long long dx = max(0, max(nodes[node].minX-q.x, q.x-nodes[node].maxX));
    long long dy = max(0, max(nodes[node].minY-q.y, q.y-nodes[node].maxY));
    return dx+dy;
}
void query(int node, const Pt& q){
    if(node==-1) return;
    if(boxDist(node,q) >= bestDist) return;
    const Pt& p = pts[nodes[node].pt];
    long long d = abs((long long)p.x-q.x) + abs((long long)p.y-q.y);
    if(d<bestDist) bestDist=d;
    int axis = nodes[node].axis;
    long long diff = axis==0 ? ((long long)q.x-p.x) : ((long long)q.y-p.y);
    int nearChild = diff<0 ? nodes[node].left : nodes[node].right;
    int farChild  = diff<0 ? nodes[node].right : nodes[node].left;
    query(nearChild, q);
    query(farChild, q);
}

int main(){
    int n,m; scanf("%d %d",&n,&m);
    pts.resize(n);
    for(auto&p:pts) scanf("%d %d",&p.x,&p.y);
    idxArr.resize(n);
    for(int i=0;i<n;i++) idxArr[i]=i;
    nodes.reserve(n);
    int root = build(0, n, 0);

    string out; out.reserve(m*7);
    for(int i=0;i<m;i++){
        Pt q; scanf("%d %d",&q.x,&q.y);
        bestDist = LLONG_MAX;
        query(root, q);
        out += to_string(bestDist); out += ' ';
    }
    out += '\n';
    fputs(out.c_str(), stdout);
}
