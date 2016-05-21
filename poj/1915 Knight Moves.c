#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define N 300 + 2  
#define INF 0x7fffff  
typedef struct node  
{  
    int x, y;  
}Node;  
Node Queue[100000], cur, now;  
int table[N][N], Dirct[N][N];  
void Init()  
{  
    memset(table, 0, sizeof(table));  
    memset(Queue, 0, sizeof(Queue));  
}  
void bfs(int size, int Sx, int Sy, int Dx, int Dy)  
{  
    int i, j, nx, ny, rear = 0, front = 0;  
    int dx[8] = { 1, 2, 1, 2, -1, -2, -1, -2 };  
    int dy[8] = { -2, -1, 2, 1, 2, 1, -2, -1 };  
    for (i = 0; i < size; i++)  
    {  
        for (j = 0; j < size; j++)  
            Dirct[i][j] = INF;  
    }  
    now.x = Sx, now.y = Sy;  
    Queue[rear++] = now;  
    Dirct[Sx][Sy] = 0;  
    while (front < rear)  
    {  
        now = Queue[front++];  
        if (now.x == Dx && now.y == Dy)  
            break;  
        for (i = 0; i < 8; i++)  
        {  
            nx = now.x + dx[i], ny = now.y + dy[i];  
            if (nx >= 0 && nx < size && ny >= 0 && ny < size && INF == Dirct[nx][ny])  
            {  
                Dirct[nx][ny] = Dirct[now.x][now.y] + 1;  
                cur.x = nx, cur.y = ny;  
                Queue[rear++] = cur;  
            }  
        }  
    }  
    printf("%d\n", Dirct[Dx][Dy]);  
}  
void solve()  
{  
    Init();  
    int size, Dx, Dy, Sx, Sy;  
    scanf("%d %d %d %d %d", &size, &Sx, &Sy, &Dx, &Dy);  
    bfs(size, Sx, Sy, Dx, Dy);  
}  
int main()  
{  
    int t;  
    scanf("%d", &t);  
    while (t--)  
        solve();  
    return 0;  
}  
