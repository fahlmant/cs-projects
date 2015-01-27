IntLoop PROC

	my_loop:
		
		mov eax, counter
		call WriteDec
		dec eax
		mov counter, eax
		cmp counter, 4
		jg my_loop
		call Crlf


	RET
IntLoop ENDP

;In main the call would be

call IntLoop

;with a variable called

counter DWORD 9