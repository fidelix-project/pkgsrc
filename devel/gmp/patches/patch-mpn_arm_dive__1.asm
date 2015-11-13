$NetBSD: patch-mpn_arm_dive__1.asm,v 1.1 2015/11/13 10:42:23 wiz Exp $

--- mpn/arm/dive_1.asm.orig	2014-03-25 14:37:55.000000000 +0000
+++ mpn/arm/dive_1.asm
@@ -112,7 +112,10 @@ L(end):	sbc	cy, r5, cy
 	mul	r9, r4, cy
 	str	r9, [rp]
 	pop	{r4-r9}
-	bx	r14
+ifdef(`ARM_THUMB_MODE',
+`	bx      r14
+',`	mov     pc, r14
+')
 
 L(unnorm):
 	rsb	tnc, cnt, #32
@@ -136,7 +139,10 @@ L(edu):	sbc	cy, r5, cy
 	mul	r9, r4, cy
 	str	r9, [rp]
 	pop	{r4-r9}
-	bx	r14
+ifdef(`ARM_THUMB_MODE',
+`	bx      r14
+',`	mov     pc, r14
+')
 EPILOGUE()
 
 	.section .rodata
