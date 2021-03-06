; Generated by holtek-gcc v3.19, Wed May 25 14:39:49 2022
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 16
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 718

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [16]
mduwr0 equ [59h]
mduwr1 equ [5ah]
mduwr2 equ [5bh]
mduwr3 equ [5ch]
mduwr4 equ [5dh]
mduwr5 equ [5eh]
mduwrctrl equ [5fh]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___txr_rxr1 equ [280]
___u1sr equ [277]
public _send_char1
#pragma debug scope 2 1
#line 7 "c:\users\���\desktop\11.��е��\uart1.c"
_send_char1 .section 'code'
_send_char1 proc
    local _send_char1_2 db 1 dup(?)	; 0,1
	mov ra,a
	mov _send_char1_2[0],a
#pragma debug variable 7 2 _send_char1_2+0 "s"
#line 8 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,ra
	lmov [280],a
_L3:
#line 9 "c:\users\���\desktop\11.��е��\uart1.c"
	lsnz [277].0
	jmp _L3
	ret
_send_char1 endp
#line 9 "c:\users\���\desktop\11.��е��\uart1.c"
#pragma debug scope 1 1
public _send_buff1
#pragma debug scope 3 1
#line 16 "c:\users\���\desktop\11.��е��\uart1.c"
_send_buff1 .section 'code'
_send_buff1 proc
public _send_buff1_2
    local _send_buff1_2 db 2 dup(?)	; 2,0
#pragma debug pointer 42 7 3
#pragma debug variable 42 3 _send_buff1_2+0 "s"
#line 17 "c:\users\���\desktop\11.��е��\uart1.c"
	jmp _L6
_L7:
#line 19 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,ra
	fcall _send_char1
#line 20 "c:\users\���\desktop\11.��е��\uart1.c"
	inc _send_buff1_2[0]
	sz z
	inc _send_buff1_2[1]
_L6:
#line 17 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,_send_buff1_2[0]
	mov mp,a
	mov a,_send_buff1_2[1]
	mov sbp,a
	fcall _Crom2Prom
	mov ra,a
	sz ra
	jmp _L7
	ret
_send_buff1 endp
#line 17 "c:\users\���\desktop\11.��е��\uart1.c"
#pragma debug scope 1 1
___wdtc equ [62]
___stm2c0 equ [313]
___stm2c1 equ [314]
___pds0 equ [339]
___sledc1 equ [86]
___pas0 equ [333]
___u1cr1 equ [278]
___u1cr2 equ [279]
___mfi5 equ [56]
___brg1 equ [281]
___intc3 equ [19]
___intc0 equ [16]
public _inituart1
#pragma debug scope 4 1
#line 27 "c:\users\���\desktop\11.��е��\uart1.c"
_inituart1 .section 'code'
_inituart1 proc
#line 28 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,175
	mov [62],a
#line 29 "c:\users\���\desktop\11.��е��\uart1.c"
	lclr [313]
#line 30 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,49
	lorm a,[314]
#line 31 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,40
	lorm a,[339]
#line 32 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,48
	mov [86],a
#line 33 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,192
	lorm a,[333]
#line 34 "c:\users\���\desktop\11.��е��\uart1.c"
	lset [278].7
#line 35 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,228
	lorm a,[279]
#line 36 "c:\users\���\desktop\11.��е��\uart1.c"
	set [56].1
#line 37 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,16
	lmov [281],a
#line 39 "c:\users\���\desktop\11.��е��\uart1.c"
	set [19].3
#line 40 "c:\users\���\desktop\11.��е��\uart1.c"
	set [16].0
	ret
_inituart1 endp
#line 40 "c:\users\���\desktop\11.��е��\uart1.c"
#pragma debug scope 1 1
public _get_buff1
#pragma debug scope 5 1
#line 43 "c:\users\���\desktop\11.��е��\uart1.c"
_get_buff1 .section 'code'
_get_buff1 proc
public _get_buff1_2
    local _get_buff1_2 db 3 dup(?)	; 3,0
#pragma debug pointer 43 7 5
#pragma debug variable 43 5 _get_buff1_2+0 "rbuff"
#pragma debug variable 7 5 _get_buff1_2+2 "c"
#line 44 "c:\users\���\desktop\11.��е��\uart1.c"
	clr rb
	clr rc
_L11:
#line 47 "c:\users\���\desktop\11.��е��\uart1.c"
	lsnz [277].2
	jmp _L11
