#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(), d=inf.readInt();
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a=inf.readInt(),b=inf.readInt(); g[a].push_back(b); g[b].push_back(a);}
    int kj=ans.readInt(); // jury's optimal count
    int k=ouf.readInt(0,n);
    if(k!=kj) quitf(_wa,"reported %d offices but optimum is %d",k,kj);
    vector<int> chosen(k);
    vector<char> isCh(n+1,0);
    for(int i=0;i<k;i++){ chosen[i]=ouf.readInt(1,n); if(isCh[chosen[i]]) quitf(_wa,"city %d repeated",chosen[i]); isCh[chosen[i]]=1; }
    // multi-source BFS, find min distance between two distinct chosen via meeting edges
    vector<int> dist(n+1,-1), src(n+1,0);
    queue<int> q;
    for(int c:chosen){ dist[c]=0; src[c]=c; q.push(c); }
    int best=INT_MAX;
    while(!q.empty()){int u=q.front();q.pop(); for(int v:g[u]){ if(dist[v]==-1){dist[v]=dist[u]+1;src[v]=src[u];q.push(v);} else if(src[v]!=src[u]) best=min(best,dist[u]+dist[v]+1); } }
    if(k>=2 && best<d) quitf(_wa,"two offices at distance %d < %d",best,d);
    quitf(_ok,"valid: %d offices, pairwise distance >= %d",k,d);
}
