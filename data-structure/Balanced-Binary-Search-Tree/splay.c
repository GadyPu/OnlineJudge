#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
#define size(_) ((_)==null ? 0 : (_)->size)
typedef struct _spt{
	int client, key, size;
	struct _spt *pre, *ch[2];
}splay;
splay *null, *root, stack[Max_N];
int sz = 0;
splay *_calloc(int client, int key){
	splay *p = &stack[sz++];
	p->pre = p->ch[0] = p->ch[1] = null;
	p->size = 1, p->key = key, p->client = client;
	return p;
}
void push_up(splay *x){
	if (x == null) return;
	x->size = size(x->ch[0]) + size(x->ch[1]) + 1;
}
void rotate(splay *x, int d){
	splay *y = x->pre;
	y->ch[!d] = x->ch[d];
	if (x->ch[d] != null) x->ch[d]->pre = y;
	x->pre = y->pre;
	if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
	x->ch[d] = y;
	y->pre = x;
	push_up(y);
	if (y == root) root = x;
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
				if (y->ch[1] == x)
					rotate(y, 0), rotate(x, 0);
				else rotate(x, 1), rotate(x, 0);
			}
		}
	}
	push_up(x);
}
void insert(int client, int key){
	splay *fp = null, *p = root;
	if (root == null){
		root = _calloc(client, key);
		return;
	}
	for (; p != null;){
		fp = p;
		if (key > p->key) p = p->ch[1];
		else p = p->ch[0];
	}
	p = _calloc(client, key);
	if (fp->key > key) fp->ch[0] = p;
	else fp->ch[1] = p;
	p->pre = fp;
	splay_splay(p, null);
	push_up(p);
}
void _delete(int key){
	splay *p = root, *rt = null;
	while (p != null && p->key != key) p = p->ch[key > p->key];
	if (p == null) return;
	splay_splay(p, null);
	rt = root->ch[0];
	if (rt == null){
		rt = root->ch[1];
	}
	else {
		splay *tmp = rt->ch[1];
		while (tmp != null && tmp->ch[1] != null) tmp = tmp->ch[1];
		if (tmp != null) splay_splay(tmp, root);
		rt = root->ch[0];
		rt->ch[1] = root->ch[1];
		root->ch[1]->pre = rt;
	}
	root = rt;
	root->pre = null;
	if (root != null) push_up(root);
}
void initialize(){
	null = _calloc(-1, -1);
	null->size = 0;
	root = null;
}
splay *find_kth(splay *x, int k){
	int t = 0;
	for (; x != null;){
		t = size(x->ch[0]);
		if (k == t + 1) break;
		else if (k <= t) x = x->ch[0];
		else k -= t + 1, x = x->ch[1];
	}
	if (x == null){
		return null;
	} else {
		splay_splay(x, null);
		return root;
	}
}
int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
#endif
	int n, a, b;
	initialize();
	splay *ret = NULL;
	while (~scanf("%d", &n) && n){
		ret = NULL;
		if (2 == n || 3 == n){
			if (2 == n && root) ret = find_kth(root, root->size);
			else if (3 == n && root) ret = find_kth(root, 1);
			if (ret == null || root == null) printf("0\n");
			else printf("%d\n", ret->client), _delete(ret->key);
		} else {
			scanf("%d %d", &a, &b);
			insert(a, b);
		}

	}
	return 0;
}
