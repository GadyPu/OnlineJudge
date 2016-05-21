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
const int N = 100010;
typedef unsigned long long ull;
struct UnionFind {
    bool vis[N];
    int par[N], rank[N];
    inline void init(int n) {
        rep(i, n) {
            par[i] = i;
            vis[i] = false, rank[i] = 0;
        }
    }
    inline int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
        return true;
    }
    inline void work(int a, int b, bool &f) {
        vis[a] = vis[b] = true;
        if (!unite(a, b)) f = false;
    }
    inline void judge() {
        int cnt = 0;
        rep(i, N) {
            // 题目给出的并不一定是只有一个集合，它可能给出多个集合，彼此并不联通 
            if (vis[i] && par[i] == i) cnt++; 
        }
        puts(1 == cnt ? "Yes" : "No");
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b;
    while (~scanf("%d %d", &a, &b) && a + b != -2) {
        if (!a && !b){ printf("Yes\n"); continue; }
        bool f = true;
        go.init(N);
        while (a || b) {
            go.work(a, b, f);
            scanf("%d %d", &a, &b);
        }
        if (!f) { puts("No"); continue; }
        go.judge();
    }
    return 0;
}
