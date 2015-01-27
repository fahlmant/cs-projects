TITLE Reversed Array					(revarray.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Reverse Array, Assign 5 pt. 1
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/3/2014
;Desc: Reverse an array in place without copying to another array
;************************************

.data

array		DWORD 7, 8, 9, 2, 3, 5, 6
counter		DWORD LENGTHOF array/2
min_index		DWORD 0
max_index		DWORD ?
loop_done		DWORD 0
message		BYTE "TEST",0




.code
main PROC


	
	mov eax, SIZEOF DWORD
	mov ebx, LENGTHOF array
	mul ebx
	sub eax, SIZEOF DWORD
	mov max_index, eax				;gets the max index of the array

	mov esi, min_index
	mov edi, max_index
	mov eax, 0
	mov ebx, 0

	print_loop:
		mov eax, array[esi]
		call WRITE_NUM
		add esi, SIZEOF DWORD			;loops through each element of the array, and has a check to make sure its not out of bounds

		cmp esi, edi
		jle print_loop

	mov esi, min_index

	cmp loop_done, 1		;check to see if this is before or after array is reversed
	je end_label
		
	my_loop:
		mov eax, array[esi]			;takes the first and last elements, stores them in eax, ebx
		mov ebx, array[edi]			
		mov array[esi], ebx			; switches the values
		mov array[edi], eax
		
		add esi, SIZEOF DWORD		;move esi up to the next value
		sub edi, SIZEOF DWORD		;move edi to the previous values

		dec counter				;does it number of elements/2 so each value is processed once

		cmp counter, 0
		jg my_loop
	
	call Crlf

	mov esi, min_index
	mov edi, max_index			;resets everything and calls print loop
	mov loop_done, 1
	call print_loop

	end_label:



	exit
main ENDP

WRITE_NUM PROC

	call WriteDec			;saves me a whole line of code
	call Crlf			

	ret
WRITE_NUM ENDP 


END main