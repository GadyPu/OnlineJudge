#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::min;
using std::find;
using std::pair;
using std::swap;
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
const int N = 1000000;
const int INF = 0x3f3f3f3f;
bool vis[N >> 2];
struct Node {
    int s;
    bool mat[4][4];
}que[N];
const int dx[] = { 0, 0, 0, -1, 1, }, dy[] = { 0, -1, 1, 0, 0, };
inline int hash(Node &x) {
    int ret = 0, k = 1;
    rep(i, 4) {
        rep(j, 4) {
            ret += k * x.mat[i][j];
            k <<= 1;
        }
    }
    return (ret + N) % N;
}
void bfs() {
    int lb = 0, ub = 1, v = hash(que[0]);
    if(!v || v == 65535) { puts("0"); return; }
    que[0].s = 1, cls(vis, false), vis[v] = true;
    while(lb != ub) {
        Node &x = que[lb++];
        rep(i, 4) {
            rep(j, 4) {
                Node t = x;
                rep(k, 5) {
                    int nx = dx[k] + i, ny = dy[k] + j;
                    if(nx < 0 || nx > 3 || ny < 0 || ny > 3) continue;
                    t.mat[nx][ny] ^= 1;
                }
                t.s = x.s + 1;
                v = hash(t);
                if(!v || v == 65535) { printf("%d\n", x.s); return; }
                if(vis[v]) continue;
                vis[v] = true;
                que[ub++] = t;
            }
        }
    }
    puts("Impossible");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[10];
    while(~scanf("%s", buf)) {
        rep(i, 4) {
            if(i) scanf("%s", buf);
            rep(j, 4) {
                que[0].mat[i][j] = buf[j] == 'b' ? 1 : 0;
            }
        }
        bfs();
    }
    return 0;
}
