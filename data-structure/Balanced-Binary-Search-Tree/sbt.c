#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 200000
#define size(_) ((_)==NULL ? 0 : (_)->size)
typedef struct _sbt{
	int client, key, size;
	struct _sbt *ch[2];
}SBTNode, *SBT;
SBTNode stack[Max_N];
int sz = 0;
void rotate(SBT *x, int d){
	SBT k = (*x)->ch[!d];
	(*x)->ch[!d] = k->ch[d];
	k->ch[d] = *x;
	k->size = (*x)->size;
	(*x)->size = size((*x)->ch[0]) + size((*x)->ch[1]) + 1;
	*x = k;
}
void Maintain(SBT *x, int d){
	if ((*x)->ch[d] == NULL) return;
	if (size((*x)->ch[d]->ch[d]) > size((*x)->ch[!d])) rotate(x, !d);
	else if (size((*x)->ch[d]->ch[!d]) > size((*x)->ch[!d]))
		rotate(&((*x)->ch[d]), d), rotate(x, !d);
	else return;
	Maintain(&((*x)->ch[d]), 0);
	Maintain(&((*x)->ch[!d]), 1);
	Maintain(x, 0), Maintain(x, 1);
}
void insert(SBT *x, int client, int key){
	if (*x == NULL){
		*x = &stack[sz++];
		(*x)->ch[0] = (*x)->ch[1] = NULL;
		(*x)->key = key, (*x)->size = 1, (*x)->client = client;
	} else {
		(*x)->size++;
		insert(&((*x)->ch[key > (*x)->key]), client, key);
		Maintain(x, key >= (*x)->key);
	}
}
void _delete(SBT *x, int key){
	if (*x == NULL) return;
	(*x)->size--;
	if ((*x)->key == key){
		if (!(*x)->ch[0] || !(*x)->ch[1]){
			*x = (*x)->ch[0] ? (*x)->ch[0] : (*x)->ch[1];
		} else {
			SBT ret = (*x)->ch[1];
			for (; ret->ch[0] != NULL; ret = ret->ch[0]);
			_delete(&((*x)->ch[1]), (*x)->key = ret->key);
		}
	} else {
		_delete(&((*x)->ch[key > (*x)->key]), key);
	}
}
SBT find_kth(SBT x, int k){
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
	SBT root = NULL, ret = NULL;
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
