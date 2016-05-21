#include<stdio.h>  
#include<string.h>  
char buf[2001];  
int rec(int n){  
    if (n < 10) return n;  
    else{  
        int res = 0;  
        do{  
            res += n % 10;  
        } while (n /= 10);  
        return rec(res);  
    }  
}  
void solve(){  
    int i = 0, res = 0, n = strlen(buf);  
    for (i = 0; i < n; i++) res += buf[i] - '0';  
    printf("%d\n",rec(res));  
}  
int main(){  
    while (gets(buf) && buf[0] != '0')  
        solve();  
} 
