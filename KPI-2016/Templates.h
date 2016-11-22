#pragma once

#define GEN0(buf, tmpl)			sprintf_s(buf, 1024, tmpl)
#define GEN1(buf, tmpl, val)		sprintf_s(buf, 1024, tmpl, val)
#define GEN2(buf, tmpl, valOne, valTwo)	sprintf_s(buf,1024, tmpl, valOne, valTwo)
#define GEN3(buf, tmpl, valOne, valTwo, valThree) sprintf_s(buf,1024, tmpl, valOne, valTwo, valThree)

#define ASM_GLOBAL ".586\n.model flat, stdcall\nincludelib kernel32.lib\n"

#define ASM_INCLUDE_SPRINT "WriteString PROTO\n"
#define ASM_INCLUDE_IPRINT "WriteDec PROTO\n"

#define ASM_STR "%s db %s,0 \n"
#define ASM_INT "%s dword %s \n"

#define ASM_SPRINT "mov EDX, offset %s\ninvoke WriteString\n"
#define ASM_IPRINT "mov EAX, %s\ninvoke WriteInt\n"
#define ASM_ENDL "invoke Crlf\n"

#define ASM_MAIN ".code\n "
#define ASM_BEGIN "main PROC\n\ninvoke SetConsoleTitleA, offset cname\n"


#define ASM_INIT "push %s\n"
#define ASM_INITE "pop %s\n"

#define ASM_PLUS "pop eax\npop ebx\nadd eax, ebx\npush eax\n"
#define ASM_MINUS "pop ebx\npop eax\nsub eax, ebx\npush eax\n"
#define ASM_MUL "pop eax\npop ebx\nimul eax, ebx\npush eax\n"
#define ASM_DIV "pop ebx\npop eax\ncdq\ndiv ebx\npush eax\n"

#define ASM_IF "mov eax, %s\ncmp eax, %s\n"
#define ASM_LESS "ja @if\n"
#define ASM_MORE "jb @if\n"
#define ASM_ENDIF "jmp @endElse\n@if:\n"
#define ASM_ENDELSE "@endElse:\n"

#define ASM_CIRCLE "@circle:\nmov eax, %s\ncmp eax, %s\n"
#define ASM_CIRCLEEND "jmp @circle\n@if:\n"

#define ASM_FUNC "%s PROC uses ebx ebp esi edi"
#define ASM_FUNC_PARAM ", %s:dword"
#define ASM_FUNC_START "\n"
#define ASM_FUNC_RETURN "mov eax, %s\nret 8\n"
#define ASM_FUNC_END "%s ENDP\n\n"

#define ASM_INVOKE_FUNC "invoke %s"
#define ASM_INVOKE_PARAM ", %s"
#define ASM_PUSH_INVOKE "\npush eax\n"

#define ASM_END "invoke WaitMsg\ninvoke ExitProcess, 0\nend main"



#define ASM_SOUT_CHAR(literalValue) "mov EDX, offset "<<literalValue<< "\ninvoke WriteString\ninvoke Crlf\n"
#define ASM_SOUT_INT(literalValue) "pop eax\n\ninvoke WriteDec\n"

#define ASM_SIN_INT(literalValue) "invoke ReadDec\nmov "<<literalValue<<", eax\n"

#define ASM_FIRST_IF_PARAM(literalValue) "mov eax, "<<literalValue<<"\n"
#define ASM_SECOND_IF_PARAM_ABOVE(literalValue) "cmp eax, "<<literalValue<<"\njb @if\n"
#define ASM_SECOND_IF_PARAM_BELOW(literalValue) "cmp eax, "<<literalValue<<"\nja @if\n"
#define ASM_CONDITION_END "jmp @endElse\n@if:\n"
#define ASM_ELSE_END "@endElse:\n"
#define ASM_FIRST_VAL(iden) "mov eax, "<<iden<<"\n"



#define ASM_RETURN "invoke WaitMsg\ninvoke ExitProcess, 0\n"