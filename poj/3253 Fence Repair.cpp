#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<queue>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::string;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 20010;
const int INF = ~0u>>1;
typedef long long ll;
struct Node {
    ll dat, w;
    Node *ch[2];
    Node() {}
    Node(ll _dat_, ll _w_, Node *l = NULL, Node *r = NULL) {
        dat = _dat_, w = _w_;
        ch[0] = l, ch[1] = r;
    }
    Node(const Node &x) {
        dat = x.dat, w = x.w;
        ch[0] = x.ch[0], ch[1] = x.ch[1];
    }
    inline bool operator<(const Node &x) const {
        return w > x.w;
    }
}A[N];
struct Hoffmancode {
    ll sum;
    Node *root;
    priority_queue<Node> q;
    inline void solve(int n) {
        ll v;
        sum = 0;
        rep(i, n) {
            scanf("%lld", &v);
            A[i] = Node(v, v);
            q.push(A[i]);
        }
        CreateHoffmanTree();
        CreateHoffmanCode(root, "");
        printf("%lld\n", sum);
    }
    inline void CreateHoffmanTree() {
        Node *l = NULL, *r = NULL;
        while (!q.empty() && q.size() != 1) {
            l = new Node(q.top()); q.pop();
            r = new Node(q.top()); q.pop();
            q.push(Node(INF, l->w + r->w, l, r));
        }
        if (1 == q.size()) {
            root = new Node(q.top()); q.pop();
        }
    }
    inline void CreateHoffmanCode(Node *x, string s) {
        if (!x) return;
        if (x->dat != INF) {
            sum += x->dat * s.length();
        }
        CreateHoffmanCode(x->ch[0], s + '0');
        CreateHoffmanCode(x->ch[1], s + '1');
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        work.solve(n);
    }
    return 0;
}
