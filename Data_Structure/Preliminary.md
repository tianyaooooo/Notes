# 2	预备知识
## 2.1 指针定义
### 地址
内存单元的编号（从0开始的非负整数FFFFFFFF）。内存的单元是字节，即字节和编号是一一对应的。
![](https://note.youdao.com/yws/api/personal/file/WEB1c3f3cccfc7ec4663e9c21855c5bc63f?method=download&shareKey=9a0207a506e1a66c4afc195fa85e2cdf)  

### 指针
指针就是地址，地址就是指针。指针本质上是一个操作受限（不能加、乘等）的非负整数。指针变量是存放内存单元地址的变量。

## 2.2	指针分类
### 基本类型的指针
```C++
int * p; // p是个（指针）变量名字， int * 表示该变量 p 只能存储 int 类型的地址
int i =10;
int j;
p = &i; // *p等价于i
j = * p; // 等价于j = i
```
![](https://note.youdao.com/yws/api/personal/file/WEB75c2e1b58def3dd84dc678dde7c86062?method=download&shareKey=d48a5994c60902a2f60e356a07e3bddb)  

综上，p 存放了 i 的地址，所以我们说 p 指向了 i；p 和 i 是完全不同的两个变量，修改其中的任意一个变量的值不改变另一个的值；  

p 指向 i，* p就是 i 本身，即所有出现 * p 的地方都可以换成 i，所有出现 i 的地方都可以换成 * p；  

常量和表达式前不能加 &，如 & (3+5) 错。  

**另：如何通过 被调函数 修改 主调函数中普通变量的值？**  
    实参为相关变量的地址；  
    形参为以该变量的类型为类型的指针变量；  
    在被调函数中通过 *形参变量名 的方式就可以修改主函数中变量的值  
    
```C++
void f (int * p)
{
  *p = 100;
}

int main ()
{
  int i = 9;
  f (&i); // i的值变为100
  return 0;
}
```

### 指针和（一维）数组的关系
数组名：一维数组名是个指针常量，它存放的是一维数组第一个元素的地址，它的值不能被改变，即一维数组名 指向 数组的第一个元素。

下标和指针的关系：**a[i] <<==>> *(a+i)**，具体而言假设p是指针变量，则p+i的值是p+i*(p所指向的变量所占的字节数)。

## 2.3 结构体
### 如何使用结构体？

```C++
struct Student
{
	int sid;
	char name[200];
	int age;
};

int main ()
{
  struct Student st = {1000, “zhnagsan”,20};
	st.sid = 99; // 第一种方式
  
  struct Student * pst;
	pst = &st;
	pst->sid = 99; // 第二种方式 含义： pst 所指向的结构体变量中的sid成员
   // pst->sid 等价于 (*pst).sid，(*pst).sid 等价于 st.sid，pst->sid 等价于 st.sid （方式一二等价）	
  return 0; 
}
```
注意：普通结构体变量和结构体指针变量作为函数传参，推荐第二种，因为只发送地址，只占4个字节，内存消耗少，若用方式一，如上例子中定义的结构体，需要发送大于208个字节的信息。  

**另：关于 typedef 的用法**  

```C++
typedef int HAHA; // 为 int 再重新多取一个名字，HAHA 等价于 int 

typedef struct Student
{
	int sid;
	char name[200];
	int age;
}ST, * PST; // PST 代表了 struct Student * , ST 代表了 struct Student 

int main()
{
	ST st; // 等价于 struct Student st;
	PST pst = &st; // 等价于 ST * pst = &st; 等价于 struct Student * pst = &st; 
	return 0;
}
```
## 2.4 动态内存的分配和释放

```C++
#include<iostream>
#include<malloc.h>
using namespace std;

int main()
{
	int a[5] = {4, 10, 2, 8, 6}; //静态分配数组 
	
	int len;
	cout<<"请输入你需要分配的数组的长度： len = ";
	cin>>len;
	int * pArr = (int *) malloc (sizeof(int)*len);
	/* malloc 为分配内存的函数，分配的内存为 () 中的值，例如 len = 5，分配内存为20个字节
	   但 malloc仅返回第一个字节地址，而无法知道几个字节为一个变量，称为干地址，没有实际意义
	   (int *) 将分配的内存每4个字节划为一块；(double *) 八个字节为一块等等……
	   此时，pArr 存放了第一个元素的地址，类似于数组名 a
	*/   
	*pArr = 4; // 类似于 a[0] = 4
	pArr[1] = 10; // 类似于 a[1]=10 
	
	free(pArr); //把pArr所代表的动态分配的20个字节的内存释放 
	return 0; 
}
```

注意：malloc 需手动释放（free）内存，或程序全部结束后释放，可用于**跨函数使用内存**——即函数执行完毕，由 malloc 分配的内存仍然保留，可继续用于后续操作，类似全局变量。
