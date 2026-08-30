#include <bits/stdc++.h>
using namespace std;
int par[100005];
int find(int x){while(par[x]!=x)x=par[x]=par[par[x]];return x;}
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<array<int,4>> e(m);
    for(int i=0;i<m;i++){int a,b,w;scanf("%d %d %d",&a,&b,&w);e[i]={w,a,b,i};}
    vector<array<int,4>> es=e; sort(es.begin(),es.end());
    for(int i=1;i<=n;i++)par[i]=i;
    long long mst=0;
    vector<vector<array<int,2>>> tree(n+1);
    vector<char> inMST(m,0);
    for(auto&ed:es){ int w=ed[0],a=ed[1],b=ed[2],idx=ed[3]; int ra=find(a),rb=find(b); if(ra!=rb){par[ra]=rb;mst+=w;tree[a].push_back({b,w});tree[b].push_back({a,w});inMST[idx]=1;}}
    int LOG=1; while((1<<LOG)<max(2,n)) LOG++;
    vector<vector<int>> up(LOG+1, vector<int>(n+1,0));
    vector<vector<int>> mx(LOG+1, vector<int>(n+1,0));
    vector<int> depth(n+1,0);
    vector<char> vis(n+1,0);
    for(int s=1;s<=n;s++) if(!vis[s]){
        vector<int> stk={s}; vis[s]=1; up[0][s]=s;
        while(!stk.empty()){int u=stk.back();stk.pop_back();
            for(auto&pr:tree[u]){int v=pr[0],w=pr[1]; if(!vis[v]){vis[v]=1;depth[v]=depth[u]+1;up[0][v]=u;mx[0][v]=w;stk.push_back(v);}}}
    }
    for(int k=1;k<=LOG;k++) for(int v=1;v<=n;v++){ up[k][v]=up[k-1][up[k-1][v]]; mx[k][v]=max(mx[k-1][v], mx[k-1][up[k-1][v]]); }
    auto maxOnPath=[&](int u,int v)->int{
        int res=0;
        if(depth[u]<depth[v]) swap(u,v);
        int diff=depth[u]-depth[v];
        for(int k=0;k<=LOG;k++) if(diff>>k&1){ res=max(res,mx[k][u]); u=up[k][u]; }
        if(u==v) return res;
        for(int k=LOG;k>=0;k--) if(up[k][u]!=up[k][v]){ res=max(res,max(mx[k][u],mx[k][v])); u=up[k][u]; v=up[k][v]; }
        return max(res, max(mx[0][u],mx[0][v]));
    };
    for(int i=0;i<m;i++){
        if(inMST[i]) printf("%lld\n", mst);
        else { int a=e[i][1],b=e[i][2],w=e[i][0]; printf("%lld\n", mst - maxOnPath(a,b) + w); }
    }
}
