	AREA |.text|, CODE, READONLY	; required
	ENTRY				; required
	mov r1, #1
	mov r2, #2
	ldr r3, =x			; ADDRESS of X
	ldr r4, y		    	; The VALUE of y 
	ldr r5, [r3]			; The VALUE of X 
	add r6, r5, #-1		; r5 = r4-1
	str r7, y			; put r1 into x
	ldr r8, y			; just checking
Loop B Loop		;infinite loop
	AREA UserData, DATA, READWRITE, ALIGN=3	; required
x	DCD 15			; Note RPI uses  x: .int 15
y 	DCD 0xbad0
	END			; required

    END