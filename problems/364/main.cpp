#include <bits/stdc++.h>
using namespace std;

struct Node{ int len, pref0, pref1, suf0, suf1, best; };
int n;
vector<Node> tr;
vector<int> bits;

Node merge(const Node&L, const Node&R){
    Node res;
    res.len = L.len+R.len;
    res.pref0 = (L.pref0==L.len) ? L.len+R.pref0 : L.pref0;
    res.pref1 = (L.pref1==L.len) ? L.len+R.pref1 : L.pref1;
    res.suf0 = (R.suf0==R.len) ? R.len+L.suf0 : R.suf0;
    res.suf1 = (R.suf1==R.len) ? R.len+L.suf1 : R.suf1;
    res.best = max({L.best, R.best, L.suf0+R.pref0, L.suf1+R.pref1});
    return res;
}

void build(int node,int l,int r){
    if(l==r){
        int b=bits[l];
        tr[node] = { 1, b==0?1:0, b==1?1:0, b==0?1:0, b==1?1:0, 1 };
        return;
    }
    int m=(l+r)/2;
    build(2*node,l,m); build(2*node+1,m+1,r);
    tr[node]=merge(tr[2*node], tr[2*node+1]);
}
void update(int node,int l,int r,int pos){
    if(l==r){
        int b=bits[l];
        tr[node] = { 1, b==0?1:0, b==1?1:0, b==0?1:0, b==1?1:0, 1 };
        return;
    }
    int m=(l+r)/2;
    if(pos<=m) update(2*node,l,m,pos); else update(2*node+1,m+1,r,pos);
    tr[node]=merge(tr[2*node], tr[2*node+1]);
}

int main(){
    static char buf[200006];
    scanf("%s", buf);
    string s(buf);
    n=(int)s.size();
    bits.resize(n+1);
    for(int i=1;i<=n;i++) bits[i]=s[i-1]-'0';
    tr.assign(4*(n+1), Node());
    build(1,1,n);

    int m; scanf("%d",&m);
    string out; out.reserve(m*7);
    for(int q=0;q<m;q++){
        int x; scanf("%d",&x);
        bits[x] ^= 1;
        update(1,1,n,x);
        out += to_string(tr[1].best);
        out += (q==m-1) ? '\n' : ' ';
    }
    fputs(out.c_str(), stdout);
}
