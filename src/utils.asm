	section		.text
	global		strcheck, strnorm, lpow

; rdi = num
; rsi = exp
lpow:
	cmp 	rsi, 0
	jg	.start

	mov 	rax, 1
	jmp	.exit

.start	mov 	rax, rdi
	dec	rsi
.loop	cmp	rsi, 0
	je	.exit

	mul	rdi
	dec	rsi
	jmp	.loop

.exit	ret

; Set all char a 0 - 25 value
; rax = result
; rdi = val
strnorm:
.loop:	cmp	byte [rdi], 0
	je	.exit
	cmp	byte [rdi], 57
	jle	.c48
	cmp	byte [rdi], 90
	jle 	.c65
	cmp	byte [rdi], 122
	jle	.c97
.c48:	cmp	byte [rdi], 48
	mov	rax, 48
	jge	.sub
.c65:	cmp	byte [rdi], 65
	mov	rax, 55
	jge	.sub
.c97:	cmp	byte [rdi], 97
	mov	rax, 87
	jge	.sub
	jmp	.err
.sub:	sub	byte [rdi], al

	inc 	rdi
	jmp	.loop

.err:	mov	rax, -1

.exit:	ret

; rax = result
; rdi = val
; rsi = base
strcheck:
	xor	rax, rax
.loop:	cmp	byte [rdi], 0
	je	.exit
	
	cmp	byte [rdi], sil
	jge	.err

	inc	rdi
	jmp	.loop

.err:	sub	rax, 1
.exit:	ret