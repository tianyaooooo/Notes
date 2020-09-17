/*
本程序的功能包括：用图的邻接矩阵存储方式创建带权无向图、深度优先遍历、广度优先遍历 
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define INFINITY 65535
#define MAX 10

typedef struct Graph 
{
	char * pVertexs; // 顶点表，为节省空间，根据顶点数量动态申请数组空间 
	int ** pEdges; // 邻接矩阵，二维动态数组 
	int NumVertexs; // 当前图中的顶点数 
	int NumEdges; // 当前图中的顶点数
} GRAPH, * PGRAPH;

bool visited[MAX]; //设置为全局变量，DFS DFSTraverse BFS BFSTraverse 函数都有用到

/********************************************************/
// 广度优先遍历需要的循环队列 
typedef struct Queue
{
	int * pBase; // 循环数组的首地址
	int front; // 队头
	int rear; // 队尾 
} QUEUE, * PQUEUE;

// 队列的相关操作 
void init(PQUEUE pQ);
bool is_empty(PQUEUE pQ);
bool is_full(PQUEUE pQ);
bool en_queue(PQUEUE pQ, int val);
bool out_queue(PQUEUE pQ, int * pVal);
/********************************************************/

// 用图的邻接矩阵存储方式创建带权无向图
void CreateGraph(PGRAPH G);
// 从下标为 i 的顶点 pVertexs[i] 开始进行深度优先访问，若是连通图则可遍历所有顶点 
void DFS(PGRAPH G, int i); 
// 深度优先遍历
void DFSTraverse(PGRAPH G);
// 从下标为 i 的顶点 pVertexs[i] 开始进行广度优先访问，若是连通图则可遍历所有顶点 
void BFS(PGRAPH G, int i); 
// 广度优先遍历 
void BFSTraverse(PGRAPH G);

 
int main()
{
	GRAPH G;
	CreateGraph(&G); 
	cout<<"深度优先遍历：" ;
	DFSTraverse(&G);
	cout<<"\n广度优先遍历：" ;
	BFSTraverse(&G);
	return 0;
} 
 
void CreateGraph(PGRAPH G)
{
	cout<<"请输入图的顶点数和边数，用空格隔开：";
	cin>>G->NumVertexs>>G->NumEdges;
	G->pVertexs = new char[G->NumVertexs];
	cout<<"请输入图的顶点，用空格隔开：" ; 
	for (int i = 0; i < G->NumVertexs; i++)
	{
		cin>>G->pVertexs[i]; // 例如输入 B C D A E
	}
	G->pEdges = new int*[G->NumVertexs];
	for (int i = 0; i <G->NumVertexs; i++)
	{
		G->pEdges[i] = new int [G->NumVertexs];	
	} 
	// 邻接矩阵初始化
	for (int i = 0; i <G->NumVertexs; i++)
	{
		for (int j = 0; j <G->NumVertexs; j++)
		{
			G->pEdges[i][j] = INFINITY;	
		}		
	}  
	for (int i = 0; i <G->NumEdges; i++)
	{
		cout<<"请输入边(vi, vj)的下标 i, j 和权，用空格隔开：";
		// 例如刚才输入的 B C D A E 分别对应 v0 v1 v2 v3 v4
		// 若 B 和 C 间存在权为5的边，则此处输入 0 1 5，当然也可以直接输入顶点字符，然后在顶点表里寻找对应标号 
		int j, k, w;
		cin>>j>>k>>w;
		G->pEdges[j][k] = w;
		G->pEdges[k][j] = w; // 无向图，对称阵 		 
	}	
}

void DFS(PGRAPH G, int i)
{
	visited[i] = true;
	cout<<G->pVertexs[i];
	for (int j = 0; j < G->NumVertexs; j++)
	{
		if (G->pEdges[i][j] != INFINITY && visited[j] == false)
		{
			DFS(G, j);
		}	
	}	
} 

void DFSTraverse(PGRAPH G) 
{
	for (int i = 0; i < G->NumVertexs; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < G->NumVertexs; i++)
	{
		if (visited[i] == false)
		{
			DFS(G, i); //若是连通图，只会执行一次 DFS(G,0)
		}
	}
}

void BFS(PGRAPH G, int i)
{
	QUEUE Q;
	init(&Q); 
	visited[i] = true;
	cout<<G->pVertexs[i];
	en_queue(&Q, i);
	while (!is_empty(&Q))
	{
		out_queue(&Q, &i);
		for (int j = 0; j < G->NumVertexs; j++)
		{
			if (G->pEdges[i][j] != INFINITY && visited[j] == false)
			{
				visited[j] = true;
				cout<<G->pVertexs[j];
				en_queue(&Q, j);
			}
		}
	}
	
}

void BFSTraverse(PGRAPH G)
{
	for (int i = 0; i < G->NumVertexs; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < G->NumVertexs; i++)
	{
		if (visited[i] == false)
		{
			BFS(G, i); //若是连通图，只会执行一次 BFS(G,0)
		}
	}	
}

/********************************************************/
// 队列的相关操作 
void init(PQUEUE pQ)
{
	pQ->pBase = new int[MAX];
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
	if ((pQ->rear + 1) % MAX == pQ->front)
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
	    pQ->rear = (pQ->rear + 1) % MAX;
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
		pQ->front = (pQ->front + 1) % MAX;
		return true;
	}
}
/********************************************************/

