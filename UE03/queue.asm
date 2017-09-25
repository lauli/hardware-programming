  .global queue_init, queue_put, queue_get, queue_empty

MAX_SIZE .equ 16*4

  .bss queue, MAX_SIZE, 4

  .data
head .word -1
tail .word -1

  .text
headPointer .word head
tailPointer .word tail
queuePointer .word queue

queue_init:
  mov r0, #-1
  ldr r1, headPointer
  str r0, [r1]
  ldr r1, tailPointer
  str r0, [r1]
  ldr r1, queuePointer
  str r0, [r1]
  bx lr

queue_put:
  ldr r1, headPointer
  ldr r1, [r1]
  ldr r2, tailPointer
  ldr r2, [r2]
  ; r1 contains the value of the head pointer (if the queue is empty, pointer is -1)
  ; r2 contains the value of the tail pointer (if the queue is empty, pointer is -1)

  ; check if queue is empty
  cmp r1, #-1
  bne put
  cmp r2, #-1
  bne put

  ;queue is empty
  ldr r3, queuePointer
  mov r2, #0	 ;sets head to 0
  ldr r1, headPointer
  str r2, [r1] ; saves 0 to head

  mov r2, #0	 ;sets tail to 0
  str r0, [r3, r2]	;saves value of r0 in queue at index r2 (which is value of tailpointer)


  add r2, #4	 ;tail++
  ldr r1, tailPointer
  str r2, [r1] ;saves value of r2 into our tailpointer (tail++)


  mov r0, #1;
  bx lr

put:
  cmp r1, r2
  beq returnNotSuccessful ;queue is full

  ldr r3, queuePointer ;there is space left in the queue
  str r0, [r3, r2]

  mov r4, #MAX_SIZE
  sub r4, #52

  cmp r2, r4
  bne increaseTail

  mov r2, #0;
  b returnSuccessful

increaseTail:
  add r2, #4
  b returnSuccessful

returnSuccessful:
  ldr r4, headPointer
  str r1, [r4]
  ldr r4, tailPointer
  str r2, [r4]
  mov r0, #1
  bx lr

returnNotSuccessful:
  mov r0, #0;
  bx lr

queue_empty:
	ldr r2, tailPointer
	ldr r2, [r2]
	cmp r2, #-1
	beq queue_isEmpty

queue_isNotEmpty:
	mov r0, #0
	bx lr

queue_isEmpty:
	mov r0, #1
	bx lr

queue_get:
	ldr r1, headPointer
	ldr r1, [r1]
  	ldr r2, tailPointer
  	ldr r2, [r2]
  	ldr r3, queuePointer

	cmp r1, #-1
	beq returnNotSuccessful

	ldr r4, [r3, r1]	;save value from queue r3 at index r1 into r4
	str r4, [r0] 	;save value of r4 to value, where r0 points to
	add r1, #4	;increase headPointer

	mov r4, #MAX_SIZE
	sub r4, #48

  	cmp r1, r4
	beq setHeadToNull

	cmp r1, r2
	beq setToDefault

	ldr r4, headPointer
  	str r1, [r4]
  	bx lr


setHeadToNull:
	mov r1, #0
	cmp r1, r2
	beq setToDefault

	b returnSuccessful

setTailToNull:
	mov r2, #0
	b returnSuccessful

setToDefault:
	mov r1, #-1
	mov r2, #-1
	b returnSuccessful
