#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
using std::queue;
using std::vector;
using std::cin;
const int Max_N = 1100;
struct Node{
    int v;
    Node *f, *ch[2];
    inline void set(int _v = 0, Node *p = NULL){
        v = _v, f = ch[0] = ch[1] = p;
    }
    inline void link(Node *x, bool d){
        ch[d] = x;
        x->f = this;
    }
};
struct BinaryTree{
    Node *tail, *root, *null;
    Node stack[Max_N], *ptr[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
    }
    inline Node *newNode(int v){
        Node *p = tail++;
        p->set(v, null);
        return p;
    }
    inline void gogo(int n){
        char c;
        int i, v, a, b;
        for (i = 1; i <= n; i++){
            scanf("%d", &v);
            ptr[i] = newNode(v);
        }
        for (i = 1; i <= n; i++){
            cin >> c;
            if (c == 'd'){
                scanf("%d %d", &a, &b);
                ptr[i]->link(ptr[a], 0);
                ptr[i]->link(ptr[b], 1);
            } else if (c == 'l'){
                scanf("%d", &a);
                ptr[i]->link(ptr[a], 0);
            } else if (c == 'r'){
                scanf("%d", &b);
                ptr[i]->link(ptr[b], 1);
            } else {
                ;
            }
            if (ptr[i]->f == null) root = ptr[i];
        }
    }
    inline void bfs(){
        queue<Node *> que;
        vector<int> ans;
        que.push(root);
        while (!que.empty()){
            Node *x = que.front();
            que.pop();
            ans.push_back(x->v);
            if (x->ch[0] != null) que.push(x->ch[0]);
            if (x->ch[1] != null) que.push(x->ch[1]);
        }
        int n = ans.size();
        for (int i = 0; i < n; i++){
            printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
        }
    }
}tree;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)){
        tree.init(), tree.gogo(n), tree.bfs();
    }
    return 0;
}
