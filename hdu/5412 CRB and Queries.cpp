#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
#define lc root<<1
#define rc root<<1|1
const int N = 100010;
const int INF = 0x3f3f3f3f;
struct Node {
    int v, s, c;
    Node *ch[2];
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + c;
    }
    inline void setc(int _v, int _s, Node *p) {
        v = _v, s = c = _s, ch[0] = ch[1] = p;
    }
    inline int cmp(int x) const {
        if (x == v) return -1;
        return x > v;
    }
};
int sum, arr[N];
struct SBT {
    int top;
    Node *null, *tail, *pool[N], stack[N << 5], *ptr[N << 2];
    inline void init(int n) {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->setc(0, 0, NULL);
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        seg_built(1, 1, n);
    }
    inline Node *newNode(int v) {
        Node *p = !top ? tail++ : pool[--top];
        p->setc(v, 1, null);
        return p;
    }
    inline void rotate(Node *&x, int d) {
        Node *k = x->ch[!d]; x->ch[!d] = k->ch[d]; k->ch[d] = x;
        k->s = x->s; x->push_up(); x = k;
    }
    inline void Maintain(Node *&x, int d) {
        if (!x->ch[d]->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) rotate(x, !d);
        else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) rotate(x->ch[d], d), rotate(x, !d);
        else  return;
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node* &x, int key) {
        if (!x->s) { x = newNode(key); return; }
        int d = x->cmp(key);
        x->s++;
        if (-1 == d) { x->c++; return; }
        insert(x->ch[d], key);
        x->push_up();
        Maintain(x, d);
    }
    inline void erase(Node* &x, int key){
    if (!x->s) return;
    int d = x->cmp(key);
    x->s--;
    if (-1 == d) {
        if (x->c > 1) {
            x->c--;
        } else if (!x->ch[0]->s || !x->ch[1]->s) {
            pool[top++] = x;
            x = x->ch[0]->s ? x->ch[0] : x->ch[1];
        } else {
            Node *ret = x->ch[1];
            for (; ret->ch[0]->s; ret = ret->ch[0]);
            erase(x->ch[1], x->v = ret->v);
        }
    } else {
        erase(x->ch[d], key);
    }
    if (x->s) x->push_up();
}
    inline int sbt_rank(Node *x, int key) {
        int t, cur = 0;
        for (; x->s;) {
            t = x->ch[0]->s;
            if (key < x->v) x = x->ch[0];
            else if (key >= x->v) cur += x->c + t, x = x->ch[1];
        }
        return cur;
    }
    inline void seg_built(int root, int l, int r) {
        ptr[root] = null;
        for (int i = l; i <= r; i++) insert(ptr[root], arr[i]);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_built(lc, l, mid);
        seg_built(rc, mid + 1, r);
    }
    inline void seg_query(int root, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            sum += sbt_rank(ptr[root], val);
            return;
        }
        int mid = (l + r) >> 1;
        seg_query(lc, l, mid, x, y, val);
        seg_query(rc, mid + 1, r, x, y, val);
    }
    inline void seg_modify(int root, int l, int r, int pos, int val) {
        if (pos > r || pos < l) return;
        erase(ptr[root], arr[pos]);
        insert(ptr[root], val);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_modify(lc, l, mid, pos, val);
        seg_modify(rc, mid + 1, r, pos, val);
    }
    inline void kth(int n, int a, int b, int k) {
        int l = 0, r = INF;
        while (l < r) {
            sum = 0;
            int mid = (l + r) >> 1;
            seg_query(1, 1, n, a, b, mid);
            if (sum < k) l = mid + 1;
            else r = mid;
        }
        printf("%d\n", l);
    }
    inline void solve(int n) {
        init(n);
        int m, a, b, c, k;
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &a);
            if (2 == a) {
                scanf("%d %d %d", &b, &c, &k);
                kth(n, b, c, k);
            } else {
                scanf("%d %d", &b, &c);
                seg_modify(1, 1, n, b, c);
                arr[b] = c;
            }
        }
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        go.solve(n);
    }
    return 0;
}
