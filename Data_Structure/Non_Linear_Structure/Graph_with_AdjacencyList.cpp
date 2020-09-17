/*
本程序的功能包括：用图的邻接表存储方式创建带权无向图、深度优先遍历、广度优先遍历 
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define INFINITY 65535
#define MAX 10

// 边表的结点 
typedef struct EdgeNode
{
	int index;
	int weight;
	struct EdgeNode * next;
} EdgeNode;

// 顶点表的结点 
typedef struct VertexNode
{
	char data;
	EdgeNode * firstedge; 
	
} VertexNode;

typedef struct Graph
{
	VertexNode * pVertexs; // 顶点表，动态数组 
	int NumVertexs; // 当前图中的顶点数 
	int NumEdges; // 当前图中的边数
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

// 用图的邻接表存储方式创建带权无向图
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
	G->pVertexs = new VertexNode[G->NumVertexs];
	cout<<"请输入图的顶点，用空格隔开：" ; 
	for (int i = 0; i < G->NumVertexs; i++)
	{
		cin>>G->pVertexs[i].data; // 输入顶点，例如 B C D A E 
		G->pVertexs[i].firstedge = NULL; // 初始化顶点的第一条边 
	}
	// 建立边表
	EdgeNode * e;
	for (int i = 0; i < G->NumEdges; i++)
	{
		cout<<"请输入边(vi, vj)的下标 i, j 和权，用空格隔开：";
		// 例如刚才输入的 B C D A E 分别对应 v0 v1 v2 v3 v4
		// 若 B 和 C 间存在权为5的边，则此处输入 0 1 5，当然也可以直接输入顶点字符，然后在顶点表里寻找对应标号 
		int j, k, w;
		cin>>j>>k>>w;
		e = new EdgeNode;
		e->index = k;
		e->weight =  w;
		e->next = G->pVertexs[j].firstedge;
		G->pVertexs[j].firstedge = e; // 头插法 
		
		e = new EdgeNode;
		e->index = j;
		e->weight =  w;
		e->next = G->pVertexs[k].firstedge;
		G->pVertexs[k].firstedge = e; // 无向图 对称 
	} 
}

void DFS(PGRAPH G, int i)
{
	visited[i] = true;
	cout<<G->pVertexs[i].data;
	EdgeNode * e = G->pVertexs[i].firstedge;
	while (NULL != e && visited[e->index] == false)
	{
		DFS(G, e->index);
		e = e->next;
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
			DFS(G, i);
		}
	}
}

void BFS(PGRAPH G, int i)
{
	QUEUE Q;
	init(&Q);
	visited[i] = true;
	cout<<G->pVertexs[i].data;
	en_queue(&Q, i);
	EdgeNode * e;
	while (!is_empty(&Q))
	{
		out_queue(&Q, &i);
		e = G->pVertexs[i].firstedge;
		while (e != NULL && visited[e->index] == false)
		{
			visited[e->index] = true;
			cout<<G->pVertexs[e->index].data;
			en_queue(&Q, e->index);
			e = e->next;
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
			BFS(G, i);
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

