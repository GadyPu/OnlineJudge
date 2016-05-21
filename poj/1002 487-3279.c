#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
int ret[Max_N];
int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
int _switch(char ch){
    if (ch == 'A' || ch == 'B' || ch == 'C') return 2;
    else if (ch == 'D' || ch == 'E' || ch == 'F') return 3;
    else if (ch == 'G' || ch == 'H' || ch == 'I') return 4;
    else if (ch == 'J' || ch == 'K' || ch == 'L') return 5;
    else if (ch == 'M' || ch == 'N' || ch == 'O') return 6;
    else if (ch == 'P' || ch == 'R' || ch == 'S') return 7;
    else if (ch == 'T' || ch == 'U' || ch == 'V') return 8;
    else if (ch == 'W' || ch == 'X' || ch == 'Y') return 9;
    return ch - '0';
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[300];
    int t, i, n, cnt, sum, flag = 0, k = 0;
    scanf("%d\n", &t);
    while (t--){
        gets(buf);
        sum = 0;
        for (i = 0; buf[i]!='\0'; i++){
            if (buf[i] >= '0' && buf[i] <= '9' || buf[i] >= 'A' && buf[i] <= 'Z'){
                sum = sum * 10 + _switch(buf[i]);
            }
        }
        ret[k++] = sum;
    }
    i = 0;
    qsort(ret, k, sizeof(ret[0]), cmp);
    while (i < k){
        cnt = 0, n = ret[i];
        for (; n == ret[i]; i++) cnt++;
        if (cnt > 1){
            flag = 1;
            printf("%03d-%04d %d\n", n / 10000, n % 10000, cnt);
        }
    }
    if (!flag) printf("No duplicates.\n");
    return 0;
}
