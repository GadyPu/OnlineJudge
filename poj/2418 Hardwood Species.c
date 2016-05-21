#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef char State[33];
State st[1000010];
int cmp(const char* src, const char *_src){
    return strcmp((char *)src, (char *)_src);
}
int main(){
    State ret, buf;
    int i, k, cnt = 0;
    while (gets(ret)) strcpy(st[cnt++], ret);
    qsort(st, cnt, sizeof(st[0]), cmp);
    i = 0;
    while (i < cnt){
        strcpy(buf, st[i]), k = 0;
        for (; 0 == strcmp(buf, st[i]); i++) k++;
        printf("%s %.4lf\n", buf, (double)k * 100 / cnt);
    }
    return 0;
}
