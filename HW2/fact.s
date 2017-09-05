	AREA |.text|, CODE, READONLY
	ENTRY
	; load computing value(s) into r0, r1
	; go to the command
	; write r0 into the corrisponding variable
	mov r0, #0
	bl fact
	str r0, fact0
	
	mov r0, #1
	bl fact
	str r0, fact1
	
	mov r0, #2
	bl fact
	str r0, fact2
	
	mov r0, #5
	bl fact 
	str r0, fact5
	
	mov r0, #12
	bl fact
	str r0, fact12
	
	; integer division
	mov r0, #9
	mov r1, #2
	bl idiv
	str r0, div9 
	
	mov r0, #10
	mov r1, #2
	bl idiv
	str r0, div10
	
	mov r0, #11
	mov r1, #2
	bl idiv
	str r0, div11
	
	; pow (x, n) x^n
	mov r0, #21
	mov r1, #0
	bl power
	str r0, pow0
	
	mov r0, #21
	mov r1, #1
	bl power
	str r0, pow1
	
	mov r0, #21
	mov r1, #2
	bl power
	str r0, pow2
	
	mov r0, #21
	mov r1, #7
	bl power
	str r0, pow7
	
	b Loop ; end in infinite loop
	
one
	mov r0, #1 ; set r0 to 1
	bx LR; go back to "main"

fact ; factorial function
	cmp r0, #0 ; for case 0, will equal 1
	beq one


; running (r1) = value (r0)
	mov r1, r0
; for running > 1
	; running - 1
	; value = value * running
factloop ; loop for factorial multiplication
	sub r1, #1
	cmp  r1, #1
	ble factexit ; exit loop if value is less than or equal to 1
	mul r2, r0, r1
	mov r0, r2
	b factloop 
	
factexit
	bx LR; go back to "main"

idiv ;  interger division function
	; division counter (r2)
	mov r2, #0
	; num (r0)
	; det (r1)
	; for num > det
		; increase division counter
		; num = num - det
idivloop
	cmp r0, r1
	ble idivexit
	add r2, #1
	sub r0, r1
	b idivloop

idivexit
	bx LR ; go back to "main"
	
zero
	mov r0, #1
	bx LR

power ; power function
	cmp r1, #0
	beq zero

	; for counter > 0
	; r0 = r0 * r0
powerloop
	cmp r1, #1
	ble powerexit
	sub r1, #1
	; temp value (r3)
	mul r3, r0, r0
	mov r0, r3
	b powerloop

powerexit
	bx LR ; go back to "main"
	
		
Loop b Loop ; infinite loop
	AREA UserData, DATA, READWRITE, ALIGN=3
fact0 	DCD -1
fact1 	DCD -1
fact2 	DCD -1
fact5 	DCD -1
fact12 	DCD -1
div9 		DCD -1
div10 	DCD -1
div11 	DCD -1
pow0		DCD -1
pow1		DCD -1
pow2		DCD -1
pow7		DCD -1
	END