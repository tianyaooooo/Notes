// 用 C++ 中的类实现，思路方法和之前用 struct 完全相同  

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Node
{
	int data;
	struct Node * pNext;	
} NODE, * PNODE;

class Queue
{
private:
	PNODE front, rear;	
public:
	Queue()
	{
		front = new NODE;
		if (front == NULL)
		{
			cout<<"动态内存分配失败！"<<endl;
			exit(-1); 
		}
		front->pNext = NULL;
		rear = front;
	}
	
	void en_queue(int val)
	{
		PNODE pNew = new NODE;
		if (pNew == NULL)
		{
			cout<<"动态内存分配失败！"<<endl;
			exit(-1); 
		}
		pNew->data = val;
		pNew->pNext = NULL;
		rear->pNext = pNew; // 将 pNew 挂到队列尾部 
		rear = pNew; 
		return;
	}
	
	bool is_empty()
	{
		return front == rear? true:false;
	}
	
	bool out_queue(int * pVal)
	{
		if (is_empty())
		{
			return false;
		}
		else
		{
			PNODE pTemp = front->pNext;
			*pVal = pTemp->data;
			front->pNext = pTemp->pNext;
			if (rear == pTemp)
			{
				rear = front;
			}
			delete pTemp;
			return true; 
		}
	}
	
	void traverse()
	{
		PNODE pTemp = front;
		while (pTemp != rear) 
		{
			pTemp = pTemp->pNext;
			cout<<pTemp->data<<' ';
		}
		cout<<endl;
	}
	
	void clear()
	{
		PNODE p = front->pNext;
		while (p != NULL)
		{
			PNODE q = p->pNext;
			delete p;
			p = q;
		}
		rear = front;
		return;
	}
	
	~Queue()
	{
		clear();
		delete front;
	}	
};

int main()
{
	Queue Q;
	int val; // 出队的元素
	Q.en_queue(1);
	Q.en_queue(2);
	Q.en_queue(3);
	Q.en_queue(4);
	Q.en_queue(5);
	Q.en_queue(6);
	Q.en_queue(7);
	Q.en_queue(8); // 链式队列不存在满的概念 
	Q.traverse();
	if (Q.out_queue(&val))
	{
		cout<<"出队成功！出队的元素是："<<val<<endl; 
	}
	else
	{
		cout<<"出队失败！"<<endl; 
	}
	Q.traverse();
	return 0;
}

