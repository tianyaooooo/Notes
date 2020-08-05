#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Stack
{
	int * pBase; //存储的是数组的第一个元素的地址 
	int len; // 栈所能容纳的最大元素个数 
	int top; // 栈顶元素序号 
} STACK, * PSTACK;

// 初始化，目的是造出一个空栈 
void init(PSTACK pS, int length);
// 压栈 
bool push(PSTACK pS, int val);
// 出栈 把 pS 所指向的栈出栈一次，并把出栈的元素存入 pVal 形参所指向的变量中，如果出栈失败（已是空栈），返回 false，否则返回 true 
bool pop(PSTACK pS, int * pVal);
// 从栈顶到栈底遍历输出 
void show(PSTACK pS);

int main()
{
	int val; // 出栈元素的值 
	STACK S;
	init(&S, 6); 
	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	push(&S, 5);
	//push(&S, 6);
	show(&S);
	if(pop(&S, &val))
	{
		cout<<"出栈成功！出栈的元素是"<<val<<endl; 
	}
	else
	{
		cout<<"出栈失败！"<<endl; 
	}
	show(&S);
	return 0;
}

void init(PSTACK pS, int length)
{
	pS->pBase = (int *)malloc(sizeof(int)*length);
	if (pS->pBase == NULL)
	{
		cout<<"动态内存分配失败！"<<endl;
		exit(-1); 
	}
	pS->len = length;
	pS->top = -1;
	return;
} 

bool push(PSTACK pS, int val)
{
	if (pS->top == pS->len - 1) // 此处不考虑动态扩容，动态扩容方法详见 ArrayList.cpp 
	{
		return false; 
	}
	else
	{
		pS->top++; 
		pS->pBase[pS->top] = val;
		return true;
	}
}

bool pop(PSTACK pS, int * pVal)
{
	if (pS->top == -1)
	{
		return false;
	}
	else
	{
		*pVal = pS->pBase[pS->top];
		pS->top--;
		return true; 
	}
}

void show(PSTACK pS)
{
	for (int i = pS->top; i > -1; i--)
		{
			cout<<pS->pBase[i]<<' ';
		}
		cout<<endl;	
} 

