#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    char ch;
    int freq;
    Node *lchild,*rchild;
} Node;

Node *getNewNode(int freq,char ch){
    Node *p = (Node *)malloc(sizeof(Node));
    p->ch =ch;
    p->freq = freq;
    p->lchild = p->rchild =NULL;
    return p;
}

void clear(Node *root){
    if(root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
Node *buildHaffmanTree(Node **node_arr,int n){
   
    return NULL;
}

int main(){
    char s[10];
    int n,freq;
    scanf("%d",&n);
    Node **node_arr = (Node **)malloc(n*sizeof(Node *));
    for(int i = 0;i<n;i++){
        scanf("%s%d",s,&freq);
        node_arr[i] =getNewNode(freq,s[0]);
    }
    Node *root = buildHaffmanTree(node_arr,n);

    clear(root);
    return 0;
}