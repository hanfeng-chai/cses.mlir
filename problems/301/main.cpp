#include <bits/stdc++.h>
using namespace std;
int par_[100005];
int find(int x){while(par_[x]!=x)x=par_[x]=par_[par_[x]];return x;}
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<pair<int,int>>> g(n+1);
    vector<int> ea(m), eb(m);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);ea[i]=a;eb[i]=b;g[a].push_back({b,i});g[b].push_back({a,i});}
    for(int i=1;i<=n;i++)par_[i]=i;
    for(int i=0;i<m;i++){int ra=find(ea[i]),rb=find(eb[i]); if(ra!=rb)par_[ra]=rb;}
    vector<int> ecnt(n+1,0);
    for(int i=0;i<m;i++) ecnt[find(ea[i])]++;
    for(int v=1;v<=n;v++) if(find(v)==v && (ecnt[v]&1)){ printf("IMPOSSIBLE\n"); return 0; }
    vector<int> disc(n+1,0); int timer=0;
    vector<int> outdeg(n+1,0);
    vector<int> dirF(m,0), dirT(m,0); vector<char> oriented(m,0);
    vector<int> it_(n+1,0), parNode(n+1,0), parEdge(n+1,-1);
    for(int s=1;s<=n;s++){
        if(disc[s]) continue;
        vector<int> stk={s}; disc[s]=++timer; parEdge[s]=-1;
        while(!stk.empty()){
            int u=stk.back();
            if(it_[u] < (int)g[u].size()){
                auto pr=g[u][it_[u]++]; int v=pr.first, id=pr.second;
                if(id==parEdge[u]) continue;
                if(!disc[v]){ disc[v]=++timer; parNode[v]=u; parEdge[v]=id; stk.push_back(v); }
                else { if(!oriented[id]){ oriented[id]=1; dirF[id]=u; dirT[id]=v; outdeg[u]++; } }
            } else {
                stk.pop_back();
                int pe=parEdge[u];
                if(pe!=-1){ int p=parNode[u];
                    if(outdeg[u]&1){ dirF[pe]=u; dirT[pe]=p; outdeg[u]++; }
                    else { dirF[pe]=p; dirT[pe]=u; outdeg[p]++; }
                    oriented[pe]=1; }
            }
        }
    }
    string out; out.reserve((size_t)m*8);
    for(int i=0;i<m;i++){ out+=to_string(dirF[i]); out+=' '; out+=to_string(dirT[i]); out+='\n'; }
    fputs(out.c_str(),stdout);
}
