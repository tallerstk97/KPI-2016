.586
.model flat, stdcall
includelib kernel32.lib
ExitProcess PROTO,
x:DWORD
WaitMsg PROTO
Crlf PROTO
 WriteInt PROTO
Str_copy PROTO :DWORD, :DWORD
SetConsoleTitleA PROTO :DWORD
WriteString PROTO

.data
bufmath sdword ?

.const

cname db 'KPI-2016 Compiler',0
L01 db 'fsdfdsfs',0 
L02 dword 0 

.code
main PROC

invoke SetConsoleTitleA, offset cname
mov EDX, offset L01
invoke WriteString
call Crlf
invoke Crlf
call waitMsg
call ExitProcess
main ENDP
END main