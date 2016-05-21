#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define INF 0x7ffffff  
#define N 100000 + 10  
int Queue[N << 1], path[N];  
void bfs(int n, int k)  
{  
    int i, nx, now, rear = 0, front = 0;  
    int dx[] = { -1, 1 };  
    for (i = 0; i < N; i++)  
        path[i] = INF;  
    path[n] = 0;  
    Queue[rear++] = n;  
    while (front < rear)  
    {  
        now = Queue[front++];  
        if (now == k)  
            break;  
        for (i = 0; i < 3; i++)  
        {  
            if (i < 2)  
                nx = now + dx[i];  
            else  
                nx = now << 1;  
            if (nx >= 0 && nx < N && INF == path[nx])  
            {  
                path[nx] = path[now] + 1;  
                Queue[rear++] = nx;  
            }  
        }  
    }  
    printf("%d\n", path[k]);  
}  
void solve(int n, int k)  
{  
    if (n > k)  
    {  
        printf("%d\n", n - k);  
        return;  
    }  
    memset(Queue, 0, sizeof(Queue));  
    memset(path, 0, sizeof(path));  
    bfs(n, k);  
}  
int main()  
{  
    int n, k;  
    while (EOF != scanf("%d %d", &n, &k))  
        solve(n, k);  
    return 0;  
}  
