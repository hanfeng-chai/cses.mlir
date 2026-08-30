#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt();
    vector<int> code(max(0,n-2));
    for(int i=0;i<n-2;i++) code[i]=inf.readInt();
    vector<vector<int>> g(n+1);
    vector<int> deg(n+1,0);
    for(int i=0;i<n-1;i++){ int a=ouf.readInt(1,n), b=ouf.readInt(1,n); if(a==b) quitf(_wa,"self loop %d",a); g[a].push_back(b); g[b].push_back(a); deg[a]++; deg[b]++; }
    // connected & tree
    vector<char> vis(n+1,0); int cnt=0; vector<int> st={1}; vis[1]=1;
    while(!st.empty()){int u=st.back();st.pop_back();cnt++;for(int v:g[u])if(!vis[v]){vis[v]=1;st.push_back(v);}}
    if(cnt!=n) quitf(_wa,"output is not a connected tree");
    if(n>2){
        vector<int> d=deg;
        priority_queue<int,vector<int>,greater<int>> pq;
        for(int v=1;v<=n;v++) if(d[v]==1) pq.push(v);
        vector<int> res; res.reserve(n-2);
        for(int it=0; it<n-2; it++){
            while(!pq.empty() && d[pq.top()]!=1) pq.pop();
            int leaf=pq.top(); pq.pop();
            d[leaf]=0;
            int nb=-1; for(int v:g[leaf]) if(d[v]>0){ nb=v; break; }
            res.push_back(nb);
            if(--d[nb]==1) pq.push(nb);
        }
        if(res!=code) quitf(_wa,"Prufer code of output tree differs from input");
    }
    quitf(_ok,"valid tree with correct Prufer code");
}
