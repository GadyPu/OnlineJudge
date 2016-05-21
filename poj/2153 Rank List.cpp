#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
using std::cin;
using std::map;
using std::string;
map<string, int> ret;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    string buf;
    int n, m, v, tmp;
    while (cin >> n) {
        getchar();
        for (int i = 0; i < n; i++) {
            getline(cin, buf);
            ret[buf] = 0;
        }
        cin >> m;
        while (m--) {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                cin >> v;
                getchar();
                getline(cin, buf);
                ret[buf] += v;
            }
            tmp = ret["Li Ming"];
            map<string, int>::iterator ite;
            for (ite = ret.begin(); ite != ret.end(); ++ite) {
                if (ite->second > tmp) ans++;
            }
            printf("%d\n", ans + 1);
        }
        ret.clear();
    }
    return 0;
}


#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
typedef char State[35];
char *target = "Li Ming";
const int Max_N = 11000;
struct Node {
    State name;
    int data, s;
    bool color;
    Node *fa, *ch[2];
    inline void set(int _v, char *src, bool _color, int i, Node *p) {
        data = _v, color = _color, s = i;
        fa = ch[0] = ch[1] = p;
        strcpy(name, src);
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(char *src) const {
        if (0 == strcmp(src, name)) return -1;
        else if (-1 == strcmp(src, name)) return 0;
        return 1;
    }
};
struct RedBlackTree {
    Node *root, *null;
    Node stack[Max_N], *tail;
    void init() {
        tail = &stack[0];
        null = tail++;
        null->set(0, "", 0, 0, NULL);
        root = null;
    }
    inline Node *newNode(char *name, int v) {
        Node *p = tail++;
        p->set(v, name, 1, 1, null);
        return p;
    }
    inline void rotate(Node* &x, bool d) {
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if (y->ch[d] != null) y->ch[d]->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        y->s = x->s;
        x->push_up();
    }
    inline void insert(char *name, int v = 0) {
        int d = 0;
        Node *x = root, *y = null;
        while (x->s) {
            x->s++;
            d = x->cmp(name);
            y = x, x = x->ch[d];
        }
        x = newNode(name, v);
        if (y != null) { d = x->cmp(y->name), y->ch[!d] = x; }
        else root = x;
        x->fa = y;
        insert_fix(x);
    }
    inline void insert_fix(Node* &x) {
        while (x->fa->color){
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if (uncle->color) {
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if (x == par->ch[d]) {
                rotate(x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(Gp, d);
            }
        }
        root->color = 0;
    }
    inline Node *find(Node *x, char *name) {
        while (x->s) {
            int d = x->cmp(name);
            if (-1 == d) break;
            x = x->ch[d];
        }
        return x;
    }
    inline void Modify(char *str, int v) {
        Node* ret = find(root, str);
        ret->data += v;
    }
    inline void dfs(Node *x, int v, int &ans) {
        if (x != null){
            dfs(x->ch[0], v, ans);
            if (x->data > v) ans++;
            dfs(x->ch[1], v, ans);
        }
    }
    inline void query() {
        int cnt = 0, ans = 0;
        int v = find(root, target)->data;
        dfs(root, v, ans);
        printf("%d\n", ans + 1);
    }
}rbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[100];
    int n, m, val;
    while (~scanf("%d\n", &n)) {
        rbt.init();
        for (int i = 0; i < n; i++) {
            gets(buf);
            rbt.insert(buf);
        }
        scanf("%d\n", &m);
        while (m--) {
            for (int i = 0; i < n; i++) {
                gets(buf);
                sscanf(buf, "%d", &val);
                rbt.Modify(strchr(buf, ' ') + 1, val);
            }
            rbt.query();
        }
    }
    return 0;
}
