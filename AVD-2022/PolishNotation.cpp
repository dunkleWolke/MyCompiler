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
		int len = 0,							//����� �����
			lenout = 0,							//����� �������� ������
			semicolonid = 0;						//�� ��� �������� ������� � ������ � �������
		char t, oper = '\0';
		int hesis = 0;				//������� ������/���� ���������/���-�� ������
		int indoffunk;							//������ ��� ������ �� ������� � ��������
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
			if (t == LEX_RIGHTHESIS)						//������������ ����� �� ������ ����� ������
			{
				while (st.top().lexema != LEX_LEFTHESIS)
				{
					outstr[lenout++] = st.top();			//���������� � �������� ������ ��������� ������ ����� ��������
					hesis++;
					st.pop();								//������� ������� �����
				}
				st.pop();								//������� ����� ������ � �����
			}
			if (t == LEX_ID || t == LEX_LITERAL)
			{
				if (lextable.table[i + 1].lexema == LEX_LEFTHESIS)
				{
					outstr[lenout++] = lextable.table[i];
					indoffunk = i;
					i += 2;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS)
					{								//���� ������ ���������� �������, ������������ �� � ������
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
				st.push(lextable.table[i]);							//�������� � ���� ����� ������
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
					if (ArifmPriorities(oper) > pr)																		//���� ��������� ����������� �������� ������ �������� �� ������� �����
						st.push(lextable.table[i]);																		//��������� �������� � ����
					else
					{
						while (st.size() && ArifmPriorities(oper) <= ArifmPriorities(idtable.table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable.table[i]);
					}
				}
			}
			oper = NULL;				//�������� ���� �����
		}
		while (st.size())
		{
			outstr[lenout++] = st.top();												//����� � ������ ���� ������ �� �����
			st.pop();
		}
		for (int i = lexpos, k = 0; i < lexpos + lenout; i++, k++)
		{
			lextable.table[i] = outstr[k];										//������ � ������� �������� ������
			rc = true;
		}
		lextable.table[lexpos + lenout] = lextable.table[semicolonid];         //������� �������� � ������ � �������
		for (int i = 0; i < hesis; i++)
		{
			for (int j = lexpos + lenout + 1; j < lextable.size; j++)				//�������� �� ������ �����
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