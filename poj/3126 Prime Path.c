#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define INF 0x7ffffff  
#define N 10000 + 2  
int PrimeTable[N], Queue[N << 1], Drict[N];  
int IsPrime(int n)  
{  
    int i;  
    for (i = 2; i*i <= n; i++)  
    if (0 == n % i)  
        return 0;  
    return 1 != n;  
}  
void Init()  
{  
    int i;  
    memset(PrimeTable, 0, sizeof(PrimeTable));  
    for (i = 1000; i <= 10000; i++)  
    {  
        if (IsPrime(i))  
            PrimeTable[i] = 1;  
    }  
}  
void bfs(int start, int end)  
{  
    int i, j, cur, now, rear = 0, front = 0, flag = 1;;  
    if (!PrimeTable[start] || !PrimeTable[end])  
        flag = 0;  
    char buf[5] = { 0 };  
    for (i = 0; flag & 1, i < N; i++)  
        Drict[i] = INF;  
    Queue[rear++] = start;  
    Drict[start] = 0;  
    while (front < rear && flag)  
    {  
        now = Queue[front++];  
        if (now == end)  
            break;  
        for (j = 3; j >= 0; j--)  
        {  
            sprintf(buf, "%d", now);  
            for (i = 0; i <= 9; i++)  
            {  
                buf[j] = i + '0';  
                int nx = atoi(buf);  
                if (PrimeTable[nx] && nx < N && INF == Drict[nx])  
                {  
                    cur = nx;  
                    Drict[cur] = Drict[now] + 1;  
                    Queue[rear++] = cur;  
                }  
            }  
        }  
    }  
    if (INF == Drict[end] || !flag)  
        printf("Impossible\n");  
    else  
        printf("%d\n", Drict[end]);  
}  
void solve()  
{  
    int n1, n2;  
    scanf("%d %d", &n1, &n2);  
    bfs(n1, n2);  
}  
int main()  
{  
    Init();  
    int t;  
    scanf("%d", &t);  
    while (t--)  
        solve();  
    return 0;  
}  
