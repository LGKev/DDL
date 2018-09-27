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


  		mov	sp, r7
  		add	sp, sp, #4
		pop	{r7, pc}

		/* busy wait/ e.g for recursion, use this for fib
		movia r10,5000000
		wait:
		subi r10,r10,1
		bne r10,r0,wait
		*/
