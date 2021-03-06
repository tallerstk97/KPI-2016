﻿#include "stdafx.h"

#pragma once
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef stack<short> MFSTSTSTACK; // стек автомата

#define TRACE_START	sprintf_s(buf, 255, "\n\n%-4s: %-20s%-30s%-20s\n", "Шаг","Правило","Входная лента","Стек")

#define TRACE1 sprintf_s(buf, 255, "%-4d: %-20s%-30s%-20s\n",\
++FST_TRACE_n, rule.getCRule(rbuf,nrulechain), getCLenta(lbuf,lenta_position),getCSt(sbuf))

#define TRACE2 sprintf_s(buf, 255, "%-4d: %-20s%-30s%-20s\n",\
FST_TRACE_n," ", getCLenta(lbuf, lenta_position),getCSt(sbuf))

#define TRACE3 sprintf_s(buf, 255, "%-4d: %-20s%-30s%-20s\n",\
++FST_TRACE_n, " ",  getCLenta(lbuf, lenta_position), getCSt(sbuf))

#define TRACE4(c) sprintf_s(buf, 255, "%-4d: %-20s\n", ++FST_TRACE_n, c)

#define TRACE5(c) sprintf_s(buf, 255, "%-4d: %-20s\n", FST_TRACE_n, c)

#define TRACE6(c, k) sprintf_s(buf, 255, "%-4d: %-20s%d\n", FST_TRACE_n, c, k)

#define TRACE7 sprintf_s(buf, 255, "%-4d: %-20s\n", state.lenta_position, rule.getCRule(rbuf,state.nrulechain))

namespace MFST
{
	struct Rule
	{
		int count = 0;
		char rule[DEV_MAX_WORD][DEV_WORD_SIZE];
	};

	struct MfstState // состояние автомата
	{
		short lenta_position; // позиция на ленте
		short nrule; // номер текущего правила
		short nrulechain; // номер текущей цепочки, текущего правила
		MFSTSTSTACK st; // стек автомата
		MfstState();
		MfstState(
			short pposition, // позиция на ленте
			MFSTSTSTACK pst, // стек автомата 
			short pnrulechain // номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition, // позиция на ленте
			MFSTSTSTACK pst, // стек автомата
			short pnrule, // номер текущего правила
			short pnrulechain // номер текущей цепочки, текущего правила
		);
	};
	struct Mfst // магазинный автомат
	{
		enum RC_STEP { // код возврата функции step
			NS_OK, // найдено правило и цепочка, цепочка записана в стек
			NS_NORULE, // не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN, //не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR, // неизвестный нетерминальный символ грамматики
			TS_OK, // тек.символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK, // тек.символ ленты != вершине стека, восттановленно состояние
			LENTA_END, // текущая позиция ленты >= lenta_size
			SURPRISE // неожиданный код возврата (ошибка в step)
		};
		struct MfstDiagnosis // диагностика
		{
			short lenta_position; // позиция на ленте
			RC_STEP rc_step; // код завершения шага
			short nrule; // номер правила
			short nrule_chain; // номер цепочки правила
			short trace_pos;
			MfstDiagnosis();
			MfstDiagnosis( // диагностика
				short plenta_position, // позиция на ленте
				RC_STEP prc_step, // код завершения шага
				short pnrule, // номер правила
				short pnrule_chain // номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER]; // последние самые глубокие сообщения

		GRBALPHABET* lenta; // перекодированныя (TS/NS) лента (из LEX)
		short lenta_position; // текущая позиция на ленте
		short nrule; // номер текущего правила
		short nrulechain; // номер текущей цепочки, текущего правила
		short lenta_size; // размер ленты
		GRB::Greibach grebach; // грамматика Грейбах
		LT::LexTable lex;
		MFSTSTSTACK st; // стек автомата
		std::stack<MfstState> storestate; // стек для сохранения состояний
		Mfst();
		Mfst(
			LT::LexTable plex, // результат работы лексического анализатора
			GRB::Greibach pgrebach // грамматика Грейбах
		);
		char* getCSt(char* buf); // получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25); // лента: n символов с pos
		char* getDiagnosis(short n, char* buf, Log::LOG log, Parm::PARM param); // получить n-ую строку диагностики или 0x00
		bool savestate(Log::LOG log, Parm::PARM param); // сохранить состояние автомата
		bool restate(Log::LOG log, Parm::PARM param); // восстановить состояние автомата
		bool push_chain( // поместить цепочку правила в стек
			GRB::Rule::Chain chain // цепочка правила
		);
		RC_STEP step(Log::LOG log, Parm::PARM param); // выполнить шаг автомата
		bool start(Log::LOG log, Parm::PARM param); // запустить автомат
		bool savediagnosis(
			RC_STEP pprc_step // код завершения шага
		);
		void printrules(Log::LOG log, Parm::PARM param); // ввести последовательность правил

		struct Deducation // вывод
		{
			size_t size; // количество шагов в выводе
			short* nrules; // номер правил грамматики
			short* nrulechains; // номера цепочек правил грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducatuon;
		bool savededucation(); // сохранить дерево вывода
	};
};