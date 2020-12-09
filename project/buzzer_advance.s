	.arch msp430g2553
	.p2aligh 2
	.text

	.data
	.extern freq
	.extern state2_stat

	.text

	.global buzzer_advance

buzzer_advance:
	cmp #0, &state2_stat
	jz else

if:
	add #225, &freq
	jmp exit
else:
	sub #450, &freq

exit:
	mov &freq, r12
	call #get_period

	call #buzzer_set_period
	pop r0
