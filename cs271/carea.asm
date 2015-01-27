TITLE Circle Area					(carea.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Circle Area
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/14/2014
;Desc: Takes in a radius, calculates area of the circle
;************************************

.data

radIn	BYTE "Please enter a radius:",0
answer	BYTE "Area of the circle:",0
radius	REAL8 ?

.code

main PROC

	FINIT

	mov edx, OFFSET radIn
	call WriteString
	call Crlf

	call ReadFloat			;get radius
	FMUL ST(0), ST(0)		;square radius, store in ST(0)
	FLDPI				;load PI into ST(1)
	FMUL ST(0), ST(1)		;Multiplies r-squared by pi

	mov edx, OFFSET answer
	call WriteString
	call Crlf
	call	WriteFloat		



	exit
main ENDP




END main