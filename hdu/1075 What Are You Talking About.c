#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<ctype.h>  
typedef char State[12];  
typedef struct _trie{  
    State word;  
    struct _trie *next[26];  
}trie, *Trie;  
trie node[900000];  
int sz = 0;  
char buf[3010];  
Trie built(){  
    Trie T = &node[sz++];  
    memset(T, 0, sizeof(trie));  
    return T;  
}  
void insert(Trie T, char *src, char *word){  
    char *p = src;  
    while (*p != '\0'){  
        if (T->next[*p - 'a'] == NULL) T->next[*p - 'a'] = built();  
        T = T->next[*p - 'a'];  
        p++;  
    }  
    strcpy(T->word, word);  
}  
char* search(Trie T, char *src){  
    char *p = src;  
    while (*p != '\0'){  
        if (T == NULL || T->next[*p - 'a'] == NULL) return NULL;  
        T = T->next[*p - 'a'];  
        p++;  
    }  
    return (char *)(T->word);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    State s1, s2;  
    Trie root = built();  
    while (gets(buf)){  
        if (0 == strcmp(buf, "START")) continue;  
        else if (0 == strcmp(buf, "END")) break;  
        else{  
            sscanf(buf, "%s %s", s1, s2);  
            insert(root, s2, s1);  
        }  
    }  
    while (gets(buf)){  
        if (0 == strcmp(buf, "START")) continue;  
        else if (0 == strcmp(buf, "END")) break;  
        else{  
            char *p = NULL;  
            int i, j, n = strlen(buf);  
            for (i = 0; i < n; i++){  
                int k = 0;  
                for (j = i; isalpha(buf[j]) != 0; j++){  
                    s1[k++] = buf[i++];  
                }  
                s1[k] = '\0';  
                p = search(root, s1);  
                if (p != NULL && *p != '\0') printf("%s", p);  
                else printf("%s", s1);  
                printf("%c", buf[i]);  
            }  
        }  
        printf("\n");  
    }  
    return 0;  
}  
