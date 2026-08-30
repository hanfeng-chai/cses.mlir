#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(), m=inf.readInt();
    map<pair<int,int>,int> avail;
    for(int i=0;i<m;i++){int a=inf.readInt(),b=inf.readInt(); if(a>b)swap(a,b); avail[{a,b}]++;}
    vector<vector<int>> g(n+1); vector<int> indeg(n+1,0);
    for(int i=0;i<m;i++){ int a=ouf.readInt(1,n), b=ouf.readInt(1,n); int x=a,y=b; if(x>y)swap(x,y);
        auto it=avail.find({x,y}); if(it==avail.end()||it->second==0) quitf(_wa,"edge %d %d is not an unused input edge",a,b);
        it->second--; g[a].push_back(b); indeg[b]++; }
    queue<int> q; for(int v=1;v<=n;v++) if(indeg[v]==0)q.push(v); int seen=0;
    while(!q.empty()){int u=q.front();q.pop();seen++;for(int v:g[u])if(--indeg[v]==0)q.push(v);}
    if(seen!=n) quitf(_wa,"orientation contains a cycle");
    quitf(_ok,"valid acyclic orientation");
}
