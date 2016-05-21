#include<cstdio>  
#include<cstdlib>  
#include<ctime>  
#include<iostream>  
#include<algorithm>  
const int Max_N = 100000;  
const double alpha = 0.75;  
struct Node{  
    int v, s;  
    Node *ch[2];  
    inline void set(int _v = 0, int _s = 0, Node *p = NULL){  
        v = _v, s = _s, ch[0] = ch[1] = p;  
    }  
    inline void push_up(){  
        s = ch[0]->s + ch[1]->s + 1;  
    }  
    inline bool isbad(){  
        return s * alpha < std::max(ch[0]->s, ch[1]->s);  
    }  
    inline int cmp(int x) const{  
        return v == x ? -1 : x>v;  
    }  
};  
struct ScapeGoat{  
    Node *tail, *root, *null;  
    Node stack[Max_N], *store[Max_N];  
    int mDepth, mSize, top;  
    double loga;  
    void init(){  
        tail = &stack[0];  
        null = tail++;  
        root = null;  
        top = 0, mSize = 1, loga = log2(1.0 / alpha);  
    }  
    Node *newNode(int v){  
        Node *p = null;  
        if (!top) p = tail++;  
        else p = store[--top];  
        p->set(v, 1, null);  
        return p;  
    }  
    Node *flatten(Node *x, Node *y){  
        if (x == null) return y;  
        x->ch[1] = flatten(x->ch[1], y);  
        return flatten(x->ch[0], x);  
    }  
    Node *built(Node *x, int n){  
        if (!n){  
            x->ch[0] = null;  
            return x;  
        }  
        Node *y = built(x, n >> 1);  
        Node *z = built(y->ch[1], n - 1 - (n >> 1));  
        y->ch[1] = z->ch[0];  
        z->ch[0] = y;  
        y->push_up();  
        return z;  
    }  
    void rebuilt(Node* &x){  
        Node *t = null;  
        t = built(flatten(x, t), x->s);  
        x = t->ch[0];  
    }  
    bool insert(Node* &x, int v, int depth){  
        if (x == null){  
            x = newNode(v);  
            return depth > mDepth;  
        }  
        x->s++;  
        if (!insert(x->ch[v > x->v], v, depth + 1)){  
            if (!x->isbad()) return 1;  
            rebuilt(x);  
        }  
        return 0;  
    }  
    void insert(int v){  
        mDepth = (int)(log2(mSize) / loga);  
        insert(root, v, 1);  
        mSize = std::max(mSize, root->s);  
    }  
    void del(Node* &x, int v){  
        if (x == null) return;  
        x->s--;  
        int d = x->cmp(v);  
        if (-1 == d){  
            if (!x->ch[0]->s || !x->ch[1]->s){  
                store[top++] = x;  
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];  
            } else {  
                Node *ret = x->ch[1];  
                for (; ret->ch[0] != null; ret = ret->ch[0]);  
                del(x->ch[1], x->v = ret->v);  
            }  
        } else {  
            del(x->ch[d], v);  
        }  
        /*if (x != null) x->push_up();*/  
    }  
    inline void del(int v){  
        del(root, v);  
        if (root->s < alpha * mSize){  
            rebuilt(root);  
            mSize = root->s;  
        }  
    }  
    inline int find_kth(int k){  
        Node *x = root;  
        int t = -1;  
        for (; x != null;){  
            t = x->ch[0]->s;  
            if (k == t + 1) break;  
            else if (k <= t) x = x->ch[0];  
            else k -= t + 1, x = x->ch[1];  
        }  
        return x->v;  
    }  
}sgt;  
int main(){  
    int a = clock();  
    sgt.init();  
    for (int i = 0; i < 100000; i++){  
        sgt.insert(rand());  
    }  
    for (int i = 0; i < 100000; i++){  
        int t = sgt.find_kth(1);  
        sgt.del(t);  
    }  
    printf("%d\n", clock() - a);  
    system("pause");  
    return 0;  
}  
