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
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
using std::multimap;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 100100;
typedef unsigned long long ull;
struct Node {
    int v;
    Node *ch[2];
    inline void setc(int _v, Node *p) {
        v = _v;
        ch[0] = ch[1] = p;
    }
};
struct BST {
    Node *root, *null, *tail;
    Node stack[Max_N];
    inline void init() {
        tail = &stack[0];
        null = tail++;
        null->setc(0, NULL);
        root = null;
    }
    inline Node *newNode(int v) {
        Node *p = tail++;
        p->setc(v, null);
        return p;
    }
    inline void insert(Node *&x, int v) {
        if (x == null) { x = newNode(v); return; }
        insert(x->ch[v > x->v], v);
    }
    inline void dfs(vector<int> &res, Node *x) {
        if (x != null) {
            res.pb(x->v);
            dfs(res, x->ch[0]);
            dfs(res, x->ch[1]);
        }
    }
    inline void insert(int v) {
        insert(root, v);
    }
    inline void go() {
        vector<int> res;
        dfs(res, root);
        int n = sz(res);
        rep(i, n) printf("%d%c", res[i], i < n - 1 ? ' ' : '\n');
    }
}bst;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v;
    while (~scanf("%d", &n)) {
        bst.init();
        rep(i, n) scanf("%d", &v), bst.insert(v);
        bst.go();
    }
    return 0;
}
