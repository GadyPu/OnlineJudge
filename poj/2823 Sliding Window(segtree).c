#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 1000010
#define INF 0x7fffffff
#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)>(b)?(b):(a))
typedef struct _seg{
    int min, max;
}SegTree;
SegTree seg[3000000];
int ret[Max_N], min[Max_N], max[Max_N];
void built(int root, int l, int r){
    if (l == r){
        seg[root].min = seg[root].max = ret[l];
        return;
    } else {
        int mid = (l + r) >> 1;
        built(root << 1, l, mid);
        built(root << 1 | 1, mid + 1, r);
        seg[root].max = _max(seg[root << 1].max, seg[root << 1 | 1].max);
        seg[root].min = _min(seg[root << 1].min, seg[root << 1 | 1].min);
    }
}
int query(int root, int _x, int _y, int x, int y, int d){
    int mid, v1, v2;
    if (x > _y || y < _x) return (d == 0 ? INF : -INF);
    if (x <= _x && y >= _y) return (d == 0 ? seg[root].min : seg[root].max);
    mid = (_x + _y) >> 1;
    v1 = query(root << 1, _x, mid, x, y, d);
    v2 = query(root << 1 | 1, mid + 1, _y, x, y, d);
    return (d == 0 ? _min(v1, v2) : _max(v1, v2));
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int i, d, n, k;
    while (~scanf("%d %d", &n, &k)){
        for (i = 1; i <= n; i++) scanf("%d", &ret[i]);
        d = 0, built(1, 1, n);
        for (i = 0; i + k <= n; i++){
            min[d] = query(1, 1, n, i + 1, i + k, 0);
            max[d++] = query(1, 1, n, i + 1, i + k, 1);
        }
        for (i = 0; i < d; i++){
            printf("%d", min[i]);
            if (i < d - 1) printf(" ");
        }
        printf("\n");
        for (i = 0; i < d; i++){
            printf("%d", max[i]);
            if (i < d - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
