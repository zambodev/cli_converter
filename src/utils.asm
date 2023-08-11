	section		.text
	global		strcheck, strnorm, lpow, strlend, strwtodec, strdtodec, retval, decwtobase, decdtobase

; rdi = normalized string
; rsi = base
; rax = result
strwtodec:
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

; rdi = whole number
; rsi = new base
; rdx = result str
; rcx = alphabet
decwtobase:

.loop:	cmp 	rdi, 0
	je	.exit

	; result[] = whole % base
	mov 	rax, rdi
	push	rdx
	xor	rdx, rdx
	div 	rsi
	mov	rdi, rax
	mov	rax, rcx
	add	rax, rdx
	pop	rdx
	xor	r8, r8
	mov	r8b, byte [rax]
	mov	byte [rdx], r8b
	inc	rdx

	jmp	.loop

.exit:	ret

; rdi = normalized string
; rsi = base
; rax = result
strdtodec:
	sub 	rsp, 16
	; rcx = exponent
	mov 	rcx, 1

	xorpd	xmm0, xmm0
.loop:	cmp 	byte [rdi], 0
	je	.exit
	cmp 	byte [rdi], '.'
	je	.exit
	cmp 	byte [rdi], ','
	je	.exit

	; xmm1 = pow(base, exp)
	xorpd 	xmm1, xmm1
	push	rdi
	push	rsi
	mov	rdi, rsi
	mov 	rsi, rcx
	call	lpow
	push	rax
	addsd	xmm1, [rsp]
	pop	rax
	inc 	rcx
	pop	rsi
	pop	rdi

	; xmm1 = num / xmm1
	movdqu	oword [rsp], xmm0
	push	rdx
	xor	rdx, rdx
	xorpd	xmm0, xmm0
	mov	dl, byte [rdi]
	push	rdx
	addsd	xmm0, [rsp]
	pop	rdx
	divsd	xmm0, xmm1
	movaps	xmm1, xmm0
	pop	rdx
	movdqu	xmm0, oword [rsp]

	; res = res + xmm1
	addsd 	xmm0, xmm1

	inc	rdi
	jmp	.loop

.exit:	add	rsp, 16
	ret

; rdi = decimal number
; rsi = new base
; rdx = result str
; rcx = alphabet
decdtobase:
	xorpd	xmm0, xmm0
	xorpd	xmm1, xmm1
	xorpd 	xmm2, xmm2
	movsd 	xmm0, qword [rdi]
	movsd 	xmm1, qword [rsi]

.loop	comisd 	xmm0, xmm2
	je	.exit

	mulsd 	xmm0, xmm1
	xor	rax, rax
	cvttsd2si 	rax, xmm0
	push	rax
	add	rax, rcx
	xor	r8, r8
	mov	r8b, byte [rax]
	mov	byte [rdx], r8b
	cvtsi2sd	xmm3, qword [rsp]
	subsd	xmm0, xmm3
	pop	rax
	inc	rdx

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