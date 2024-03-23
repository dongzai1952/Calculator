#include "func_config.h"

const char* func_list[] = { "sin","cos","tan","asin","acos","atan"};		//可用的函数列表

/*
* 函数查找函数
*/
int func_config_func_find(char* str)
{
	int i;
	int flag = 0;
	for (i = 0; i < 6; i++)
	{
		if (strcmp(func_list[i], str) == 0) 
		{
			flag = 1;
			break;
		}
	}
	if (flag) return i;
	else return -1;
}

/*
* 函数使用函数
*/
double func_config_func_use(int func_numb,double x)
{
	switch (func_numb)
	{
	case 0:return sin(x);
	case 1:return cos(x);
	case 2:return tan(x);
	case 3:return asin(x);
	case 4:return acos(x);
	case 5:return atan(x);
	default:return -1;
	}
}