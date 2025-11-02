#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define KEY(n) (n ? n->key :-1)
/**
**二叉树转广义表**
**/



typedef struct Node
{
    int key;
    Node *lchild,*rchild;
} Node;

Node *getNewNode(int key){
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root,int key){
    if(root ==NULL) return getNewNode(key);
    if(rand()%2) root->lchild = insert(root->lchild,key);
    else root->rchild = insert(root->rchild,key);
    return root;
}
Node *getRandomBinaryTree(int n){
    Node *root =NULL;
    for (int i = 0;i<n;i++){
        root =insert(root,rand()%100);
        
    }
    return root;
}
void clear(Node *root){
    if(root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
//序列化
//////////////////////////////////////////////
char buff[1000];
int len = 0;        //广义表长度

void __serialize(Node *root){
    if(root == NULL) return;

    len += snprintf(buff+len,100,"%d",root->key);
    if(root->lchild == NULL && root->rchild ==NULL) return ;
    len +=snprintf(buff +len,100,"(");
    __serialize(root->lchild);
    if(root->rchild)
    {
        len +=snprintf(buff +len,100,",");
        __serialize(root->rchild);
    }
    len +=snprintf(buff +len,100,")");   
    return ;
}
void serialize(Node *root){
    memset(buff,0,sizeof(buff));
    len =0;
    __serialize(root);
    return ;
}

////////////////////////////////////////////


void print(Node *node){
    printf("%d(%d,%d)\n",KEY(node),
                        KEY(node->lchild),
                        KEY(node->rchild));
}
void output(Node *root){
    if(root==NULL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;

}
int main(){
    srand(time(0));
    #define MAX_OP 11
    Node *root = getRandomBinaryTree(MAX_OP);
    
    serialize(root);
    output(root);
    printf("Buff[]:%s\n",buff);

    return 0;
}