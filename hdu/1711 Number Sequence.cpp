#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
const int Max_N = 10004;  
int n, m, next[Max_N], pat[Max_N], text[Max_N * 100];  
void get_next(int *next, int *P){  
    int i, j;  
    for (i = 1, j = next[0] = 0; i < m; i++){  
        while (j > 0 && P[i] != P[j]) j = next[j - 1];  
        if (P[i] == P[j]) j++;  
        next[i] = j;  
    }  
}  
int kmp(int *next, int *P, int *T){  
    int i, j;  
    for (i = j = 0; i < n; i++){  
        while (j > 0 && T[i] != P[j]) j = next[j - 1];  
        if (T[i] == P[j]) j++;  
        if (j == m) return i - m + 2;  
    }  
    return -1;  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int i, t;  
    scanf("%d", &t);  
    while (t--){  
        scanf("%d %d", &n, &m);  
        for (i = 0; i < n; i++) scanf("%d", &text[i]);  
        for (i = 0; i < m; i++) scanf("%d", &pat[i]);  
        get_next(next, pat);  
        printf("%d\n", kmp(next, pat, text));  
    }  
    return 0;  
}  
