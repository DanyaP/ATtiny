.include "tn13def.inc"
.cseg


main:	ldi r17,$F
	ldi r18,$F0
	add r17,r18
	sub r26,r30
	rjmp a

r:	add r17,r30
	sub r17, r26
	sen
	sev

a:	cp r17,r18
	rjmp r