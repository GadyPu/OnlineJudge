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
const int N = 30;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
char buf[11000];
struct Node {
    char dat;
    int w;
    Node *ch[2];
    Node(char _dat_, int _w_, Node *l = NULL, Node *r = NULL) {
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
};
struct Hoffmancode {
    int sum;
    Node *root;
    priority_queue<Node> q;
    inline char to_lower(char ch) {
            return ch >= 'A' && ch <= 'Z' ? ch + 32 : ch;
    }
    inline void CreateHoffmanTree() {
        Node *l = NULL, *r = NULL;
        while (!q.empty() && q.size() != 1) {
            l = new Node(q.top()); q.pop();
            r = new Node(q.top()); q.pop();
            Node ret(0, l->w + r->w, l, r);
            q.push(ret);
        }
        if (!q.empty()) {
            root = new Node(q.top()); q.pop();
        }
    }
    inline void CreateHoffmanCode(Node *x, string str) {
        if (!x) return;
        if (x->dat != 0) {
            sum += (str.length() * x->w);
        }
        CreateHoffmanCode(x->ch[0], str + "0");
        CreateHoffmanCode(x->ch[1], str + "1");
    }
    inline void solve() {
        sum = 0, root = NULL;
        int arr[N] = { 0 }, tot = 0, n = strlen(buf);
        while (!q.empty()) q.pop();
        for (int i = 0; i < n; i++) {
            arr[to_lower(buf[i]) - '_']++;
        }
        for (int i = 0; i < 28; i++) {
            if (arr[i]) {
                tot++;
                Node ret('_' + i, arr[i]);
                q.push(ret);
            }
        }
        if (1 == tot) {
            printf("%d %d 8.0\n", n * 8, n);
            return;
        }
        CreateHoffmanTree();
        CreateHoffmanCode(root, "");
        printf("%d %d %.1lf\n", n * 8, sum, (double)(n * 8) / sum);
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%s", buf) && 0 != strcmp(buf, "END")) {
        work.solve();
    }
    return 0;
}
