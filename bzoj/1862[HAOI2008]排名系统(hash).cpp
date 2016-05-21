#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<map>
using std::min;
using std::pair;
using std::string;
typedef char State[100];
typedef unsigned long long ull;
const int Max_N = 260000;
struct Node{
    int v, s, t, id;
    Node *ch[2];
    inline void
    set(int _v = 0, int _s = 0, int _t = 0, int _id = 0, Node *p = NULL){
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
#define BASE 133
#define MOD 299997
#define MAXN 500000
int now[Max_N], _time[Max_N];
struct HashSet{
    int head[MAXN];
    int tot, next[MAXN];
    ull hash[MAXN];
    char src[Max_N][12];
    inline ull GetHash(char *s){
        ull re = 0;
        while (*s != '\0') re = re * BASE + *s++;
        return re;
    }
    inline int Insert(char *s) {
        ull _hash = GetHash(s);
        int x = _hash % MOD;
        for (int i = head[x]; i; i = next[i]){
            if (hash[i] == _hash) return i;
        }
        next[++tot] = head[x];
        hash[tot] = _hash;
        head[x] = tot;
        strcpy(src[tot], s);
        return tot;
    }
}map;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v;
    sbt.init();
    State s1, buf;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++){
        gets(buf);
        if (buf[0] == '+'){
            sscanf(&buf[1], "%s %d", s1, &v);
            int x = map.Insert(s1);
            if (now[x])    sbt.del(now[x], _time[x]);
            now[x] = v, _time[x] = i;
            sbt.insert(now[x], _time[x], x);
        } else if (buf[0] == '?' && isalpha(buf[1])){
            sscanf(&buf[1], "%s", s1);
            int x = map.Insert(s1);
            printf("%d\n", sbt.find(now[x], _time[x]));
        } else {
            int ed;
            sscanf(&buf[1], "%d", &v);
            ed = min(v + 9, map.tot);
            for (int j = v; j <= ed; j++) {
                printf("%s%c", map.src[sbt.rank(j)], j != ed ? ' ' : '\n');
            }
        }
    }
    return 0;
}
