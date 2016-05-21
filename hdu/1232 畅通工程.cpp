#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::vector;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 1; i <= (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
typedef unsigned long long ull;
struct UnionFind {
    int par[N], rank[N];
    inline void init(int n) {
        rep(i, n) {
            par[i] = i;
            rank[i] = 0;
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
        if (rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    inline void result(int n) {
        int tot = 0;
        rep(i, n) { if (par[i] == i) tot++; }
        printf("%d\n", tot - 1);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, a, b;
    while (~scanf("%d", &n) && n) {
        go.init(n);
        scanf("%d", &m);
        rep(i, m) scanf("%d %d", &a, &b), go.unite(a, b);
        go.result(n);
    }
    return 0;
}
