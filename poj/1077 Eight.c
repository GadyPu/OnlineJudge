#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 400000  
#define Hash_Size 100003  
typedef int State[9];  
State st[Max_N],goal,start;  
typedef struct list{int num;struct list *pNext;}List;  
struct node{int num;struct list *pNext;}HashTable[Hash_Size + 1];  
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};  
int rear,front,sum,dist[Max_N],fa[Max_N],dir[Max_N],last_dir[Max_N];  
char path[5]="udlr",buf[50];  
List *addnode(int num)  
{  
    List *p=(List *)malloc(sizeof(List));  
    p->num=num,p->pNext=NULL;  
    return p;  
}  
int hash(int n)  
{  
    int i;  
    sum=0;  
    for(i=0;i<9;i++) sum = sum * 10 + st[n][i];  
    return sum % Hash_Size;  
}  
  
int exist(int n)  
{  
    int ret=hash(n);  
    if(!HashTable[ret].num){  
        HashTable[ret].num=sum;  
        return 1;  
    } else if (HashTable[ret].num == sum){  
        return 0;  
    } else {  
        List *p=HashTable[ret].pNext;  
        if(p == NULL){  
            HashTable[ret].pNext=addnode(sum);  
        } else {  
            p=HashTable[ret].pNext;  
            while(p->pNext!=NULL){  
                if(p->num == sum) return 0;  
                p=p->pNext;  
            }  
            if(p->num !=sum) p->pNext=addnode(sum);  
            else return 0;  
            }  
        }  
    return 1;  
}  
void bfs()  
{  
    int i,z=0;  
    rear=front=0;  
    memset(dist,-1,sizeof(dist));  
    dist[0]=0;  
    memset(fa,-1,sizeof(fa));  
    memset(last_dir,0,sizeof(last_dir));  
    memset(HashTable,0,sizeof(HashTable));  
    memcpy(&st[rear++],start,sizeof(start));  
    while(front<rear){  
        int *p=(int *)st[front];  
        if(!memcmp(p,goal,sizeof(goal))) break;  
        for(i=0;i<9;i++){ if(!p[i]){ z=i; break; } }  
        int x=z/3,y=z%3;  
        for(i=0;i<4;i++){  
            int nx=x+dx[i],ny=y+dy[i];  
            int nz=nx * 3 + ny;  
            if(nx>=0 && nx<3 && ny>=0 && ny<3){  
                int *np=(int *)st[rear];  
                memcpy(np,p,sizeof(goal));  
                np[z]=np[nz];  
                np[nz]=0;  
                if(exist(rear)){  
                    dist[rear]=dist[front]+1;  
                    fa[rear]=front;  
                    last_dir[rear]=i;  
                    rear++;  
                }  
            }  
        }  
        front++;  
    }  
}  
void print_path()  
{  
    int c=0;  
    if(-1 == dist[front]){  
        printf("unsolvable\n");  
        return;  
    }  
    memset(dir,0,sizeof(dir));  
    while(-1!=fa[front]){  
        dir[c++]=last_dir[front];  
        front=fa[front];  
    }  
    while(c--){  
        printf("%c",path[dir[c]]);  
    }  
    printf("\n");  
}  
void solve()  
{  
    int i=0,j=0,n=strlen(buf);  
    for(i=1;i<=9;i++) goal[i-1]=(i == 9 ? 0 : i);  
    for(i=0;i<n;i++){  
        if(buf[i]>='0' && buf[i]<='8') start[j++]=buf[i]-'0';  
        else if(buf[i] == 'x') start[j++]=0;  
    }  
    bfs();  
    print_path();  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    while(gets(buf))  
        solve();  
    return 0;  
}  
