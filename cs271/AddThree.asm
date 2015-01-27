AddThree PROC


	mov eax, [ebp + 16]
	add eax, [ebp + 12]
	add eax, [ebp + 8]
	pop ebp

	RET
AddThree ENDP

;To call AddThree

	push num1
	push num2
	push num3
	call AddThree
	add esp, 12
