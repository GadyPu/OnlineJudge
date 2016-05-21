#include<stdio.h>  
int sz, heap[15];  
void push(int x){  
    int i = sz++;  
    while (i > 0){  
        int p = (i - 1) >> 1;  
        if (heap[p] >= x) break;  
        heap[i] = heap[p];  
        i = p;  
    }  
    heap[i] = x;  
}  
int pop(){  
    int i = 0,ret=heap[0], x = heap[--sz];  
    while ((i << 1) + 1 < sz){  
        int a = (i << 1) + 1, b = (i << 1) + 2;  
        if (b < sz && heap[a] <= heap[b]) a = b;  
        if (heap[a] <= x) break;  
        heap[i] = heap[a];  
        i = a;  
    }  
    heap[i] = x;  
    return ret;  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int t, x, n, cnt;  
    scanf("%d", &t);  
    while (t--){  
        sz = 0, n = 10;  
        scanf("%d", &cnt);  
        while (n--){  
            scanf("%d", &x);  
            push(x);  
        }  
        pop(), pop();  
        printf("%d %d\n", cnt, pop());  
    }  
    return 0;  
}  
