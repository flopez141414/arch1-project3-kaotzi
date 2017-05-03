
	.arch			msp430g2553
	.p2align		1,0
	


	.text

	.globl move_up
move_up:	
	; void move_up(selector) {
	; int moveMe = 0;
	switch(selector)
	; case 0:
	; moveMe +=1
	; case 1:
	; moveMe +=1
	; case 2:
	; moveMe +=1
	; case 3:
	; moveMe +=1
	;default:
	;call move_bar( moveMe);
	;....................................
	; 
	;}


		 .data
selector:       .word

         .text
jt:      .word default ; jt[0]
         .word option1;  ; jt[1]
         .word option2;  ; jt[2]
         .word option3;  jt[3]
		 .word option4;  jt[4]

         .global move_up
move_up:
         move #0,r13; r13 = number 0=moveMe;
         ;; range check on selector (selector)
         cmp #5, &selector     
         jc default      ; s-5 < 0 

         ;; index into jt
         mov &selector, r12
         add r12, r12    ; r12=2*selector
         mov jt(r12), r0 ; jmp jt[selector]

         ;; switch table options
         ;; same order as in source code
option0: mov #1, r13     ; moveme+01 and moveMe is stored in r13
                         ; no break
option1:add #1, r13     ; add+01 and moveMe
                         ; no break
option2: add #1, r13     ; add+01 and moveMe
                         ; no break
option3: add #1, r13     ; add+01 and moveMe
                         ; no break
default: add #1, r13     ; add+01 and moveMe
                         ; no break						 

default: call #move_bar(moveMe)    ; call moveMe
                         ;  but doesn't matter
end:     pop r0
