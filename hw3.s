	AREA |.text|, CODE, READONLY
	ENTRY
	
	mov r0, #2 ; var i = 2
	mov r1, #N ; var N
	ldr r3, =numbers
	
main
	bl check
	add r0, #1
	
	; if i <= N
	cmp r0, r1
	ble main
	
	; store results
	
	b Loop ; end in infinite loop

; check if value at i is empty (==0)
check

	; MLA{S} Rd, Rm, Rs, Rn
	; Rd := (Rn + (Rm * Rs))
	
	mov r5, #4
	; add address of array index + index * 4
	mla r4, r0, r5, r3 
	
	; mul r4, r0, r5 ; i * 4
	; add r3, r4 ; add address of array index + index * 4
	
	ldr r5, [r4] ; load value from from memory of array index
	cmp r5, #0 ; compare value at memory to 0
	beq prime
	b goback
	
prime
	; set the value at i to 1
	mov r6, #1
	str r6, [r4]
	

	mov r5, r0	; var x = i
remove
	add r5, r0 ; x += i
	; while x + i <= n
	cmp r5, r1
	bgt goback
	
	; set the value at x to -1
	; MLA{S} Rd, Rm, Rs, Rn
	; Rd := (Rn + (Rm * Rs))
	mov r7, #4
	; address of array index (r3) + ( x * 4 )
	mla r4, r5, r7, r3 
	mov r6, #-1
	str r6, [r4]
	
	b remove

goback
	bx LR ; go back to main
	

Loop b Loop ; infinite loop
	AREA UserData, DATA, READWRITE, ALIGN=3
N EQU 4
results % (N+1) * 4
numbers fill (N+1) * 4, 0
	END