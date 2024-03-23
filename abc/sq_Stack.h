#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__

#include <iostream>
using namespace std;
//定义顺序查找栈类
template <class T>
class sq_Stack
{
private:
	int mm;				//存储空间容量
	int top;			//栈顶指针
	T* s;				//顺序栈存储空间首地址
public:
	int return_top(void);
	sq_Stack(int);		//栈初始化
	void prt_sq_Stack();	//顺序输出栈顶指针与栈中元素
	int flag_sq_Stack();	//检测顺序栈状态
	void ins_sq_Stack(T);	//入栈
	T del_sq_Stack();		//退栈
	T read_sq_Stack();		//读栈顶元素
};

//返回top值
template <class T>
int sq_Stack<T>::return_top(void)
{
	return top;
}
//建立容量为mm的空栈
template <class T>
sq_Stack<T>::sq_Stack(int m)		//构造函数
{
	mm = m;
	s = new T[mm];
	top = 0;
	return;
}

//顺序输出栈顶指针与栈中元素
template <class T>
void sq_Stack<T>::prt_sq_Stack()
{
	int i;
	cout << "top=" << top << endl;
	for (i = top; i > 0; i--) cout << s[i - 1] << endl;
	return;
}

//检测顺序栈的状态
template <class T>
int sq_Stack<T>::flag_sq_Stack()
{
	if (top == mm) return -1;	//满栈返回-1
	if (top == 0) return 0;		//空栈返回0
	return 1;					//正常情况返回1
}

//入栈
template <class T>
void sq_Stack<T>::ins_sq_Stack(T x)
{
	if (top == mm)				//满栈
	{
		cout << "Stack overflow!" << endl;
		return;
	}
	top++;
	s[top - 1] = x;
	return;
}

//退栈
template <class T>
T sq_Stack<T>::del_sq_Stack(void)
{
	T y;
	if (top == 0)
	{
		cout << "Stack underflow!" << endl;
		return 0;
	}
	y = s[top - 1];
	top--;
	return y;
}

//读出栈顶元素
template <class T>
T sq_Stack<T>::read_sq_Stack(void)
{
	if (top == 0)
	{
		cout << "Stack empty!" << endl;
		return 0;
	}
	return (s[top - 1]);
}

#endif