TITLE Quadratic Formula					(qform.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Quadratic Formula
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/14/2014
;Desc: Computes x based on an a, b and c read in using the quadratic formula
;************************************

.data

a_prompt		BYTE "A:",0
b_prompt		BYTE "B:",0
c_prompt		BYTE "C:",0

a_co			REAL8 ?		;a
a_co_d		REAL8 ?		;double a
ac			REAL8 ?		; a times c
b_co			REAL8 ?		;b
b_co_s		REAL8 ?		;b squared
b_co_neg		REAL8 ?		;negative b
c_co			REAL8 ?		;c
product		REAL8 ?		;Holds 4*a*c, then b squared - 4ac, then the sqaure root of that
x_one		REAL8 ?		;first x
x_two		REAL8 ?		;second x
four			REAL8 4.0
two			REAL8 2.0

.code

main PROC

	FINIT

	mov edx, OFFSET a_prompt
	call WriteString	
	call ReadFloat
	fstp a_co
	call Crlf

	mov edx, OFFSET b_prompt
	call WriteString
	call ReadFloat
	fstp b_co
	call Crlf

	mov edx, OFFSET c_prompt
	call WriteString
	call ReadFloat
	fstp c_co
	call Crlf

	mov edx, 0

	call QuadForm

	FLD x_one
	call WriteFloat
	FSTP x_one
	call Crlf

	FLD x_two
	call WriteFloat
	FSTP x_two
	call Crlf

	
	
	exit
main ENDP



QuadForm PROC

	FLD a_co			;push a
	FLD two			;push two
	FMULP			;multiplies a times 2
	FSTP	a_co_d		;stores in a_co_d

	FLD b_co			;push b
	FCHS				;chage sign of ST(0)
	FSTP b_co_neg		;stores in b_co_neg

	FLD b_co			;push b
	FMUL ST(0), ST(0)	;square b 
	FSTP b_co_s		;and store in b_co_s

	FLD c_co			;multiply a and c
	FLD a_co
	FMULP 
	FSTP	ac			;store in ac

	FLD ac
	FLD four		
	FMULP			;multiply ac by 4
	FSTP product		;store in product

	FLD b_co_s
	FLD product		;subtracts product from b squared (b_co_s - product)
	FSUB 
	FSTP product

	FLD product		;takes the square root of product, stores back in product
	FSQRT
	FSTP product


	FLD b_co_neg
	FLD product
	FADD
	FDIV a_co_d
	FSTP x_one

	FLD b_co_neg
	FLD product
	FSUB
	FDIV a_co_d
	FSTP x_two



	
	

	ret
QuadForm ENDP


END main