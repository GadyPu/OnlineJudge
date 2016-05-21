#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 51000
typedef struct _seg{
    int val, addMark;
}SegTree;
SegTree seg[Max_N << 2];
int arr[Max_N];
void built(int root, int x, int y){
    seg[root].addMark = 0;
    if (x == y){
        seg[root].val = arr[x];
        return;
    }
    int mid = (x + y) >> 1;
    built(root << 1, x, mid);
    built(root << 1 | 1, mid + 1, y);
    seg[root].val = seg[root << 1].val + seg[root << 1 | 1].val;
}
void pushDown(int root){
    if (seg[root].addMark != 0){
        seg[root << 1].addMark += seg[root].addMark;
        seg[root << 1 | 1].addMark += seg[root].addMark;
        seg[root << 1].val += seg[root].addMark;
        seg[root << 1 | 1].val += seg[root].addMark;
        seg[root].addMark = 0;
    }
}
void update(int root, int _x, int _y, int x, int y, int addVal){
    if (x > _y || y < _x) return;
    if (x <= _x && y >= _y){
        seg[root].addMark += addVal;
        seg[root].val += addVal;
        return;
    }
    pushDown(root);
    int mid = (_x + _y) >> 1;
    update(root << 1, _x, mid, x, y, addVal);
    update(root << 1 | 1, mid + 1, _y, x, y, addVal);
    seg[root].val = seg[root << 1].val + seg[root << 1 | 1].val;
}
int query(int root, int _x, int _y, int x, int y){
    if (x > _y || y < _x) return 0;
    if (x <= _x && y >= _y) return seg[root].val;
    pushDown(root);
    int mid = (_x + _y) >> 1;
    int v1 = query(root << 1, _x, mid, x, y);
    int v2 = query(root << 1 | 1, mid + 1, _y, x, y);
    return v1 + v2;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[100], s1[100];
    int i, t, n, a, b, c = 1;
    scanf("%d", &t);
    while (t--){
        printf("Case %d:\n", c++);
        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &arr[i]);
        built(1, 1, n);
        getchar();
        while (gets(buf) && strcmp(buf, "End") != 0){
            sscanf(buf, "%s %d %d", s1, &a, &b);
            if (0 == strcmp(s1, "Query")) printf("%d\n", query(1, 1, n, a, b));
            else if (0 == strcmp(s1, "Add")) update(1, 1, n, a, a, b);
            else update(1, 1, n, a, a, -b);
        }
    }
    return 0;
}
