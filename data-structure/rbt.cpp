#define LOCAL
#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<ctime>
const int Max_N = 3000000;
struct Node{
    int data, s, c;
    bool color;
    Node *fa, *ch[2];
    inline void set(int _v, int i, bool _color, Node *p){
        data = _v, color = _color, s = c = i;
        fa = ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + c;
    }
    inline void push_down(){
        for (Node *x = this; x->s; x = x->fa) x->s--;
    }
};
struct RedBlackTree{
    int top;
    Node *root, *null;
    Node stack[Max_N], *tail, *store[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, 1, null);
        return p;
    }
    inline void rotate(Node* &x, bool d){
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if (y->ch[d] != null) y->ch[d]->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        x->push_up();
        y->push_up();
    }
    inline void insert(int v){
        Node *x = root, *y = null;
        while (x->s){
            x->s++;
            if (v == x->data){
                x->c++;
                return;
            }
            y = x, x = x->ch[v > x->data];
        }
        x = newNode(v);
        if (y != null) y->ch[v > y->data] = x;
        else root = x;
        x->fa = y;
        x->push_up();
        insert_fix(x);
    }
    inline void insert_fix(Node* &x){
        while (x->fa->color){
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if (uncle->color){
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if (x == par->ch[d]){
                rotate(x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(Gp, d);
            }
        }
        root->color = 0;
    }
    inline Node *find(Node *x, int data){
        while (x->s && x->data != data) x = x->ch[x->data < data];
        return x;
    }
    inline void del_fix(Node* &x){
        while (x != root && !x->color){
            bool d = x == x->fa->ch[0];
            Node *par = x->fa, *sibling = par->ch[d];
            if (sibling->color){
                sibling->color = 0;
                par->color = 1;
                rotate(x->fa, !d);
                sibling = par->ch[d];
            } else if (!sibling->ch[0]->color && !sibling->ch[1]->color){
                sibling->color = 1, x = par;
            } else {
                if (!sibling->ch[d]->color){
                    sibling->ch[!d]->color = 0;
                    sibling->color = 1;
                    rotate(sibling, d);
                    sibling = par->ch[d];
                }
                sibling->color = par->color;
                sibling->ch[d]->color = par->color = 0;
                rotate(par, !d);
                break;
            }
        }
        x->color = 0;
    }
    void del(int data){
        Node *z = find(root, data);
        if (z == null) return;
        if (z->c > 1){
            z->c--;
            z->push_down();
            return;
        }
        Node *y = z, *x = null;
        if (z->ch[0]->s && z->ch[1]->s){
            y = z->ch[1];
            while (y->ch[0]->s) y = y->ch[0];
        }
        x = y->ch[y->ch[0] == null];
        x->fa = y->fa;
        if (y->fa == null) root = x;
        else y->fa->ch[y->fa->ch[1] == y] = x;
        if (z != y) z->data = y->data;
        y->fa->push_down();
        if (y->color == 0) del_fix(x);
        store[top++] = y;
    }
}rbt_tree;
int main(){
    int a = clock();
    rbt_tree.init();
    for (int i = 0; i < 2000000; i++){
        rbt_tree.insert(i);
    }

    //rbt_tree.insert(6);
    //rbt_tree.insert(5);
    //rbt_tree.del(6);

    printf("%d\n", clock() - a);
    return 0;
}
