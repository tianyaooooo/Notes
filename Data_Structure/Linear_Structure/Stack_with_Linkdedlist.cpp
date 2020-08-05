#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Node
{
	int data;
	struct Node * pNext;	
} NODE, * PNODE;

typedef struct Stack
{
	PNODE pTop; 
	PNODE pBottom;
} STACK, * PSTACK;

// 初始化，目的是造出一个空栈 
void init(PSTACK pS);
// 压栈 
void push(PSTACK pS, int val);
// 判断栈是否为空 
bool is_empty(PSTACK pS);
// 出栈 把 pS 所指向的栈出栈一次，并把出栈的元素存入 pVal 形参所指向的变量中，如果出栈失败（已是空栈），返回 false，否则返回 true 
bool pop(PSTACK pS, int * pVal);
// 从栈顶到栈底遍历输出 
void traverse(PSTACK pS);
// 清空栈，但栈结构还在（重回 init 后的样子） 
void clear(PSTACK pS);

int main()
{
	int val; // 出栈元素的值 
	STACK S;
	init(&S); 
	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	push(&S, 5);
	push(&S, 6);
	traverse(&S);
	if(pop(&S, &val))
	{
		cout<<"出栈成功！出栈的元素是"<<val<<endl; 
	}
	else
	{
		cout<<"出栈失败！"<<endl; 
	}
	traverse(&S);
	clear(&S);
	traverse(&S);
	return 0;
}

void init(PSTACK pS)
{
	pS->pBottom = (PNODE)malloc(sizeof(NODE));
	if (pS->pBottom == NULL)
	{
		cout<<"动态内存分配失败！"<<endl;
		exit(-1); 
	}
	pS->pTop = pS->pBottom; 
	pS->pBottom->pNext = NULL; // 别忘记清空指针域！！ 
	return; 
}

void push(PSTACK pS, int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL)
	{
		cout<<"动态内存分配失败！"<<endl;
		exit(-1); 
	}
	pNew->data = val;
	pNew->pNext = pS->pTop;
	pS->pTop = pNew; 
	return;
}

bool is_empty(PSTACK pS)
{
	if (pS->pBottom == pS->pTop)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool pop(PSTACK pS, int * pVal)
{
	if (is_empty(pS))
	{
		return false;
	}
	else
	{
		PNODE r = pS->pTop;
		*pVal = r->data;
		pS->pTop = r->pNext;
		free(r);
		r = NULL; // 别忘记清空指针
		return true;
	}
}

void traverse(PSTACK pS)
{
	PNODE p = pS->pTop;
	while(p != pS->pBottom)
	{
		cout<<p->data<<' ';
		p = p->pNext;
	}
	cout<<endl;
	return;
}

void clear(PSTACK pS)
{
	if (is_empty(pS))
	{
		return;
	}
	else
	{
		PNODE p = pS->pTop;
		while (p != pS->pBottom)
		{
			PNODE q = p->pNext;
			free(p);
			p = q;
			q = NULL;
		}
		pS->pTop = pS->pBottom;
		p = NULL;
	}
	return;
} 

