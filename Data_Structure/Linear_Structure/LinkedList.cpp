#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Node
{
	int data; // 数据域
	struct Node * pNext; // 指针域 	
}NODE, * PNODE; // NODE 相当于 struct Node，* PNODE 相当于 struct Node *

// 创建一个非循环单链表 
PNODE create_list();
// 遍历链表 
void traverse_list(PNODE pHead);
// 判断链表是否为空
bool is_empty(PNODE pHead);
// 求链表长度
int length_list(PNODE pHead); 
// 插入结点 （在第 pos 个元素前插入一个新的结点，该结点的值为 val，1 <= pos <= len + 1） 
bool insert_list(PNODE pHead, int pos, int val);
// 删除结点（返回是否删除并带回删除的值） 
bool delete_list(PNODE pHead, int pos, int * pval);
// 排序
void sort_list(PNODE pHead);
 
int main()
{
	PNODE pHead = create_list();
	traverse_list(pHead);
	if (is_empty(pHead))
	{
		cout<<"链表为空！"<<endl; 
	}
	else
	{
		cout<<"链表不空！"<<endl; 
	}
	cout<<"链表长度为 "<<length_list(pHead)<<endl;
	sort_list(pHead);
	traverse_list(pHead);
	insert_list(pHead, 10, 666);
	traverse_list(pHead);
	
	int val;
	if (delete_list(pHead, 3, &val))
	{
		cout<<"删除成功！您删除的元素是："<<val<<endl; 
	}
	traverse_list(pHead);
	return 0;
}

PNODE create_list()
{
	cout<<"请输入您需要生成的链表的结点个数： len = ";
	int len;
	cin>>len;
	// 分配了一个不存放有效数据的头结点 
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	if (pHead == NULL) // 总是忘记！ 
	{
		cout<<"内存分配失败，程序终止！"<<endl;
		exit(-1); 
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL; // 不要忘了，因为可能一个数据也没有
	 
	for (int i = 0; i < len; i++)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if (pNew == NULL)
		{
			cout<<"内存分配失败，程序终止！"<<endl;
			exit(-1); 
		}
		cout<<"请输入第 "<<i + 1<<" 个结点的值："; 
		cin>>pNew->data;
		pTail->pNext = pNew;
		pNew->pNext = NULL; // 注意！！ 
		pTail = pNew;
	}
	return pHead; 
}

void traverse_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	while (p != NULL)
	{
		cout<<p->data<<' ';
		p = p->pNext; // 类似 ++ 
	}
	cout<<endl;
	return; 
}

bool is_empty(PNODE pHead)
{
	if (pHead->pNext == NULL)
	{
		return true;
	}
	return false;
}

int length_list(PNODE pHead)
{
	int len = 0;
	PNODE p = pHead->pNext;
	while (p != NULL)
	{
		len++;
		p = p->pNext; // 总是忘记！ 
	}
	return len;
}

// 以选择排序为例 
void sort_list(PNODE pHead)
{
	PNODE p, q;
	int temp;
	p = pHead->pNext;
	while (p != NULL)
	{
		q = p->pNext;
		while (q != NULL)
		{
			if (p->data > q->data)
			{
				temp = p->data;
				p->data = q->data;
				q->data = temp;	
			}
			q = q->pNext;
		}
		p = p->pNext;
	}
} 

bool insert_list(PNODE pHead, int pos, int val)
{
	if (pos < 1)
	{
		cout<<"给定插入位置小于下界！"<<endl; 
		return false;
	}
	int i = 0;
	PNODE p = pHead;
	while (i < pos - 1 && p != NULL) // 为了找到 pos 前一个结点的位置，两种情况：找到了或链表结束了还不够 pos 指定位置的前一个位置 
	{
		p = p->pNext;
		i++;
	} // while 执行结束时 p 指向 pos 前一个结点（可能是中间结点也可能是尾结点） 或  NULL（此时定要返回 false）
      // 当 pos 为 1 时，不用执行 while 循环，p 已指向 pos 前一结点，即 pHead
	if (p == NULL) 
	{
		cout<<"给定插入位置大于上界！"<<endl; 
		return false;
	}
	PNODE q = (PNODE) malloc(sizeof(NODE)); 
	if (q == NULL)
	{
		cout<<"内存分配失败，程序终止！"<<endl;			
		exit(-1); 
	}
	q->data = val;
	PNODE r = p->pNext;
	p->pNext = q;
	q->pNext = r;
	return true;
}

bool delete_list(PNODE pHead, int pos, int * pval)
{
	if (pos < 1)
	{
		cout<<"给定删除位置小于下界！"<<endl; 
		return false;
	}
	int i = 0;
	PNODE p = pHead;
	while (i < pos - 1 && p->pNext != NULL) 
	{
		p = p->pNext;
		i++;
	} // while 执行结束时 p 指向 pos 前一个结点（待删除元素是存放着有效数据的 p->pNext）或尾结点（此时定要返回 false） 
	if (p->pNext == NULL) 
	{
		cout<<"给定删除位置大于上界！"<<endl; 
		return false;
	}
	
	PNODE r = p->pNext;
	* pval = r->data;
	p->pNext = p->pNext->pNext;
	free(r);
	r = NULL;
	return true;
}


/* 
1. 插入结点的两种方法（伪代码） 
把 q 所指向的结点插到 p 所指向的结点后面 

方法一：通过临时变量，类似于两个数交换值 t = a, a = b, b = t 
r = p->pNext;
p->pNext = q;
q->pNext = r; 

方法二：先连后断
q->pNext = p->pNext;
p->pNext = q; // 两行代码不能换顺序 
 
2. 删除结点 
r = p->pNext;
p->pNext = p->pNext->pNext
free(r); // 内存释放很重要，否则造成内存泄露
*/

