#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
typedef char State[40];  
typedef struct tries_t{  
    int flag;  
    struct tries_t *pNext[26];  
}tries, *Tries;  
State ret[50010];  
tries node[200000];  
int sz = 0;  
Tries built(){  
    Tries T = &node[sz++];  
    memset(T, 0, sizeof(tries));  
    return T;  
}  
void insert(Tries T, char *str){  
    char *p = str;  
    while (*p != '\0'){  
        if (T->pNext[*p - 'a'] == NULL){  
            T->pNext[*p - 'a'] = built();  
        }  
        T = T->pNext[*p - 'a'];  
        p++;  
    }  
    T->flag = 1;  
}  
int search(Tries T, char *str){  
    char *p = str;  
    while (*p != '\0'){  
        if (T == NULL || T->pNext[*p - 'a'] == NULL) return 0;  
        T = T->pNext[*p - 'a'];  
        p++;  
    }  
    return T->flag;  
}  
int main(){  
    State buf;  
    Tries root = built();  
    int i, j, count = 0;  
    while (EOF != scanf("%s", buf)) {  
        insert(root, buf);  
        strcpy(ret[count++], buf);  
    }  
    for (i = 0; i < count; i++){  
        int n = strlen(ret[i]);  
        for (j = 1; j < n; j++){  
            State tp1 = { 0 }, tp2 = { 0 };  
            strncpy(tp1, ret[i], j);  
            strncpy(tp2, ret[i] + j, n - j);  
            if (search(root, tp1) && search(root, tp2)){  
                printf("%s\n", ret[i]);  
                break;  
            }  
        }  
    }  
    return 0;  
}  
