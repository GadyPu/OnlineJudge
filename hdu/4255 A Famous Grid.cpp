#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 110;
int Sx, Sy, G[N][N];
bool prime[N * N + 10], vis[N][N];
const int dx[] = { 0, 0, -1, 1}, dy[] = { -1, 1, 0, 0 };
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const Node &x) const {
        return s > x.s;
    }
};
bool isPrime(int n) {
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) return false;
    }
    return n != 1;
}
void init() {
    int x = 0, y = 0, tot = N * N;
    G[0][0] = N * N;
    while(tot > 1) {
        while(y + 1 <  N && !G[x][y + 1]) G[x][++y] = --tot;
        while(x + 1 <  N && !G[x + 1][y]) G[++x][y] = --tot;
        while(y - 1 >= 0 && !G[x][y - 1]) G[x][--y] = --tot;
        while(x - 1 >= 0 && !G[x - 1][y]) G[--x][y] = --tot;
    }
    for(int i = 1; i <= N * N; i++) {
        prime[i] = isPrime(i);
    }
}
void bfs(int tar) {
    cls(vis, false);
    priority_queue<Node> q;
    q.push(Node(Sx, Sy, 0));
    vis[Sx][Sy] = true;
    while(!q.empty()) {
        Node t = q.top(); q.pop();
        rep(i, 4) {
            int x = dx[i] + t.x, y = dy[i] + t.y;
            if(x < 0 || x >= N || y < 0 || y >= N) continue;
            if(prime[G[x][y]] || vis[x][y]) continue;
            if(G[x][y] == tar) { printf("%d\n", t.s + 1); return; }
            q.push(Node(x, y, t.s + 1));
            vis[x][y] = true;
        }
    }
    puts("impossible");
}
void solve(int n, int m, int &k) {
    rep(i, N) {
        rep(j, N) {
            if(G[i][j] == n) Sx = i, Sy = j;
        }
    }
    printf("Case %d: ", k++);
    bfs(m);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    int n, m, k = 1;
    while(~scanf("%d %d", &n, &m)) {
        solve(n, m, k);
    }
    return 0;
}
