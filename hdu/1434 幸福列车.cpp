#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::string;
using std::vector;
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
const int N = 10010;
typedef unsigned long long ull;
struct Node {
    int rp;
    string name;
    Node(int i = 0, string j = "") :rp(i), name(j) {}
    inline bool operator<(const Node &a) const {
        return rp == a.rp ? name < a.name : rp > a.rp;
    }
};
priority_queue<Node> que[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[22],tmp[22];
    int n, m, rp, xi, xj;
    while (~scanf("%d %d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &xi);
            while (xi--) {
                scanf("%s %d", buf, &rp);
                que[i].push(Node(rp, buf));
            }
        }
        while (m--) {
            scanf("%s", buf);
            if (!strcmp(buf, "GETON")) {
                scanf("%d %s %d", &xi, tmp, &rp);
                que[xi].push(Node(rp, tmp));
            } else if (!strcmp(buf, "JOIN")) {
                scanf("%d %d", &xi, &xj);
                while (!que[xj].empty()) {
                    que[xi].push(que[xj].top());
                    que[xj].pop();
                }
            } else {
                scanf("%d", &xi);
                printf("%s\n", que[xi].top().name.c_str());
                que[xi].pop();
            }
        }
        rep(i, n + 1) while (!que[i].empty()) que[i].pop();
    }
    return 0;
}
