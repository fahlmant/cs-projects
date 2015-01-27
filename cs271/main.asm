TITLE Intro to MASM					(main.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Intro to MASM, Assignment 1
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 1/20/2014
;Desc: Prints name, instructions to user, takes two numbers and peforms and prints results of addition, subtraction, multiplication and division
;************************************

.data

	progTitle BYTE "Title: ",0dh,0ah,0
	myName BYTE "Name: Taylor Fahlman",0dh,0ah,0
	instruct BYTE "Please enter two numbers",0dh,0ah,0
	prompt1 BYTE "Number 1:", 0dh,0ah,0
	prompt2 BYTE "Number 2:", 0dh,0ah,0
	goodbye BYTE "Goodbye!",0dh,0ah,0

	sum_name BYTE "Sum: ",0
	diff_name BYTE "Difference: ",0
	pro_name BYTE "Product: ",0
	quo_name BYTE "Quotient: ",0
	rem_name BYTE "Remainder: ",0

	number_1 DWORD ?
	number_2 DWORD 7
	quotient DWORD ?
	remainder DWORD ?
	sum DWORD ?
	difference DWORD ?
	product DWORD ?


.code
main PROC

	call Clrscr

	;INTRO

	;prints name
	mov edx,OFFSET progTitle
	call WriteString


	;prints title
	mov edx, 0	
	mov	edx,OFFSET myName
	call WriteString
	call Crlf


	;prints instructions
	mov	edx, 0
	mov	edx,OFFSET instruct
	call WriteString
	call Crlf


	;GET DATA

	;prints the first prompt for the user
	mov	edx, 0
	mov	edx,OFFSET prompt1
	call WriteString
	mov	edx, 0

	;gets first number
	call  ReadInt	
	mov number_1, eax


	;prints the second prompt for the user
	mov eax, 0
	mov edx,OFFSET prompt2
	call WriteString

	;gets second number
	call  ReadInt	
	mov number_2, eax
	
	mov eax, 0

	;CALCULATE

	;performs addition
	mov eax, number_2
	add eax, number_1
	mov sum, eax

	;performs subtraction
	mov eax, 0
	mov eax, number_1
	sub eax, number_2
	mov difference, eax

	;performs multiplication
	mov eax, 0
	mov eax, number_2
	mul number_1
	mov product, eax

	;performs division
	mov eax, number_1
	mov ebx, number_2
	div ebx
	mov quotient, eax
	mov remainder, edx


	;DISPLAY RESULTS

	;prints sum
	mov eax, sum
	mov edx,OFFSET sum_name
	call WriteString
	call WriteDec
	call Crlf

	;prints difference
	mov eax, difference
	mov edx,OFFSET diff_name
	call WriteString
	call WriteDec
	call Crlf

	;prints product
	mov eax, product
	mov edx,OFFSET pro_name
	call WriteString
	call WriteDec
	call Crlf

	;prints quotient
	mov eax, quotient
	mov edx,OFFSET quo_name
	call WriteString
	call WriteDec
	call Crlf

	;prints remainder
	mov eax, remainder
	mov edx,OFFSET rem_name
	call WriteString
	call WriteDec
	call Crlf
	call Crlf


	;GOODBYE

	mov edx,OFFSET goodbye
	call WriteString
	call Crlf

	exit
main ENDP

END main