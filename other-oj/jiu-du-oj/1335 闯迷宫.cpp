#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<queue>
using std::queue;
const int N = 110;
const int INF = ~0u >> 1;
struct Node {
    int x, y;
    Node(int _x = 0, int _y = 0) :x(_x), y(_y){}
};
int map[N][N], dist[N][N];
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
void bfs(int n) {
    queue<Node> que;
    Node tp1(0, 0);
    que.push(tp1);
    dist[0][0] = 0;
    while (!que.empty()) {
        tp1 = que.front(); que.pop();
        if (tp1.x == n - 1 && tp1.y == n - 1) {
            printf("%d\n", dist[n - 1][n - 1]);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx = tp1.x + dx[i], ny = tp1.y + dy[i];
            if (nx >= 0 && nx < n  && ny >= 0 && ny < n && map[nx][ny] != 1 && INF == dist[nx][ny]) {
                Node tp2(nx, ny);
                dist[nx][ny] = dist[tp1.x][tp1.y] + 1;
                que.push(tp2);
            }
        }
    }
    puts("-1");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &map[i][j]);
                dist[i][j] = INF;
            }
        }
        if (1 == map[0][0] || 1 == map[n - 1][n - 1]) {
            puts("-1");
            continue;
        }
        bfs(n);
    }
    return 0;
}
