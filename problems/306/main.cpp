#include <bits/stdc++.h>
using namespace std;
int par_[100005], rnk_[100005];
int findr(int x){ while(par_[x]!=x) x=par_[x]; return x; }
struct Undo{ int ra,rb,rankInc; };
vector<Undo> stk;
bool unite(int a,int b){
    a=findr(a); b=findr(b);
    if(a==b){ stk.push_back({-1,-1,0}); return false; }
    if(rnk_[a]<rnk_[b]) swap(a,b);
    int inc = (rnk_[a]==rnk_[b])?1:0;
    par_[b]=a; rnk_[a]+=inc;
    stk.push_back({a,b,inc});
    return true;
}
void rollback(int target){
    while((int)stk.size()>target){
        Undo u=stk.back(); stk.pop_back();
        if(u.ra==-1) continue;
        par_[u.rb]=u.rb; rnk_[u.ra]-=u.rankInc;
    }
}
int main(){
    int n,m,q; scanf("%d %d %d",&n,&m,&q);
    vector<array<int,3>> edges(m);
    for(int i=0;i<m;i++){int a,b,w;scanf("%d %d %d",&a,&b,&w);edges[i]={a,b,w};}
    vector<vector<int>> qe(q);
    for(int i=0;i<q;i++){ int sz; scanf("%d",&sz); qe[i].resize(sz); for(int j=0;j<sz;j++){int e;scanf("%d",&e);qe[i][j]=e-1;} }
    vector<char> ans(q,1);
    vector<int> ord(m); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){return edges[a][2]<edges[b][2];});
    struct Ev{int w,q,e;};
    vector<Ev> evs;
    for(int i=0;i<q;i++) for(int e: qe[i]) evs.push_back({edges[e][2], i, e});
    sort(evs.begin(),evs.end(),[](const Ev&A,const Ev&B){ if(A.w!=B.w)return A.w<B.w; return A.q<B.q; });
    for(int i=1;i<=n;i++){par_[i]=i;rnk_[i]=0;}
    int pg=0, ei=0, E=evs.size();
    while(ei<E){
        int w=evs[ei].w;
        while(pg<m && edges[ord[pg]][2] < w){ int e=ord[pg]; unite(edges[e][0],edges[e][1]); pg++; }
        int j=ei;
        while(j<E && evs[j].w==w){
            int qid=evs[j].q;
            int base=stk.size();
            bool ok=true;
            int k=j;
            while(k<E && evs[k].w==w && evs[k].q==qid){
                int e=evs[k].e;
                if(!unite(edges[e][0],edges[e][1])) ok=false;
                k++;
            }
            if(!ok) ans[qid]=0;
            rollback(base);
            j=k;
        }
        ei=j;
    }
    string out; out.reserve(q*4);
    for(int i=0;i<q;i++) out += ans[i]? "YES\n":"NO\n";
    fputs(out.c_str(),stdout);
}
