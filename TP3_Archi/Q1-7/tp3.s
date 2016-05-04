.section .init9

main:

	/* initialisation de l’ecran */

	call #lcd_init

	/* emballage des arguments */

	MOV #9, R15
	MOV #7, R14
	call #mult
	MOV R13, R15
	
	PUSH #0x9

	MOV @R1, R15
	call #lcd_display_hexa
/*
	MOV #50000, R12
timer:
	DEC R12
	JZ timer
	
	PUSH #0x5

	MOV R1, R15
	call #lcd_display_hexa*/
	
	/* infinite loop */
done:
	jmp done

mult:
	MOV R14, &0x130
	MOV R15, &0x138
	MOV &0x13A, R13
	ret
	
mult_soft:
	MOV #0, R13
	MOV #0, R12
loop:
	ADD R14, R13
	INC R12
	CMP R12,R15
	JNE loop	
	ret

