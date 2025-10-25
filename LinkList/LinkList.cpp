#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DL 3
#define STR(n) #n
#define DIGIT_LEN_STR(n) "%" STR(n) "d"
//定义链表结构
typedef struct Node{
	int data;
	Node *next;
}Node;

//创建链表
Node *GetNewNode(int val){
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->next = NULL;
	return p;
}
//销毁链表
void clear(Node *head){
	if(head == NULL) return;
	for(Node *p = head,*q;p;p=q){
		//防止销毁当前节点，后面节点地址丢失，导致内存泄漏
		q = p->next;
		free(p);
	}
}
//（有头）链表插入
Node *insert(Node *head,int pos, int val){
	Node new_head, *p = &new_head,*node = GetNewNode(val);
	new_head.next = head;
	for(int i = 0; i<pos;i++) p=p->next;
	node->next = p->next;
	p->next = node;
	return new_head.next;
}
//输出操作
void output_linklist(Node *head,int flag){
        //第1行
        int len = 0,n = 0;
        for(Node *p = head;p;p=p->next) n+=1;
        for (int i = 0;i<n;i++){
                printf(DIGIT_LEN_STR(DL),i);
                printf("  ");
        }
        printf("\n");
        //第2行
        for (Node *p = head;p;p=p->next){
                printf(DIGIT_LEN_STR(DL),p->data);
                printf("->");
        }
        printf("\n");
        if(flag == 0) printf("\n\n");
        return ;
}

//链表查找（查找出来后在链表下端用箭头指出）
int find(Node *head ,int val){
	Node *p = head;
	int n = 0;
	while(p){
		if(p->data == val) {
			output_linklist(head,1);
			//len表示空格数量
			int len = n*(DL+2)+1;
			for(int i = 0; i<len; i++) printf(" ");
			printf("↑\n");
			return 1;
		}
		n+=1;
		p=p->next;
	}
	return 0;
}
int main(int argc,char *argv[]){
	//测试程序：
	srand(time(0));
	#define MAX_OP 11
	Node *head = NULL;
	for(int i = 0;i<MAX_OP;i++){
		int pos = rand()%(i+1),val = rand()%100;
		printf("insert %d at %d to linklist\n",val,pos);
		head = insert(head,pos,val);
		output_linklist(head,0);
	}
	int val;
	while(~scanf("%d",&val)){
		if(!find(head,val)){
			printf("not found\n");
		}
	}
	return 0;
}


