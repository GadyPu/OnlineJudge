#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define fork(i, k, n) for (int i = (int)k; i <= (int)n; i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 10010;
typedef unsigned long long ull;
struct Node {
    int v, s;
    Node *ch[2];
    inline void setc(int _v, int _s, Node *p) {
        v = _v, s = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
};
struct SBT {
    Node stack[Max_N];
    Node *root, *null, *tail;
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
        x = k;
    }
    inline void Maintain(Node *&x, bool d) {
        if (!x->ch[d]->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) rotate(x, !d);
        else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) rotate(x->ch[d], d), rotate(x, !d);
        else return;
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node *&x, int v) {
        if (!x->s) { x = newNode(v); return; }
        bool d = v > x->v; x->s++;
        insert(x->ch[d], v);
        x->push_up();
        Maintain(x, d);
    }
    inline int kth(int k) {
        int t;
        Node *x = root;
        for (; x->s;) {
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x->v;
    }
    inline void go() {
        vector<int> res;
        int v, q, n, k = 1;
        scanf("%d %d", &q, &n);
        printf("%d %d\n", q, (n + 1) >> 1);
        fork(i, 1, n) {
            scanf("%d", &v);
            insert(root, v);
            if (i & 1) res.push_back(kth((root->s >> 1) + 1));
        }
        n = sz(res);
        rep(i, n) {
            if ((i + 1) % 10) {
                if (i == n - 1) printf("%d\n", res[i]);
                else printf("%d ", res[i]);
            }
            else  printf("%d\n", res[i]);
        }
    }
}sbt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--){
        sbt.init();
        sbt.go();
    }
    return 0;
}
