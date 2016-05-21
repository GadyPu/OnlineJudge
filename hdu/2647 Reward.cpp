#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::queue;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 10010;
typedef unsigned long long ull;
struct Node {
    int vex, val;
    Node(int i = 0, int j = 0) :vex(i), val(j) {}
};
struct TopSort {
    vector<int> G[N];
    int topNum, inq[N];
    inline void init(int n) {
        topNum = 0;
        cls(inq, 0);
        rep(i, n) G[i].clear();
    }
    inline void built(int m) {
        int a, b;
        rep(i, m) {
            scanf("%d %d", &a, &b);
            --a, --b;
            inq[a]++;
            G[b].push_back(a);
        }
    }
    inline void bfs(int n) {
        int ans = 0;
        queue<Node> q;
        rep(i, n) {
            if (!inq[i]) { q.push(Node(i, 888)); topNum++; }
        }
        while (!q.empty()) {
            Node t = q.front(); q.pop();
            ans += t.val;
            rep(i, sz(G[t.vex])) {
                if (--inq[G[t.vex][i]] == 0) q.push(Node(G[t.vex][i], t.val + 1)), topNum++;
            }
        }
        printf("%d\n", topNum == n ? ans : -1);
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        work.init(n);
        work.built(m);
        work.bfs(n);
    }
    return 0;
}
