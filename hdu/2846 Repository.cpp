#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using std::set;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100010;
const int INF = 0x3f3f3f3f;
struct Node {
    Node *ch[26];
    int cnt;
    int f;
    Node() {
        rep(i, 26) ch[i] = NULL;
        cnt = 0;
        f = -1;
    }
}*root;
void insert(Node *x, char *str, int f) {
    int d = 0;
    char *p = str;
    while (*p != '\0') {
        d = *p - 'a';
        if (!x->ch[d]) x->ch[d] = new Node();
        x = x->ch[d];
        if (x->f != f) {
            x->f = f;
            x->cnt++;
        }
        p++;
    }
}
int query(Node *x, char *str) {
    char *p = str;
    while (*p != '\0') {
        if (!x || !x->ch[*p - 'a']) return 0;
        x = x->ch[*p - 'a'];
        p++;
    }
    return x->cnt;
}
void built(int t) {
    int n;
    char buf[100];
    rep(i, t) {
        scanf("%s", buf);
        n = strlen(buf);
        rep(j, n) {
            insert(root, buf + j, i);
        }
    }
}
void solve(int n) {
    int m;
    char buf[100];
    root = new Node();
    built(n);
    scanf("%d", &m);
    while (m--) {
        scanf("%s", buf);
        printf("%d\n", query(root, buf));
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        solve(n);
    }
    return 0;
}
