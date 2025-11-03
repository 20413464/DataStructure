#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define KEY(n) (n ? n->key :-1)
#define MAX_NODE 11
/**功能：
**1.二叉树转广义表**
************************************
**2.广义表转二叉树
**（1）遇到关键字->生成新节点
**（2）遇到“(”->将新生成的节点压入栈      
**（3）遇到“,”->标记当前处理右子树      
**（4）遇到“)”->将栈顶节点出栈         
**（5）每生成新节点->根据标记设置左右子树 
*************************************
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


//反序列化
////////////////////////////////////////////
Node *deserialize(char *buff, int n){
    Node **s = (Node **)malloc(sizeof(Node *)* MAX_NODE);
    int top = -1,flag = 0,scode = 0;
    Node *p = NULL, *root =NULL;
    for (int i = 0;buff[i];i++){
        switch (scode)
        {
        case 0:{
            if(buff[i]>= '0' && buff[i]<='9') scode = 1;
            else if(buff[i] == '(') scode = 2;
            else if(buff[i] == ',') scode = 3;
            else  scode = 4;
            i-=1;
        }
            break;
        
        case 1:{
            int key =0;
            while (buff[i]<='9' && buff[i]>='0'){
                key = key*10+buff[i]-'0';
                i += 1;
            
            }
            p=getNewNode(key);
            if(top>=0 && flag == 0) s[top]->lchild = p;
            if(top>=0 && flag == 1) s[top]->rchild = p;
            i-=1;
            scode = 0;
            
        }
            break;
        case 2:{
            s[++top] = p;
            flag = 0; 
            scode = 0;   
        }
            break;
        case 3:{
            flag = 1;
            scode = 0;
        }
            break;
        case 4:{
            root = s[top];
            top -= 1;
            scode = 0;
        } 
            break;
        }
    }
    return root;
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

    Node *new_root =deserialize(buff,len);
    output(new_root);
    return 0;
}