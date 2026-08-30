#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    int root=1; for(int v=1;v<=n;v++) if((int)g[v].size()>=2){root=v;break;}
    vector<int> leaves; vector<char> vis(n+1,0);
    vector<int> stk={root}; vis[root]=1;
    while(!stk.empty()){int u=stk.back();stk.pop_back(); if((int)g[u].size()==1) leaves.push_back(u); for(int v:g[u]) if(!vis[v]){vis[v]=1;stk.push_back(v);} }
    int k=leaves.size();
    int need=(k+1)/2;
    printf("%d\n", need);
    string out; out.reserve((size_t)need*8);
    int half=k/2;
    for(int i=0;i<need;i++){ int j=(i+half)%k; out+=to_string(leaves[i]); out+=' '; out+=to_string(leaves[j]); out+='\n'; }
    fputs(out.c_str(),stdout);
}
