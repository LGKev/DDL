 	.syntax unified
 	.cpu cortex-m0
 	.align	2
 	.global	asm_sum
 	.thumb
 	.thumb_func
 GetFib:
		push	{r7, lr}
		sub	sp, sp, #4
  		add	r7, sp, #0
  		str	r0, [r7]
  		ldr	r1, [r7]
  		/* convert to nxp commands?
  		movi r3,3
  		movi r4,1
  		movi r5,1
  		LOOP:
  		add r2,r5,r4
  		mov r4,r5
  		mov r5,r2
  		addi r3,r3,1
  		blt r3,r1,LOOP
  		*/
  		str
  		mov r0,r2
  		mov	sp, r7
  		add	sp, sp, #4
		pop	{r7, pc}
		/* busy wait/ e.g for recursion, use this for fib / template
		movia r10,5000000
		wait:
		subi r10,r10,1
		bne r10,r0,wait
		*/
