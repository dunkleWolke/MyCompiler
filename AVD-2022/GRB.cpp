#include <iostream>
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), // стартовый символ //дно стека  
		6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, // неверная структура программы
			3,
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(13, TS('f'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(5, TS('m'), TS('{'), NS('N'), TS('}'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,  // конструкции в функциях
			14,
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(8, TS('u'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(7, TS('u'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(9, TS('d'), TS('f'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(8, TS('d'), TS('f'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(7, TS('p'), TS('i'), TS('('), TS('i'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('i'), TS('('), TS('i'), TS(')'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, // ошибка в выражении
			7,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 5, // условие if
			3,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M')),
			Rule::Chain(2, TS('s'), NS('E'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, // ошибка в параметрах функции
			2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
			Rule::Chain(2, TS('t'), TS('i'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, // ошибка в параметрах вызываемой функции
			8,
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('i'), NS('M'), TS(','), NS('W')),
			Rule::Chain(4, TS('l'), NS('M'), TS(','), NS('W')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M'))
		)
	);
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) // конструктор для записи символов в цепочку
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) // конструктор
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	};
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...) // конструктор
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	};
	Greibach getGreibach()
	{
		return greibach;
	}
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) // получить правило по нетерминалу, возвращающая номер правила или -1
	{
		short rc = -1;
		short k = 0;
		while ((k < size) && (rules[k].nn != pnn)) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	}
	Rule Greibach::getRule(short n) // // получить правило по номеру
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	}
	char* Rule::getCRule(char* b, short nchain) // полчить правило в виде N->цепочка
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) // получить следующую за j подходящую цепочку, вернуть её номер или -1
	{
		short rc = -1;
		while ((j < size) && (chains[j].nt[0] != t)) ++j;  // цикл по всем цепочкам в правиле
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	}
	char* Rule::Chain::getCChain(char* b) // получить правую сторону правила (цепочку)
	{
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}