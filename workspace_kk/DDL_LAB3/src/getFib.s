	.syntax unified
	.cpu cortex-m0
	.align 2
//	.global getFib
	.thumb
	.thumb_func


getFib:
	push    {r4, r7, lr}
	sub     sp, #60 ; #//x3c
	add     r7, sp, #0
	movs    r2, r0
	adds    r3, r7, #7
	strb    r2, [r3, #0]
	#arr[0] = 1;
	movs    r1, #12
	adds    r3, r7, r1
	movs    r2, #1
	strh    r2, [r3, #0]
	#arr[1] = 1;
	adds    r3, r7, r1
	movs    r2, #1
	strh    r2, [r3, #2]
	#uint8_t i = 0;
	movs    r1, #55 ; //0x37
	adds    r3, r7, r1
	movs    r2, #0
	strb    r2, [r3, #0]
	# for(i = 2; i<=n;i++)
	adds    r3, r7, r1
	movs    r2, #2
	strb    r2, [r3, #0]
	b.n     0x4c6

	movs    r0, #55 ; //0x37
	adds    r3, r7, r0
	ldrb    r3, [r3, #0]
	subs    r2, r3, #1
	movs    r4, #12
	adds    r3, r7, r4
	lsls    r2, r2, #1
	ldrh    r1, [r2, r3]
	adds    r3, r7, r0
	ldrb    r3, [r3, #0]
	subs    r2, r3, #2
	adds    r3, r7, r4
	lsls    r2, r2, #1
	ldrh    r3, [r2, r3]
	adds    r2, r7, r0
	ldrb    r2, [r2, #0]
	adds    r3, r1, r3
	uxth    r1, r3
	adds    r3, r7, r4
	lsls    r2, r2, #1
	strh    r1, [r2, r3]
	//for(i = 2; i<=n;i++)
	adds    r3, r7, r0
	ldrb    r2, [r3, #0]
	adds    r3, r7, r0
	adds    r2, #1
	strb    r2, [r3, #0]
	movs    r3, #55 ; //0x37
	adds    r2, r7, r3
	adds    r3, r7, #7
	ldrb    r2, [r2, #0]
	ldrb    r3, [r3, #0]
	cmp     r2, r3
	bls.n   0x492
	#n = arr[n-1];
	adds    r3, r7, #7
	ldrb    r3, [r3, #0]
	subs    r2, r3, #1
	movs    r3, #12
	adds    r3, r7, r3
	lsls    r2, r2, #1
	ldrh    r2, [r2, r3]
	adds    r3, r7, #7
	strb    r2, [r3, #0]
	#return n;
	adds    r3, r7, #7
	ldrb    r3, [r3, #0]
	uxth    r3, r3
	movs    r0, r3
  	mov     sp, r7
   	add     sp, #60 ; // 0x3c
	pop     {r4, r7, pc}
