#include "Generation.h"
#include "IT.h"
#include <iostream>
#include <stack>

using namespace std;

void Generation::Generation(LT::LexTable& t, IT::IdTable& idif, Log::LOG log, wchar_t outfile[])
{
	ofstream file(outfile);
	if (!file.is_open())											//проверка на открытие файла иначе ошибка
		throw ERROR_THROW(113);
	
	int pods = 0;
	int ColI = 0;
	struct 
	{
		int nf;
		int col;
	}f;
	char* flag1 = (char*)"more";
	char* flag2 = (char*)"less";
	char* flag3 = (char*)"equal";
	char* flag4 = (char*)"nequal";
	bool isif = false;
	char step[] = { 's', 't', 'e', 'p', 'e', 'n', '\0' };
	char sravs[] = { 's', 'r', 'a', 'v', 's', '\0' };
	file << ".586P\n.MODEL FLAT, stdcall\nincludelib libucrt.lib\nincludelib kernel32.lib\nincludelib ../Debug/StaticLib.lib\nExitProcess PROTO : DWORD";
	file << "\nSetConsoleTitleA PROTO :DWORD\nGetStdHandle PROTO :DWORD\n ";
	file << "\n\nstepen PROTO: DWORD, :DWORD\nsravs PROTO: DWORD, :DWORD\nprintu PROTO: DWORD\nprints PROTO: DWORD\n";
	for (int ll = 0; ll < idif.size; ll++)
	{
		if (idif.table[ll].idtype == IT::F &&
			(strcmp(idif.table[ll].id, step) != 0) &&
			(strcmp(idif.table[ll].id, sravs) != 0))
		{
			file << idif.table[ll].id << " PROTO ";
			int nump = 0;
			int c = idif.table[ll].idxfirstLE;
			while (t.table[c].lexema != LEX_RIGHTHESIS)
			{
				if (t.table[c].lexema == LEX_ID && idif.table[t.table[c].idxTI].idtype == IT::P) nump++;
				c++;
			}
			while (nump != 0)
			{
				ll++;
				nump--;
				if (nump != 0)
				{
					if (idif.table[ll].iddatatype == IT::UINT)
						file << ": DWORD, ";
					else if (idif.table[ll].iddatatype == IT::STR)
						file << ": DWORD, "; //  ????????
				}

				else if (nump == 0)
				{
					{
						if (idif.table[ll].iddatatype == IT::UINT)
							file << ": DWORD\n";
						else if (idif.table[ll].iddatatype == IT::STR)
							file << ": DWORD\n";
					}
					break;
				}
			}
		}
	}
	file << "\n.STACK 8192\n\n";
	file << ".CONST\n\n";
	for (int i = 0; i < idif.size; i++)
	{
		if (idif.table[i].idtype == IT::L)
		{
			if (idif.table[i].iddatatype == IT::STR)
			{
				file << "\t" << idif.table[i].id << " byte '" << idif.table[i].value.vstr.str << "', 0" << "\n";
			}
			else if (idif.table[i].iddatatype == IT::UINT)
			{
				if (idif.table[i].si == IT::Ten)
				{
					file << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Ten << '\n';
				}
				else if (idif.table[i].si == IT::Hex)
				{
					file << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Hex << "h\n";
				}
			}
		}
	}
	file << "\n.DATA\n\n";
	for (int i = 0; i < idif.size; i++)
	{

		if ((idif.table[i].idtype == IT::F) &&
			(strcmp(idif.table[i].id, sravs) != 0) &&
			(strcmp(idif.table[i].id, step) != 0))
		{
			if (idif.table[i].iddatatype == IT::UINT)
				file << "\tret_" << idif.table[i].id << " DWORD ?" << '\n';
			else if (idif.table[i].iddatatype == IT::STR)
				file << "\tret_" << idif.table[i].id << " DWORD ? " << '\n';
		}
	}
	for (int i = 0; i < idif.size; i++)
	{

		if (idif.table[i].idtype == IT::V)
		{
			if (idif.table[i].iddatatype == IT::STR)
			{
				file << "\t" << idif.table[i].id << " DWORD ? \n";
			}
			else if (idif.table[i].iddatatype == IT::UINT)
			{
				file << "\t" << idif.table[i].id << " DWORD ?\n";
			}
		}
	}
	file << "\n.CODE\n\n";
	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].idxTI > -1)
		{
			if ((idif.table[t.table[i].idxTI].idtype == IT::F) &&
				(strcmp(idif.table[t.table[i].idxTI].id, sravs) != 0) &&
				(strcmp(idif.table[t.table[i].idxTI].id, step) != 0) &&
				(t.table[i - 2].lexema == 'f'))
			{
				int fnumer = t.table[i].idxTI;
				int nump = 0;
				int c = idif.table[t.table[i].idxTI].idxfirstLE;
				while (t.table[c].lexema != LEX_RIGHTHESIS)
				{
					if (t.table[c].lexema == LEX_ID && idif.table[t.table[c].idxTI].idtype == IT::P) nump++;
					c++;
				}
				file << idif.table[t.table[i].idxTI].id << " PROC ";
				for (int j = 0; j < idif.size; j++)
				{
					if (idif.table[j].idtype == IT::P)
					{
						nump--;
						if (nump != 0)
						{
							if (idif.table[j].iddatatype == IT::UINT)
								file << idif.table[j].id << ": DWORD, ";
							else if (idif.table[j].iddatatype == IT::STR)
								file << idif.table[j].id << ": DWORD, ";
						}

						else if (nump == 0)
						{
							{
								if (idif.table[j].iddatatype == IT::UINT)
									file << idif.table[j].id << ": DWORD\n";
								else if (idif.table[j].iddatatype == IT::STR)
									file << idif.table[j].id << ": DWORD\n";
							}
							break;
						}
					}
				}
				while (t.table[i].lexema != '}' || isif != false)
				{
					if (t.table[i - 1].lexema == '=')
					{
						LT::Entry lex = t.table[i - 2];
						int pos1 = i;
						while (t.table[i].lexema != ';')
						{
							if (t.table[i].lexema == 'i')
							{
								if (idif.table[t.table[i].idxTI].idtype == IT::V)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::P)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::F || idif.table[t.table[i].idxTI].idtype == IT::S)
								{
									int l = i;
									i++; // ??????????????? КОГДА ВЫЗЫВАЕШЬ ФУНКЦИЮ, ГДЕ ХРАНИТСЯ РЕЗУЛЬТАТ?
									/*for (int k = l + 1; k < (l + 1 + numofp); k++, i++)
									{
										file << "\tpush " << idif.table[t.table[k].idxTI].id << "\n";
									}*/
									while (t.table[i].lexema != '@')
									{
										if ((idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L || idif.table[t.table[i].idxTI].idtype == IT::V) && idif.table[t.table[i].idxTI].iddatatype == IT::STR)
										{
											file << "\tpush offset " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L || idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										i++;
									}
									int numofp = t.table[i].par;
									file << "\tcall " << idif.table[t.table[l].idxTI].id << "\n";
									if (strcmp(idif.table[t.table[l].idxTI].id, sravs) == 0 ||
										strcmp(idif.table[t.table[l].idxTI].id, step) == 0)
									{
										file << "\tpush eax\n";
									}
									else
									{
										file << "\tpush eax\n";
									}
								}
							}
							if (t.table[i].lexema == 'l')
							{
								if (idif.table[t.table[i].idxTI].iddatatype == IT::STR)
								{
									file << "\tpush offset " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
							}
							if (t.table[i].lexema == 'v')
							{
								if (idif.table[t.table[i].idxTI].id[0] == '+')
								{
									file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
								}
								else if (idif.table[t.table[i].idxTI].id[0] == '-')
								{
									file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
									/*if(idif.table[t.table[i-1].idxTI] < idif.table[t.table[i + 1].idxTI])*/
								}
								else if (idif.table[t.table[i].idxTI].id[0] == '*')
								{
									file << "\tpop eax\n\tpop ebx\n\timul ebx\n\tpush eax\n";
								}
								else if (idif.table[t.table[i].idxTI].id[0] == '/')
								{
									file << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
								}
							}
							i++;
						}
						file << "\tpop " << idif.table[lex.idxTI].id << "\n";
					}
					if (t.table[i].lexema == 'p')
					{
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
						{
							file << "\tpush  " << idif.table[t.table[i + 1].idxTI].id << '\n';
							file << "\tcall prints\n";

						}
						else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
						{
							file << "\tpush offset " << idif.table[t.table[i + 1].idxTI].id << '\n';
							file << "\tcall prints\n";

						}
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
						{

							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n\tcall printu\n";
						}
						else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
						{
							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n\tcall printu\n";
						}
					}
					if (t.table[i].lexema == 'r')
					{
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
						{
							file << "\tpush offset " << idif.table[t.table[i + 1].idxTI].id << '\n';
						}
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
						{
							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << '\n';
						}
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
						{

							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n";
						}
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
						{

							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n";
						}

						file << "\tpop eax\n";
					}
				//	if (t.table[i].lexema == 'u')		// если if
				//	{
				//		isif = true;
				//		file << "mov eax, " << idif.table[t.table[i + 2].idxTI].id << "\n";
				//		file << "cmp eax, " << idif.table[t.table[i + 4].idxTI].id << "\n";
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '<')
				//		{
				//			file << "jb less" << ColI << "\njae more" << ColI << "\n";
				//			file << "less" << ColI << ":\n";
				//			f.nf = 1;
				//			f.col = ColI;
				//		}
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '>')
				//		{
				//			file << "ja more" << ColI << "\njbe less" << ColI << "\n";
				//			file << "more" << ColI << ":\n";
				//			f.nf = 2;
				//			f.col = ColI;
				//		}
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '<' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
				//		{
				//			file << "jbe less" << ColI << "\nja more" << ColI << "\n";
				//			file << "less" << ColI << ":\n";
				//			f.nf = 1;
				//			f.col = ColI;
				//		}
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '>' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
				//		{
				//			file << "jae more" << ColI << "\njb less" << ColI << "\n";
				//			file << "more" << ColI << ":\n";
				//			f.nf = 2;
				//			f.col = ColI;
				//		}
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '=' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
				//		{
				//			file << "je equal" << ColI << "\njne nequal" << ColI << "\n";
				//			file << "equal" << ColI << ":\n";
				//			f.nf = 4;
				//			f.col = ColI;
				//		}
				//		if (idif.table[t.table[i + 3].idxTI].id[0] == '!' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
				//		{
				//			file << "jne nequal" << ColI << "\nje equal" << ColI << "\n";
				//			file << "nequal" << ColI << ":\n";
				//			f.nf = 3;
				//			f.col = ColI;
				//		}
				//		ColI++;
				//	}
				//	if (t.table[i].lexema == '}')
				//	{
				//		isif = false;
				//		if (f.nf == 1) file << flag1 << f.col << ":\n";
				//		if (f.nf == 2) file << flag2 << f.col << ":\n";
				//		if (f.nf == 3) file << flag3 << f.col << ":\n";
				//		if (f.nf == 4) file << flag4 << f.col << ":\n";
				//	}
					i++;
				}
				file << "ret\n";
				file << idif.table[fnumer].id << " ENDP\n\n";
			}
		}
		if (t.table[i].lexema == 'm')
		{
			file << "main PROC\nSTART:\n";
			while (isif == true || t.table[i].lexema != '}')
			{
				if (t.table[i - 1].lexema == '=')
				{
					LT::Entry lex = t.table[i - 2];
					int pos1 = i;
					while (t.table[i].lexema != ';')
					{
						if (t.table[i].lexema == 'i')
						{
							if (idif.table[t.table[i].idxTI].idtype == IT::V)
							{
								file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							else if (idif.table[t.table[i].idxTI].idtype == IT::P)
							{
								file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							else if (idif.table[t.table[i].idxTI].idtype == IT::F || idif.table[t.table[i].idxTI].idtype == IT::S)
							{
								int l = i;
								i++;
								while (t.table[i].lexema != '@')
								{
									if ((idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L) && idif.table[t.table[i].idxTI].iddatatype == IT::STR)
									{
										file << "\tpush offset " << idif.table[t.table[i].idxTI].id << "\n";
									}
									else if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
									{
										file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									else if (idif.table[t.table[i].idxTI].idtype == IT::V)
									{
										file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									i++;
								}
								int numofp = t.table[i].par;
								file << "\tcall " << idif.table[t.table[l].idxTI].id << "\n";
								if (strcmp(idif.table[t.table[l].idxTI].id, sravs) == 0 ||
									strcmp(idif.table[t.table[l].idxTI].id, step) == 0)
								{
									file << "\tpush eax\n";
								}
								else
								{
									file << "\tpush " << "eax\n";
								}
							}
						}
						if (t.table[i].lexema == 'l')
						{
							if (idif.table[t.table[i].idxTI].iddatatype == IT::STR)
							{
								file << "\tpush offset " << idif.table[t.table[i].idxTI].id << "\n";
							}
							else
							{
								file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
						}
						if (t.table[i].lexema == 'v')
						{
							if (idif.table[t.table[i].idxTI].id[0] == '+')
							{
								file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else if (idif.table[t.table[i].idxTI].id[0] == '-')
							{
								file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
							}
							else if (idif.table[t.table[i].idxTI].id[0] == '*')
							{
								file << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							}
							else if (idif.table[t.table[i].idxTI].id[0] == '/')
							{
								file << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
							}
						}
						i++;
					}

					file << "\tpop " << idif.table[lex.idxTI].id << "\n";
				}
				if (t.table[i].lexema == 'p')
				{
					if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
					{
						file << "\tpush  " << idif.table[t.table[i + 1].idxTI].id << '\n';
						file << "\tcall prints\n";

					}
					else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::STR && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
					{
						file << "\tpush offset " << idif.table[t.table[i + 1].idxTI].id << '\n';
						file << "\tcall prints\n";

					}
					if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::V)
					{

						file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n\tcall printu\n";
					}
					else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UINT && idif.table[t.table[i + 1].idxTI].idtype == IT::L)
					{
						file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << "\n\tcall printu\n";
					}
				}
				if (t.table[i].lexema == 'u')		// если if
				{
					isif = true;
					file << "mov eax, " << idif.table[t.table[i + 2].idxTI].id << "\n";
					file << "cmp eax, " << idif.table[t.table[i + 4].idxTI].id << "\n";
					/*if (idif.table[t.table[i + 3].idxTI].id[0] == '<')
					{
						file << "jb less" << ColI << "\njae more" << ColI << "\n";
						file << "less" << ColI << ":\n";
						f.nf = 1;
						f.col = ColI;
					}
					if (idif.table[t.table[i + 3].idxTI].id[0] == '>')
					{
						file << "ja more" << ColI << "\njbe less" << ColI << "\n";
						file << "more" << ColI << ":\n";
						f.nf = 2;
						f.col = ColI;
					}
					if (idif.table[t.table[i + 3].idxTI].id[0] == '<' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
					{
						file << "jbe less" << ColI << "\nja more" << ColI << "\n";
						file << "less" << ColI << ":\n";
						f.nf = 1;
						f.col = ColI;
					}
					if (idif.table[t.table[i + 3].idxTI].id[0] == '>' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
					{
						file << "jae more" << ColI << "\njb less" << ColI << "\n";
						file << "more" << ColI << ":\n";
						f.nf = 2;
						f.col = ColI;
					}
					if (idif.table[t.table[i + 3].idxTI].id[0] == '=' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
					{
						file << "je equal" << ColI << "\njne nequal" << ColI << "\n";
						file << "equal" << ColI << ":\n";
						f.nf = 4;
						f.col = ColI;
					}
					if (idif.table[t.table[i + 3].idxTI].id[0] == '!' && idif.table[t.table[i + 3].idxTI].id[1] == '=')
					{
						file << "jne nequal" << ColI << "\nje equal" << ColI << "\n";
						file << "nequal" << ColI << ":\n";
						f.nf = 3;
						f.col = ColI;
					}
					ColI++;*/

					if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_GREAT)
					{
						file << "ja more" << ColI << "\njbe less" << ColI << "\n";
						file << "more" << ColI << ":\n";
						f.nf = 2;
						f.col = ColI;
					}
					else if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_LESS)
					{
						file << "jb less" << ColI << "\njae more" << ColI << "\n";
						file << "less" << ColI << ":\n";
						f.nf = 1;
						f.col = ColI;
					}
					else if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_EQUAL)
					{
						file << "je equal" << ColI << "\njne nequal" << ColI << "\n";
						file << "equal" << ColI << ":\n";
						f.nf = 4;
						f.col = ColI;
					}
					else if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_GREATEQUAL)
					{
						file << "jae more" << ColI << "\njb less" << ColI << "\n";
						file << "more" << ColI << ":\n";
						f.nf = 2;
						f.col = ColI;
					}
					else if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_LESSEQUAL)
					{
						file << "jbe less" << ColI << "\nja more" << ColI << "\n";
						file << "less" << ColI << ":\n";
						f.nf = 1;
						f.col = ColI;
					}
					else if ((string)(const char*)idif.table[t.table[i + 3].idxTI].id == SEM_NOTEQUAL)
					{
						file << "jne nequal" << ColI << "\nje equal" << ColI << "\n";
						file << "nequal" << ColI << ":\n";
						f.nf = 3;
						f.col = ColI;
					}
					ColI++;
				}
				if (t.table[i].lexema == '}')
				{
					isif = false;
					if (f.nf == 1) file << flag1 << f.col << ":\n";
					if (f.nf == 2) file << flag2 << f.col << ":\n";
					if (f.nf == 3) file << flag3 << f.col << ":\n";
					if (f.nf == 4) file << flag4 << f.col << ":\n";
				}
				i++;
			}
			file << "call ExitProcess\n" << "main" << " ENDP\n\nend main";
		}
	}
	file.close();
}