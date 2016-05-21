#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<map>
using std::min;
using std::map;
using std::string;
const int Max_N = 260000;
char src[Max_N][12];
typedef char State[100];
struct Node{
    int v, s, t, id;
    Node *ch[2];
    inline void set(int _v = 0, int _s = 0, int _t = 0, int _id = 0, Node *p = NULL){
        ch[0] = ch[1] = p;
        v = _v, s = _s, t = _t, id = _id;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(int _v, int _t) const{
        if (v == _v){
            return t == _t ? -1 : _t > t;
        }
        return v > _v;
    }
};
struct SizeBalanceTree{
    Node stack[Max_N];
    Node *root, *null, *tail;
    Node *store[Max_N];
    int top;
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
        top = 0;
    }
    inline Node *newNode(int v, int t, int id){
        Node *p = null;
        if (top) p = store[--top];
        else p = tail++;
        p->set(v, 1, t, id, null);
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
    inline void insert(Node* &x, int v, int t, int id){
        if (x == null){
            x = newNode(v, t, id);
            return;
        } else {
            x->s++;
            int d = x->cmp(v, t);
            insert(x->ch[d], v, t, id);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline void del(Node*  &x, int v, int t){
        if (x == null) return;
        x->s--;
        int d = x->cmp(v, t);
        if (-1 == d){
            if (!x->ch[0]->s || !x->ch[1]->s){
                store[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0] != null; ret = ret->ch[0]);
                x->v = ret->v, x->t = ret->t, x->id = ret->id;
                del(x->ch[1], ret->v, ret->t);
            }
        } else {
            del(x->ch[d], v, t);
        }
        if (x != null) x->push_up();
    }
    inline int find(Node *x, int v, int t){
        int k = 0, cur = 0;
        for (; x != null;){
            int d = x->cmp(v, t);
            k = x->ch[0]->s;
            if (-1 == d) break;
            else if (!d) x = x->ch[0];
            else cur += k + 1, x = x->ch[1];
        }
        return cur + k + 1;
    }
    inline int rank(Node *x, int k){
        for (; x != null;){
            int t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x->id;
    }
    inline void insert(int v, int t, int id){
        insert(root, v, t, id);
    }
    inline void del(int v, int t){
        del(root, v, t);
    }
    inline int find(int v, int t){
        return find(root, v, t);
    }
    inline int rank(int k){
        return rank(root, k);
    }
}sbt;
struct node{ 
    int v, t, id; 
    node(){};
    node(int _v, int _t, int _id) :v(_v), t(_t), id(_id){}
};
map<string, node > stri;
void gogo(char *s, int v, int t, int &tot){
    string str(s);
    if (stri.count(str) != 0){
        sbt.del(stri[str].v, stri[str].t);
        stri[str].v = v, stri[str].t = t;
        sbt.insert(v, t, stri[str].id);
        return;
    }
    strcpy(src[++tot], s);
    sbt.insert(v, t, tot);
    node ret(v, t, tot);
    stri[str] = ret;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    sbt.init();
    State s1, buf;
    int n, v, tot = 0;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++){
        gets(buf);
        if (buf[0] == '+'){
            sscanf(&buf[1], "%s %d", s1, &v);
            gogo(s1, v, i, tot);
        } else if (buf[0] == '?' && isalpha(buf[1])){
            sscanf(&buf[1], "%s", s1);
            printf("%d\n", sbt.find(stri[s1].v, stri[s1].t));
        } else {
            int ed;
            sscanf(&buf[1], "%d", &v);
            ed = min(v + 9, tot);
            for (int j = v; j <= ed; j++) {
                printf("%s%c", src[sbt.rank(j)], j != ed ? ' ' : '\n');
            }
        }
    }    
    return 0;
}
