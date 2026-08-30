#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> h(n);
    for(auto&v:h) scanf("%lld",&v);

    vector<int> stk; stk.reserve(n+1);
    long long best=0;
    for(int i=0;i<=n;i++){
        long long cur = (i==n) ? 0 : h[i];
        while(!stk.empty() && h[stk.back()]>=cur){
            long long height=h[stk.back()]; stk.pop_back();
            int left = stk.empty() ? -1 : stk.back();
            long long width = i-left-1;
            best = max(best, height*width);
        }
        stk.push_back(i);
    }
    printf("%lld\n", best);
}
