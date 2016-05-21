#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<ctime>
const int RED= 1;
const int BLACK = 0;
struct Node{
    int data;
    bool color;
    Node *fa, *left, *right;
    Node() :color(BLACK), data(0){ fa = left = right = NULL; }
    Node(int _v, Node *p) :data(_v), color(RED){ fa = left = right = p; }
};
struct RedBlackTree{
    Node *root, *null;
    void init(){
        null = new Node();
        root = null;
    }
    /*
    * 
    *    
    * 
    *    对红黑树的节点(x)进行右旋转
    *    
    *          px                            px
    *          /                             /
    *  ->    x                             y
    *       / \                           / \
    *  ->  y   rx     --(右旋)-->        ly   x
    *      / \                               / \
    *     ly  ry                            ry  rx
    *
    *
    *
    */
    //   旋转操作可以不传递引用(reference)话说传引用会快一些。。。
    void rotate_right(Node* &x){
        Node *y = x->left;
        x->left = y->right;
        if (y->right != null) y->right->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else if (x->fa->left == x) x->fa->left = y;
        else x->fa->right = y;
        y->right = x;
        x->fa = y;
    }
    //   左旋同上
    void rotate_left(Node* &x){
        Node *y = x->right;
        x->right = y->left;
        if (y->left != null) y->left->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else if (x->fa->left == x) x->fa->left = y;
        else x->fa->right = y;
        y->left = x;
        x->fa = y;
    }
    Node *find(Node *x, int &data){
        while (x != null && x->data != data){
            x = data < x->data ? x->left : x->right;
        }
        return x;
    }
    void insert(int v){
        Node *x = root;
        Node *y = null;
        while (x != null) {        // 先找到带插入节点的位置，y保存该路径上最后一个节点
            y = x;
            x = v < x->data ? x->left : x->right;
        }
        x = new Node(v, null);
        if (y != null){            // 确定新节点x与其父节点y的大小关系，再将它们连起来
            if (v < y->data) y->left = x;
            else y->right = x;
        } else {
            root = x;
        }
        x->fa = y;
        insert_fix(x);
    }
    void insert_fix(Node* &x){
        while (x->fa->color != BLACK){
            // x为当前节点
            // par x的父节点，Gp x的祖父节点， uncle x的叔叔节点
            Node *par = x->fa, *Gp = par->fa, *uncle = null;
            if (par == Gp->left){                // 若父节点是祖父的左孩子
                uncle = Gp->right;               // 叔叔为祖父的右孩子
                if (uncle->color == RED){        // 若叔叔颜色为红色 
            //    Case1：父亲和叔叔节点变为红色，祖父颜色变为红色
            //    将祖父节点设置为当前节点，再继续(因为Gp由黑变成红色，Gp的父节点可能为红色)
            //    所以要继续向上递归调整
                    par->color = BLACK;            
                    Gp->color = RED;
                    uncle->color = BLACK;
                    x = Gp;
                } else if (x == par->right){
            //    Case2：x为右孩子，将父节点设置为当前节点，再进行左旋
            //    即变成Case3：
                    rotate_left(x = par);
                } else {
            //    Case3：x,父节点，祖父节点三者共线(左侧)
            //    将祖父节点改为红色，父节点改为黑色
            //    此时调整完成，红黑树性质得到恢复(想想为什么??)
                    Gp->color = RED;
                    par->color = BLACK;
                    rotate_right(Gp);
                }
            } else {
            //    同上,只是由左变成右而已
                uncle = Gp->left;
                if (uncle->color == RED){
                    par->color = BLACK;
                    Gp->color = RED;
                    uncle->color = BLACK;
                    x = Gp;
                } else if (x == par->left){
                    rotate_right(x = par);
                } else {
                    Gp->color = RED;
                    par->color = BLACK;
                    rotate_left(Gp);
                }
            }
        }
        //   将根置为黑色
        root->color = BLACK;
    }
    void del(int data){
        //    先找到待删除的节点
        Node *z = find(root, data);
        //    若没找到直接退出
        if (z == null) return;
        Node *y = z, *x = null;
        //    若z的左右孩子均不为空，则用y保存z的右子树中最小的节点
        if (z->left != null && z->right != null){
            y= z->right;
            while (y->left != null) y = y->left;
        }
        //    此时y只有左子树，或只有右子树，或左右子树均不存在
        //    x可能为 null !!!
        x = y->left != null ? y->left : y->right;
        //    将x与y的父节点连接起来，这里可能会改变null节点的fa指针,但没有关系的。。。
        x->fa = y->fa;
        if (y->fa == null) root = x;
        //    确定y节点与其父亲的左右关系
        else  if (y->fa->left == y) y->fa->left = x;
        else y->fa->right = x;
        //    若z不等于y 拷贝数据，y才是真正要删除的节点
        if (z != y) z->data = y->data;
        //    如果删除的节点y的颜色为黑色，对树进行调整使得树满足红黑树的要求
        if (y->color == BLACK) del_fix(x);
        //    释放y
        delete y;
    }
    void del_fix(Node* &x){
        while (x != root && x->color == BLACK){
            Node *par = x->fa, *sibling = null;
            if (par->left == x){
                sibling = par->right;
                if (sibling->color == RED){
                    sibling->color = BLACK;
                    par->color = RED;
                    rotate_left(par);
                    sibling = par->right;
                } else 
                if (sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color = RED;
                    x = par;
                } else {
                    if (sibling->right->color == BLACK){
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotate_right(sibling);
                        sibling = par->right;
                    }
                    sibling->color = par->color;
                    par->color = BLACK;
                    sibling->right->color = BLACK;
                    rotate_left(par);
                    break;
                }
            } else {
                sibling = par->left;
                if (sibling->color == RED){
                    sibling->color = BLACK;
                    par->color = RED;
                    rotate_right(par);
                    sibling = par->left;
                } else 
                if (sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color = RED;
                    x = par;
                } else {
                    if (sibling->left->color == BLACK){
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotate_left(sibling);
                        sibling = par->left;
                    } else {
                        sibling->color = par->color;
                        par->color = BLACK;
                        sibling->left->color = BLACK;
                        rotate_right(par);
                        break;
                    }
                }

            }
        }
        x->color = BLACK;
    }
}rbt_tree;
int main(){
    int a = clock();
    rbt_tree.init();
    for (int i = 0; i < 2000000; i++){
        rbt_tree.insert(i);
    }
    for (int i = 0; i < 2000000; i++){
        rbt_tree.del(i);
    }
    printf("%d\n", clock() - a);

    return 0;
}
