#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
typedef char State[24];  
typedef struct _trie{  
    int cnt;  
    struct _trie *next[26];  
}trie, *Trie;  
State st[1020];  
trie node[200000];  
int sz = 0, count = 0;  
Trie built(){  
    Trie T = &node[sz++];  
    memset(T, 0, sizeof(trie));  
    return T;  
}  
void insert(Trie T, char *src){  
    char *p = src;  
    while (*p != '\0'){  
        if (T->next[*p - 'a'] == NULL) T->next[*p - 'a'] = built();  
        T = T->next[*p - 'a'];  
        T->cnt++;  
        p++;  
    }  
}  
int search(Trie T, char *src){  
    char *p = src;  
    while (*p != '\0'){  
        if (T == NULL || T->next[*p - 'a'] == NULL) return 0;  
        T = T->next[*p - 'a'];  
        p++;  
    }  
    return T->cnt;  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    Trie root = built();  
    State ret, temp;  
    while (~scanf("%s", ret)){   
        insert(root, ret);   
        strcpy(st[count++], ret);  
    }  
    int i, t = 0;  
    while (t < count){  
        int n = strlen(st[t]);  
        for (i = 0; i < n; i++){  
            strncpy(temp, st[t], (i + 1) * sizeof(char));  
            temp[i + 1] = '\0';  
            if (1 == search(root, temp) || n == i + 1){  
                printf("%s %s\n", st[t], temp);  
                break;  
            }  
        }  
        t++;  
    }  
    return 0;  
}  
