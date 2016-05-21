#include<stdio.h>    
#include<stdlib.h>    
#include<string.h>    
#define Max_N 200000    
#define size(_) ((_)==NULL ? 0 :(_)->size)    
typedef struct _sbt{  
    int val, size;  
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
    else if (size((*x)->ch[d]->ch[!d]) > size((*x)->ch[!d])){  
        rotate(&((*x)->ch[d]), d), rotate(x, !d);  
    } else {  
        return;  
    }  
    Maintain(&((*x)->ch[0]), 0);  
    Maintain(&((*x)->ch[1]), 1);  
    Maintain(x, 0);  
    Maintain(x, 1);  
}  
void insert(SBT *x, int val){  
    int d = 0;  
    if (*x == NULL){  
        *x = &stack[sz++];  
        (*x)->val = val, (*x)->size = 1;  
        (*x)->ch[0] = (*x)->ch[1] = NULL;  
    } else {  
        (*x)->size++;  
        d = val > (*x)->val;  
        insert(&((*x)->ch[d]), val);  
        Maintain(x, val > (*x)->val);  
    }  
}  
void _remove(SBT *x, int val){  
    int d = 0;  
    SBT ret = NULL;  
    if ((*x) == NULL) return;  
    (*x)->size--;  
    if ((*x)->val == val){  
        if ((*x)->ch[0] == NULL || (*x)->ch[1] == NULL){  
            (*x) = ((*x)->ch[0] != NULL ? (*x)->ch[0] : (*x)->ch[1]);  
        } else {  
            ret = (*x)->ch[1];  
            while (ret->ch[0] != NULL) ret = ret->ch[0];  
            (*x)->val = ret->val;  
            _remove(&((*x)->ch[1]), ret->val);  
        }  
    } else {  
        d = val > (*x)->val;  
        _remove(&((*x)->ch[d]), val);  
    }  
}  
SBT find_kth(SBT x, int k){  
    int t = 0;  
    for (;;){  
        t = size(x->ch[0]);  
        if (k == t + 1) break;  
        else if (k < t + 1) x = x->ch[0];  
        else k -= t + 1, x = x->ch[1];  
    }  
    return x;  
}  
int find_rank(SBT x, int val, int cur){  
    int t = 0;  
    for (;;){  
        t = size(x->ch[0]);  
        if (x->val == val) break;  
        else if (val < x->val) x = x->ch[0];  
        else cur += t + 1, x = x->ch[1];  
    }  
    return cur + t + 1;  
}  
int pre(SBT x, int val){  
    int ret = -1;  
    for (; x != NULL;){  
        if (val <= x->val){  
            x = x->ch[0];  
        } else {  
            ret = x->val;  
            x = x->ch[1];  
        }  
    }  
    return ret;  
}  
int suc(SBT x, int val){  
    int ret = -1;  
    for (; x != NULL;){  
        if (val >= x->val){  
            x = x->ch[1];  
        } else {  
            ret = x->val;  
            x = x->ch[0];  
        }  
    }  
    return ret;  
}  
void travle(SBT x){  
    if (x != NULL){  
        travle(x->ch[0]);  
        printf("%d ", x->val);  
        travle(x->ch[1]);  
    }  
}  
int main(){  
    SBT root = NULL;  
    return 0;  
} 
