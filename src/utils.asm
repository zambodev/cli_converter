	section		.text
	global		strcheck

; rax = result
; rdi = val
; rsi = base
strcheck:
	xor	rax, rax
	add	rsi, 48
loop:	cmp	byte [rdi], 0
	je	exit
	
	cmp	byte [rdi], sil
	jge	bad

	inc	rdi
	jmp	loop

bad:	sub	rax, 1
exit:	ret