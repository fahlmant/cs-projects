TITLE Fibonacci Calc					(fib.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Fibonacci Calculator, Assignment 2
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 1/29/2014
;Desc: Takes users name, displays greeting, then takes a number and calculates fibonacci up to that term
;************************************

.data

number_1		DWORD ?
number_2		DWORD ?
sum			DWORD ?
remainder		DWORD ?
count		DWORD ?
LOW_LIMIT		DWORD 1
HIGH_LIMIT	DWORD 46

progtitle		BYTE "Program Title: Fibonacci Calculator",0
myname		BYTE "Name: Taylor Fahlman",0
greet		BYTE "Hello, ",0
yourname		BYTE 32 DUP(0)
name_prompt	BYTE "Please enter your name: ",0
num_prompt	BYTE "Please enter a number (preferably bewteen 1 and 46):",0
space		BYTE ",      ",0
goodbye		BYTE "Goodbye, ",0


.code
main PROC

	call Clrscr

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
	

	;loop to take in number
	num_in:

		;print out prompt for number
		mov edx,OFFSET num_prompt
		call WriteString
		call Crlf
		call ReadInt

		;compares number to 1 and 46
		cmp eax, LOW_LIMIT
		;if eax < 1 jump to num_in
		jb num_in
		;if eax > 46 jump to num_in
		cmp eax, HIGH_LIMIT
		ja num_in
		
	mov number_1, eax 

	mov eax, 1
	cmp eax, number_1
	je term_one



	;set sum to 0, counter to 1 and limit to the input
	mov eax, 0
	mov ebx, 1
	dec number_1
	mov ecx, number_1

	;initialize the first and second numbers for the fibinocci loop
	mov number_1, 0
	mov number_2, 1

	call Crlf

	;print out the first term
	mov eax, number_2
	mov edx,OFFSET space
	call WriteInt
	call WriteString

	;reset eax
	mov eax, 0
	mov edx, 0

	;fibonacci loop
	myLoop:
		add eax, number_1		;adds first term to fib sum
		add eax, number_2		;adds second term to fib sum
		mov sum, eax			;store sum in a variable
		mov eax, number_2		;set the first term to the second term
		mov number_1, eax		
		mov eax, sum			;put sum back in eax
		mov number_2, eax		;set the second term to the total so far

		;prints out fibonacci term calculated, and spaces
		mov eax, sum
		mov edx,OFFSET space
		call WriteInt
		call WriteString

		inc ebx				;increment counter
		mov edx, 0
		mov count, ebx


		;checks if the output needs a newline
		mov eax, count
		mov ebx, 5
		div ebx				;divides count by 5
		mov remainder, edx		
		mov eax, remainder	
		cmp remainder, 0		;compares remainder to 0 to see if 5 numbers have been printed out
		jne after_call			;If not 5 terms out yet, go to end of loop
		
		;Gives newline 
		new_line:
			call Crlf

		after_call:
			mov edx, 0			;reset edx
			mov eax, 0			;reset eax
			mov ebx, count			;put count back into ebx

		loop myLoop				;loop back to top

		jmp end_prog

	term_one:

		mov eax, 1
		mov edx,OFFSET space
		call WriteInt
		call WriteString



	end_prog:

		call Crlf
		;prints goodbye
		mov edx,OFFSET goodbye
		call WriteString
		mov edx,OFFSET yourname
		call WriteString
	
		call Crlf

	exit
main ENDP

END main