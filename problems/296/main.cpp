#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> code(max(0,n-2));
    vector<int> deg(n+1,1);
    for(int i=0;i<n-2;i++){scanf("%d",&code[i]); deg[code[i]]++;}
    if(n==2){ printf("1 2\n"); return 0; }
    int ptr=1; while(deg[ptr]!=1) ptr++;
    int leaf=ptr;
    string out; out.reserve((size_t)n*6);
    for(int i=0;i<n-2;i++){
        int a=code[i];
        out += to_string(leaf); out+=' '; out += to_string(a); out+='\n';
        if(--deg[a]==1 && a<ptr) leaf=a;
        else { ptr++; while(deg[ptr]!=1) ptr++; leaf=ptr; }
    }
    out += to_string(leaf); out+=' '; out += to_string(n); out+='\n';
    fputs(out.c_str(), stdout);
}
