;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2 ; align 2 is actually enought for our purposes
Base

;    uint8_t size = 1000 / 8;

SIZE     DCW   125

;    uint8_t* array= (uint8_t*)malloc(size);

ARRAY    FILL  125,0xFF,1

		 ALIGN 4
			 
RESULT   DCB   0
I        DCB   0
L        DCB   0
;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3
; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren
				
				mov r0, #0                         ; r0 - first iterator (i < size)
				mov r1, #0                         ; r1 - second iterator(l < 8)
				ldr r3, =SIZE                 
				ldrh r3,[r3] ; r3 - array size value
				ldr r4, =ARRAY                     ; r4 - array adress

for_1 			cmp r0, r3                         
				bhs end_for_1;
				
				
				ldrb r6,[r4,r0]; check if byte == 0
				cmp r6, #0
				addeq r0, #1
				beq for_1
				
				mov r6,#8 
				mul r6, r6,r0  ; r6 is first checking NUMBER
				
				mov r1, #0 ; l = 0
				
				cmp r0, #0 ; if (i == 0) l = 2
				bne for_2
				
				mov r1, #2 ; l = 2
				add r6, #2 ; first checking is 2
				;vst3
				;vld3
for_2           cmp r1,#8
				bhs end_for_2
				
				cmp r6,#2
				blo end_while_1
				
				mul r7, r6, r6 ;r8 is excluding number
			
while_1         cmp r7,#1000
				bhs end_while_1
				mov r12, #8 ;TODO : LINK REGISTRE
				udiv r8, r7, r12 ; r8 is excluding index
				
				ldrb r9,[r4,r8] ; r10 is byte value where excluding bit is
				
				mov r10, #1
				mov r11, #7
				
				mul r12, r8, r12 ; i * 8
				
				sub r12, r7, r12 ; x % 8;
				
				sub r12, r11, r12 ; 7 - x%8
				
				lsl r10, r10, r12 ; r11 = 1 << (7-number%8)
				bic r9, r9, r10 ; b10 = r11 ^ r10; r10 & ~r11
			
				strb r9, [r4,r8] ; array[excluding_index] = r10
				
				add r7, r6 ; excluding number += number (number * (mul + 1))
				
				b while_1
end_while_1
				add r1,#1 ; increment l
				add r6,#1 ; increment checking number
				b for_2
end_for_2
				add r0, #1 ; increment i
				b for_1
end_for_1				            
forever         b   forever                         ; Anw-26
                ENDP
                END