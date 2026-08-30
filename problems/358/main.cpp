#include <bits/stdc++.h>
using namespace std;

// segment tree over j=1..n, tracking bal(j) = cntL_{>=j} - cntR_{>=j}
// supports range-add on [1,c] and global min/max query
struct SegTree{
    int n;
    vector<long long> mn, mx, lazy;
    void init(int n_){
        n=n_;
        mn.assign(4*n,0); mx.assign(4*n,0); lazy.assign(4*n,0);
    }
    void apply(int node,long long v){ mn[node]+=v; mx[node]+=v; lazy[node]+=v; }
    void push(int node){
        if(lazy[node]!=0){
            apply(2*node,lazy[node]); apply(2*node+1,lazy[node]);
            lazy[node]=0;
        }
    }
    void update(int node,int l,int r,int ql,int qr,long long v){
        if(qr<l || r<ql) return;
        if(ql<=l && r<=qr){ apply(node,v); return; }
        push(node);
        int m=(l+r)/2;
        update(2*node,l,m,ql,qr,v);
        update(2*node+1,m+1,r,ql,qr,v);
        mn[node]=min(mn[2*node],mn[2*node+1]);
        mx[node]=max(mx[2*node],mx[2*node+1]);
    }
    void rangeAdd(int l,int r,long long v){ if(l<=r) update(1,1,n,l,r,v); }
    long long globalMin(){ return mn[1]; }
    long long globalMax(){ return mx[1]; }
};

int main(){
    int n; scanf("%d",&n);
    SegTree st; st.init(n);
    string out; out.reserve(n*2);
    for(int i=0;i<n;i++){
        int c,s; scanf("%d %d",&c,&s);
        long long delta = (s==1) ? 1 : -1;
        st.rangeAdd(1, c, delta);
        long long mn=st.globalMin(), mx=st.globalMax();
        if(mn>=0) out += '>';
        else if(mx<=0) out += '<';
        else out += '?';
        out += '\n';
    }
    fputs(out.c_str(), stdout);
}
