.586P
.MODEL FLAT, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO : DWORD
SetConsoleTitleA PROTO :DWORD
GetStdHandle PROTO :DWORD
 

stepen PROTO: DWORD, :DWORD
sravs PROTO: DWORD, :DWORD
printu PROTO: DWORD
prints PROTO: DWORD
su PROTO : DWORD, : DWORD, : DWORD

.STACK 8192

.CONST

	LEX1 DWORD 4
	LEX2 DWORD 2h
	LEX3 DWORD 2
	LEX4 DWORD 1
	LEX5 DWORD 3
	LEX6 byte 'exampleExample', 0
	LEX7 byte 'example', 0
	LEX8 DWORD 1
	LEX9 byte 'Okey', 0
	LEX10 byte 'Yes', 0
	LEX11 byte 'Yes', 0
	LEX12 byte 'Yes', 0

.DATA

	ret_su DWORD ?
	sures DWORD ?
	maina DWORD ?
	mainb DWORD ?
	mainc DWORD ?
	mainsum DWORD ?
	mainsumo DWORD ?
	mainstr DWORD ? 
	mainstro DWORD ? 
	mainrezs DWORD ?

.CODE

su PROC a: DWORD, b: DWORD, d: DWORD
	push a
	push b
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push d
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop sures
	push sures
	pop eax
ret
su ENDP

main PROC
START:
	push LEX1
	pop maina
	push LEX2
	pop mainb
	push maina
	push LEX3
	call stepen
	push eax
	pop mainc
	push mainc
	call printu
	push maina
	push mainb
	push mainc
	call su
	push eax
	pop mainsum
	push mainsum
	call printu
	push LEX4
	push maina
	push LEX5
	call su
	push eax
	pop mainsumo
	push mainsumo
	call printu
	push offset LEX6
	pop mainstr
	push offset LEX7
	pop mainstro
	push mainstr
	push mainstro
	call sravs
	push eax
	pop mainrezs
mov eax, mainrezs
cmp eax, LEX8
je equal0
jne nequal0
equal0:
	push offset LEX9
	call prints
nequal0:
mov eax, mainb
cmp eax, maina
jne nequal1
je equal1
nequal1:
	push offset LEX10
	call prints
equal1:
mov eax, maina
cmp eax, mainc
jae more2
jb less2
more2:
	push offset LEX11
	call prints
less2:
mov eax, mainb
cmp eax, mainc
jbe less3
ja more3
less3:
	push offset LEX12
	call prints
more3:
call ExitProcess
main ENDP

end main