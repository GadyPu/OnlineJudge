#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
typedef char State[11];  
typedef struct tries_t{  
    State eng;  
    struct tries_t *pNext[26];  
}tries, *Tries;  
tries node[300000];  
int sz = 0;  
Tries root = NULL;  
Tries built(){  
    Tries T = &node[sz++];  
    memset(T, 0, sizeof(tries));  
    return T;  
}  
void insert(Tries T, char *source, char *eng){  
    Tries q = NULL;  
    char *p = source;  
    while (*p != '\0'){  
        int t = *p - 'a';  
        if (T->pNext[t] == NULL){  
            q = built();  
            T->pNext[t] = q;  
            T = q;  
        }  
        else T = T->pNext[t];  
        p++;  
    }  
    strcpy(T->eng, eng);  
}  
void search(Tries T, char *source){  
    char *p = source;  
    while (*p != '\0'){  
        int t = *p - 'a';  
        if (T == NULL || T->pNext[t] == NULL){  
            printf("eh\n");  
            return;  
        }  
        T = T->pNext[t];  
        p++;  
    }  
    printf("%s\n", T->eng);  
}  
int main(){  
    root = built();  
    State buf,eng, fori;  
    while (gets(buf) && buf[0] != '\0') {  
        sscanf(buf, "%s %s", eng, fori);  
        insert(root, fori, eng);  
    }  
    while (gets(fori)) search(root, fori);  
    return 0;  
} 
