#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
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
using std::stack;
using std::queue;
using std::vector;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 100010;
typedef unsigned long long ull;
queue<int> que; stack<int> stk;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v, t;
    char buf[10];
    scanf("%d", &t);
    while (t--) {
        scanf("%d %s", &n, buf);
        if ('F' == buf[2]) {
            rep(i, n) {
                scanf("%s", buf);
                if ('I' == buf[0]) scanf("%d", &v), que.push(v);
                else {
                    if (que.empty()) { puts("None"); continue; }
                    printf("%d\n", que.front()), que.pop();
                }
            }
        } else {
            rep(i, n) {
                scanf("%s", buf);
                if ('I' == buf[0]) scanf("%d", &v), stk.push(v);
                else {
                    if (stk.empty()) { puts("None"); continue; }
                    printf("%d\n", stk.top()), stk.pop();
                }
            }
        }
        while (!stk.empty()) stk.pop(); while (!que.empty()) que.pop();
    }
    return 0;
}
