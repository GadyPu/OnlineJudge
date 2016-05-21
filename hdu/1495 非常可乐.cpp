#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::queue;
using std::vector;
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
const int Max_N = 110;
typedef unsigned long long ull;
bool vis[Max_N][Max_N][Max_N];
int N, M, S;
struct Node {
    int x, y, z, s;
    Node(int i = 0, int j = 0, int k = 0, int l = 0) :x(i), y(j), z(k), s(l) {}
};
inline bool judge(const Node &q) {
    int t = S >> 1;
    if (q.x == t && q.y == t) return true;
    if (q.x == t && q.z == t) return true;
    if (q.y == t && q.x == t) return true;
    if (q.y == t && q.z == t) return true;
    if (q.z == t && q.y == t) return true;
    if (q.z == t && q.x == t) return true;
    return false;
}
int bfs() {
    if (S & 1) return 0;
    int v;
    cls(vis, false);
    queue<Node> q;
    q.push(Node(S, 0, 0, 0));
    vis[S][0][0] = true;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (judge(t)) return t.s;
        if (t.x > 0 && t.y < N) {
            v = N - t.y;
            if (v < t.x && !vis[t.x - v][N][t.z]) {
                q.push(Node(t.x - v, N, t.z, t.s + 1));
                vis[t.x - v][N][t.z] = true;
            } else {
                if (t.x + t.y <= N && !vis[0][t.x + t.y][t.z]) {
                    q.push(Node(0, t.x + t.y, t.z, t.s + 1));
                    vis[0][t.x + t.y][t.z] = true;
                }
            }
        }
        if (t.x > 0 && t.z < M) {
            v = M - t.z;
            if (v < t.x && !vis[t.x - v][t.y][M]) {
                q.push(Node(t.x - v, t.y, M, t.s + 1));
                vis[t.x - v][t.y][M] = true;
            } else {
                if (t.z + t.x <= M && !vis[0][t.y][t.z + t.x]) {
                    q.push(Node(0, t.y, t.x + t.z, t.s + 1));
                    vis[0][t.y][t.x + t.z] = true;
                }
            }
        }
        if (t.y > 0 && t.x < S) {
            v = S - t.x;
            if (v < t.y && !vis[S][t.y - v][t.z]) {
                q.push(Node(S, t.y - v, t.z, t.s + 1));
                vis[S][t.y - v][t.z] = true;
            } else {
                if (t.x + t.y <= S && !vis[t.x + t.y][0][t.z]) {
                    q.push(Node(t.x + t.y, 0, t.z, t.s + 1));
                    vis[t.x + t.y][0][t.z] = true;
                }
            }
        }
        if (t.y > 0 && t.z < M) {
            v = M - t.z;
            if (v < t.y && !vis[t.x][t.y - v][M]) {
                q.push(Node(t.x, t.y - v, M, t.s + 1));
                vis[t.x][t.y - v][M] = true;
            } else {
                if (t.z + t.y <= M && !vis[t.x][0][t.z + t.y]) {
                    q.push(Node(t.x, 0, t.z + t.y, t.s + 1));
                    vis[t.x][0][t.z + t.y] = true;
                }
            }
        }
        if (t.z > 0 && t.y < N) {
            v = N - t.y;
            if (v < t.z && !vis[t.x][N][t.z - v]) {
                q.push(Node(t.x, N, t.z - v, t.s + 1));
                vis[t.x][N][t.z - v] = true;
            } else {
                if (t.y + t.z <= N && !vis[t.x][t.y + t.z][0]) {
                    q.push(Node(t.x, t.z + t.y, 0, t.s + 1));
                    vis[t.x][t.z + t.y][0] = true;
                }
            }
        }
        if (t.z > 0 && t.x < S) {
            v = S - t.x;
            if (v < t.z && !vis[S][t.y][t.z - v]) {
                q.push(Node(S, t.y, t.z - v, t.s + 1));
                vis[S][t.y][t.z - v] = true;
            } else {
                if (t.x + t.z <= S && !vis[t.x + t.z][t.y][0]) {
                    q.push(Node(t.x + t.z, t.y, 0, t.s + 1));
                    vis[t.x + t.z][t.y][0] = true;
                }
            }
        }
    }
    return 0;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &S, &N, &M) && S + M + N) {
        int res = bfs();
        if (!res) puts("NO");
        else printf("%d\n", res);
    }
    return 0;
}
