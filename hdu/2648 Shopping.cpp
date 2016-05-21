#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include<algorithm>
typedef char State[35];
char *target = "memory";
const int Max_N = 11000;
struct Node{
    State name;
    int v, s;
    Node *ch[2];
    inline void
    set(int _v = 0, char *src = "", int _s = 0,Node *p = NULL){
        ch[0] = ch[1] = p;
        v = _v, s = _s, strcpy(name, src);
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(char *src) const{
        if (0 == strcmp(src, name)) return -1;
        else if (-1 == strcmp(src, name)) return 0;
        return 1;
    }
};
struct SizeBalanceTree{
    Node *tail, *null, *root;
    Node stack[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
    }
    inline Node *newNode(char *name, int v){
        Node *p = tail++;
        p->set(v, name, 1, null);
        return p;
    }
    inline void rotate(Node* &x, int d){
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    inline void Maintain(Node* &x, int d){
        if (x->ch[d] == null) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s){
            rotate(x, !d);
        } else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s){
            rotate(x->ch[d], d), rotate(x, !d);
        } else {
            return;
        }
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node* &x, char *name, int v){
        if (x == null){
            x = newNode(name, v);
            return;
        } else {
            x->s++;
            int d = x->cmp(name);
            insert(x->ch[d], name, v);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline Node *Modify(Node *x, char *name){
        if (x == null) return null;
        int d = x->cmp(name);
        if (-1 == d) return x;
        else return Modify(x->ch[d], name);
    }
    inline void insert(char *str, int v = 0){
        insert(root, str, v);
        return;
    }
    inline void Modify(char *str, int v){
        Node* ret = Modify(root, str);
        ret->v += v;
    }
    inline void dfs(Node *x, int v, int &ans){
        if (x != null){
            dfs(x->ch[0], v, ans);
            if (x->v > v) ans++;
            dfs(x->ch[1], v, ans);
        }
    }
    inline void query(){
        int cnt = 0, ans = 0;
        int v = Modify(root, target)->v;
        dfs(root, v, ans);
        printf("%d\n", ans + 1);
    }
}sbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[100];
    int n, m, val;
    while (~scanf("%d", &n)){
        sbt.init();
        for (int i = 0; i < n; i++){
            scanf("%s", buf);
            sbt.insert(buf);
        }
        scanf("%d", &m);
        while (m--){
            for (int i = 0; i < n; i++){
                scanf("%d %s", &val, buf);
                sbt.Modify(buf, val);
            }
            sbt.query();
        }
    }
    return 0;
}
