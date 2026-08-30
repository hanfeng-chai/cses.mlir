#include <bits/stdc++.h>
using namespace std;
int par[100005];
int find(int x){while(par[x]!=x)x=par[x]=par[par[x]];return x;}
int main(){
    int n,m,k; scanf("%d %d %d",&n,&m,&k);
    vector<pair<int,int>> edges(m);
    unordered_map<long long,int> mp; mp.reserve(m*2);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);if(a>b)swap(a,b);edges[i]={a,b};mp[(long long)a*100001+b]=i;}
    vector<int> brk(k);
    vector<char> isBroken(m,0);
    for(int i=0;i<k;i++){int a,b;scanf("%d %d",&a,&b);if(a>b)swap(a,b);int id=mp[(long long)a*100001+b];brk[i]=id;isBroken[id]=1;}
    for(int i=1;i<=n;i++)par[i]=i;
    int comp=n;
    for(int i=0;i<m;i++) if(!isBroken[i]){int ra=find(edges[i].first),rb=find(edges[i].second);if(ra!=rb){par[ra]=rb;comp--;}}
    vector<int> res(k);
    for(int i=k-1;i>=0;i--){ res[i]=comp; int id=brk[i]; int ra=find(edges[id].first),rb=find(edges[id].second); if(ra!=rb){par[ra]=rb;comp--;} }
    for(int i=0;i<k;i++) printf("%d ", res[i]);
    printf("\n");
}
