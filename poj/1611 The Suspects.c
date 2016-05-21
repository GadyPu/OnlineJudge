#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 30040  
int par[Max_N], rank[Max_N];  
void init(int n){  
    int i;  
    for (i = 0; i < n; i++){  
        par[i] = i;  
        rank[i] = 1;  
    }  
}  
int find(int x){  
    if (x == par[x]) return x;  
    else return par[x] = find(par[x]);  
}  
void unite(int x, int y){  
    x = find(x), y = find(y);  
    if (x == y) return;  
    if (rank[x] >= rank[y]){  
        par[y] = x;  
        rank[x] += rank[y];  
    } else {  
        par[x] = y;  
        rank[y] += rank[x];  
    }  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int n, m, t, l, p, k;  
    while (~scanf("%d %d", &n, &m)){  
        if (0 == n && 0 == m) break;  
        init(n);  
        while (m--){  
            scanf("%d %d", &t, &k);  
            l = t;  
            for (l = 1; l < t; l++){  
                scanf("%d", &p);  
                unite(k, p);  
            }  
        }  
        printf("%d\n", rank[par[0]]);  
    }  
    return 0;  
}  
