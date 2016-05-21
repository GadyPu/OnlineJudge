#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
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
const int N = 100001;
const int INF = 0x3f3f3f3f;
int vis[10], sum[N + 10];
void init() {
    int v, j;
    sum[0] = 0;
    for(int i = 1; i <= N; i++) {
        v = i;
        bool f = true;
        cls(vis, 0);
        do vis[v % 10]++; while(v /= 10);
        for(j = 0; j < 10; j++) {
            if(vis[j] > 1) { f = false; break;}
        }
        sum[i] = sum[i - 1] + f;
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    int t, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &x, &y);
        printf("%d\n", sum[y] - sum[x - 1]);
    }
    return 0;
}
