#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "Lexanaliz.h"
#include <ctime>
#include <cstdlib>
#include <cwchar>
#include <iomanip>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG lg;
		lg.stream->open(logfile);
		if (!lg.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy(lg.logfile, logfile);
			return lg;
		}
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;

		while (*ptr != "")
		{
			*log.stream << *ptr;
			ptr++;
		}
	}

	void WriteLine(LOG log, const wchar_t* wc, ...)
	{
		const wchar_t** ptr = &wc;

		char temp[100];

		while (*ptr != L"")
		{
			wcstombs(temp, *ptr++, sizeof(temp));
			*log.stream << temp;
		}
	}
	void WriteLog(LOG log)
	{
		*log.stream << "\n---- Протокол ----\n---- Дата: ";
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 20, "%x %X", timeinfo);
		*log.stream << buffer;
		*log.stream << " ----\n";
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char inInfo[PARM_MAX_SIZE];
		char outInfo[PARM_MAX_SIZE];
		char logInfo[PARM_MAX_SIZE];

		wcstombs(inInfo, parm.in, sizeof(inInfo));
		wcstombs(outInfo, parm.out, sizeof(outInfo));
		wcstombs(logInfo, parm.log, sizeof(logInfo));

		*log.stream << "-----Параметры----- " << endl;
		*log.stream << "-in:\t" << inInfo << endl;
		*log.stream << "-log:\t" << logInfo << endl;
		*log.stream << "-out:\t" << outInfo << endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные ----\n"
			<< "Количество символов: " << in.size
			<< "\nПроигнорировано: " << in.ignor
			<< "\nКоличество строк: " << in.lines << "\n\n";
	}
	void WriteText(LOG log, In::IN in)
	{
		*log.stream << "Первая фаза анализатора :" << '\n';
		int i = 0;
		while (in.text[i] != '\0')
		{
			*log.stream << in.text[i];
			i++;
		}
		*log.stream << '\n';
	}
	//**********************************
	void WritePN(LT::LexTable lt, LOG log, IT::IdTable it)
	{
		int stroka = 1, i = 0;
		bool str = true;
		*log.stream << endl << endl << "Польская запись построена ->" << endl << endl;
		while (i <= lt.size && lt.table[i].lexema != '-')
		{
			if (str)
			{
				if (stroka < 10)
					*log.stream << '0' << stroka << "   ";
				else *log.stream << stroka << "   ";
			}
			if (stroka == lt.table[i].sn)
			{
				str = false;
				if (lt.table[i].lexema == 'v')
				{
					*log.stream << it.table[lt.table[i].idxTI].id;
				}
				else
				{
					if (lt.table[i].lexema == LEX_NEWPROC) *log.stream << lt.table[i].lexema << lt.table[i].par;
					else
						*log.stream << lt.table[i].lexema;
				}
				i++;
			}
			else
			{
				stroka += 1;
				*log.stream << endl;
				str = true;
			}
		}
	}
	//**********************************
	void WriteLT(LT::LexTable lt, LOG log, IT::IdTable it)
	{
		int stroka = 1, i = 0;
		bool str = true;
		*log.stream << "\n\nПротокол по работе анализатора ->\n\n";
		while (i != lt.size)
		{
			if (str)
			{
				if (stroka < 10)
					*log.stream << '0' << stroka << "   ";
				else *log.stream << stroka << "   ";
			}
			if (stroka == lt.table[i].sn)
			{
				str = false;
				if (lt.table[i].lexema == 'v')
				{
					*log.stream << it.table[lt.table[i].idxTI].id;
				}
				else	*log.stream << lt.table[i].lexema;
				i++;
			}
			else
			{
				stroka += 1;
				*log.stream << '\n';
				str = true;
			}
		}
	}
	void WriteLT_ALL(LT::LexTable lt, LOG log)
	{
		*log.stream << "\n\nПротокол по работе ТЛ - Полная ТЛ ->\n\n"
			<< "---+----------------------+-----------------+--------------------------+\n"
			<< " № | номер в табл идентиф |    лексема      |  номер в исходном коде   |\n"
			<< "---+----------------------+-----------------+--------------------------+\n";
		for (int i = 0; i < lt.size; i++)
		{
			*log.stream << setw(3) << i << '|' << setw(22) << lt.table[i].idxTI << '|' << setw(17) << lt.table[i].lexema
				<< '|' << setw(26) << lt.table[i].sn << '|' << endl;
			*log.stream << "---+----------------------+-----------------+--------------------------+\n";
		}
	}
	void WriteIT_ALL(IT::IdTable it, LOG log)
	{
		*log.stream << "\n\nПротокол по работе ТИ - Полная ТИ ->\n\n"
			<< "---+----------------------+-----------------+---------------+--------------------+---------------------+\n"
			<< " № | инд первой стр в ТЛ  |  идентификатор  |  тип данных   | тип идентификатора |      значение       |\n"
			<< "---+----------------------+-----------------+---------------+--------------------+---------------------+\n";
		for (int i = 0; i < it.size; i++)
		{
			*log.stream << setw(3) << i << "|" << setw(22) << it.table[i].idxfirstLE << '|' << setw(17) << it.table[i].id
				<< '|' << setw(15) << it.table[i].iddatatype<< '|' << setw(20) << it.table[i].idtype << '|';
			if (it.table[i].idtype != IT::L)
			{
				if (it.table[i].iddatatype == IT::UINT)
				{
					*log.stream << setw(10) << it.table[i].value.vint.Ten;
				}
				else
				{
					for (int j = 0; j < it.table[i].value.vstr.len; j++)
					{
						*log.stream << it.table[i].value.vstr.str[j];
					}
				}
			}
			else
			{
				if (it.table[i].iddatatype == IT::UINT)
				{
					if (it.table[i].si == IT::Ten)
						*log.stream << setw(10) << it.table[i].value.vint.Ten;
					else
						*log.stream << setw(10) << it.table[i].value.vint.Hex;
				}
				else
				{
					for (int j = 0; j < it.table[i].value.vstr.len; j++)
					{
						*log.stream << it.table[i].value.vstr.str[j];
					}
				}
			}
			*log.stream << endl << "---+----------------------+-----------------+---------------+--------------------+---------------------+\n";
		}
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "\nОшибка " << error.id << ": " << error.message;
		if (!error.inext.col == -1)
			*log.stream << ", строка: " << error.inext.line << ", позиция: " << error.inext.col;
		*log.stream << ", строка: " << error.inext.line;
		cout << "Программа завершена с ошибкой" << endl;
		system("pause");
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}