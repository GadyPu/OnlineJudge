#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 0x3f3f3f3f
#define _max(a,b) ((a)>(b)?(a):(b))
typedef struct _node{
    int val, addMark;
}SegTree;
SegTree seg[600000];
int arr[300000];
void built(int root, int istart, int iend){
    seg[root].addMark = 0;
    if (istart == iend){
        seg[root].val = arr[istart];
        return;
    } else {
        int mid = (iend + istart) >> 1;
        built(root << 1, istart, mid);
        built(root << 1 | 1, mid + 1, iend);
        seg[root].val = _max(seg[root << 1].val, seg[root << 1 | 1].val);
    }
}
void pushDown(int root){
    if (seg[root].addMark != 0){
        seg[root << 1].addMark = seg[root].addMark;
        seg[root << 1 | 1].addMark = seg[root].addMark;
        seg[root << 1].val = seg[root].addMark;
        seg[root << 1 | 1].val = seg[root].addMark;
        seg[root].addMark = 0;
    }
}
void update(int root, int nstart, int nend, int ustart, int uend, int addVal){
    if (ustart > nend || uend < nstart) return;
    if (ustart <= nstart && uend >= nend){
        seg[root].addMark = addVal;
        seg[root].val = addVal;
        return;
    }
    pushDown(root);
    int mid = (nstart + nend) >> 1;
    update(root << 1, nstart, mid, ustart, uend,addVal);
    update(root << 1 | 1, mid + 1, nend, ustart, uend, addVal);
    seg[root].val = _max(seg[root << 1].val, seg[root << 1 | 1].val);
}
int query(int root, int nstart, int nend, int qstart, int qend){
    if (qstart > nend || qend < nstart) return -INF;
    if (qstart <= nstart && qend >= nend) return seg[root].val;
    pushDown(root);
    int mid = (nstart + nend) >> 1;
    int v1 = query(root << 1, nstart, mid, qstart, qend);
    int v2 = query(root << 1 | 1, mid + 1, nend, qstart, qend);
    return _max(v1, v2);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char ch;
    int i, n, m, a, b;
    while (~scanf("%d %d", &n, &m)){
        for (i = 1; i <= n; i++) scanf("%d", &arr[i]);
        built(1, 1, n);
        while (m--){
            getchar();
            scanf("%c %d %d", &ch, &a, &b);
            if ('Q' == ch) printf("%d\n", query(1, 1, n, a, b));
            else update(1, 1, n, a, a, b);
        }
    }
    return 0;
}
