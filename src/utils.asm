	section		.text
	global		strcheck, strnorm, lpow, strlend, strtodec

; rdi = normalized string
; rsi = base
; rax = result
strtodec:
	; rcx = exponent
	push	rdi
	push	rsi
	call	strlend
	mov	rcx, rax
	dec	rcx
	pop	rsi
	pop	rdi

	xor	rax, rax
.loop:	cmp 	byte [rdi], 0
	je	.exit
	cmp 	byte [rdi], '.'
	je	.exit
	cmp 	byte [rdi], ','
	je	.exit

	; r8 = pow(base, exp)
	push	rax
	push	rdi
	push	rsi
	mov	rdi, rsi
	mov 	rsi, rcx
	call	lpow
	mov	r8, rax
	dec 	rcx
	pop	rsi
	pop	rdi
	pop	rax

	; r8 = num * r8
	push	rax
	xor	rax, rax
	mov	al, byte [rdi]
	mul	r8
	mov 	r8, rax
	pop	rax

	; res = res + r8
	add 	rax, r8

	inc	rdi
	jmp	.loop

.exit:	ret

; rdi = str
; rax = result
strlend:
	xor	rax, rax
.loop:	cmp 	byte [rdi], 0
	je	.exit
	cmp 	byte [rdi], '.'
	je	.exit
	cmp 	byte [rdi], ','
	je	.exit

	inc 	rax

	inc 	rdi
	jmp	.loop

.exit:	ret

; rdi = num
; rsi = exp
; rax = result
lpow:
	cmp 	rsi, 0
	jg	.start

	mov 	rax, 1
	jmp	.exit

.start:	mov 	rax, rdi
	dec	rsi
.loop:	cmp	rsi, 0
	je	.exit

	mul	rdi
	dec	rsi
	jmp	.loop

.exit:	ret

; Set all char a 0 - 25 value
; rdi = val
; rax = result
strnorm:
.loop:	cmp	byte [rdi], 0
	je	.exit
	cmp	byte [rdi], '.'
	je	.nxt
	cmp	byte [rdi], ','
	je	.nxt

	cmp	byte [rdi], 57
	jle	.c48
	cmp	byte [rdi], 90
	jle 	.c65
	cmp	byte [rdi], 122
	jle	.c97
	jmp	.err

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

.nxt:	inc 	rdi
	jmp	.loop

.err:	mov	rax, -1

.exit:	ret

; rax = result
; rdi = str
; rsi = base
strcheck:
	xor	rax, rax
.loop:	cmp	byte [rdi], 0
	je	.exit
	cmp	byte [rdi], '.'
	je	.nxt
	cmp	byte [rdi], ','
	je	.nxt

	cmp	byte [rdi], sil
	jge	.err

.nxt:	inc	rdi
	jmp	.loop
.err:	sub	rax, 1
.exit:	ret