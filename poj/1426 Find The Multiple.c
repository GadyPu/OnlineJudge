#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#define Max_N 1000  
typedef char State[104];  
typedef struct node_t{ State st; }node;  
node Queue[Max_N],cur,now;  
int vis[220];  
int mod(char *str,int n)  
{  
    int i, res = 0, len = strlen(str);  
    for (i = 0; i < len; i++){  
        res = (res * 10 + str[i] - '0') % n;  
    }  
    return res;  
}  
void bfs(int n)  
{  
    char buf[3];  
    memset(vis, 0, sizeof(vis));  
    int i, rear = 0, front = 0;  
    now.st[0] = '1', now.st[1] = '\0';  
    Queue[rear++] = now;  
    while (front < rear){  
        now = Queue[front++];  
        if (!mod(now.st, n)) break;  
        for (i = 0; i < 2; i++){  
            sprintf(buf, "%d", i);  
            strcpy(cur.st, now.st);  
            strcat(cur.st, buf);  
            int res = mod(cur.st, n);  
            if (!vis[res]){  
                vis[res] = 1;  
                Queue[rear++] = cur;  
            }  
        }  
    }  
    printf("%s\n",now.st);  
}  
int main()  
{  
    int n;  
    while (EOF != scanf("%d", &n) && n != 0)  
        bfs(n);  
    return 0;  
} 
