TITLE Quadratic Formula					(qform.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Letter Matrix
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/14/2014
;Desc: Makes 3 letter matricies, each elemet has a 50% chance of being a vowel
;************************************

.data

randVal		DWORD ?
alpha		BYTE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
vowel		BYTE "AEIOU"
inner_counter	DWORD 0
counter		DWORD 0

max_index		DWORD 12		;Number of elements

tableB  BYTE   65,  65,  65, 65
Rowsize = ($ - tableB)
        BYTE   65,  65,  65, 65
        BYTE   65,  65,  65, 65
	   


.code

main PROC


prog_loop:

	call Gen_matrix

	mov esi, 0

	print_loop:
		mov edx, 0
		mov ecx, 0
		movzx eax, tableB[esi]		;access each element, and prints it out
		call WriteChar
		add esi, SIZEOF BYTE
		inc inner_counter
		mov eax, inner_counter		;every 4 elemts calls new line
		mov ebx, 4
		div ebx
		cmp edx, 0
		jne next
		call Crlf
		mov inner_counter, 0

		next:
			cmp esi, max_index
			jl print_loop
	
	call Crlf
	call Crlf

	inc counter
	cmp counter, 3
	jl prog_loop
	
	exit
main ENDP

Gen_matrix PROC

	mov edi, 0

	matrix_loop:
 
		mov eax, 2
		call RandomRange
		mov randVal, eax		;Gets a random number, either 1 or 0

		cmp randVal, 1
		je vowel_label			;If 1, goes to vowel fill

		mov eax, 22
		call RandomRange		;Consonant fill, gets a random letter from letter array
		mov randVal, eax
		mov esi, randVal
		mov dl, alpha[esi]		;puts it in tableB[current element]
		mov tableB[edi], dl

		jmp end_label
	
		vowel_label:
		
			mov eax, 5
			call RandomRange	;Vowel fill, gets a random vowel from vowel array
			mov randVal, eax
			mov esi, randVal
			mov dl, vowel[esi]
			mov tableB[edi], dl		;puts it in tableB[current element]



		end_label:
			
			add edi, SIZEOF BYTE
			cmp edi, max_index
			jb matrix_loop


	real_end:

	ret
Gen_matrix ENDP






END main