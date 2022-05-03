	.arch msp430g2553
	.p2align 1, 0
	.text
	.data
	.extern gameOver

jmp_table:
	.word case_0 
	.word case_1
	
	.global play
play:	
	mov &gameOver, r12
	add r12, r12
	mov jmp_table(r12), r0
case_0:
	call moveBird
	call gameMode
	jmp end
case_1:
	call gameOverText
	mov #0, r12
	call buzzer_set_period
	jmp end
end:
	pop r0
	pop r0
	
