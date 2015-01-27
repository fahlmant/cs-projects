TITLE 2D Array Sum				(2darrsum.asm)

INCLUDE Irvine32.inc

;************************************
;Program: 2D Array Sum
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/14/2014
;Desc: Adds together a row of a 2D array
;************************************

.data

accumulator	DWORD ?
rowNum		DWORD ?


table   DWORD  0, 1, 2, 3
	   DWORD  4, 5 ,6 , 7
	   DWORD  8, 9, 10, 11

RowSize = 4		; number of elements per row in table

.code

main PROC

	

	mov  eax, 1			;row number
	mov	ebx, 4
	mul	ebx
	mov rowNum,eax
	push rowNum


	push RowSize		;moves the size of a row in the table into ecx
	call	calc_row_sum

	call WriteDec
	call Crlf
	exit
main ENDP


calc_row_sum PROC

	push ebp
	mov ebp, esp
	mov ecx, [ebp + 12]
	mov eax, [ebp + 8]
	mov ebx, OFFSET table
	



	mul ecx		;multiplies the row size by the row number
	mov ebx, eax	;offset of the row
	mov eax, 0	;initialize the accumulator
	mov esi, 0	;sets esi to the first column



	add_loop:
		
		mov eax, table[ebx + esi*SIZEOF DWORD]		;int adding
		add accumulator, eax					;For bytes use
		inc esi								;movzx edx,BYTE PTR[ebx + esi]
		cmp esi, RowSize						;add	eax,edx
		jl add_loop

	mov eax, accumulator


	pop ebp

	ret

calc_row_sum ENDP

END main