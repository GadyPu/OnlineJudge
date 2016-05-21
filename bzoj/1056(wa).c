#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define Max_N 300000
#define size(T) ((T)==NULL ? 0 : (T)->size)
#define _size(T) (size((T)->ch[0]) + size((T)->ch[1]) + 1)
typedef struct _trie{ int val, idx; struct _trie *ch[26]; }trie;
typedef struct _treap{
	char name[12];
	int val, idx, size, fix;
	struct _treap *ch[2];
}treap, *Treap;
trie _stack[Max_N];
treap stack[Max_N];
int sz = 0, _sz = 0;
trie *built(){
	trie *x = &_stack[_sz++];
	memset(x, 0, sizeof(trie));
	return x;
}
void trie_insert(trie *x, char *src, int val, int idx){
	char *p = src;
	while (*p != '\0'){
		if (x->ch[*p - 'A'] == NULL) x->ch[*p - 'A'] = built();
		x = x->ch[*p - 'A'];
		p++;
	}
	x->idx = idx, x->val = val;
}
trie *trie_query(trie *x, char *src){
	char *p = src;
	while (*p != '\0'){
		if (x == NULL || x->ch[*p - 'A'] == NULL) return NULL;
		x = x->ch[*p - 'A'];
		p++;
	}
	return x;
}
int _random(){
	static int x = 1840828537;
	x += (x << 2) | 1;
	return x;
}
void rotate(Treap *x, int d){
	Treap k = (*x)->ch[!d];
	(*x)->ch[!d] = k->ch[d];
	k->ch[d] = *x;
	(*x)->size = _size(*x);
	k->size = _size(k);
	*x = k;
}
void treap_insert(Treap *x, char *name, int val, int idx, int fix){
	int d = 0;
	if (*x == NULL){
		*x = &stack[sz++];
		strcpy((*x)->name, name);
		(*x)->ch[0] = (*x)->ch[1] = NULL;
		(*x)->size = 1, (*x)->val = val, (*x)->idx = idx, (*x)->fix = fix;
		return;
	} else if (val != (*x)->val){
		d = val > (*x)->val;
		treap_insert(&((*x)->ch[d]), name, val, idx, fix);
		if ((*x)->ch[d]->fix < (*x)->fix) rotate(x, !d);
		(*x)->size = _size(*x);
	} else {
		d = idx < (*x)->idx;
		treap_insert(&((*x)->ch[d]), name, val, idx, fix);
		if ((*x)->ch[d]->fix < (*x)->fix) rotate(x, !d);
		(*x)->size = _size(*x);
	}
}
void _delete(Treap *x, int val, int idx){
	if ((*x)->val == val){
		if ((*x)->idx == idx){
			if ((*x)->ch[0] == NULL || (*x)->ch[1] == NULL){
				*x = ((*x)->ch[0] != NULL ? (*x)->ch[0] : (*x)->ch[1]);
			} else {
				if ((*x)->ch[0]->fix < (*x)->ch[1]->fix){
					rotate(x, 1);
					(*x)->size--;
					_delete(&((*x)->ch[1]), val, idx);
				} else if ((*x)->ch[0]->fix > (*x)->ch[1]->fix){
					rotate(x, 0);
					(*x)->size--;
					_delete(&((*x)->ch[0]), val, idx);
				}
			}
		} else if (idx < (*x)->idx){
			(*x)->size--;
			_delete(&((*x)->ch[1]), val, idx);
		} else if (idx > (*x)->idx){
			(*x)->size--;
			_delete(&((*x)->ch[0]), val, idx);
		}
	} else if (val < (*x)->val){
		(*x)->size--;
		_delete(&((*x)->ch[0]), val, idx);
	} else {
		(*x)->size--;
		_delete(&((*x)->ch[1]), val, idx);
	}
}
Treap find_kth(Treap x, int k){
	int t = 0;
	for (;;){
		t = size(x->ch[0]);
		if (k == t + 1) break;
		else if (k < t + 1) x = x->ch[0];
		else k -= t + 1, x = x->ch[1];
	}
	return x;
}
int find_rank(Treap x, int val, int idx, int cur){
	int t = 0;
	for (; x != NULL;){
		t = size(x->ch[0]);
		if (val == x->val){
			for (; x != NULL;){
				t = size(x->ch[0]);
				if (idx == x->idx) return cur + t + 1;
				else if (idx > x->idx) x = x->ch[0];
				else cur += t + 1, x = x->ch[1];
			}
		}
		else if (val < x->val) x = x->ch[0];
		else cur += t + 1, x = x->ch[1];
	}
	return cur + t + 1;
}
int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
#endif
	Treap root = NULL;
	trie *_root = built();
	char s1[100], buf[100];
	int i, j, n, num, k = 0;
	scanf("%d\n", &n);
	while (n--){
		k++;
		gets(buf);
		trie *ret = NULL;
		Treap ans = NULL;
		if (buf[0] == '+'){
			sscanf(&buf[1], "%s %d", s1, &num);
			ret = trie_query(_root, s1);
			if (ret == NULL || ret->idx == 0){
				trie_insert(_root, s1, num, k);
				treap_insert(&root, s1, num, k, _random());
			} else {
				_delete(&root, ret->val, ret->idx);
				treap_insert(&root, s1, num, ret->idx, _random());
				ret->val = num;
			}
		} else if (buf[0] == '?' && isalpha(buf[1])){
			sscanf(&buf[1], "%s", s1);
			ret = trie_query(_root, s1);
			printf("%d\n", root->size - find_rank(root, ret->val, ret->idx, 0) + 1);
		} else {
			sscanf(&buf[1], "%d", &num);
			j = (num + 9 <= root->size ? num + 9 : root->size);
			for (i = num; i <= j; i++){
				ans = find_kth(root, root->size - i + 1);
				printf("%s", ans->name);
				if (i < j) printf(" ");
			}
			printf("\n");
		}
	}
	return 0;
}

