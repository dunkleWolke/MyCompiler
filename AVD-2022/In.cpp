#include "In.h"
#include "Error.h"
#include "Parm.h"
#include "IT.h"
#include <string>
#include <locale>
#include <fstream>
#include <iostream>
using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		string Separator_symbol = { ';', ',', '{', '}', '(', ')', '=', '+', '-', '-', '<', '>', '/', '*', '!',  '\n'};
		IN inn;
		int k = 0;
		bool next = false, flag_separate = true,
			flag_nl = false, flag_after_control_symb = false;
		inn.lines = inn.size = inn.ignor = 0;
		inn.text = new unsigned char[IN_MAX_LEN_TEXT];
		ifstream reading(infile);
		if (!reading.is_open()) throw ERROR_THROW(110);
		while (!reading.eof())
		{
			int index = 0;
			string q;
			getline(reading, q);
			q += '\n';
			for (int i = 0; i < q.length(); ++i)
			{
				unsigned char a;
				a = q[i];
				int c = 0;
				if (a == '\"')
				{
					if (index % 2 == 0)		flag_separate = false;
					else					flag_separate = true;
					index++;
				}
				if (flag_nl && a == ' ' && flag_separate) continue;
				if (flag_after_control_symb && a == ' ') continue;
				if (flag_after_control_symb && q[i] != ' ') {
					inn.text[k++] = ' '; flag_after_control_symb = false;
				}
				for (int c = 0; c < Separator_symbol.length(); c++)
				{
					if (a == Separator_symbol[c])
					{
						if (q[i + 1] == Separator_symbol[6])
						{
							inn.text[k++] = ' ';
							break;
						}
						else if (i > 0)
						{
							if (q[i - 1] == Separator_symbol[6] || q[i - 1] == Separator_symbol[10] || q[i - 1] == Separator_symbol[11] || q[i-1] == Separator_symbol[14])
							{
								flag_after_control_symb = true;
								break;
							}
							else if (!flag_nl && inn.text[k - 1] != ' ') inn.text[k++] = ' ';
							
							flag_after_control_symb = true;
						}
						else if (!flag_nl && inn.text[k - 1] != ' ') inn.text[k++] = ' ';
						flag_after_control_symb = true;
					}
				}
				if (IN::T == inn.code[a]) { inn.text[k++] = a; }
				else if (IN::I == inn.code[a]) { inn.ignor += 1; }
				else if (IN::F == inn.code[a])
				{
					throw ERROR_THROW_IN(111, inn.lines, i);
				}
				else
					inn.text[k++] = inn.code[a];

				if (a == ' ')	flag_nl = true;
				else flag_nl = false;

				inn.size += 1;
			}
			next = true;
			inn.lines += 1;
		}reading.close();
		inn.text[k] = '\0';

		return inn;
	}

	void Delete(IN& in)
	{
		delete[] in.text;
	}
}