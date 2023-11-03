
#include "framework.h"
#include <windows.h>

// TODO: Это пример библиотечной функции.
#include <iostream>
extern "C"
{
	unsigned int __stdcall stepen(unsigned int val1, unsigned int val2)
	{
		unsigned int res;
		res = pow(val1, val2);
		return res;
	}
	unsigned int __stdcall sravs(char* str1, char* str2)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "RUSSIAN");
		unsigned int res = 0;
		if (strcmp(str1, str2) == 0) res = 1;
		else res = 0;
		return res;
	}
	void __stdcall prints(char* str)
	{
		std::cout << str << std::endl;
	}
	void __stdcall printu(unsigned int ui)
	{
		std::cout << ui << std::endl;
	}
}
