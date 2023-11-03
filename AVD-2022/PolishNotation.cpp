#include "PolishNotation.h"
#include <iostream>
using namespace std;

namespace PN
{
	void SearchEq(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			if ((lextable.table[i].lexema == LEX_EQUALSSIGN) || (lextable.table[i].lexema == LEX_RETURN) || (lextable.table[i].lexema == LEX_PRINT))
			{
				PolishNotation(i + 1, lextable, idtable);
			}
		}
	}
	bool PolishNotation(int lexpos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		std::stack<LT::Entry> st;
		LT::Entry outstr[200];
		int len = 0,							//общая длина
			lenout = 0,							//длина выходной строки
			semicolonid = 0;						//ид для элемента таблицы с точкой с запятой
		char t, oper = '\0';
		int hesis = 0;				//текущий символ/знак оператора/кол-во скобок
		int indoffunk;							//индекс для замены на элемент с функцией
		bool rc = false;
		int npar = 0;
		for (int i = lexpos; lextable.table[i].lexema != LEX_SEMICOLON; i++)
		{
			len = i;
			semicolonid = i + 1;
		}
		len++;
		for (int i = lexpos; i < len; i++)
		{
			t = lextable.table[i].lexema;
			if (lextable.table[i].lexema == LEX_PLUS)
				oper = idtable.table[lextable.table[i].idxTI].id[0];
			if (t == LEX_RIGHTHESIS)						//выталкивание всего до другой левой скобки
			{
				while (st.top().lexema != LEX_LEFTHESIS)
				{
					outstr[lenout++] = st.top();			//записываем в выходную строку очередной символ между скобками
					hesis++;
					st.pop();								//удаляем вершину стека
				}
				st.pop();								//удаляем левую скобку в стеке
			}
			if (t == LEX_ID || t == LEX_LITERAL)
			{
				if (lextable.table[i + 1].lexema == LEX_LEFTHESIS)
				{
					outstr[lenout++] = lextable.table[i];
					indoffunk = i;
					i += 2;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS)
					{								//пока внутри аргументов функции, переписываем их в строку
						if (lextable.table[i].lexema != LEX_COMMA)
						{
							outstr[lenout++] = lextable.table[i++];
						}
						else
						{
							npar++;
							hesis++;
							i++;
						}
					}
					outstr[lenout++] = lextable.table[indoffunk];
					outstr[lenout - 1].lexema = LEX_NEWPROC;
					outstr[lenout - 1].par = npar + 1;
					outstr[lenout - 1].idxTI = lextable.table[indoffunk].idxTI;
					npar = 0;
					hesis += 1;
				}
				else
					outstr[lenout++] = lextable.table[i];
			}
			if (t == LEX_LEFTHESIS)
			{
				st.push(lextable.table[i]);							//помещаем в стек левую скобку
				hesis++;
			}

			if (oper == '+' || oper == '-' || oper == '*' || oper == '/')
			{
				if (!st.size())
					st.push(lextable.table[i]);
				else {
					int pr, id;
					if (st.top().lexema == '(' || st.top().lexema == ')')
						pr = 1;
					else {
						id = st.top().idxTI;
						pr = ArifmPriorities(idtable.table[id].id[0]);
					}
					if (ArifmPriorities(oper) > pr)																		//если приоритет добавляемой операции больше операции на вершине стека
						st.push(lextable.table[i]);																		//добавляем операции в стек
					else
					{
						while (st.size() && ArifmPriorities(oper) <= ArifmPriorities(idtable.table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable.table[i]);
					}
				}
			}
			oper = NULL;				//обнуляем поле знака
		}
		while (st.size())
		{
			outstr[lenout++] = st.top();												//вывод в строку всех знаков из стека
			st.pop();
		}
		for (int i = lexpos, k = 0; i < lexpos + lenout; i++, k++)
		{
			lextable.table[i] = outstr[k];										//запись в таблицу польской записи
			rc = true;
		}
		lextable.table[lexpos + lenout] = lextable.table[semicolonid];         //вставка элемента с точкой с запятой
		for (int i = 0; i < hesis; i++)
		{
			for (int j = lexpos + lenout + 1; j < lextable.size; j++)				//сдвигаем на лишнее место
			{
				lextable.table[j] = lextable.table[j + 1];
			}
			lextable.table[lextable.size - hesis + i + 1].lexema = '-';
			lextable.table[lextable.size - hesis + i + 1].sn = 0;
			lextable.table[lextable.size - hesis + i + 1].idxTI = TI_NULLIDX;
		}
		return rc;
	}
	int ArifmPriorities(char symb)
	{
		if (symb == LEX_LEFTHESIS || symb == LEX_RIGHTHESIS)
			return 1;
		if (symb == '+' || symb == '-')
			return 2;
		if (symb == '*' || symb == '/')
			return 3;
	}
}