TITLE Integer Average					(avg.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Integer Average Assignment 3
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 2/5/2014
;Desc: Takes users name, displays greeting, then continuously takes numbers until a negative is entered. 
;Then calculates integer average and prints it out
;************************************

.data

sum			DWORD ?
counter		DWORD 0
average		DWORD ?

LOW_LIMIT		DWORD 1
HI_LIMIT		DWORD 100

progtitle		BYTE "Program Title: Integer Average",0
myname		BYTE "Name: Taylor Fahlman",0
greet		BYTE "Hello, ",0
yourname		BYTE 32 DUP(0)
name_prompt	BYTE "Please enter your name: ",0
num_prompt	BYTE "Please enter a number:",0
inst			BYTE "You will be prompted to enter a number between 1 and 100. ",0
inst2		BYTE "Once you are done entering numbers, enter a negative number.",0
inst3		BYTE "If you enter a number over 100 or under 1, it will not be counted.",0
total		BYTE "Total:",0
terms		BYTE "Number of Terms: ",0
avg			BYTE	"Average (rounded): ",0
goodbye		BYTE "Goodbye, ",0




.code
main PROC

	call Clrscr
	call Intro
	call NumberLoop
	call Answer	
	call Bye
	
	exit
main ENDP

Intro PROC


	;print out title
	mov edx,OFFSET progtitle
	call WriteString
	call Crlf

	;print out my name
	mov edx,OFFSET myname
	call WriteString
	call Crlf

	;print out prompt for users name
	mov edx,OFFSET name_prompt
	call WriteString
	call Crlf

	;get user name
	mov edx,OFFSET yourname
	mov ecx,SIZEOF yourname
	call ReadString

	;greet the user and print out their name
	mov edx,OFFSET greet
	call WriteString
	mov edx,OFFSET yourname
	call WriteString
	call Crlf
	call Crlf

	;prints out instructions
	mov edx,OFFSET inst
	call WriteString
	call Crlf
	mov edx,OFFSET inst2
	call WriteString
	call Crlf
	call Crlf
	
	RET	
intro ENDP

NumberLoop PROC

	num_get:
		
		;promt the user for a number
		mov edx,OFFSET num_prompt
		call WriteString
		call Crlf
		call ReadDec

		;check input

		cmp eax, HI_LIMIT
		ja num_get
		cmp eax, LOW_LIMIT
		jb ending

		;adds number to eax
		add sum, eax
		inc counter
		call Crlf

		jmp num_get

		ending:

	RET
NumberLoop ENDP

Answer PROC

		;prints sum
		call Crlf
		mov edx,OFFSET total
		mov eax, sum
		call WriteString
		call WriteDec
		call Crlf

		;prints number of inputed terms
		mov edx,OFFSET terms
		mov eax, counter
		call WriteString
		call WriteDec
		call Crlf
	
		;prints average
		mov eax, sum
		mov ebx, counter
		mov edx, 0
		div ebx

		mov edx,OFFSET avg
		call WriteString
		call WriteDec
		call Crlf

	RET
Answer ENDP


Bye PROC

		mov edx,OFFSET goodbye
		call WriteString
		mov edx,OFFSET yourname
		call WriteString
		call Crlf


	RET
Bye ENDP



END main