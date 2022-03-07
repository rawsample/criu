
#include "common/asm/linkage.h"

#ifdef CONFIG_32BIT
#define ADD     add
#define ADDI    addiu

#else
#define ADD     dadd
#define ADDIU   daddiu
#endif  /* CONFIG_32BIT */


/*
 * Input:
 *  a0  destination
 *  a1 source
 *  a2 count
 */

	.section .head.text, "ax"
ENTRY(memcpy)
	.set noreorder

	ADD v0,zero,a0
	ADDIU t1,zero,0
loop:
	beq t1,a2,exit
	nop
	lb t2,0(a1)
	sb t2,0(a0)
	ADDIU t1,t1,1
	ADDIU a0,a0,1
	ADDIU a1,a1,1
	j loop
	nop

exit:
	jr ra
	nop
END(memcpy)
