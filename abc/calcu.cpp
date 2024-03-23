//sq_Stack.h
#include <iostream>
#include "sq_Stack.h"
#include "func_config.h"
#include <sstream>
#include <string>
#include "calcu.h"

using namespace std;

int priority(char ch);
double multy_number_in(char** temp, int* cnt);

/*
* 计算函数：传入字符串，返回double结果
*/
double calculator(char *str,char **sta)
{
	sq_Stack<char> OPS(20);				//运算符栈
	sq_Stack<double> OVS(20);			//数字栈
	OPS.ins_sq_Stack(';');

	//char str[26];
	fgets(str, 25, stdin);
	char* temp = str;
	int flag = 1;		//符号位
	int func_numb = -1;	//函数标志位，函数代号
	char func_buffer[10];//函数暂存缓存
	char* func_buffer_ptr = func_buffer;//函数暂存缓存操作指针

	while (1)
	{
		if (*temp >= '0' && *temp <= '9')		//读入数字
		{
			double cache;						//建立一个缓存
			int cnt = 0;				//统计数的位数
			cache = multy_number_in(&temp, &cnt);
			if (*temp == '.')			//是小数
			{
				temp++;
				cnt = 0;		//重新计数
				cache += multy_number_in(&temp, &cnt) * pow(0.1, cnt);
				OVS.ins_sq_Stack(cache*flag);		//入栈
			}
			else OVS.ins_sq_Stack(cache*flag);
			flag = 1;
		}
		else if (*temp == '+' || *temp == '-' || *temp == '*' || *temp == '/' || *temp == '^' || *temp == '(' || *temp == ')'||*temp==';'|| *temp == '{' ||* temp == '}')	//是运算符
		{
			if (*temp == '-' && (OPS.read_sq_Stack() == ';' || OPS.read_sq_Stack() == '(') && (*(temp - 1) < '0' || *(temp - 1) > '9') && *(temp - 1) != ')' && *(temp - 1) != '%')		//为负号
			{
				flag = -1;
				temp++;
			}
			else if (*temp == '+' && (OPS.read_sq_Stack() == ';' || OPS.read_sq_Stack() == '(') && (*(temp - 1) < '0' || *(temp - 1) > '9') && *(temp - 1) != ')'&&*(temp - 1) != '%')	//为正号
			{
				temp++;
			}
			else if (*temp == '(' || *temp == '{' || priority(*temp) > priority(OPS.read_sq_Stack()))		//优先级高
			{
				OPS.ins_sq_Stack(*temp);
				temp++;
			}

			else if (*temp == ')' && OPS.read_sq_Stack() == '(')		//括号处理
			{
				OPS.del_sq_Stack();
				temp++;
			}
			else if (*temp == '}' && OPS.read_sq_Stack() == '{')		//函数括号处理
			{
				OPS.del_sq_Stack();
				temp++;
				if (func_numb != -1)								//有函数
				{
					OVS.ins_sq_Stack(func_config_func_use(func_numb, OVS.del_sq_Stack()));		//计算函数结果，并存入数字栈
					func_numb = -1;
				}
			}
			else if ((*temp <'0' || *temp > '9') && (priority(*temp) <= priority(OPS.read_sq_Stack())) && OPS.return_top() > 1)		//优先级低
			{
				char ch = OPS.del_sq_Stack();
				double i,j;
				i = OVS.del_sq_Stack();
				j = OVS.del_sq_Stack();
				if (ch == '+') OVS.ins_sq_Stack(i + j);
				else if (ch == '-') OVS.ins_sq_Stack(j - i);
				else if (ch == '*') OVS.ins_sq_Stack(i * j);
				else if (ch == '/') OVS.ins_sq_Stack(j / i);
				else if (ch == '^') OVS.ins_sq_Stack(pow(j,i));
			}
			if (*temp == ';'&&OPS.read_sq_Stack()==';' && OVS.return_top() == 1)			//运算完成
			{
				*sta[0] = '\0';
				return OVS.del_sq_Stack();
				break;
			}
		}
		else if (*temp == '%')
		{
			OVS.ins_sq_Stack(0.01*OVS.del_sq_Stack());
			temp++;
		}
		else if (*temp >= 'a' && *temp <= 'z')					//可能是函数
		{
			func_buffer_ptr = func_buffer;						//指针指向buffer首部
			while (1)
			{
				if (*temp == '{') break;
				if (*temp == ';') goto ERR0;
				*func_buffer_ptr = *temp;
				temp++; 
				func_buffer_ptr++;
			}
			*func_buffer_ptr = '\0';						//变为字符串
			func_numb = func_config_func_find(func_buffer);		//查找函数
			if (func_numb == -1)
			{
				*sta = "ERR1: Can not find such function!";
				break;
			}
		}
		else
		{
			ERR0:
			*sta = "ERR0: Invalid format!";
			break;
		}
	}
 }

 /*
 * 功能：优先级函数传入运算符，返回其优先级
 */
int priority(char ch)
{
	switch (ch)
	{
	case ';':return 0;
	case '-':return 1;
	case '+':return 1;
	case '*':return 2;
	case '/':return 2;
	case '^':return 3;
	default:return -1;
	}
}

/*
* 功能：从str循环读入字符直到遇见非数字字符结束，将读入到的数按多位数形式返回，并返回多位数的位数。
* 参数：**temp：指向当前读入指针的指针。*cnt：指向计数器cnt的指针。
* 返回：从str读入的多位数。
*/
double multy_number_in(char** temp, int* cnt)
{
	double number;	//要返回的数
	number = **temp - '0';
	(*cnt)++;
	while (1)
	{
		(*temp)++;
		if (**temp >= '0' && **temp <= '9')	//下一位是数字
		{
			number = number * 10 + (**temp - '0');
			(*cnt)++;
		}
		else break;		//返回后指针指向非数字字符
	}
	return number;
}