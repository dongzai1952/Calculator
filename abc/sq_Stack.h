#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__

#include <iostream>
using namespace std;
//����˳�����ջ��
template <class T>
class sq_Stack
{
private:
	int mm;				//�洢�ռ�����
	int top;			//ջ��ָ��
	T* s;				//˳��ջ�洢�ռ��׵�ַ
public:
	int return_top(void);
	sq_Stack(int);		//ջ��ʼ��
	void prt_sq_Stack();	//˳�����ջ��ָ����ջ��Ԫ��
	int flag_sq_Stack();	//���˳��ջ״̬
	void ins_sq_Stack(T);	//��ջ
	T del_sq_Stack();		//��ջ
	T read_sq_Stack();		//��ջ��Ԫ��
};

//����topֵ
template <class T>
int sq_Stack<T>::return_top(void)
{
	return top;
}
//��������Ϊmm�Ŀ�ջ
template <class T>
sq_Stack<T>::sq_Stack(int m)		//���캯��
{
	mm = m;
	s = new T[mm];
	top = 0;
	return;
}

//˳�����ջ��ָ����ջ��Ԫ��
template <class T>
void sq_Stack<T>::prt_sq_Stack()
{
	int i;
	cout << "top=" << top << endl;
	for (i = top; i > 0; i--) cout << s[i - 1] << endl;
	return;
}

//���˳��ջ��״̬
template <class T>
int sq_Stack<T>::flag_sq_Stack()
{
	if (top == mm) return -1;	//��ջ����-1
	if (top == 0) return 0;		//��ջ����0
	return 1;					//�����������1
}

//��ջ
template <class T>
void sq_Stack<T>::ins_sq_Stack(T x)
{
	if (top == mm)				//��ջ
	{
		cout << "Stack overflow!" << endl;
		return;
	}
	top++;
	s[top - 1] = x;
	return;
}

//��ջ
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

//����ջ��Ԫ��
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