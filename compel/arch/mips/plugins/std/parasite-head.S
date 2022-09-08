
#include "common/asm/linkage.h"

	.section .head.text, "ax"
ENTRY(__export_parasite_head_start)
	.set push
	.set noreorder
	jal	parasite_service
	nop
#ifdef CONFIG_32BIT
	.byte	0x00, 0x00, 0x00, 0x0d	//break
#else
	.byte	0x0d, 0x00, 0x00, 0x00	//break
#endif
	.set pop
//	.byte 0x40,0x01,0x00,0x00	//pause
END(__export_parasite_head_start)

