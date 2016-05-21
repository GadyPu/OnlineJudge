#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 11  
typedef int State[Max_N];  
State st[Max_N],ret;  
int dfs(int *list,int cur,int n,int sum){  
    int i,j;  
    if(cur==n){  
        memset(st,0,sizeof(st));  
        memcpy(&st[0],list,sizeof(ret));  
        for(i=1;i<n;i++){  
            for(j=0;j<n-i;j++)  
                st[i][j]=st[i-1][j]+st[i-1][j+1];  
        }  
        if(sum == st[n-1][0]){  
            for(i=0;i<n;i++) printf("%d ",st[0][i]);  
            printf("\n");  
            return 0;  
        }  
    }else{  
        for(i=1;i<=n;i++){  
            int flag=1;  
            for(j=0;j<cur;j++) { if(i == list[j]) flag=0; }  
            if(flag){  
                list[cur]=i;  
                if(!dfs(list,cur+1,n,sum))  
                    return 0;  
            }  
        }  
    }  
    return 1;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int N,sum;  
    while(EOF!=scanf("%d %d",&N,&sum))  
    {  
        memset(ret,0,sizeof(ret));  
        dfs(ret,0,N,sum);  
    }  
    return 0;  
}  
