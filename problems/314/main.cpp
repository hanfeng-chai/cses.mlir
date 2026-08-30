#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> g(n+1), rg(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);rg[b].push_back(a);}
    vector<int> order; order.reserve(n);
    vector<char> vis(n+1,0);
    {
        vector<int> idx(n+1,0), s; s.push_back(1); vis[1]=1;
        vector<int> post; post.reserve(n);
        while(!s.empty()){
            int u=s.back();
            if(idx[u] < (int)g[u].size()){
                int v=g[u][idx[u]++];
                if(!vis[v]){vis[v]=1; s.push_back(v);}
            } else { post.push_back(u); s.pop_back(); }
        }
        order=post; reverse(order.begin(),order.end());
    }
    int N=order.size();
    vector<int> rpo(n+1,-1);
    for(int i=0;i<N;i++) rpo[order[i]]=i;
    vector<int> idom(n+1,-1); idom[1]=1;
    auto intersect=[&](int a,int b){ while(a!=b){ while(rpo[a]>rpo[b]) a=idom[a]; while(rpo[b]>rpo[a]) b=idom[b]; } return a; };
    bool changed=true;
    while(changed){
        changed=false;
        for(int i=0;i<N;i++){
            int b=order[i]; if(b==1) continue;
            int ni=-1;
            for(int p: rg[b]){ if(rpo[p]==-1) continue; if(idom[p]!=-1){ if(ni==-1) ni=p; else ni=intersect(p,ni); } }
            if(ni!=-1 && idom[b]!=ni){ idom[b]=ni; changed=true; }
        }
    }
    vector<int> crit; int x=n;
    while(true){ crit.push_back(x); if(x==1) break; x=idom[x]; }
    sort(crit.begin(),crit.end());
    printf("%d\n",(int)crit.size());
    string out; for(int c:crit){ out+=to_string(c); out+=' '; } out+='\n';
    fputs(out.c_str(),stdout);
}
