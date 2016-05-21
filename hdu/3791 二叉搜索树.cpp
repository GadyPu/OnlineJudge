#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
using std::vector;
const int Max_N = 100;
struct Node{
    int v;
    Node *ch[2];
    inline void set(int _v = 0, Node *p = NULL){
        v = _v;
        ch[0] = ch[1] = p;
    }
};
struct BinaryTree{
    Node *tail, *root, *null;
    Node stack[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
    }
    inline  Node *newNode(int v){
        Node *p = tail++;
        p->set(v, null);
        return p;
    }
    inline void insert(Node* &x, int v){
        if (x == null){
            x = newNode(v);
            return;
        }
        insert(x->ch[v > x->v], v);
    }
    inline void dfs(Node *x, vector<int> &ans){
        if (x != null){
            ans.push_back(x->v);
            dfs(x->ch[0], ans);
            dfs(x->ch[1], ans);
        }
    }
    inline void insert(int v){
        insert(root, v);
    }
    inline void dfs(vector<int> &ans){
        dfs(root, ans);
    }
    inline void gogo(vector<int> &ans){
        int m;
        char buf[100]; 
        while (getchar() != '\n');
        scanf("%s", buf);
        init(), m = strlen(buf);
        for (int i = 0; i < m; i++) insert(buf[i] - '0');
        dfs(ans);
    }
}tree;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n){
        vector<int> a, b;
        tree.gogo(a);
        for (int i = 0; i < n; i++){
            tree.gogo(b);
            if (a == b) puts("YES");
            else puts("NO");
            b.clear();
        }
    }
    return 0;
}
