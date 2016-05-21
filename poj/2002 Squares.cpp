#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::abs;
using std::sort;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 40007;
const int INF = 0x3f3f3f3f;
struct P {
    int x, y;
    P() {}
    P(int i , int j) :x(i), y(j) {}
    inline bool operator<(const P &k) const {
        return x == k.x ? y < k.y : x < k.x;
    }
}A[N];
struct Hash_Set {
    int tot, head[N];
    struct edge { int x, y, next; }G[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void insert(P &k) {
        int u = abs(k.x + k.y) % N;
        G[tot] = (edge){ k.x, k.y, head[u] }; head[u] = tot++;
    }
    inline bool find(P k) {
        int u = abs(k.x + k.y) % N;
        for(int i = head[u]; ~i; i = G[i].next) {
            edge &e = G[i];
            if(k.x == e.x && k.y == e.y) return true;
        }
        return false;
    }
}hash;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, x1, x2, x3, x4, y1, y2, y3, y4, ans;
    while(~scanf("%d", &n), n) {
        hash.init();
        rep(i, n) {
            scanf("%d %d", &A[i].x, &A[i].y);
            hash.insert(A[i]);
        }
        sort(A, A + n);
        ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                x1 = A[i].x, y1 = A[i].y;
                x2 = A[j].x, y2 = A[j].y;
                x3 = y1 - y2 + x1, y3 = x2 - x1 + y1;
                x4 = y1 - y2 + x2, y4 = x2 - x1 + y2;
                if(hash.find(P(x3, y3)) && hash.find(P(x4, y4))) ans++;
            }
        }
        printf("%d\n", ans >> 1);
    }
    return 0;
}
