#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<string> g(n);
    for(auto&r:g){ char buf[3005]; scanf("%s",buf); r=buf; }
    vector<long long> cnt(k,0);
    vector<int> h(n,0);
    vector<long long> sh(n+1); vector<int> sw(n+1); // stack of (height, width)
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) h[j] = (i>0 && g[i][j]==g[i-1][j]) ? h[j]+1 : 1;
        int top=0; long long S=0;
        for(int j=0;j<n;j++){
            if(j>0 && g[i][j]!=g[i][j-1]){ top=0; S=0; }
            long long w=1;
            while(top>0 && sh[top]>=h[j]){ S-=sh[top]*sw[top]; w+=sw[top]; top--; }
            top++; sh[top]=h[j]; sw[top]=(int)w;
            S+=(long long)h[j]*w;
            cnt[g[i][j]-'A'] += S;
        }
    }
    for(int c=0;c<k;c++) printf("%lld\n", cnt[c]);
}
