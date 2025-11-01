#include <stdio.h>
#include <stdlib.h>
#include <time.h>



//定义数据结构
typedef struct Node{
    int key;
    struct Node *lchild, *rchild;
    
} Node;

//创建二叉树
Node *getNewNode(int key){
    Node *p = (Node *)malloc(sizeof(Node));
    p->key =key;
    p->lchild = p->rchild = NULL;
    return p;
}


//随机插入节点
Node *insert(Node *root, int key){
    if(root == NULL) return getNewNode(key);
    if(rand()%2) root->lchild = insert(root->lchild,key);
    else root->rchild = insert(root->rchild,key);

    return root;

    

}

//销毁
void clear(Node *root){
     if(root == NULL) return ;
     clear(root->lchild);
     clear(root->rchild);
     free(root);
     return ;

}
#define MAX_NODE 10
Node *queue[MAX_NODE+5];
int head,tail;

//广度优先遍历
void bfs(Node * root){
    head = tail = 0;
    queue[tail++] = root;
    while(head < tail){
        Node *node = queue[head];
        printf("\nnode:%d",node->key);
        if(node->lchild){
            queue[tail++] = node->lchild;
            printf("\t%d->%d(left)\n",node->key,node->lchild->key);

        }
        if(node->rchild){
            queue[tail++] = node->rchild;
            printf("\t%d->%d(right)\n",node->key,node->rchild->key);

        }
        
        head++;
    }
    return ;
}
int tot = 0;
 //深度优先遍历
void dfs(Node * root){
    if(root ==NULL) return ;
    int start,end;
    tot +=1;
    start = tot;
    if(root->lchild) dfs(root->lchild);
    if(root->rchild) dfs(root->rchild);
    tot +=1;
    end = tot;
    printf("%d:[%d,%d]\n",root->key,start,end);
    return ;
}

int main(int argc,char **argv){
    srand(time(0));
    Node *root =NULL;
    
    for (int i = 0;i<MAX_NODE;i++){
        root = insert(root,rand()%100);
    }
    
    bfs(root);
    dfs(root);
    return 0;
}