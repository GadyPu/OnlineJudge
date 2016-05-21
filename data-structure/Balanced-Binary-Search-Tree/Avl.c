#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
#define _max(a,b) ((a)>(b)?(a):(b))
#define size(_) ((_)==NULL ? 0 : (_)->size)
#define Height(_) ((_)==NULL ? -1 : (_)->Height)
typedef struct _avl{
	int client, key, size, Height;
	struct _avl *ch[2];
}AvlTree, *Avl;
AvlTree stack[Max_N];
int sz = 0;
void update(Avl x){
	if (x == NULL) return;
	x->size = size(x->ch[0]) + size(x->ch[1]) + 1;
	x->Height = _max(Height(x->ch[0]), Height(x->ch[1])) + 1;
}
void rotate(Avl *x, int d){
	Avl k = (*x)->ch[!d];
	(*x)->ch[!d] = k->ch[d];
	k->ch[d] = *x;
	update(*x);
	update(k);
	*x = k;
}
void Maintain(Avl *x, int d){
	if (Height((*x)->ch[d]) - Height((*x)->ch[!d]) == 2){
		if (Height((*x)->ch[d]->ch[d]) - Height((*x)->ch[d]->ch[!d]) == 1) rotate(x, !d);
		else if (Height((*x)->ch[d]->ch[d]) - Height((*x)->ch[d]->ch[!d]) == -1){
			rotate(&((*x)->ch[d]), d), rotate(x, !d);
		}
	}
}
void insert(Avl *x, int client, int key){
	if (*x == NULL){
		*x = &stack[sz++];
		(*x)->ch[0] = (*x)->ch[1] = NULL;
		(*x)->key = key, (*x)->Height = 0, (*x)->size = 1, (*x)->client = client;
	} else {
		int d = key > (*x)->key;
		insert(&((*x)->ch[d]), client, key);
		update(*x);
		Maintain(x, d);
	}
}
void _delete(Avl *x, int key){
	if (*x == NULL) return;
	if ((*x)->key == key){
		if (!(*x)->ch[0] || !(*x)->ch[1]){
			*x = (*x)->ch[0] ? (*x)->ch[0] : (*x)->ch[1];
		} else {
			Avl ret = (*x)->ch[1];
			for (; ret->ch[0] != NULL; ret = ret->ch[0]);
			_delete(&((*x)->ch[1]), (*x)->key = ret->key);
		}
	} else {
		_delete(&((*x)->ch[key > (*x)->key]), key);
	}
	if (*x != NULL){
		update(*x);
		Maintain(x, 0), Maintain(x, 1);
	}
}
Avl find_kth(Avl x, int k){
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
	Avl root = NULL, ret = NULL;
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
