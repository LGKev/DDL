 	.syntax unified
 	.cpu cortex-m0
 	.align	2
 	.global	GetFib
 	.thumb
 	.thumb_func
 GetFib:
		push	{r7, lr}
		sub	sp, sp, #4
  		add	r7, sp, #0
  		str	r0, [r7]
  		ldr	r1, [r7]
  		// convert to nxp commands?
  		movs r3,#3
  		movs r4,#1
  		movs r5,#1

  		//if input is 1 or 2
  		cmp r1,r3
  		blt END
  		// all other cases
  		LOOP:
  		adds r2,r5,r4
  		mov r4,r5
  		mov r5,r2
  		adds r3,r3,#1

  		cmp     r3, r1
        ble     LOOP
		mov r0,r2
  		//str
  		b TERMINATE
  		END:
  		movs r0, #1
  		b TERMINATE
TERMINATE:

  		mov	sp, r7
  		add	sp, sp, #4
		pop	{r7, pc}
