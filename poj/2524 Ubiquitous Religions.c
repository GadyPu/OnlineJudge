#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 50002  
int N,M,par[Max_N],rank[Max_N];  
void init(int n)  
{  
    int i;  
    for(i=1;i<=n;i++)  
    {  
        par[i]=i;  
        rank[i]=0;  
    }  
}  
int find(int x)  
{  
    if(x == par[x]) return x;  
    else return par[x]=find(par[x]);  
}  
void unite(int x,int y)  
{  
    x=find(x),y=find(y);  
    if(x == y) return;  
    if(rank[x] < rank[y]) {  
        par[x]=y;  
    } else {  
        par[y]=x;  
        if(rank[x] == rank[y]) rank[x]++;  
    }  
}  
int same(int x,int y)  
{  
    return find(x) == find(y);  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int i,a,b,n=0;  
    while(EOF !=scanf("%d %d",&N,&M) && 0!=N && 0!=M)  
    {  
        init(N);  
        int count=0;  
        for(i=0;i<M;i++)  
        {  
            scanf("%d %d",&a,&b);  
            if(!same(a,b)) { unite(a,b),count++; };  
        }  
        printf("Case %d: %d\n",++n,N-count);  
    }  
    return 0;  
}  
