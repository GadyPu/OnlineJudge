#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 1025  
int ret[Max_N];  
void swap(int *a, int *b){  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
int cmp(const void *a, const void *b){  
    return *(int *)a - *(int *)b;  
}  
void print(int n){  
    int i;  
    for (i = 0; i < n - 1; i++) printf("%d ", ret[i]);  
    printf("%d\n", ret[n - 1]);  
}  
void solve(int *list, int n){  
    int i, k = 0, flag = 0;;  
    for (i = n - 1; i >= 0; i--){  
        if (i > 0 && list[i] > list[i - 1]){  
            k = i - 1;  
            break;  
        }  
    }  
    if (0 == k && -1 == i){  
        qsort(list, n, sizeof(list[0]), cmp);  
        return;  
    }  
    for (i = k + 1; i < n; i++){  
        if (list[k] > list[i]){  
            swap(&list[k], &list[i - 1]);  
            flag = 1;  
            break;  
        }  
    }  
    if (!flag) swap(&list[k], &list[n - 1]);  
    qsort(&list[k + 1], n - k - 1, sizeof(list[0]), cmp);  
}  
int main(){  
  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int i, t, n, k;  
    scanf("%d", &t);  
    while (t--){  
        scanf("%d %d", &n, &k);  
        for (i = 0; i < n; i++) scanf("%d", &ret[i]);  
        for (i = 0; i < k; i++) solve(ret, n);  
        print(n);  
    }  
    return 0;  
}  
