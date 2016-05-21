#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
using std::cin;
using std::swap;
using std::vector;
const int Max_N = 1010;
struct Node {
    int v, rev;
    Node *fa, *ch[2];
    inline void set(int _v, Node *p) {
        v = _v, rev = 0;
        fa = ch[0] = ch[1] = p;
    }
    inline void link(Node *x, bool d) {
        ch[d] = x;
        x->fa = this;
    }
    inline void update() {
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    inline void push_down() {
        if (rev != 0) {
            ch[0]->update();
            ch[1]->update();
            rev ^= 1;
        }
    }
};
struct BinaryTree {
    Node *root, *null, *tail, *ptr[Max_N], stack[Max_N];
    void init() {
        tail = &stack[0];
        null = tail++;
        null->set(0, NULL);
        root = null;
    }
    inline Node *newNode(int v) {
        Node *p = tail++;
        p->set(v, null);
        return p;
    }
    inline void gogo(int n) {
        char c;
        int i, v, a, b;
        for (i = 1; i <= n; i++) {
            scanf("%d", &v);
            ptr[i] = newNode(v);
        }
        for (i = 1; i <= n; i++) {
            cin >> c;
            if (c == 'd'){
                scanf("%d %d", &a, &b);
                ptr[i]->link(ptr[a], 0);
                ptr[i]->link(ptr[b], 1);
            } else if (c == 'l') {
                scanf("%d", &a);
                ptr[i]->link(ptr[a], 0);
            } else if (c == 'r') {
                scanf("%d", &b);
                ptr[i]->link(ptr[b], 1);
            }
            if (ptr[i]->fa == null) root = ptr[i];
        }
    }
    inline void PreOder(Node *x, vector<int> &res) {
        if (x != null) {
            x->push_down();
            res.push_back(x->v);
            PreOder(x->ch[0], res);
            PreOder(x->ch[1], res);
        }
    }
    inline void PreOder() {
        vector<int> res;
        if (root == null) {
            puts("NULL");
            return;
        }
        root->update();
        PreOder(root, res);
        int n = res.size();
        for (int i = 0; i < n; i++) {
            printf("%d%c", res[i], i < n - 1 ? ' ' : '\n');
        }
    }
}tree;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        tree.init();
        tree.gogo(n);
        tree.PreOder();
    }
    return 0;
}
