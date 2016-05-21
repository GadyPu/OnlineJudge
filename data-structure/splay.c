#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
#define node_size(T) (((T)==NULL) ? 0 :((T)->size))
#define _size(T) (node_size((T)->ch[1]) + node_size((T)->ch[0]) + 1)
typedef struct _node{
	int val, size;
	struct _node *pre, *ch[2];
}splay;
splay *null, stack[Max_N];
int sz = 0, arr[Max_N];
int IsPrim(int n){
	int i;
	for (i = 2; i * i <= n; i++) if (0 == n % i) return 0;
	return n != 1;
}
splay *_calloc(int val){
	splay *p = &stack[sz++];
	memset(p, 0, sizeof(splay));
	p->size = 1, p->val = val;
	return p;
}
void init(){
	null = _calloc(-1);
	null->val = -1, null->size = 0;
}
void rotate(splay *x, int c){
	splay *y = x->pre;
	y->ch[!c] = x->ch[c];
	if (x->ch[c] != NULL) x->ch[c]->pre = y;
	x->pre = y->pre;
	if (y->pre != NULL){
		if (y->pre->ch[0] == y) y->pre->ch[0] = x;
		else y->pre->ch[1] = x;
	}
	y->size = _size(y);
	x->ch[c] = y;
	y->pre = x;
	x->size = _size(x);
}
void splay_splay(splay *x, splay *f){
	for (; x->pre != f;){
		if (x->pre->pre == f){
			rotate(x, x->pre->ch[0] == x);
		} else {
			splay *y = x->pre, *z = y->pre;
			if (z->ch[0] == y){
				if (y->ch[0] == x) rotate(y, 1), rotate(x, 1);
				else rotate(x, 0), rotate(x, 1);
			} else {
				if (y->ch[1] == x) rotate(y, 0), rotate(x, 0);
				else rotate(x, 1), rotate(x, 0);
			}
		}
	}
}
splay *insert(int val, splay *root){
	splay *fp = NULL, *p = root;
	if (root == NULL){
		root = _calloc(val);
		root->pre = null;
		return root;
	}
	for (; p != NULL;){
		fp = p;
		if (p->val > val) p = p->ch[0];
		else p = p->ch[1];
	}
	p = _calloc(val);
	if (fp->val > val) fp->ch[0] = p;
	else fp->ch[1] = p;
	p->pre = fp;
	splay_splay(p, null);
	p->size = _size(p);
	return p;
}
splay *get_min(splay *root){
	while (root->ch[0] != NULL) root = root->ch[0];
	splay_splay(root, null);
	return root;
}
splay *_delete(splay *root){
	splay *p = NULL;
	if (root->ch[0] == NULL && root->ch[1] == NULL) return NULL;
	if (root->ch[0] == NULL) root = root->ch[1];
	else if (root->ch[1] == NULL) root = root->ch[0];
	else {
		p = get_min(root->ch[1]);
		splay_splay(p, root);
		p->ch[0] = root->ch[0];
		root->ch[0]->pre = p;
		root = p;
	}
	root->pre = null;
	root->size = _size(root);
	return root;
}
splay *splay_findk(splay *root, int k){
	int tmp;
	splay *ret = root;
	for (; ret != NULL;){
		tmp = node_size(ret->ch[0]);
		if (k == tmp + 1) break;
		if (k <= tmp) ret = ret->ch[0];
		else k -= tmp + 1, ret = ret->ch[1];
	}
	splay_splay(ret, null);
	return ret;
}
void splay_print(splay *root){
	if (root != NULL){
		splay_print(root->ch[0]);
		printf("%d ", root->val);
		splay_print(root->ch[1]);
	}
}
int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
#endif
	splay *root = NULL;
	return 0;
}
