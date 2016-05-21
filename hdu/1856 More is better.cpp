#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
const int Max_N = 100050;
struct UnionFind{
    int ans, par[Max_N], rank[Max_N], num[Max_N];
    inline void init(int n){
        ans = 1;
        for (int i = 1; i < Max_N; i++){
            par[i] = i;
            rank[i] = 0;
            num[i] = 1;
        }
    }
    inline int find(int x){
        while (x != par[x]){
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline void unite(int x, int y){
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]){
            par[x] = y;
            num[y] += num[x];
            num[x] = 0;
            ans = std::max(num[y], x);
        } else {
            par[y] = x;
            num[x] += num[y];
            num[y] = 0;
            ans = std::max(num[x], ans);
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
}rec;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, a, b;
    while (~scanf("%d", &n)){
        rec.init(n);
        for (int i = 0; i < n; i++){
            scanf("%d %d", &a, &b);
            rec.unite(a, b);
        }
        printf("%d\n", rec.ans);
    }
    return 0;
}
