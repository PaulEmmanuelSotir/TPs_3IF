.section .init9

main:
	/* initialisation de l’ecran */

	call #lcd_init

	/* convention appel */
	MOV #10, R15 
	CALL #fact
	
	MOV R14, R15
	call #lcd_display_number
	
	/* infinite loop */
done:
	jmp done

fact:
	CMP #0, R15
	JNE else
	MOV #1, R14
	RET
else:
	PUSH R15
	DEC R15
	call #fact
	POP R15
	call #mult
	MOV R13, R14
	RET
	
mult:
	MOV R15, &0x130
	MOV R14, &0x138
	MOV &0x13A, R13
	ret
