	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 2
	.globl	_bubble_p                       ; -- Begin function bubble_p
	.p2align	2
_bubble_p:                              ; @bubble_p
	.cfi_startproc
; %bb.0:
	add	x8, x0, x1, lsl #3
LBB0_1:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_4 Depth 2
	sub	x8, x8, #8
	cmp	x8, x0
	b.ls	LBB0_6
; %bb.2:                                ;   in Loop: Header=BB0_1 Depth=1
	mov	x10, x0
	mov	x9, x0
	b	LBB0_4
LBB0_3:                                 ;   in Loop: Header=BB0_4 Depth=2
	mov	x10, x9
	cmp	x9, x8
	b.hs	LBB0_1
LBB0_4:                                 ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x11, [x9, #8]!
	ldr	x12, [x10]
	cmp	x11, x12
	b.ge	LBB0_3
; %bb.5:                                ;   in Loop: Header=BB0_4 Depth=2
	stp	x11, x12, [x10]
	b	LBB0_3
LBB0_6:
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
