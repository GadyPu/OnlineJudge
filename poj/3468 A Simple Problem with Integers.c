#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
typedef long long ll;
typedef struct _seg{
    ll val, addMark;
}SegTree;
SegTree seg[Max_N << 2];
void built(ll root, ll x, ll y){
    seg[root].addMark = 0;
    if (x == y){
        scanf("%lld", &seg[root].val);
        return;
    } else {
        ll mid = (x + y) >> 1;
        built(root << 1, x, mid);
        built(root << 1 | 1, mid + 1, y);
        seg[root].val = seg[root << 1].val + seg[root << 1 | 1].val;
    }
}
void pushDown(ll root, ll len){
    if (seg[root].addMark != 0){
        seg[root << 1].addMark += seg[root].addMark;
        seg[root << 1 | 1].addMark += seg[root].addMark;
        seg[root << 1].val += (len - (len >> 1)) * seg[root].addMark;
        seg[root << 1 | 1].val += (len >> 1) * seg[root].addMark;
        seg[root].addMark = 0;
    }
}
void update(ll root, ll _x, ll _y, ll x, ll y, ll val){
    if (x > _y || y < _x) return;
    if (x <= _x  && _y <= y){
        seg[root].addMark += val;
        seg[root].val += val * (_y - _x + 1);
        return;
    }
    pushDown(root, _y - _x + 1);
    ll mid = (_x + _y) >> 1;
    update(root << 1, _x, mid, x, y, val);
    update(root << 1 | 1, mid + 1, _y, x, y, val);
    seg[root].val = seg[root << 1].val + seg[root << 1 | 1].val;
}
ll query(ll root, ll _x, ll _y, ll x, ll y){
    if (x > _y || y < _x) return 0;
    if (x <= _x  && _y <= y) return seg[root].val;
    pushDown(root, _y - _x + 1);
    ll mid = (_x + _y) >> 1;
    ll v1 = query(root << 1, _x, mid, x, y);
    ll v2 = query(root << 1 | 1, mid + 1, _y, x, y);
    return v1 + v2;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char ch;
    ll a, b, c, N, Q;
    while (~scanf("%lld %lld", &N, &Q)){
        built(1, 1, N);
        while (Q--){
            getchar();
            scanf("%c", &ch);
            if ('Q' == ch){
                scanf("%lld %lld", &a, &b);
                printf("%lld\n", query(1, 1, N, a, b));
            } else {
                scanf("%lld %lld %lld", &a, &b, &c);
                update(1, 1, N, a, b, c);
            }
        }
    }
    return 0;
}
