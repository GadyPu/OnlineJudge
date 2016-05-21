#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
const int Max_N = 100050;
struct UnionFind{
    int par[Max_N], rank[Max_N];
    inline void init(int n){
        for (int i = 1; i <= n; i++){
            par[i] = i;
            rank[i] = 0;
        }
    }
    inline int find(int x){
        while (x != par[x]){
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline void unite(int x, int y){
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]){
            par[x] = y;
        } else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
};
struct Node{
    int v, npl;
    Node *ch[2];
    inline void set(int _v = 0, int _npl = -1, Node *p = NULL){
        v = _v, npl = _npl;
        ch[0] = ch[1] = p;
    }
    inline void push_up(){
        npl = ch[1]->npl + 1;
    }
};
struct LeftistTree{
    int N, top;
    UnionFind rec;
    Node *tail, *null;
    Node stack[Max_N], *ptr[Max_N], *store[Max_N];
    void init(int n){
        tail = &stack[0];
        null = tail++;
        null->set();
        N = n, top = 0, rec.init(n);
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 0, null);
        return p;
    }
    inline Node* Merge(Node* &x, Node* &y){
        if (x == null) return y;
        if (y == null) return x;
        if (y->v > x->v) std::swap(x, y);
        x->ch[1] = Merge(x->ch[1], y);
        if (x->ch[1]->npl > x->ch[0]->npl)
            std::swap(x->ch[0], x->ch[1]);
        x->push_up();
        return x;
    }
    inline int get_max(int i){
        return ptr[i]->v;
    }
    inline void insert(){
        int v;
        for (int i = 1; i <= N; i++){
            scanf("%d", &v);
            ptr[i] = newNode(v);
        }
    }
    inline void del(int i){
        int ret = get_max(i);
        Node *x = newNode(ret >> 1);
        store[top++] = ptr[i];
        ptr[i] = Merge(ptr[i]->ch[0], ptr[i]->ch[1]);
        ptr[i] = Merge(ptr[i], x);
    }
    inline void gogo(int a, int b){
        int ans = 0;
        a = rec.find(a), b = rec.find(b);
        if (a == b){
            printf("-1\n");
            return;
        }
        rec.unite(a, b);
        del(a), del(b);
        if (rec.rank[a] > rec.rank[b]){
            ptr[a] = Merge(ptr[a], ptr[b]);
            ans = ptr[a]->v;
        } else {
            ptr[b] = Merge(ptr[a], ptr[b]);
            ans = ptr[b]->v;
        }
        printf("%d\n", ans);
    }
}lft;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, a, b;
    while (~scanf("%d", &n)){
        lft.init(n), lft.insert();
        scanf("%d", &m);
        while (m--){
            scanf("%d %d", &a, &b);
            lft.gogo(a, b);
        }
    }
    return 0;
}
