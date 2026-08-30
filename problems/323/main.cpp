#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<string> g(n);
    for(auto&r:g){ char buf[3005]; scanf("%s",buf); r=buf; }
    vector<long long> cnt(k,0);
    vector<int> prev(n,0), cur(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int d;
            if(i==0||j==0) d=1;
            else if(g[i][j]==g[i-1][j] && g[i][j]==g[i][j-1] && g[i][j]==g[i-1][j-1])
                d=min(prev[j], min(cur[j-1], prev[j-1]))+1;
            else d=1;
            cur[j]=d;
            cnt[g[i][j]-'A'] += d;
        }
        swap(prev,cur);
    }
    for(int c=0;c<k;c++) printf("%lld\n", cnt[c]);
}
