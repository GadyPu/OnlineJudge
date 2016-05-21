#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define  N 5  
#define INF 0x7ffffff  
typedef struct node{ int x, y; }Node;  
Node cur, now, fa[N][ N], Queue[N << 5];  
int maze[N][N], Drict[N][N],last_dir[N][N],dir[N * N];  
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };  
void read(){  
    int i, j;  
    for (i = 0; i < N; i++){  
        for (j = 0; j < N; j++)  
            scanf("%d", &maze[i][j]);  
    }  
}  
void bfs(int x, int y){  
    int i, j, nx, ny, rear = 0, front = 0;  
    for (i = 0; i < N; i++){  
        for (j = 0; j < N; j++)  
            Drict[i][j] = INF;  
    }  
    Drict[x][x] = 0;  
    cur.x = x, cur.y = x;  
    Queue[rear++] = cur;  
    while (front < rear){  
        now = Queue[front++];  
        if (y == now.x && y == now.y)  
            break;  
        for (i = 0; i < 4; i++){  
            nx = now.x + dx[i], ny = now.y + dy[i];  
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && INF == Drict[nx][ny] && 1!= maze[nx][ny]){  
                cur = (Node){ nx, ny };  
                Drict[nx][ny] = Drict[now.x][now.y] + 1;  
                fa[nx][ny] = now;  
                Queue[rear++] = cur;  
                last_dir[nx][ny] = i;  
            }  
        }  
    }  
}  
void print_path(int x, int y){  
    int i, c = 0;  
    while (1){  
        int fx = fa[x][y].x, fy = fa[x][y].y;  
        if (fx == x && fy == y)  
            break;  
        dir[c++] = last_dir[x][y];  
        x = fx, y = fy;  
    }  
    x = y = 0;  
    printf("(0, 0)\n");  
    while (c--){  
        for (i = 0; i<4; i++){  
            if (i == dir[c]){  
                printf("(%d, %d)\n", x += dx[i], y += dy[i]);  
                break;  
            }  
        }  
    }  
}  
void solve(){  
    memset(Queue, 0, sizeof(Queue));  
    bfs(0, 4);  
    print_path(4, 4);  
}  
int main()  
{  
    read();  
    solve();  
    return 0;  
}  
