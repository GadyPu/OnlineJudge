#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
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
using std::multiset;
using std::multimap;
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
const int Max_N = 100010;
typedef unsigned long long ull;
struct Node {
    int id, f;
    Node(int i = 0, int j = 0) :id(i), f(j) {}
    friend bool operator<(const Node &a, const Node &b) {
        return a.f == b.f ? a.id > b.id : a.f < b.f;
    }
};
priority_queue<Node> que[3];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[10];
    int n, a, b, k;
    while (~scanf("%d", &n)) {
        k = 1;
        rep(i, n) {
            scanf("%s", buf);
            if (buf[0] == 'I') {
                scanf("%d %d", &a, &b);
                que[a - 1].push(Node(k++, b));
            } else {
                scanf("%d", &a);
                if (que[a - 1].empty()) { puts("EMPTY"); continue; }
                printf("%d\n", que[a - 1].top().id); que[a - 1].pop();
            }
        }
        rep(i, 3) {
            while (!que[i].empty()) que[i].pop();
        }
    }
    return 0;
}
