#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 5000  
typedef struct node_t{ int from, to, cost; }edge;  
edge es[Max_N];  
int V,E,par[Max_N], rank[Max_N];  
void init(int n){  
    int i;  
    for (i = 0; i < n; i++){  
        par[i] = i;  
        rank[i] = 0;  
    }  
}  
int find(int x){  
    if (x == par[x]) return x;  
    else return par[x] = find(par[x]);  
}  
void unite(int x, int y){  
    x = find(x), y = find(y);  
    if (x == y) return;  
    if (rank[x] < rank[y]) par[x] = y;  
    else{  
        par[y] = x;  
        if (rank[x] == rank[y]) rank[x]++;  
    }  
}  
int same(int x, int y){  
    return find(x) == find(y);  
}  
int cmp(const void *a, const *b){  
    edge t = *(edge *)a, _t = *(edge *)b;  
    return t.cost - _t.cost;  
}  
int kruskal(){  
    init(V);  
    qsort(es, E, sizeof(es[0]), cmp);  
    int i, res = 0;  
    for (i = 0; i<E; i++){  
        edge e = es[i];  
        if (!same(e.from, e.to)){  
            unite(e.from, e.to);  
            res += e.cost;  
        }  
    }  
    return res;  
}  
int main()  
{  
#ifdef LOCAL  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w+", stdout);  
#endif  
    char ch;  
    int i,a,b,c;  
    while (EOF != scanf("%d", &V) && 0 != V){  
        scanf("%d", &E);  
        for (i = 0; i < E; i++){  
            scanf("%d %d %d", &a, &b, &c);  
            es[i] = (edge){ --a, --b, c };  
        }  
        printf("%d\n", kruskal());  
        scanf("%c", &ch);  
    }  
    return 0;  
}  
