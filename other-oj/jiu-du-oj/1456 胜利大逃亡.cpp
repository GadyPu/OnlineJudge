#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Max_N 1000000
typedef struct _node{
    int x, y, z;
}node;
node cur, Queue[Max_N];
int A, B, C, T, map[52][52][52], dist[52][52][52];
int dx[] = { 1, -1, 0, 0, 0, 0 }, dy[] = { 0, 0, 1, -1, 0, 0 }, dz[] = { 0, 0, 0, 0, 1, -1 };
int bfs(){
    int i, rear = 0, front = 0;
    memset(dist, -1, sizeof(dist));
    dist[0][0][0] = 0;
    Queue[rear++] = (node){ 0, 0, 0 };
    while (front < rear){
        cur = Queue[front++];
        if (cur.x == A - 1 && cur.y == B - 1 && cur.z == C - 1) return dist[cur.x][cur.y][cur.z];
        for (i = 0; i < 6; i++){
            int nx = dx[i] + cur.x, ny = dy[i] + cur.y, nz = dz[i] + cur.z;
            if (nx >= 0 && nx < A && ny >= 0 && ny < B && nz >= 0 && nz < C && -1 == dist[nx][ny][nz] && !map[nx][ny][nz]){
                dist[nx][ny][nz] = dist[cur.x][cur.y][cur.z] + 1;
                Queue[rear++] = (node){ nx, ny, nz };
            }
        }
    }
    return -1;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, i, j, k;
    scanf("%d", &t);
    while (t--){
        scanf("%d %d %d %d", &A, &B, &C, &T);
        for (i = 0; i < A; i++){
            for (j = 0; j < B; j++){
                for (k = 0; k < C; k++)
                    scanf("%d", &map[i][j][k]);
            }
        }
        if (map[A - 1][B - 1][C - 1]) printf("-1\n");
        else{
            int ret = bfs();
            if (-1 == ret || ret > T) printf("-1\n");
            else printf("%d\n", ret);
        }
    }
    return 0;
}
