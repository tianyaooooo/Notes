#include<iostream>
#include<stdlib.h>
using namespace std;
#define MAXSIZE 6

typedef struct Queue
{
	int * pBase; // 循环数组的首地址
	int front; // 队头
	int rear; // 队尾 
} QUEUE, * PQUEUE;

// 函数声明时通常只写出形参类型，这样更简洁直观
// 初始化队列
void init(PQUEUE);
// 判断队列是否为空
bool is_empty(PQUEUE);
// 队列是否已满
bool is_full(PQUEUE);
// 入队 
bool en_queue(PQUEUE, int);
// 出队 
bool out_queue(PQUEUE, int *);
// 遍历输出 
void traverse(PQUEUE);

int main()
{
	QUEUE Q;
	int val; // 出队的元素 
	init(&Q);
	en_queue(&Q, 1);
	en_queue(&Q, 2);
	en_queue(&Q, 3);
	en_queue(&Q, 4);
	en_queue(&Q, 5); 
	en_queue(&Q, 6); // 此时已满，无法入队
	en_queue(&Q, 7);
	en_queue(&Q, 8);
	traverse(&Q);
	if (out_queue(&Q, &val))
	{
		cout<<"出队成功！出队的元素是："<<val<<endl; 
	}
	else
	{
		cout<<"出队失败！"<<endl; 
	}
	traverse(&Q);
	return 0;
}

void init(PQUEUE pQ)
{
	pQ->pBase = (int *)malloc(sizeof(int)*MAXSIZE);
	if (pQ->pBase == NULL)
	{
		cout<<"动态内存分配失败！"<<endl;
		exit(-1); 
	}
	pQ->front = 0;
	pQ->rear = 0;
	return;
} 

bool is_empty(PQUEUE pQ)
{
	if (pQ->front == pQ->rear)
	{
		return true;
	}
	return false;
}

bool is_full(PQUEUE pQ)
{
	if ((pQ->rear + 1) % MAXSIZE == pQ->front)
	{
		return true;
	}
	return false;
}

bool en_queue(PQUEUE pQ, int val)
{
	if (is_full(pQ))
	{
		return false;
	}
	else
	{
		pQ->pBase[pQ->rear] = val;
	    pQ->rear = (pQ->rear + 1) % MAXSIZE;
	    return true;
	}	
}

bool out_queue(PQUEUE pQ, int * pVal)
{
	if (is_empty(pQ))
	{
		return false;
	}
	else
	{
		*pVal = pQ->pBase[pQ->front];
		pQ->front = (pQ->front + 1) % MAXSIZE;
		return true;
	}
}

void traverse(PQUEUE pQ)
{
	int i = pQ->front;
	while (i != pQ->rear)
	{
		cout<<pQ->pBase[i]<<' ';
		i = (i + 1) % MAXSIZE;
	}
	cout<<endl;
}

