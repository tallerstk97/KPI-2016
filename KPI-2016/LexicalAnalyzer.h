﻿#pragma once
#include "stdafx.h"
namespace LA
{
	struct LexAnaliz	// структура в которой будут хранится две таблицы
	{
		LT::LexTable l;
		IT::IdTable iT;
	};	
	LexAnaliz LexicalAnaliz(Div::Divide dev, Log::LOG log, Parm::PARM param);	// лексический анализ
	void AddID(IT::Entry iT, bool isDecFunction, char pref[255], char word[255], char decFunction[ID_MAXSIZE]);	//доб. имени идент.
	void AddSTF(LexAnaliz &Lex, char *name, int i, int paramCount);
	int WhereI(LexAnaliz lex, int i);
	int WhereBrace(LexAnaliz lex, int i);
	void funcParamCount(LexAnaliz &Lex);
}
#undef It
#undef Lt