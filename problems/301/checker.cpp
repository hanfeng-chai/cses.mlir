#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(), m=inf.readInt();
    vector<int> pa(n+1); for(int i=1;i<=n;i++)pa[i]=i;
    function<int(int)> find=[&](int x){ while(pa[x]!=x)x=pa[x]=pa[pa[x]]; return x; };
    map<pair<int,int>,int> avail;
    vector<int> ea(m),eb(m);
    for(int i=0;i<m;i++){int a=inf.readInt(),b=inf.readInt(); ea[i]=a;eb[i]=b; int x=a,y=b; if(x>y)swap(x,y); avail[{x,y}]++; int ra=find(a),rb=find(b); if(ra!=rb)pa[ra]=rb;}
    vector<int> ecnt(n+1,0); for(int i=0;i<m;i++) ecnt[find(ea[i])]++;
    bool possible=true; for(int v=1;v<=n;v++) if(find(v)==v && (ecnt[v]&1)) possible=false;
    string first=ouf.readToken();
    if(first=="IMPOSSIBLE"){
        if(possible) quitf(_wa,"said IMPOSSIBLE but a valid orientation exists");
        quitf(_ok,"correctly IMPOSSIBLE");
    }
    if(!possible) quitf(_wa,"gave orientation but none exists (some component has odd edges)");
    int a1=atoi(first.c_str());
    vector<int> outdeg(n+1,0);
    for(int i=0;i<m;i++){ int a=(i==0?a1:ouf.readInt(1,n)); int b=ouf.readInt(1,n);
        int x=a,y=b; if(x>y)swap(x,y); auto it=avail.find({x,y}); if(it==avail.end()||it->second==0) quitf(_wa,"edge %d %d not an unused input edge",a,b); it->second--; outdeg[a]++; }
    for(int v=1;v<=n;v++) if(outdeg[v]&1) quitf(_wa,"node %d has odd outdegree %d",v,outdeg[v]);
    quitf(_ok,"valid even-outdegree orientation");
}
