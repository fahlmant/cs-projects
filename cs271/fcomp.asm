TITLE Floating Comparison					(fcomp.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Floating Comparison
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/14/2014
;Desc: Compares two floating point numbers, tells us if x is lower or not
;************************************

.data

lowMessage	BYTE "X is lower", 0
highMessage	BYTE "X is not lower", 0
x			REAL8 1.2
y			REAL8 2.34

.code

main PROC

	FINIT

	FLD x		;pushes x
	FCOMP y		;compares ST(0) with y
	FNSTSW ax	;moves the answer to the correct status register bit
	SAHF		

	jnb high_loop 

		mov edx, OFFSET lowMessage ;tells us that x is lower after comparison
		call WriteString
		call Crlf
		jmp end_label

	high_loop:
		mov edx, OFFSET highMessage  ;tells us that x is not lower after comparison
		call WriteString
		call Crlf

	end_label:


	exit
main ENDP




END main