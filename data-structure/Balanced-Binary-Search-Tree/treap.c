#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 110000
#define size(_) ((_)==NULL ? 0 : (_)->size)
typedef struct _trp{
	int client, key, size, fix;
	struct _trp *ch[2];
}treap, *Treap;
treap stack[Max_N];
int sz = 0;
int run(){
	static int x = 1840828537;
	x += (x << 2) | 1;
	return x;
}
void update(Treap x){
	if (x == NULL) return;
	x->size = size(x->ch[0]) + size(x->ch[1]) + 1;
}
void rotate(Treap *x, int d){
	Treap k = (*x)->ch[!d];
	(*x)->ch[!d] = k->ch[d];
	k->ch[d] = *x;
	k->size = (*x)->size;
	update(*x);
	*x = k;
}
void insert(Treap *x, int client, int key){
	if (*x == NULL){
		*x = &stack[sz++];
		(*x)->ch[0] = (*x)->ch[1] = NULL;
		(*x)->key = key, (*x)->size = 1, (*x)->client = client, (*x)->fix = run();
	} else {
		int d = key > (*x)->key;
		insert(&((*x)->ch[d]), client, key);
		update(*x);
		if ((*x)->ch[d]->fix < (*x)->fix) rotate(x, !d);
	}
}
void _delete(Treap *x, int key){
	if (*x == NULL) return;
	if ((*x)->key == key){
		if (!(*x)->ch[0] || !(*x)->ch[1]){
			*x = (*x)->ch[0] ? (*x)->ch[0] : (*x)->ch[1];
		} else {
			int d = (*x)->ch[0]->fix < (*x)->ch[1]->fix;
			rotate(x, d);
			_delete(&((*x)->ch[d]), key);
		}
	} else {
		_delete(&((*x)->ch[key>(*x)->key]), key);
	}
	if (*x != NULL) update(*x);
}
Treap find_kth(Treap x, int k){
	int t = 0;
	for (; x != NULL;){
		t = size(x->ch[0]);
		if (k == t + 1) break;
		else if (k <= t) x = x->ch[0];
		else k -= t + 1, x = x->ch[1];
	}
	return x;
}
int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
#endif
	int n, a, b;
	Treap root = NULL, ret = NULL;
	while (~scanf("%d", &n) && n){
		ret = NULL;
		if (2 == n || 3 == n){
			if (2 == n && root) ret = find_kth(root, root->size);
			else if (3 == n && root) ret = find_kth(root, 1);
			if (!ret || !root) printf("0\n");
			else printf("%d\n", ret->client), _delete(&root, ret->key);
		} else {
			scanf("%d %d", &a, &b);
			insert(&root, a, b);
		}

	}
	return 0;
}
