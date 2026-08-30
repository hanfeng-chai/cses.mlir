#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; long long k; scanf("%d %lld",&n,&k);
    vector<long long> x(n);
    for(auto&v:x) scanf("%lld",&v);

    int N2=2*n;
    vector<long long> px(N2+1,0);
    for(int i=0;i<N2;i++) px[i+1]=px[i]+x[i%n];

    // jump[0][s] = furthest end reachable (exclusive) starting a chunk at s, sum<=k
    const int LOG=19; // 2^19 > 2*2e5
    vector<vector<int>> jump(LOG, vector<int>(N2+1));
    {
        // two pointers: for s=0..N2-1, find furthest e
        // use prefix sums with pointer that only moves forward
        int e=0;
        for(int s=0;s<N2;s++){
            if(e<s) e=s;
            while(e<N2 && px[e+1]-px[s] <= k) e++;
            jump[0][s]=e; // covers [s,e)
        }
        jump[0][N2]=N2;
    }
    for(int lvl=1; lvl<LOG; lvl++){
        for(int s=0;s<=N2;s++){
            int mid=jump[lvl-1][s];
            jump[lvl][s] = jump[lvl-1][min(mid,N2)];
        }
    }

    int best=INT_MAX;
    for(int s=0;s<n;s++){
        int target=s+n;
        int cur=s, cnt=0;
        for(int lvl=LOG-1; lvl>=0; lvl--){
            if(jump[lvl][cur] < target){
                cur=jump[lvl][cur];
                cnt += (1<<lvl);
            }
        }
        cnt++; // one more chunk to reach/exceed target
        best=min(best,cnt);
    }
    printf("%d\n", best);
}
