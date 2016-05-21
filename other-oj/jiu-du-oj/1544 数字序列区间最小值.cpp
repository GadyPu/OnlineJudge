#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using std::min;
const int Max_N = 101000;
const int INF = 0x7fffffff;
struct SegTree{
    struct Node{
        int v;
    }seg[Max_N << 2];
    void init(int n){
        built(1, 1, n);
    }
    inline void built(int root, int l, int r){
        if (l == r){
            scanf("%d", &seg[root].v);
            return;
        }
        int mid = (l + r) >> 1;
        built(root << 1, l, mid);
        built(root << 1 | 1, mid + 1, r);
        seg[root].v = min(seg[root << 1].v, seg[root << 1 | 1].v);
    }
    inline int query(int root, int l, int r, int x, int y){
        if (x > r || y < l) return INF;
        if (x <= l && y >= r){
            return seg[root].v;
        }
        int mid = (l + r) >> 1;
        int v1 = query(root << 1, l, mid, x, y);
        int v2 = query(root << 1 | 1, mid + 1, r, x, y);
        return min(v1, v2);
    }
    inline void gogo(int n){
        int m, a, b;
        scanf("%d", &m);
        while (m--){
            scanf("%d %d", &a, &b);
            printf("%d\n", query(1, 1, n, a, b));
        }
    }
}sg;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)){
        sg.init(n), sg.gogo(n);
    }
    return 0;
}
