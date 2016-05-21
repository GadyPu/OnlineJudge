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
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
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
const int Max_N = 1010;
typedef unsigned long long ull;
struct UnionFind {
    bool exit[Max_N];
    int par[Max_N], rank[Max_N];
    inline void init(int n) {
        rep(i, n + 1) {
            par[i] = i;
            rank[i] = 0;
            exit[i] = false;
        }
    }
    inline int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) {
            par[x] = y;
            exit[x] = true;
        } else {
            par[y] = x;
            exit[y] = true;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    inline void result(int n) {
        int tot = -1;
        rep(i, n + 1) if (!exit[i]) tot++;
        printf("%d\n", tot);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        go.init(n);
        rep(i, m) scanf("%d %d", &a, &b), go.unite(a, b);
        go.result(n);
    }
    return 0;
}
