#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE 1			
#define LT_MAXSIZE 4096				
#define	LT_TI_NULLIDX 0xffffffff	
#define LEX_UINTEGER 't'				
#define LEX_STRING 't'				
#define	LEX_ID 'i'					
#define LEX_IF 'u'
#define LEX_MAIN 'm'
#define LEX_LITERAL 'l'				
#define	LEX_FUNCTION 'f'			
#define LEX_DECLARE 'd'				
#define LEX_RETURN 'r'				
#define LEX_PRINT 'p'				
#define LEX_SEMICOLON ';'			
#define LEX_COMMA ','				
#define LEX_LEFTBRACE '{'			
#define LEX_BRACELET '}'			
#define LEX_LEFTHESIS '('			
#define LEX_RIGHTHESIS ')'			
#define LEX_PLUS 'v'				
#define LEX_MINUS 'v'				
#define LEX_STAR 'v'				
#define LEX_DIRSLASH 'v'			
#define LEX_EQUALSSIGN '='
#define LEX_BOLS 's'
#define LEX_MENS 's'
#define LEX_LEQUAL 's'
#define LEX_NEQUAL 's'
#define LEX_CMP 'c'
#define LEX_STEP 'e'
#define LEX_NEWPROC '@'

namespace LT
{
	struct Entry
	{
		char lexema;
		int sn;
		int idxTI;
		int par = -1;
	};

	struct LexTable
	{
		int size;
		Entry* table;
	};

	LexTable Create();
	void Add(
		LexTable& lextable,
		Entry entry);
	Entry GetEntry(
		LexTable& lextable,
		int n
	);
	void Delete(LexTable& lextable);
}