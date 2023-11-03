#pragma once
#define ID_MAXSIZE 12				
#define TI_MAXSIZE 4096				
#define TI_INT_DEFAULT 0x00000000	
#define TI_STR_DEFAULT 0x00			
#define TI_NULLIDX	   0xffffffff	
#define TI_STR_MAXSIZE 255			
#define TI_INT_MAXSIZE 0x7FFFFFFF
//типы идентификаторов: переменная, функция, параметр, литерал, стандартная функция

namespace IT
{
	enum IDDATATYPE { UINT = 1, STR = 2 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5, U = 6, O = 7 }; 
	enum SI { Ten = 1, Hex = 2 };

	struct Entry
	{

		
		int idxfirstLE;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		SI si;
		int pars = -1;
		IDDATATYPE* parmstype;
		union
		{
			struct
			{
				unsigned int Ten;
				char Hex[TI_STR_MAXSIZE];
			} vint;
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE];
			} vstr;
		} value;
	};

	struct IdTable
	{
		int size;
		Entry* table;
	};

	IdTable Create(
	);

	void Add(
		IdTable& idtable,
		Entry entry);

	Entry GetEntry(
		IdTable& idtable,
		int n);

	int IsId(
		IdTable& idtable,
		char id[ID_MAXSIZE]);

	void Delete(IdTable& idtable);
}


                            