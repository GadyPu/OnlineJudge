#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char State[12];
typedef struct _trie{
    int cnt;
    struct _trie *next[10];
}trie, *Trie;
State st[10002];
trie node[1000000];
int sz = 0;
Trie built(){
    Trie T = &node[sz++];
    memset(T, 0, sizeof(trie));
    return T;
}
void insert(Trie T, char *src){
    char *p = src;
    while (*p != '\0'){
        if (T->next[*p - '0'] == NULL) T->next[*p - '0'] = built();
        T = T->next[*p - '0'];
        T->cnt++;
        p++;
    }
}
int search(Trie T, char *src){
    char *p = src;
    while (*p != '\0'){
        if (T == NULL || T->next[*p - '0'] == NULL) return 0;
        T = T->next[*p - '0'];
        p++;
    }
    return T->cnt;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n;
    State rev;
    scanf("%d", &t);
    while (t--){
        sz = 0;
        scanf("%d", &n);
        Trie root = built();
        int k = n, count = 0, flag = 0;
        while (k--){
            scanf("%s", rev);
            strcpy(st[count++], rev);
            insert(root, rev);
        }
        for (k = 0; k < n; k++){
            if (search(root, st[k]) > 1){
                printf("NO\n");
                flag = 1;
                break;
            }
        }
        if(!flag) printf("YES\n");
    }
    return 0;
}
