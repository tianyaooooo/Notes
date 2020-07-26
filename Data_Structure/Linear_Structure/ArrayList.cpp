#include<iostream>
#include<stdlib.h> 
using namespace std;

//定义了一个名叫 struct Arr 的数据类型，改数据类型包含三个成员 
struct Arr
{
	int * pBase; //存储的是数组第一个元素的地址 
	int len; // 数组所能容纳的最大元素个数 
	int cnt; // 当前数组有效元素的个数
	double increment; // 自动增长因子，老师说需要用 allocate 函数，但我对此不太熟悉，故自己写了一种，如有错误还请指出 
};

// 初始化数组 
void init_arr(struct Arr * pArr, int len,  double alpha); 
// 动态扩容 
bool extend_arr(struct Arr * pArr);
// 在最后一位添加元素 
bool append_arr(struct Arr * pArr, int val);
// 在数组第 pos 个元素前插入元素，1 <= pos <= cnt  
bool insert_arr(struct Arr * pArr, int pos, int val);
// 删除数组中的第 pos 个元素前，1 <= pos <= cnt，并记录删除的元素是什么 
bool delete_arr(struct Arr * pArr, int pos, int * pVal);
// 返回给定 index 在数组中对应的值 （略） 
int get_arr(struct Arr * pArr, int index);
// 在数组中寻找给定值，并返回其下标，不存在则返回-1 
int find_arr(struct Arr * pArr, int val); 
// 判断数组是否为空 
bool is_empty(struct Arr * pArr);
// 判断数组是否已满 
bool is_full(struct Arr * pArr);
// 数组元素升序排列 
void sort_arr(struct Arr * pArr);
// 显示数组 
void show_arr(struct Arr * pArr);
// 倒置数组 
void reverse_arr(struct Arr * pArr);

int main ()
{
	struct Arr arr;
	int initlen = 2;
	int a = 2;
	int val;
	init_arr(&arr, initlen, a);
	append_arr(&arr, 1);
	append_arr(&arr, 2);
	append_arr(&arr, 3);
	insert_arr(&arr, 1, 99);
	insert_arr(&arr, 4, 88);
	//insert_arr(&arr, -1, 77); // 插入失败！插入范围越界！ 
	show_arr(&arr);
	if (delete_arr(&arr, 1, &val))
	{
		cout<<"删除成功！您删除的元素是："<<val<<endl; 
	}
	show_arr(&arr);
	reverse_arr(&arr);
	show_arr(&arr);
	sort_arr(&arr);
	show_arr(&arr);
	int index = find_arr(&arr, 99);
	cout<<index<<endl;
	return 0;
}
 
void init_arr(struct Arr * pArr, int length, double alpha)
{
	pArr->pBase = (int *) malloc(sizeof(int)*length);
	if (pArr->pBase==NULL)
	{
		cout<<"动态内存分配失败！"<<endl;
		exit(-1); // 终止整个程序 
	}
	pArr->cnt = 0;
	pArr->len=length;
	pArr->increment = alpha;
	return;	
}

bool is_empty(struct Arr * pArr)
{
	if (pArr->cnt==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_full(struct Arr * pArr)
{
	if (pArr->cnt==pArr->len)
	{
		return true;
	}
	else
	{
		return false;
	}
} 

bool extend_arr(struct Arr * pArr)
{
	int * ptemp = pArr->pBase; //设置临时指针，为了将来 free 原数组 
	pArr->pBase = (int *) malloc(sizeof(int)*((int)(pArr->cnt*pArr->increment))); 
	if (pArr->pBase == NULL)
	{
		cout<<"内存即将不足！"<<endl;
		exit(-1); 
	}
	for (int i = 0; i < pArr->cnt; i++)
	{
		pArr->pBase[i] = ptemp[i];
	}
	pArr->len = pArr->cnt*2;
	free(ptemp);
	return true;	
}


bool append_arr(struct Arr * pArr, int val)
{
	pArr->pBase[pArr->cnt] = val;
	pArr->cnt++;
	if (is_full(pArr))
	{
		extend_arr(pArr);
	}
	return true;
}

bool insert_arr(struct Arr * pArr, int pos, int val) //pos 从1开始 
{
	if (pos < 1 || pos > pArr->cnt)
	{
		cout << "插入失败！插入范围越界！"<<endl;
		return false; 
	}
	for (int i = pArr->cnt - 1; i >= pos - 1; i--)
	{
		pArr->pBase[i + 1] =  pArr->pBase[i];
	}
	pArr->pBase[pos - 1] = val;
	pArr->cnt++;
	if (is_full(pArr))
	{
		extend_arr(pArr);
	} 
	return true;
} 

bool delete_arr(struct Arr * pArr, int pos, int * pVal)
{
	if (is_empty(pArr))
	{
		cout<<"待删除的数组为空！"<<endl;
		return false;	
	} 
	if (pos < 1 || pos > pArr->cnt)
	{
		cout << "删除失败！删除范围越界！"<<endl;
		return false; 
	}
	* pVal = pArr->pBase[pos-1];
	for (int i = pos; i <= pArr->cnt - 1; i++)
	{
		pArr->pBase[i - 1] = pArr->pBase[i];
	} 
	pArr->cnt--; 
	return true;
	// 此处可以判断 cnt 与 len 的关系，若小于某阈值，
    // 则动态 shrink 数组，类似 extend_arr，减小空间复杂度，同时时间复杂度没有显著增加（摊还分析） 
	
}

// 注意这里不仅仅是要求输出时逆序显示，而是要求数组本身逆序 
void reverse_arr(struct Arr * pArr)
{
	int left, right;
	left = 0;
	right = pArr->cnt - 1; 
	while (left < right)
	{
		int temp;
		temp = pArr->pBase[left];
		pArr->pBase[left] = pArr->pBase[right];
		pArr->pBase[right] = temp;
		left++;
		right--;
	} 
	return;
} 

// 以冒泡排序为例 
void sort_arr(struct Arr * pArr)
{
	for (int i = 0; i < pArr->cnt - 1; i++)
	{
		for (int j = 0; j < pArr->cnt - 1 - i; j++)
		{
			if (pArr->pBase[j] > pArr->pBase[j + 1])
			{
				int temp;
				temp = pArr->pBase[j];
				pArr->pBase[j] =  pArr->pBase[j + 1];
				pArr->pBase[j + 1] = temp;
			}
			
		}	
	} 
    return; 
} 

int find_arr(struct Arr * pArr, int val)
{
	for (int i = 0; i < pArr->cnt; i++)
	{
		if (pArr->pBase[i] == val)
		{
			return i;
		}
	}
	return -1;
}

void show_arr(struct Arr * pArr)
{
	if (is_empty(pArr))
	{
		cout<<"数组为空！"<<endl;	
	} 
	else
	{
		for (int i = 0; i < pArr->cnt; i++)
		{
			cout<<pArr->pBase[i]<<' ';
		}
		cout<<endl;
	}	
} 
