#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::set;
using std::pair;
using std::vector;
using std::multiset;
using std::priority_queue;
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
    int fix, pos;
    Node(int i = 0, int j = 0) :fix(i), pos(j) {}
    inline friend bool operator<(const Node &a, const Node &b) {
        return a.fix == b.fix ? a.pos > b.pos : a.fix > b.fix;
    }
};
priority_queue<Node> que[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[10];
    int n, id, fix;
    while (~scanf("%d", &n)) {
        int pos = 1;
        rep(i, n) {
            scanf("%s", buf);
            if (buf[0] == 'R') {
                scanf("%d %d", &id, &fix);
                que[id].push(Node(fix, pos++));
            } else {
                scanf("%d", &id);
                if (que[id].empty()) { puts("No one fits!"); continue; }
                Node t = que[id].top(); que[id].pop();
                printf("%s gets Num %d: %d %d!\n", buf, t.pos, id, t.fix);
            }
        }
        rep(i, N) while (!que[i].empty()) que[i].pop();
     }
    return 0;
}
