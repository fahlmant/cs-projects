TITLE Frequence Table					(freqtable.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Frequncey Table
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/3/2014
;Desc: Reads a string and counts how many times each letter occurs, stores the ;number in a table
;************************************

.data

target		BYTE "AAAEBDCFBBC",0
freqTable		DWORD 256 DUP(0)

.code

main PROC


	call Get_freq

	mov esi, 1
	mov edi, 0

	print_loop:

		mov eax, freqTable[esi * 4]
		cmp eax, 0					;looks at the value indexed by the decimal ascii value, if its 0, goes to end of loop

		je after_write
		mov eax, esi
		call WriteChar
		mov eax, freqTable[esi * 4]		;prints out the Char and the value stored in the frequence table
		call WriteDec
		call Crlf

		after_write:
		inc esi
		cmp esi, 256					;increments index, makes sure its below the max
		jge ender
		jmp print_loop


		ender:
	exit
main ENDP

Get_freq PROC


	mov esi, 0
	mov edi, 0
	

	loop_1:

		movzx eax, target[esi * SIZEOF BYTE]	;moves decimal value of char in the string to eax
		add freqTable[eax * 4], 1			;uses this number to add 1 to the index equivalent to the ascii number	
		inc esi
		mov ecx, LENGTHOF target				
		cmp esi, ecx						;increment index and make sure it isnt out of bounds
		jl loop_1



	ret

Get_freq ENDP

END main