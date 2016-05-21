#include <stdio.h>  
#include <string.h>  
char buf[1000002];  
void solve(){  
    int i,j,n=strlen(buf);  
    for(i=1;i<=n/2;i++){  
        if(0 == n % i){  
            for(j=0;j<n;j+=i)  
                if(0!=strncmp(buf,buf+j,i)) break;  
        }  
        if(j == n) break;  
    }  
    printf("%d\n",n/i);  
}  
int main()  
{  
    while(EOF!=scanf("%s",buf) && 0 != strcmp(buf,"."))  
        solve();  
    return 0;  
}  
