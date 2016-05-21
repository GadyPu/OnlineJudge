#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
using std::vector;
const int Max_N = 60010;
struct Node {
    int idx;
    Node *next[10];
    void set() {
        idx = 0;
        for (int i = 0; i < 10; i++) next[i] = NULL;
    }
};
struct Trie {
    int l;
    char text[Max_N], buf[64];
    Node stack[Max_N * 10], *root, *tail;
    inline void link(char *src) {
        for (int j = 0; src[j] != '\0'; j++) text[l++] = src[j];
        text[l] = '\0';
    }
    void init(){
        l = 0;
        tail = &stack[0];
        root = tail++;
        root->set();
    }
    inline Node *newNode() {
        Node *p = tail++;
        p->set();
        return p;
    }
    inline void insert(Node *x, char *src, int idx) {
        char *p = src;
        while (*p != '\0') {
            if (!x->next[*p - '0']) x->next[*p - '0'] = newNode();
            x = x->next[*p - '0'];
            p++;
        }
        x->idx = idx;
    }
    inline int query(Node *x, char *src) {
        char *p = src;
        while (*p != '\0') {
            if (x->idx) return x->idx;
            if (!x || !x->next[*p - '0']) return -1;
            x = x->next[*p - '0'];
            p++;
        }
        return -1;
    }
    inline void insert(char *src, int idx) {
        insert(root, src, idx);
    }
    inline int query(char *src) {
        return query(root, src);
    }
    inline  void gogo() {
        vector<int> res;
        for (int i = 0; text[i] != '\0'; i++) {
            int ret = query(text + i);
            if (ret != -1) res.push_back(ret);
        }
        int n = res.size();
        if (n) {
            printf("Found key: ");
            for (int i = 0; i < n; i++) {
                printf("[Key No. %d]%c", res[i], i < n - 1 ? ' ' : '\n');
            }
        } else {
            puts("No key can be found !");
        }
    }
}solve;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    char buf[64];
    while (~scanf("%d %d", &n, &m)) {
        solve.init();
        while (n--) {
            scanf("%s", buf);
            solve.link(buf);
        }
        getchar(); getchar();
        for (int i = 1; i <= m; i++) {
            gets(buf);
            solve.insert(strchr(buf, ']') + 2, i);
        }
        solve.gogo();
    }
    return 0;
}
