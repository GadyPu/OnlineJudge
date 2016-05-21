#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_Szie 50
int a, b, c, ans[Max_Szie], A[Max_Szie], B[Max_Szie], C[Max_Szie];
void convert(){
    int i = 0;
    while (a || b || c){
        A[i] = a % 10;
        a /= 10;
        B[i] = b % 10;
        b /= 10;
        C[i] = c % 10;
        c /= 10;
        i++;
    }
}
void solve(){
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    sizeof(ans, 0, sizeof(ans));
    convert();
    int i, j, k;
    for (i = 3; i < 100; i++){
        k = 0;
        for (j = 0; j < Max_Szie; j++){
            int temp = A[j] + B[j] + C[j] + k;
            k = temp / 10;
            ans[j] = temp % 10;
        }
        memcpy(A, B, sizeof(B));
        memcpy(B, C, sizeof(C));
        memcpy(C, ans, sizeof(ans));
    }
    j = Max_Szie - 1;
    while (!ans[j]) j--;
    for (; j > -1; j--)
        printf("%d", ans[j]);
    printf("\n");
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &a, &b, &c))
        if (!a && !b && !c) puts("0");
        else solve();
    return 0;
}
