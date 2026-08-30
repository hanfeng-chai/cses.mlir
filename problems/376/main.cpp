#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    priority_queue<long long> heap; // max-heap
    long long cost=0;
    for(int i=0;i<n;i++){
        long long v; scanf("%lld",&v);
        heap.push(v);
        long long top=heap.top();
        if(top>v){
            cost += top-v;
            heap.pop();
            heap.push(v);
        }
    }
    printf("%lld\n", cost);
}
