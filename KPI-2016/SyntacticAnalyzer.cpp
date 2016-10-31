#include "stdafx.h"

void SA::syntacticAnalyzer(LA::LexAnaliz &Lex, std::stack<MFST::MfstState>& state, Log::LOG log, Parm::PARM param)
{
	MFST_TRACE_START;
	if(param.SA)	CON_MFST_TRACE_START
	MFST::Mfst mfst(Lex.l, GRB::getGreibach());
	mfst.start(log, param);
	mfst.printrules(log, param, state);
}
