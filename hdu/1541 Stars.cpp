#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::vector;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 15100;
typedef unsigned long long ull;
struct Node {
    int v, s, less;
    Node *ch[2];
    inline void setc(int _v, int _s, Node *p) {
        v = _v, s = less = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
};
struct SBT {
    int lev, ans[Max_N];
    Node *root, *null, *tail, stack[Max_N];
    inline void init() {
        tail = &stack[0];
        null = tail++;
        null->setc(0, 0, NULL);
        root = null;
    }
    inline Node *newNode(int v) {
        Node *p = tail++;
        p->setc(v, 1, null);
        return p;
    }
    inline void rotate(Node *&x, bool d) {
        Node *k = x->ch[!d]; x->ch[!d] = k->ch[d]; k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        if (!d) k->less += x->less;
        else x->less -= k->less;
        x = k;
    }
    inline void Maintain(Node *&x, bool d) {
        if (!x->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) rotate(x, !d);
        else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) rotate(x->ch[d], d), rotate(x, !d);
        else return;
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node *&o, int v) {
        if (!o->s) { o = newNode(v); return; }
        if (v >= o->v) lev += o->less;
        if (v <= o->v) o->less++;
        if (v == o->v) return;
        o->s++;
        insert(o->ch[v > o->v], v);
        o->push_up();
        Maintain(o, v > o->v);
    }
    inline void work(int n) {
        init();
        int x, y;
        cls(ans, 0);
        rep(i, n) {
            lev = 0;
            scanf("%d %d", &x, &y);
            insert(root, x);
            ans[lev]++;
        }
        rep(i, n) printf("%d\n", ans[i]);
    }
}sbt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        sbt.work(n);
    }
    return 0;
}
