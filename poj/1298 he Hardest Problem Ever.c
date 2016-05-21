#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
char buf[200];  
int table[26];  
void init(){  
    int i;  
    memset(table, 0, sizeof(table));  
    for (i = 0; i < 26; i++){  
        if (i - 5 < 0) table[i] = 26 + i - 5;  
        else table[i] = i - 5;  
    }  
}  
int main()  
{  
#ifdef LOCAL  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w+", stdout);  
#endif  
    init();  
    int i, n;  
    while (gets(buf) && strcmp(buf,"ENDOFINPUT")!=0){  
        if (0 == strcmp(buf, "START") || 0 == strcmp(buf, "END")) continue;  
        else{  
            n = strlen(buf);  
            for (i = 0; i < n; i++){  
                if (buf[i] >= 'A' && buf[i] <= 'Z') printf("%c", 'A' + table[buf[i] - 'A']);  
                else printf("%c", buf[i]);  
            }  
        }  
        printf("\n");  
    }  
    return 0;  
}  
