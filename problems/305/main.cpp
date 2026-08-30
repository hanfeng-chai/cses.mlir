#include <bits/stdc++.h>
using namespace std;
int par[100005];
int find(int x){while(par[x]!=x)x=par[x]=par[par[x]];return x;}
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<array<int,4>> e(m);
    for(int i=0;i<m;i++){int a,b,w;scanf("%d %d %d",&a,&b,&w);e[i]={w,a,b,i};}
    sort(e.begin(),e.end());
    for(int i=1;i<=n;i++)par[i]=i;
    vector<char> ans(m,'?');
    int i=0;
    while(i<m){
        int j=i, w=e[i][0];
        while(j<m && e[j][0]==w) j++;
        for(int k=i;k<j;k++){ int a=e[k][1],b=e[k][2]; ans[e[k][3]] = (find(a)!=find(b))?'Y':'N'; }
        for(int k=i;k<j;k++){ int a=e[k][1],b=e[k][2]; int ra=find(a),rb=find(b); if(ra!=rb)par[ra]=rb; }
        i=j;
    }
    for(int k=0;k<m;k++) fputs(ans[k]=='Y'?"YES\n":"NO\n", stdout);
}
