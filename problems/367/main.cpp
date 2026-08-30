#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> h(m,0);
    long long best=0;
    for(int i=0;i<n;i++){
        static char buf[1005]; scanf("%s", buf);
        for(int j=0;j<m;j++) h[j] = (buf[j]=='*') ? 0 : h[j]+1;

        vector<int> stk; stk.reserve(m+1);
        for(int j=0;j<=m;j++){
            int cur = (j==m) ? 0 : h[j];
            while(!stk.empty() && h[stk.back()]>=cur){
                long long height=h[stk.back()]; stk.pop_back();
                int left = stk.empty() ? -1 : stk.back();
                long long width = j-left-1;
                best = max(best, height*width);
            }
            stk.push_back(j);
        }
    }
    printf("%lld\n", best);
}
