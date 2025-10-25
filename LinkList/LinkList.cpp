#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
//(无头)链表插入
Node *insert(Node *head,int pos, int val){
	if(pos == 0){
		Node *p = GetNewNode(val);
		p->next = head;
		return p;
	}
	Node *p =head;
	for(int i = 1;i<pos; i++) p = p->next;
	Node *node = GetNewNode(val);
	node->next = p->next;
	p->next = node;
	return head;
}
//输出操作
void output_linklist(Node *head){
	//第1行
	int len = 0,n = 0;
	for(Node *p = head;p;p=p->next) n+=1;
	for (int i = 0;i<n;i++){
		printf("%3d",i);
		printf("  ");
	}
	printf("\n");
	//第2行
	for (Node *p = head;p;p=p->next){
		printf("%3d",p->data);
		printf("->");
	}
	printf("\n\n\n");
	return ;
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
		output_linklist(head);
	}
	return 0;
}

