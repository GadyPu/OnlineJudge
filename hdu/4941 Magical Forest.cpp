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
using std::swap;
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
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
    int x, y, val;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), val(k) {}
    inline bool operator<(const Node &a) const {
        return x == a.x ? y > a.y : x > a.x;
    }
};
set<Node> st;
set<Node>::iterator ite;
map<int, int> x, y;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m, a, b, v, q, k, p = 1;
    scanf("%d", &t);
    while (t--) {
        st.clear(), x.clear(), y.clear();
        scanf("%d %d %d", &n, &m, &k);
        while (k--) {
            scanf("%d %d %d", &a, &b, &v);
            if (x.find(a) == x.end()) x[a] = a;
            if (y.find(b) == y.end()) y[b] = b;
            st.insert(Node(a, b, v));
        }
        printf("Case #%d:\n", p++);
        scanf("%d", &k);
        while (k--) {
            scanf("%d %d %d", &q, &a, &b);
            if (1 == q) {
                if (x.find(a) == x.end()) x[a] = a;
                if (x.find(b) == x.end()) x[b] = b;
                swap(x[a], x[b]);
            } else if (2 == q) {
                if (y.find(a) == y.end()) y[a] = a;
                if (y.find(b) == y.end()) y[b] = b;
                swap(y[a], y[b]);
            } else {
                ite  = st.find(Node(x[a], y[b]));
                printf("%d\n", ite == st.end() ? 0 : ite->val);
            }
        }
    }
    return 0;
}
