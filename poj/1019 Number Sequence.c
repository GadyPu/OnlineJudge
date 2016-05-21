#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <math.h>  
#define Max_N 31280  
typedef long long ll;  
ll ans[Max_N];  
void init()  
{  
    int i;  
    memset(ans,0,sizeof(ans));  
    ans[1]=1;  
    for(i=2;i<Max_N;i++) ans[i]=ans[i-1]+(int)log10(i)+1;  
}  
void solve(int n)  
{  
    int i;  
    ll sum=0;  
    for(i=1;i < Max_N;i++){  
        sum+=ans[i];  
        if(sum >=n) break;  
    }  
    if(sum == n){  
        if(!(int)log10(i)) printf("%d\n",i % 10);  
        else printf("%d\n",i / 10 % 10);  
        return;  
    }  
    for(;;i--){  
        int temp=i;  
        do{  
            sum--;  
            if(sum == n){  
                if(!(int)log10(i)) printf("%d\n",--i % 10);  
                else printf("%d\n",temp / 10 % 10);  
                return;  
            }  
        }while(temp/=10);  
    }  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    init();  
    int n,m;  
    scanf("%d",&n);  
    while(n--){  
        scanf("%d",&m);  
        solve(m);  
    }  
    return 0;  
}  
