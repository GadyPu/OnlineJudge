#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
const int Max_N = 100004;  
char text[Max_N * 10], pat[Max_N];  
int next[Max_N];  
void get_next(int *next, char *P){  
    int i, j, m = strlen(P);  
    for (i = 1, j = next[0] = 0; i < m; i++){  
        while (j > 0 && P[i] != P[j]) j = next[j - 1];  
        if (P[i] == P[j]) j++;  
        next[i] = j;  
    }  
}  
void kmp(int *next, char *P, char *T){  
    int i, j, cnt = 0, n = strlen(T), m = strlen(P);  
    for (i = j = 0; i < n; i++){  
        while (j > 0 && T[i] != P[j]) j = next[j - 1];  
        if (T[i] == P[j]) j++;  
        if (j == m) cnt++;  
    }  
    printf("%d\n", cnt);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int t;  
    scanf("%d", &t);  
    while (t--){  
        scanf("%s %s", pat, text);  
        get_next(next, pat);  
        kmp(next, pat, text);  
    }  
    return 0;  
}  
