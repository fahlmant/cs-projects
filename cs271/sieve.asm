TITLE Sieve of Eratosthenes					(sieve.asm)

INCLUDE Irvine32.inc

;************************************
;Program: Sieve
;Class: CS 271
;Name: Taylor Fahlman
;Due Date: 3/3/2014
;Desc: Displays the Sieve of Eratosthenes
;************************************

.data

prime_num		DWORD 2
primes		DWORD 65000 DUP(?)
MAX_NUM		DWORD 65000

tester		BYTE "Test",0
i			DWORD 2
j			DWORD 2	
index		DWORD 0


message		BYTE "TEST",0
.code

main PROC


	mov eax, 0

	jmp loop2


	loop1:
		
		mov esi, i				
		mov eax, esi				;moves current index to esi
		mov eax, 0
		mov eax, primes[esi*4]		;checks if this number has a 1 in it, if it does jumps to end, if not its prime and inner loop runs
		cmp eax, 1
		je outer_loop_end
		mov prime_num, esi



		loop2:


			mov eax, prime_num		;puts the current prime in eax
			mov ebx, j			;puts the counter in ebx
			mul ebx				;multiplies prime by count to get the index
			mov index, eax			;stores index in index		
			mov esi, index			;makes sure that the index is not over the max index, jumps to end if it is
			cmp esi, MAX_NUM
			jge end_loop2

			mov eax, esi

				
			mov primes[esi*4], 1	;puts one in the index to tell us its not prime

			add j, 1				;increments counter


			mov eax, MAX_NUM	l
			mov ebx, prime_num		;Makes max withing loop at most max_num / j
			div ebx
			cmp j, eax			;exits if counter is too big
			jge end_loop2
			jmp loop2

			end_loop2:

				mov edx, 0
				mov eax, 0
		


		outer_loop_end:
			mov j,2 				;resets inter counter
			inc i				;increments outer loop counter
			mov  eax, MAX_NUM		
			cmp i, eax			;if counter is too big, ends loop
			jle loop1				



	mov index, 2

	print_loop:
		mov esi, index
		mov eax, primes[esi*4]	;If number has a 1 in the table, goes to next number, if no one prints it out until the last index
		cmp eax, 1
		je loop_end
		mov eax, esi
		call WriteDec
		call Crlf
	
		loop_end:
		
		inc index
	
		mov eax, MAX_NUM
		cmp index, eax
		jl print_loop
	

			exit
main ENDP





END main