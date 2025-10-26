#include <stdio.h>
#include <stdlib.h>
#include <time.h>



 //定义顺序表结构
 typedef struct vector{
	int *data;
 	int size;
 }vector;
vector *initVector(int n){
	vector *v= (vector *)malloc(sizeof(vector));
	v->data = (int *)malloc(sizeof(int)*n);
	v->size = n;
	return  v;

}
void clearVector(vector *v){
	if(v == NULL) return ;
	free(v->data);
	free(v);
	return ;
}
int vectorSeek(vector *v,int pos){
	if(pos<0 || pos >=v->size) return -1;
	return v->data[pos];
 }

int insertVector(vector *v,int pos,int val){
	if(pos<0 || pos>= v->size) return 0;
	v->data[pos] = val;
	return 1;
}
//定义队列结构
typedef struct Queue{
	vector *data;
	int size,head,tail,count;
}Queue;


//判断队列是否为空
int empty(Queue *q){
	return q->count == 0;
}                       
//查看队首元素
int front(Queue *q){
	return vectorSeek(q->data,q->head);
}
//初始化队列结构
Queue *initQueue(int n){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->data = initVector(n);
	q->size = n;
        q->head = q->tail = q->count = 0;
        return q;
}
//插入数据
int push(Queue * q,int val){
	if(q->count == q->size)return 0;
	insertVector(q->data,q->tail,val);
	q->tail +=1;
	if(q->tail == q->size) q->tail = 0;
	q->count +=1;
	return 1;
}
//删除数据
int pop(Queue *q){
	if(empty(q)) return 0;
	q->head +=1;
	q->count -=1;
	return 1;
}
//销毁队列
void clearQueue(Queue *q){
	if(q == NULL) return ;
	clearVector(q->data);
	free(q);
	return ;
}

void outputQueue(Queue *q){
	printf("Queue:");
	for(int i =0; i<q->count;i++){
		printf("%4d",vectorSeek(q->data,(q->head+i)%(q->size)));
	}
	printf("\n\n");
	return ;
}
int main(int argc,char *argv[]){
	//测试程序
	srand(time(0));
	#define MAX_OP 11
	Queue *q = initQueue(5);
	for(int i =0;i<MAX_OP;i++){
		int op = rand() %5,val =rand()%100;  //0:pop | 1,2,3,4:push
		switch (op){
			case 0:
				printf("front of queue :%d\n",front(q));
				pop(q);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				printf("push %d to queue\n",val);
				push(q,val);
				break;

		}
		outputQueue(q);		
	}
	clearQueue(q);
	return 0;
}
