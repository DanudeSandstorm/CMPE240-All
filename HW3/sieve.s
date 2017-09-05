	AREA |.text|, CODE, READONLY
	ENTRY
	
snip	mov r0, #2 ; var i = 2
	mov r1, #N ; var N
	ldr r2, =numbers
	; r3 will be used to hold memory address
	; r4 will be used for comparing; extra variable
	; r5 will be used to use numbers in operations
	
main
	bl check
	add r0, #1
	
	; if i <= N
	cmp r0, r1
	ble main
	
	bl outputresults
	
	b Loop ; end in infinite loop

; check if value at i is empty (==0)
check

	; MLA{S} Rd, Rm, Rs, Rn
	; Rd := (Rn + (Rm * Rs))
	
	mov r5, #4
	; add address of array index + index * 4
	mla r3, r0, r5, r2 
	
	; mul r3, r0, r5 ; i * 4
	; add r2, r3 ; add address of array index + index * 4
	
	ldr r4, [r3] ; load value from from memory of array index
	cmp r4, #0 ; compare value at memory to 0
	beq prime
	b goback
	
prime
	; set the value at i to 1
	mov r5, #1
	str r5, [r3]
	

	mov r4, r0	; var x = i
remove
	add r4, r0 ; x += i
	; while x + i <= n
	cmp r4, r1
	bgt goback
	
	; MLA{S} Rd, Rm, Rs, Rn
	; Rd := (Rn + (Rm * Rs))
	; address of array index (r2) + ( x * 4 )
	mov r5, #4
	mla r3, r4, r5, r2 
	
	; set the value at x (value of memory of r3) to -1
	mov r5, #-1
	str r5, [r3]
	
	b remove

goback
	bx LR ; go back to main
	
outputresults
	; set up vars

	; r0 starts at 1 because it increments first run
	mov r0, #1 ; iterator
	; r1 and r2 stay the same
	ldr r3, =results
	
	; starts at 0 so increments number pointer to next location
	add r2, #4

resultsloop
	add r0, #1 ; increment iterator
	add r2, #4 ; increment number pointer to next location
	cmp r0, r1 ; if i > N
	bgt goback
	
	ldr r4, [r2] ; load value from number array
	cmp r4, #1 ; check if value is prime
	beq saveresult
	

	b resultsloop
	
saveresult
	; store the index into the memory location of results
	str r0, [r3]
	add r3, #4 ; increment results pointer to next location
	b resultsloop


Loop b Loop ; infinite loop
	AREA UserData, DATA, READWRITE, ALIGN=3
N EQU 120
results % (N+1) * 4
numbers fill (N+1) * 4, 0
	END