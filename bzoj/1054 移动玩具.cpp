#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::min;
using std::sort;
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
bool vis[N];
struct Node {
    int s;
    bool mat[4][4];
}que[N], end;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
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
inline void read(Node &x) {
    char buf[10];
    rep(i, 4) {
        scanf("%s", buf);
        rep(j, 4) {
            x.mat[i][j] = buf[j] - '0';
        }
    }
}
void bfs() {
    int lb = 0, ub = 0, ret, ans;
    ret = hash(que[0]), ans = hash(end);
    if(ret == ans) { puts("0"); return; }
    ub++, cls(vis, false), vis[ret] = true;
    while(lb != ub) {
        Node &x = que[lb++];
        ret = hash(x);
        if(ret == ans) { printf("%d\n", x.s); return; }
        rep(i, 4) {
            rep(j, 4) {
                if(!x.mat[i][j]) continue;
                rep(k, 4) {
                    int nx = dx[k] + i, ny = dy[k] + j;
                    if(nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
                    if(x.mat[nx][ny]) continue;
                    Node &t = que[ub];
                    t = x, t.s = x.s + 1;
                    swap(t.mat[i][j], t.mat[nx][ny]);
                    ret = hash(t);
                    if(vis[ret]) continue;
                    vis[ret] = true;
                    ub++;
                }
            }
        }
    }
    puts("0");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    read(que[0]), read(end);
    bfs();
    return 0;
}
