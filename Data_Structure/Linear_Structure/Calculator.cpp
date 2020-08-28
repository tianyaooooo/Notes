// 本文实现了一个简易计算器
// 仅支持自然数的加（+）减（-）乘（*）除（/）以及小括号（()）运算
// 测试用例：9+(3-1)*3+10/2 

#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;
#define MAXSIZE 100

// 定义一个栈 
// 中缀转后缀表达式的时候需要一个存放字符型元素的栈
// 后缀表达式的计算中又需要一个存放 double 型元素的栈
// 两个栈的方法一样，只是数据类型不同，故用 C++ 的类模板来实现
template <typename T>
class Stack
{
private:
	T * pBase;
	int top;
public:
	Stack()
	{
		pBase = new T[MAXSIZE];
		if (pBase == NULL)
		{
			cout<<"动态内存分配失败！"<<endl;
			exit(-1); 
		}
		top = -1;
	}
	bool push(T val);
	bool pop(T * pVal);
	bool is_empty();
	~Stack()
	{
		delete []pBase;
	}
};

template <typename T> bool Stack<T>::push(T t)
{
	if (top == MAXSIZE - 1) // 此处不考虑动态扩容
	{
		return false; 
	}
	else
	{
		top++; 
		pBase[top] = t;
		return true;
	}
}

template <typename T> bool Stack<T>::pop(T * pT)
{
	if (is_empty())
	{
		return false;
	}
	else
	{
		*pT = pBase[top];
		top--;
		return true; 
	}
}

template <typename T> bool Stack<T>::is_empty()
{
	return top == -1? true:false;
}


// 中缀表达式转后缀表达式 
// 对于负数的情况，只需对中缀表达式做一些预处理，即将负数 -a 看成是 0-a 	
bool Infix2Posrfix(char * Infix, char * Postfix)
{
	Stack<char> S;
	int i = 0, j = 0;
	char e;
	while (i < strlen(Infix))
	{
		while(Infix[i] >= '0' && Infix[i] <= '9')
		{
			//cout<<Infix[i];
			Postfix[j++] = Infix[i++];
			if (Infix[i] < '0' || Infix[i] >'9')
			{
				//cout<<" ";
				Postfix[j++] = ' ';
			}
		} // 解决多位数的问题 
				
		if (Infix[i] == '(')
		{
			S.push(Infix[i]);
		}
		else if (Infix[i] == ')')
		{
			S.pop(&e);
			while(e != '(')
			{
				//cout<<e<<" ";
				Postfix[j++] = e;
				Postfix[j++] = ' ';
				S.pop(&e);
			}
		}
		else if (Infix[i] == '+' || Infix[i] == '-')
		{
			if (!S.is_empty())
			{
				do
				{
					S.pop(&e);
					if (e == '(')
					{
						S.push(e);
						break;
					}
					else
					{
						//cout<<e<<" ";
						Postfix[j++] = e;
						Postfix[j++] = ' ';	
					}
				} while(!S.is_empty());
			}
			S.push(Infix[i]);	
		}
		else if (Infix[i] == '*' || Infix[i] == '/')
		{
			if (!S.is_empty())
			{
				do
				{
					S.pop(&e);
					if (e == '(' || e == '+' || e == '-')
					{
						S.push(e);
						break;
					}
					else
					{
						//cout<<e<<" ";
						Postfix[j++] = e;	
						Postfix[j++] = ' ';
					}
				} while(!S.is_empty());
			}
			S.push(Infix[i]);
		}
		else if (Infix[i] == '\0')
		{
			break;
		}
		else
		{
			cout<<"输入格式错误！（存在除数字和加减乘除号以外的字符）"<<endl;
			return false;
		}
		i++;
	}
	
	while(!S.is_empty())
	{
		S.pop(&e);
		//cout<<e<<" ";
		Postfix[j++] = e;	
		Postfix[j++] = ' ';
	}
	Postfix[j - 1] = '\0';
	return true;
}

// 后缀表达式的计算 
bool calc(char * Postfix, double * pResult)
{
	Stack<double> S;
	char ch[MAXSIZE];
	double a, b;
	int i = 0, j = 0;
	while (i < strlen(Postfix))
	{
		while(Postfix[i] >= '0' && Postfix[i] <= '9')
		{
			ch[j++] = Postfix[i++];
			if (Postfix[i] == ' ')
			{
				ch[j] = '\0';
				a = atof(ch);
				S.push(a);
				j = 0;
			}			
		}
		
		switch(Postfix[i])
		{
			case '+':
				S.pop(&a);
				S.pop(&b);
				S.push(b + a);
				break;
			case '-':
				S.pop(&a);
				S.pop(&b);
				S.push(b - a);
				break;
			case '*':
				S.pop(&a);
				S.pop(&b);
				S.push(b * a);
				break;
			case '/':
				S.pop(&a);
				if (a == 0)
				{
					cout<<"输入格式错误！（分母为零）"<<endl;
					return false;
				}
				S.pop(&b);
				S.push(b / a);			
		}
		i++;		
	}
	S.pop(pResult);
	return true;
}


int main()
{
	cout<<"<本文实现了一个简易计算器>"<<endl;
	cout<<"<仅支持自然数的加（+）减（-）乘（*）除（/）以及小括号（()）运算>" <<endl;
	cout<<"<对于不合法的表达式，有可能得到正确计算结果，但请避免此类输入，例如 3++5, 10+, 123 等>"<<endl; 
	cout<<endl; 
	cout<<"请输入待计算的合法表达式：";
	char InExpression[MAXSIZE], PostExpression[MAXSIZE];
	double result;
	cin.getline(InExpression, MAXSIZE);
	if (Infix2Posrfix(InExpression, PostExpression) && calc(PostExpression, &result))
	{
		cout<<"计算结果为："<<result<<endl; 
	}
	return 0;
}

