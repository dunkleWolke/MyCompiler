#include "IT.h"
#include "LT.h"
#include "Error.h"
#include "LexAnaliz.h"
#include "Semantic.h"


namespace SA
{
	bool Semantic(LT::LexTable& lt, IT::IdTable& it, Log::LOG& log)
	{
		bool sem_ok = true;
		/*int main = 0;*/
		
		for (int i = 0; i < lt.size; i++)
		{
			switch (lt.table[i].lexema)
			{

		/*	case LEX_UINTEGER:
				{
				if (it.table[lt.table[i].idxTI].iddatatype == IT::UINT)
				{
					if (it.table[lt.table[i].idxTI].value.vint.Ten > 2147483647)
					{
						sem_ok = false;
						Log::WriteError(log, Error::geterrorin(308, lt.table[i].sn, -1));

					}
				}break;*/

//				}
				

			case LEX_DIRSLASH:
			{
				if (it.table[lt.table[i].idxTI].id[0] == '/')
				{
					if (lt.table[i - 1].lexema == LEX_LITERAL && ((it.table[lt.table[i - 1].idxTI].si == IT::Ten && it.table[lt.table[i - 1].idxTI].value.vint.Ten == 0) || (it.table[lt.table[i - 1].idxTI].si == IT::Hex && it.table[lt.table[i - 1].idxTI].value.vint.Hex == "0")))
					{
						sem_ok = false;
						Log::WriteError(log, Error::geterrorin(313, lt.table[i].sn, -1));
						
						
					}
				}break;
			}
		

				

			
			case LEX_EQUALSSIGN:
			{
				if (i > 0 && lt.table[i - 1].idxTI != LT_TI_NULLIDX)
				{
					IT::IDDATATYPE lefttype = it.table[lt.table[i - 1].idxTI].iddatatype;
					bool ignore = false;

					for (int k = i + 1; lt.table[k].lexema != LEX_SEMICOLON; k++)
					{
						if (k == lt.size)
							break;
						if (lt.table[k].idxTI != LT_TI_NULLIDX)
						{
							if (!ignore)
							{
								IT::IDDATATYPE righttype = it.table[lt.table[k].idxTI].iddatatype;
								if (it.table[lt.table[k].idxTI].idtype == IT::F || it.table[lt.table[k].idxTI].idtype == IT::S) break;
								
								if (lefttype != righttype )
								{
									//Log::WriteError(log, Error::geterrorin(309, lt.table[k].sn, -1));
									throw ERROR_THROW_IN(309, lt.table[i].sn, -1);
									//sem_ok = false;
									//break;
								}
							}

							if (lt.table[k + 1].lexema == LEX_LEFTHESIS)
							{
								ignore = true;
								continue;
							}

							if (ignore && lt.table[k + 1].lexema == LEX_RIGHTHESIS)
							{
								ignore = false;
								continue;
							}
						}
						if (lefttype == IT::IDDATATYPE::STR)
						{

							char l = lt.table[k].lexema;
							
							if (l == LEX_PLUS)
							{
								Log::WriteError(log, Error::geterrorin(311, lt.table[k].sn, -1));
								//throw ERROR_THROW_IN(311, lt.table[i].sn, -1);
								sem_ok = false;
								break;
							}
						}
						/*if (lefttype == IT::IDDATATYPE::UINT)
						{
							char l = lt.table[k].lexema;
							if (l ==)
							{
								Log::WriteError(log, Error::geterrorin(311, lt.table[k].sn, -1));
								sem_ok = false;
								break;
							}
						}*/
					}break;
				}

			}
			case LEX_IF:
			{
				if (it.table[lt.table[i + 2].idxTI].iddatatype != it.table[lt.table[i + 4].idxTI].iddatatype )
				{
					Log::WriteError(log, Error::geterrorin(312, lt.table[i].sn, -1));
					//throw ERROR_THROW_IN(312, lt.table[i].sn, -1);
					sem_ok = false;
				}
				if (lt.table[i + 3].lexema != 's')
				{
					Log::WriteError(log, Error::geterrorin(314, lt.table[i].sn, -1));
					//throw ERROR_THROW_IN(314, lt.table[i].sn, -1);
					sem_ok = false;
				}break;
				
			}
			case LEX_ID:
			{
				IT::Entry e = it.table[lt.table[i].idxTI];

				if (i > 0 && lt.table[i - 2].lexema == LEX_FUNCTION)
				{
					if (e.idtype == IT::IDTYPE::F)
					{
						for (int k = i + 1; ; k++)
						{
							char l = lt.table[k].lexema;
							if (l == LEX_RETURN)
							{
								int next = lt.table[k + 1].idxTI;
								if (next != LT_TI_NULLIDX)
								{
									if (it.table[next].iddatatype != e.iddatatype)
									{
										Log::WriteError(log, Error::geterrorin(310, lt.table[k].sn, -1));
										//throw ERROR_THROW_IN(310, lt.table[i].sn, -1);
										sem_ok = false;
										break;
									}
								}
								break;
							}

							if (k == lt.size) break;
						}
					}
				}
				if (lt.table[i - 2].lexema != LEX_FUNCTION)
				{
					if (e.idtype == IT::IDTYPE::F || e.idtype == IT::IDTYPE::S)
					{
						int c = i;
						while (lt.table[c].lexema != LEX_NEWPROC)
						{
							c++;
						}
						LT::Entry le = lt.table[c];
						if (le.par > 3)
						{
							Log::WriteError(log, Error::geterrorin(304, lt.table[i].sn, -1));
							
							sem_ok = false;
							//throw ERROR_THROW_IN(304, lt.table[i].sn, -1);
						}
						int paramscount = 0;
						for (int j = i + 1; lt.table[j].lexema != LEX_NEWPROC; j++)
						{
							if (lt.table[j].lexema == LEX_ID || lt.table[j].lexema == LEX_LITERAL)
							{
								paramscount++;
								if (le.par == -1)
									break;
								IT::IDDATATYPE ctype = it.table[lt.table[j].idxTI].iddatatype;
								if (ctype != e.parmstype[paramscount - 1])
								{
									Log::WriteError(log, Error::geterrorin(307, lt.table[i].sn, -1));
									//throw ERROR_THROW_IN(307, lt.table[i].sn, -1);
									sem_ok = false;
									break;
								}
							}
							if (j == lt.size)
								break;
						}
						if (paramscount != le.par)
						{
							Log::WriteError(log, Error::geterrorin(306, lt.table[i].sn, -1));
							//throw ERROR_THROW_IN(306, lt.table[i].sn, -1);
							sem_ok = false;
						}
						if (paramscount > 3)
						{
							Log::WriteError(log, Error::geterrorin(305, lt.table[i].sn, -1));
							//throw ERROR_THROW_IN(305, lt.table[i].sn, -1);
							sem_ok = false;
						}
					}
				}break;
			}
			/*case LEX_MAIN:
			{
				main++;
				if (main == 0)
				{
					Log::WriteError(log, Error::geterrorin(301, lt.table[i].sn, -1));
					sem_ok = false;
				}
				if (main > 1)
				{
					Log::WriteError(log, Error::geterrorin(302, lt.table[i].sn, -1));
					sem_ok = false;
				} break;
			}*/
			}
		}
		return sem_ok;
	}
};