#line 48 "c:\users\���\desktop\11.��е��\uart1.c"
	lmov a,[280]
	mov ra,a
#line 51 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,rb
	add a,_get_buff1_2[0]
	mov mp,a
	mov a,rc
	adc a,_get_buff1_2[1]
	mov sbp,a
#line 49 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,ra
	sub a,_get_buff1_2[2]
	sz z
	jmp _L15
#line 54 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,ra
	mov ir,a
#line 55 "c:\users\���\desktop\11.��е��\uart1.c"
	inc rb
	sz z
	inc rc
#line 56 "c:\users\���\desktop\11.��е��\uart1.c"
	jmp _L11
_L15:
#line 51 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,0
	mov ir,a
#line 57 "c:\users\���\desktop\11.��е��\uart1.c"
	mov a,rb
	mov ra,a
	mov a,rc
	mov rb,a
	ret
_get_buff1 endp
#line 57 "c:\users\���\desktop\11.��е��\uart1.c"
#pragma debug scope 1 1
#pragma debug struct_begin 44 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int0e" ;1,1
#pragma debug field 21 8 0 1 "__int1e" ;2,1
#pragma debug field 21 8 0 1 "__cp0e" ;3,1
#pragma debug field 21 8 0 1 "__int0f" ;4,1
#pragma debug field 21 8 0 1 "__int1f" ;5,1
#pragma debug field 21 8 0 1 "__cp0f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___intc0 "__intc0" 1
#pragma debug struct_begin 46 "__intc3_bits"
#pragma debug field 21 8 0 1 "__int2e" ;0,1
#pragma debug field 21 8 0 1 "__int3e" ;1,1
#pragma debug field 21 8 0 1 "__mf4e" ;2,1
#pragma debug field 21 8 0 1 "__mf5e" ;3,1
#pragma debug field 21 8 0 1 "__int2f" ;4,1
#pragma debug field 21 8 0 1 "__int3f" ;5,1
#pragma debug field 21 8 0 1 "__mf4f" ;6,1
#pragma debug field 21 8 0 1 "__mf5f" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___intc3 "__intc3" 1
#pragma debug struct_begin 48 "__mfi5_bits"
#pragma debug field 21 8 0 1 "__ur0e" ;0,1
#pragma debug field 21 8 0 1 "__ur1e" ;1,1
#pragma debug field 21 8 0 1 "__ur2e" ;2,1
#pragma debug field 21 8 0 1 ;3,1
#pragma debug field 21 8 0 1 "__ur0f" ;4,1
#pragma debug field 21 8 0 1 "__ur1f" ;5,1
#pragma debug field 21 8 0 1 "__ur2f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___mfi5 "__mfi5" 1
#pragma debug struct_begin 50 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___wdtc "__wdtc" 1
#pragma debug struct_begin 52 "__sledc1_bits"
#pragma debug field 21 8 0 1 "__sledc10" ;0,1
#pragma debug field 21 8 0 1 "__sledc11" ;1,1
#pragma debug field 21 8 0 1 "__sledc12" ;2,1
#pragma debug field 21 8 0 1 "__sledc13" ;3,1
#pragma debug field 21 8 0 1 "__sledc14" ;4,1
#pragma debug field 21 8 0 1 "__sledc15" ;5,1
#pragma debug field 21 8 0 1 "__sledc16" ;6,1
#pragma debug field 21 8 0 1 "__sledc17" ;7,1
#pragma debug struct_end
#pragma debug union_begin 53 ""
#pragma debug field 2 52 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 53 1 ___sledc1 "__sledc1" 1
#pragma debug struct_begin 54 "__u1sr_bits"
#pragma debug field 21 8 0 1 "__txif1" ;0,1
#pragma debug field 21 8 0 1 "__tidle1" ;1,1
#pragma debug field 21 8 0 1 "__rxif1" ;2,1
#pragma debug field 21 8 0 1 "__ridle1" ;3,1
#pragma debug field 21 8 0 1 "__oerr1" ;4,1
#pragma debug field 21 8 0 1 "__ferr1" ;5,1
#pragma debug field 21 8 0 1 "__nf1" ;6,1
#pragma debug field 21 8 0 1 "__perr1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 55 ""
#pragma debug field 2 54 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 55 1 ___u1sr "__u1sr" 1
#pragma debug struct_begin 56 "__u1cr1_bits"
#pragma debug field 21 8 0 1 "__tx81" ;0,1
#pragma debug field 21 8 0 1 "__rx81" ;1,1
#pragma debug field 21 8 0 1 "__txbrk1" ;2,1
#pragma debug field 21 8 0 1 "__stops1" ;3,1
#pragma debug field 21 8 0 1 "__prt1" ;4,1
#pragma debug field 21 8 0 1 "__pren1" ;5,1
#pragma debug field 21 8 0 1 "__bno1" ;6,1
#pragma debug field 21 8 0 1 "__uarten1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 57 ""
#pragma debug field 2 56 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 57 1 ___u1cr1 "__u1cr1" 1
#pragma debug struct_begin 58 "__u1cr2_bits"
#pragma debug field 21 8 0 1 "__teie1" ;0,1
#pragma debug field 21 8 0 1 "__tiie1" ;1,1
#pragma debug field 21 8 0 1 "__rie1" ;2,1
#pragma debug field 21 8 0 1 "__wake1" ;3,1
#pragma debug field 21 8 0 1 "__adden1" ;4,1
#pragma debug field 21 8 0 1 "__brgh1" ;5,1
#pragma debug field 21 8 0 1 "__rxen1" ;6,1
#pragma debug field 21 8 0 1 "__txen1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 59 ""
#pragma debug field 2 58 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 59 1 ___u1cr2 "__u1cr2" 1
#pragma debug variable 8 1 ___txr_rxr1 "__txr_rxr1" 1
#pragma debug variable 8 1 ___brg1 "__brg1" 1
#pragma debug struct_begin 60 "__stm2c0_bits"
#pragma debug field 21 8 0 3 ;0,3
#pragma debug field 21 8 0 1 "__st2on" ;3,1
#pragma debug field 21 8 0 1 "__st2ck0" ;4,1
#pragma debug field 21 8 0 1 "__st2ck1" ;5,1
#pragma debug field 21 8 0 1 "__st2ck2" ;6,1
#pragma debug field 21 8 0 1 "__st2pau" ;7,1
#pragma debug struct_end
#pragma debug union_begin 61 ""
#pragma debug field 2 60 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 61 1 ___stm2c0 "__stm2c0" 1
#pragma debug struct_begin 62 "__stm2c1_bits"
#pragma debug field 21 8 0 1 "__st2cclr" ;0,1
#pragma debug field 21 8 0 1 "__st2dpx" ;1,1
#pragma debug field 21 8 0 1 "__st2pol" ;2,1
#pragma debug field 21 8 0 1 "__st2oc" ;3,1
#pragma debug field 21 8 0 1 "__st2io0" ;4,1
#pragma debug field 21 8 0 1 "__st2io1" ;5,1
#pragma debug field 21 8 0 1 "__st2m0" ;6,1
#pragma debug field 21 8 0 1 "__st2m1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 63 ""
#pragma debug field 2 62 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 63 1 ___stm2c1 "__stm2c1" 1
#pragma debug struct_begin 64 "__pas0_bits"
#pragma debug field 21 8 0 1 "__pas00" ;0,1
#pragma debug field 21 8 0 1 "__pas01" ;1,1
#pragma debug field 21 8 0 1 "__pas02" ;2,1
#pragma debug field 21 8 0 1 "__pas03" ;3,1
#pragma debug field 21 8 0 1 "__pas04" ;4,1
#pragma debug field 21 8 0 1 "__pas05" ;5,1
#pragma debug field 21 8 0 1 "__pas06" ;6,1
#pragma debug field 21 8 0 1 "__pas07" ;7,1
#pragma debug struct_end
#pragma debug union_begin 65 ""
#pragma debug field 2 64 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 65 1 ___pas0 "__pas0" 1
#pragma debug struct_begin 66 "__pds0_bits"
#pragma debug field 21 8 0 1 "__pds00" ;0,1
#pragma debug field 21 8 0 1 "__pds01" ;1,1
#pragma debug field 21 8 0 1 "__pds02" ;2,1
#pragma debug field 21 8 0 1 "__pds03" ;3,1
#pragma debug field 21 8 0 1 "__pds04" ;4,1
#pragma debug field 21 8 0 1 "__pds05" ;5,1
#pragma debug field 21 8 0 1 "__pds06" ;6,1
#pragma debug field 21 8 0 1 "__pds07" ;7,1
#pragma debug struct_end
#pragma debug union_begin 67 ""
#pragma debug field 2 66 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 67 1 ___pds0 "__pds0" 1

; 
; Generated by holtek-gcc v3.19, Wed May 25 14:39:49 2022
; Rebuild 718
; end of file
