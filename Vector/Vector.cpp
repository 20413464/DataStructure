#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//顺序表结构定义：
typedef struct vector_{
    int size,count;
    int *data;
}vector_;
//初始化顺序表
vector_ *getNewVector(int n){
    vector_ *p = (vector_ *)malloc(sizeof(vector_));
    p->size = n;
    p->count = 0;
    p->data = (int *)malloc(sizeof(int)*n);
    return p;
}
//销毁操作
void clear(vector_ *v){
    if(v == NULL){
    return;
    }
    free(v->data);
    free(v);
    return;
}

//顺序表的插入
int insert(vector_ *v,int pos,int val){
    if(pos<0 ||pos>v->count){
        printf("pos不符合顺序表的大小！");
        return 0;
    }
    if(v->size == v->count) 
    {	
	    printf("顺序表已满");
	    return 0;
    } 
    for(int i = v->count-1; i >=pos; i--){
    v->data[i+1] = v->data[i];
    }
    v->data[pos] = val;
    v->count+=1;
    return 1;
}
//顺序表的删除
int erase(vector_ *v,int pos){
    if(pos<0 ||pos>v->count){
        printf("pos不符合顺序表的大小！");
        return 0;
    }
    for(int i = pos+1;i<v->count;i++){
        v->data[i-1] = v->data[i];
    }
    v->count-=1;
    return 1;

}
//显示顺序表
void output_vector(vector_ *v){
	int len = 0;
	for(int i = 0;i<v->size;i++){
		len +=printf("%3d",i);
	}
	printf("\n");
	for(int i =0;i<len;i++) printf("-");
	printf("\n");
	for (int i = 0;i<v->count;i++){
		printf("%3d",v->data[i]);
	}
	printf("\n");
	printf("\n\n");
	return ;
}

int main() {
	srand(time(0));
	#define MAX_OP 20
	vector_ *v = getNewVector(MAX_OP);
	for(int i = 0;i<MAX_OP;i++){
	int op = rand()%4,pos,val;
	switch(op){
		case 0:
		case 1:
		case 2:
			pos = rand()%(v->count +2 );
			val = rand()%100;
			printf("insert %d at %d to vector = %d\n",
					val,pos,insert(v,pos,val));
			break;
		case 3:
			pos = rand()%(v->count+2);
			printf("erase item at %d in vector = %d\n",
					pos,erase(v,pos));
			break;
		}
		output_vector(v);
	}
	clear(v);




    return 0;
}
