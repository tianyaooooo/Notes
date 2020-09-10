/*
本程序的功能包括：静态创建链式二叉树、先序遍历二叉树、中序遍历二叉树、后序遍历二叉树 
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

// 创建一个静态链式二叉树 
BiTree Sta_CreateBiTree();
// 先序遍历
void PreOrderTraverse(BiTree pT);
// 中序遍历
void InOrderTraverse(BiTree pT); 
// 后序遍历
void PostOrderTraverse(BiTree pT);

int main()
{
	BiTree pT = Sta_CreateBiTree();
	cout<<"先序：";
	PreOrderTraverse(pT);
	cout<<"\n中序："; 
	InOrderTraverse(pT);
	cout<<"\n后序：";
	PostOrderTraverse(pT);
	return 0;
}

/*
在内存中建立如下二叉树
          A
        /  \
       B    C
           /
         D
          \
           E 
*/

BiTree Sta_CreateBiTree()
{
	BiTree pA =  (BiTree)malloc(sizeof(BiTNode)); 
	BiTree pB =  (BiTree)malloc(sizeof(BiTNode));
	BiTree pC =  (BiTree)malloc(sizeof(BiTNode));
	BiTree pD =  (BiTree)malloc(sizeof(BiTNode));
	BiTree pE =  (BiTree)malloc(sizeof(BiTNode));
	
	pA->data = 'A';
	pB->data = 'B';
	pC->data = 'C';
	pD->data = 'D';
	pE->data = 'E';
	
	pA->pLchild = pB;
	pA->pRchild = pC;
	pB->pLchild = pB->pRchild = NULL;
	pC->pLchild = pD;
	pC->pRchild = NULL;
	pD->pLchild = NULL;
	pD->pRchild = pE;
	pE->pLchild = pE->pRchild = NULL;
	
	return pA;
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


