#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 400000  
typedef struct trie_t{  
    int cnt;  
    struct trie_t *next[26];  
}trie, *Trie;  
trie node[Max_N];  
int sz = 0, flag = 0;  
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
    char buf[20];  
    Trie root = built();  
    while (gets(buf)){  
        if (!flag && buf[0] != '\0') insert(root, buf);  
        else if (buf[0] == '\0') flag = 1;  
        else printf("%d\n", search(root, buf));  
    }  
    return 0;  
}  
