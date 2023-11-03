#include <iostream>
#include <string>
#include <fstream>
#include "LT.h"
#include "Log.h"
#include "In.h"
#include "IT.h"
#include "FST.h"
#include "Error.h"
#include "Parm.h"
#pragma warning (disable: 4996)
using namespace std;
namespace LA
{
	void table(In::IN in, LT::LexTable& lt, IT::IdTable& it, Log::LOG log)
	{
		char mass[22] = { 't','f','d','r','p','m',';',',','{','}','(',')','=','v','u','i','i','i','l','l','l','s' };
		int INDEX = 1; char INDX[3];
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
		FST::FST* a = FST::automat();
		LT::Entry strokaLT; int index = 0;
		IT::Entry strokaIT;
		char Position1[7];		strcpy_s(Position1, " ");
		char Position2[7];		strcpy_s(Position2, " ");
		int main = 0;
		int k = 1;
		int nf = -1, np = 0;
		bool flag_separate = false, FLAG = false, lex_recognized = false, flag_unsign = false;
		int i = 0;
		string buf;
		if (in.text[0] == ' ') i++;
		while (in.text[i] != '\0')
		{
			if (in.text[i] != ' ' || flag_separate || flag_unsign)
			{
				flag_unsign = false;
				buf += in.text[i];
				if (buf == "unsigned") flag_unsign = true;
			}
			else
			{
				if (buf != (char*)"\n")
				{
					for (int i = 0; i <= 21; i++)
					{
						a[i].string = (char*)buf.c_str();
						if (FST::execute(a[i]))
						{
							lex_recognized = true;
							if (i == 0)
								if (!strcmp("string", a[i].string)) iddatatype = IT::STR;
								else iddatatype = IT::UINT;
							if (i == 5) {
									strcpy_s(Position1, "main");
									main++;
									
									if (main > 1)
									{
										//Log::WriteError(log, Error::geterrorin(302, lt.table[i].sn, -1));
										throw ERROR_THROW(302);
									}
								}
							if (i == 6 && lt.size > 1)
								if (lt.table[lt.size - 1].lexema == '}')
								{
									strcpy_s(Position1, " ");
									strcpy_s(Position2, " ");
								}
							if (i == 15)
							{
								strokaIT.iddatatype = iddatatype;
								strokaIT.idtype = IT::S;
								strokaIT.idxfirstLE = lt.size;
								strcpy_s(strokaIT.id, a[i].string);
								if (IT::IsId(it, strokaIT.id) == -1)
								{
									strokaIT.pars = 0;
									strokaLT.idxTI = it.size;
									nf = it.size;
									IT::Add(it, strokaIT);
									it.table[it.size - 1].parmstype = new IT::IDDATATYPE[2];
								}
								else strokaLT.idxTI = IT::IsId(it, strokaIT.id);
							}
							if (i == 16)
							{
								strokaIT.iddatatype = iddatatype;
								strokaIT.idtype = IT::S;
								strokaIT.idxfirstLE = lt.size;
								strcpy_s(strokaIT.id, a[i].string);
								if (IT::IsId(it, strokaIT.id) == -1)
								{
									strokaIT.pars = 0;
									strokaLT.idxTI = it.size;
									nf = it.size;
									IT::Add(it, strokaIT);
									it.table[it.size - 1].parmstype = new IT::IDDATATYPE[2];
								}
								else strokaLT.idxTI = IT::IsId(it, strokaIT.id);
							}
							if (i == 17)
							{

								if (buf.length() > 12)
									throw ERROR_THROW_IN(107, k, -1);

								if (lt.size > 1 &&
									lt.table[lt.size - 2].lexema == 'f')

								{
									strokaIT.iddatatype = iddatatype;
									strokaIT.idxfirstLE = lt.size;
									strcpy_s(strokaIT.id, a[i].string);
									strokaIT.idtype = IT::F;

									if (!strcmp(Position1, " "))
										strcpy_s(Position1, strokaIT.id);
									else strcpy_s(Position2, strokaIT.id);
									if (IT::IsId(it, strokaIT.id) == -1)
									{
										strokaIT.pars = 0;
										strokaLT.idxTI = it.size;
										nf = it.size;
										IT::Add(it, strokaIT);
										it.table[it.size - 1].parmstype = new IT::IDDATATYPE[3];
									}
									else strokaLT.idxTI = IT::IsId(it, strokaIT.id);
								}
								else
									if (lt.size > 1 &&
										lt.table[lt.size - 2].lexema == LEX_DECLARE &&
										lt.table[lt.size - 1].lexema == 't')

									{
										strokaIT.iddatatype = iddatatype;
										strokaIT.idxfirstLE = lt.size;
										strokaIT.idtype = IT::V;

										strcpy_s(strokaIT.id, Position1);
										strcat_s(strokaIT.id, a[i].string);

										if (iddatatype == 1)
										{
											strokaIT.value.vint.Ten = TI_INT_DEFAULT;
											strokaIT.value.vint.Hex[0] = TI_STR_DEFAULT;
										}
										else
										{
											strokaIT.value.vstr.str[0] = TI_STR_DEFAULT;
											strokaIT.value.vstr.len = 0;
										}

										if (IT::IsId(it, strokaIT.id) == -1)
										{
											strokaLT.idxTI = it.size;
											IT::Add(it, strokaIT);
										}
										else throw ERROR_THROW_IN(303, k, -1);
									}
									else
										if (lt.size > 1 &&
											lt.table[lt.size - 1].lexema == 't' &&
											lt.table[lt.size - 2].lexema == LEX_FUNCTION &&
											lt.table[lt.size - 3].lexema == LEX_DECLARE)
										{
											strokaIT.iddatatype = iddatatype;
											strokaIT.idxfirstLE = lt.size;
											strcpy_s(strokaIT.id, a[i].string);
											strokaIT.idtype = IT::F;

											if (!strcmp(Position1, " "))
												strcpy_s(Position1, strokaIT.id);
											else strcpy_s(Position2, strokaIT.id);


											if (IT::IsId(it, strokaIT.id) == -1)
											{
												strokaLT.idxTI = it.size;
												IT::Add(it, strokaIT);
											}
											else strokaLT.idxTI = IT::IsId(it, strokaIT.id);
										}
										else
										{
											if (lt.size > 1 &&
												lt.table[lt.size - 1].lexema == 't')
											{
												strokaIT.iddatatype = iddatatype;
												strokaIT.idxfirstLE = lt.size;


												strokaIT.id[0] = '\0';

												if (strcmp(Position1, " ") && strcmp(Position2, " ")) strcpy_s(strokaIT.id, Position2);


												strcat_s(strokaIT.id, a[i].string);

												strokaIT.idtype = IT::P;
												if (IT::IsId(it, strokaIT.id) == -1)
												{
													it.table[nf].pars++;
													strokaLT.idxTI = it.size;
													it.table[nf].parmstype[np] = iddatatype;
													np++;
													IT::Add(it, strokaIT);
												}
												else strokaLT.idxTI = IT::IsId(it, strokaIT.id);
											}
											else
											{
												if (lt.size > 1 && lt.table[lt.size - 1].lexema != 't'
													&& lt.table[lt.size - 1].lexema != LEX_FUNCTION)
												{
													if (strcmp(Position1, " "))
														strcpy_s(strokaIT.id, Position1);
													else strcpy_s(strokaIT.id, Position2);

													strcat_s(strokaIT.id, a[i].string);
													if (IsId(it, strokaIT.id) != -1)
													{
														strokaLT.idxTI = IT::IsId(it, strokaIT.id);
													}
													else
													{
														if (IsId(it, a[i].string) != -1 && (it.table[IsId(it, a[i].string)].idtype == IT::P || it.table[IsId(it, a[i].string)].idtype == IT::F || it.table[IsId(it, a[i].string)].idtype == IT::S)) strokaLT.idxTI = IT::IsId(it, a[i].string);
														else throw ERROR_THROW_IN(300, k, -1);
													}
												}
											}
										}
							}
							if (18 == i)
							{
								strokaIT.idxfirstLE = lt.size;
								strokaIT.idtype = IT::L;

								strcpy_s(strokaIT.id, "LEX");
								auto sTR = std::to_string(INDEX);
								strcat_s(strokaIT.id, (char*)sTR.c_str());
								INDEX++;

								strokaIT.si = IT::Ten;
								strokaIT.iddatatype = IT::UINT;
								strokaIT.value.vint.Ten = atoi(a[i].string);
								if (stoll(a[i].string) > TI_INT_MAXSIZE) 
							   {
							   	throw ERROR_THROW_IN(315, k, -1);
							   }
							   //тут диапазон чекаем
								strokaLT.idxTI = it.size;
								IT::Add(it, strokaIT);
							}
							if (19 == i)
							{
								strokaIT.idxfirstLE = lt.size;
								strokaIT.idtype = IT::L;

								strcpy_s(strokaIT.id, "LEX");
								auto sTR = std::to_string(INDEX);
								strcat_s(strokaIT.id, (char*)sTR.c_str());
								INDEX++;

								strokaIT.si = IT::Hex;
								strokaIT.iddatatype = IT::UINT;
								for (int d = 2, j = 0; a[i].string[d] != '\0'; d++, j++)
								{
									if (d > TI_STR_MAXSIZE) throw ERROR_THROW_IN(308, k, -1);
									strokaIT.value.vint.Hex[j] = a[i].string[d];
									if (a[i].string[d + 1] == '\0') strokaIT.value.vint.Hex[j + 1] = '\0';
								}
								strokaLT.idxTI = it.size;
								IT::Add(it, strokaIT);
							}
							if (20 == i)
							{
								strokaIT.idxfirstLE = lt.size;
								strokaIT.idtype = IT::L;
								strokaIT.iddatatype = IT::STR;
								strcpy_s(strokaIT.id, "LEX");

								auto sTR = std::to_string(INDEX);
								strcat_s(strokaIT.id, (char*)sTR.c_str());

								INDEX++;
								for (int d = 1, j = 0; a[i].string[d] != '\0'; d++, j++)
								{
									if (d > TI_STR_MAXSIZE) throw ERROR_THROW_IN(109, k, -1);
									
									if (a[i].string[d] != '"')
									{
										strokaIT.value.vstr.str[j] = a[i].string[d];
										strokaIT.value.vstr.len++;
									}
								}
								strokaIT.value.vstr.str[strokaIT.value.vstr.len] = '\0';
								strokaLT.idxTI = it.size;
								IT::Add(it, strokaIT);
							}
							else if (i == 13)
							{
								strokaIT.idxfirstLE = lt.size;
								strokaIT.id[0] = a[i].string[0];
								strokaIT.id[1] = a[i].string[1];
								strokaIT.idtype = IT::O;
								if (IT::IsId(it, a[i].string) == -1)
								{
									strokaLT.idxTI = it.size;
									IT::Add(it, strokaIT);
								}
								else strokaLT.idxTI = IT::IsId(it, a[i].string);
							}
							else if (i == 21)
							{
								strokaLT.lexema = mass[i];
								strokaLT.sn = k;
								strokaIT.idxfirstLE = lt.size;
								strokaIT.idtype = IT::IDTYPE::U;
								strcpy_s(strokaIT.id, a[i].string);
								if (IT::IsId(it, a[i].string) == -1)
								{
									strokaLT.idxTI = it.size;
									IT::Add(it, strokaIT);
								}
								else strokaLT.idxTI = IT::IsId(it, a[i].string);
							}
							if ((i < 14) && (i != 13))
								strokaLT.idxTI = LT_TI_NULLIDX;
							if (i == 11)
							{
								np = 0;
								nf = 0;
							}
							strokaLT.lexema = mass[i];
							strokaLT.sn = k;
							LT::Add(lt, strokaLT);
							delete[] a[i].rstates;
							break;
						}
						else delete[] a[i].rstates;
					}
					
					if (!lex_recognized) throw ERROR_THROW_IN(108, k, -1);
					lex_recognized = false;

				}
				else ++k;
				strokaIT.value.vint.Ten = TI_INT_DEFAULT;
				strokaIT.pars = -1;
				strokaIT.value.vint.Hex[0] = TI_STR_DEFAULT;
				strokaIT.value.vstr.len = 0;
				strokaIT.value.vstr.str[0] = TI_STR_DEFAULT;
				buf = "";
			}
			i++;
		}
		if (main == 0)
		{
			//Log::WriteError(log, Error::geterrorin(301, lt.table[i].sn, -1));
			throw ERROR_THROW(301);
		}
	}
}