#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
const int Max_N = 100000;
struct Node{
    int cnt;
    Node *next[2];
    inline void set(){
        cnt = 0;
        for (int i = 0; i < 2; i++) next[i] = NULL;
    }
};
struct Trie{
    Node stack[Max_N], *root, *tail;
    void init(){
        tail = &stack[0];
        root = tail++;
        root->set();
    }
    inline Node *newNode(){
        Node *p = tail++;
        p->set();
        return p;
    }
    inline void insert(Node *x, char *src){
        char *p = src;
        while (*p != '\0'){
            if (!x->next[*p - '0']) x->next[*p - '0'] = newNode();
            x = x->next[*p - '0'];
            x->cnt++;
            p++;
        }
    }
    inline int query(Node *x, char *src){
        char *p = src;
        while (*p != '\0'){
            if (!x || !x->next[*p - '0']) return 0;
            x = x->next[*p - '0'];
            p++;
        }
        return x->cnt;
    }
    inline void insert(char *src){
        insert(root, src);
    }
    inline int query(char *src){
        return query(root, src);
    }
}trie;
char ret[20][200], buf[200];
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    trie.init();
    int i, n = 0, k = 1, flag = 1;
    while (~scanf("%s", buf)){
        if (0 != strcmp(buf, "9")){
            trie.insert(buf);
            strcpy(ret[n++], buf);
        } else if (0 == strcmp(buf, "9")){
            flag = 0;
            for (i = 0; i < n; i++){
                if (trie.query(ret[i]) > 1){
                    printf("Set %d is not immediately decodable\n", k++);
                    flag = 1;
                    break;
                }
            }
            if (!flag) printf("Set %d is immediately decodable\n", k++);
            n =  0, flag = 1;
            trie.init();
        }
    }
    return 0;
}
