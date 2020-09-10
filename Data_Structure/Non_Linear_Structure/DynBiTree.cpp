/*
本程序的功能包括：（基于先序序列）动态创建链式二叉树、先序遍历二叉树、中序遍历二叉树、后序遍历二叉树 
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct BiTNode
{
	char data;
	struct BiTNode * pLchild;
	struct BiTNode * pRchild;
} BiTNode, * BiTree;

// 先序动态创建链式二叉树 
void Pre_Dyn_CreateBiTree(BiTree * T);
// 先序遍历
void PreOrderTraverse(BiTree pT);
// 中序遍历
void InOrderTraverse(BiTree pT); 
// 后序遍历
void PostOrderTraverse(BiTree pT);

int main()
{
	BiTree t;
	Pre_Dyn_CreateBiTree(&t);
	cout<<"先序：";
	PreOrderTraverse(t);
	cout<<"\n中序："; 
	InOrderTraverse(t);
	cout<<"\n后序：";
	PostOrderTraverse(t);
	return 0; 
}

/*
例子 
希望在内存中建立的二叉树
          A
        /  \
       B    C
        \ 
         D

转化为扩展二叉树 
          A
        /   \
       B     C
      / \   / \
     #   D #   #
        / \ 
       #  #
       
输入：AB#D##C##
输出： 先序：ABDC
       中序：BDAC
       后序：DBCA 
*/ 

/* 
动态创建链式二叉树的注意事项：
1. 形参是个指向结构体变量的指针的指针，目的是为了在函数结束后把根结点的指针带出来，类似链表删除中的 int * val
2. 我们是以先序的顺序来创建二叉树的，但问题是无论以先序还是中序或者后序，我们都无法唯一确定该二叉树，
   解决的办法是：将二叉树中每个结点的空指针引出一个虚结点，其值为一特定值，比如 '#' 表示结点为空，由此得到“扩展二叉树” 
   扩展二叉树可以做到一个遍历序列唯一确定一棵二叉树 
3. 中序和后序顺序也可以创建二叉树，比较复杂，不太会 
*/
void Pre_Dyn_CreateBiTree(BiTree * T)
{
	char temp;
	cin>>temp;
	if (temp == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (NULL == * T)
		{
			cout<<"动态内存分配失败！"<<endl;
			exit(-1); 
		} 
		(*T)->data = temp;
		Pre_Dyn_CreateBiTree(&((*T)->pLchild));
		Pre_Dyn_CreateBiTree(&((*T)->pRchild));
	}
}

void PreOrderTraverse(BiTree pT) 
{
	if (pT != NULL)
	{
		cout<<pT->data;
		PreOrderTraverse(pT->pLchild);
		PreOrderTraverse(pT->pRchild);
	}
	return;
}

void InOrderTraverse(BiTree pT) 
{
	if (pT != NULL)
	{
		InOrderTraverse(pT->pLchild);
		cout<<pT->data;
		InOrderTraverse(pT->pRchild);
	}
	return;
} 

void PostOrderTraverse(BiTree pT) 
{
	if (pT != NULL)
	{
		PostOrderTraverse(pT->pLchild);
		PostOrderTraverse(pT->pRchild);
		cout<<pT->data;
	}
	return;
} 


