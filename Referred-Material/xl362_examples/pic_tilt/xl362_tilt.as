opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 7503"

opt pagewidth 120

	opt lm

	processor	16F84
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
# 31 "C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
	psect config,class=CONFIG,delta=2 ;#
# 31 "C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
	dw 0xFFFE & 0xFFFB & 0xFFF7 & 0xFFFF ;#
	FNCALL	_main,_xl362Write
	FNCALL	_xl362Write,_spistart
	FNCALL	_xl362Write,_xfer_byte
	FNCALL	_xl362Write,_spistop
	FNCALL	_spistop,_spidelay
	FNCALL	_xfer_byte,_spidelay
	FNCALL	_spistart,_spidelay
	FNROOT	_main
	FNCALL	intlevel1,_myisr
	global	intlevel1
	FNROOT	intlevel1
	global	_buffer
	global	_CSN
psect	text229,local,class=CODE,delta=2
global __ptext229
__ptext229:
_CSN	set	51
	global	_INTF
_INTF	set	89
	global	_MISO
_MISO	set	48
	global	_MOSI
_MOSI	set	49
	global	_SCLK
_SCLK	set	50
	global	_OPTION_REG
_OPTION_REG	set	129
	global	_CSN_TRIS
_CSN_TRIS	set	1075
	global	_MISO_TRIS
_MISO_TRIS	set	1072
	global	_MOSI_TRIS
_MOSI_TRIS	set	1073
	global	_SCLK_TRIS
_SCLK_TRIS	set	1074
	file	"xl362_tilt.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_buffer:
       ds      8

; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	clrf	((__pbssBANK0)+0)&07Fh
	clrf	((__pbssBANK0)+1)&07Fh
	clrf	((__pbssBANK0)+2)&07Fh
	clrf	((__pbssBANK0)+3)&07Fh
	clrf	((__pbssBANK0)+4)&07Fh
	clrf	((__pbssBANK0)+5)&07Fh
	clrf	((__pbssBANK0)+6)&07Fh
	clrf	((__pbssBANK0)+7)&07Fh
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	??_spistart
??_spistart:	; 0 bytes @ 0x0
	global	??_spistop
??_spistop:	; 0 bytes @ 0x0
	global	??_spidelay
??_spidelay:	; 0 bytes @ 0x0
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	?_spistart
?_spistart:	; 0 bytes @ 0x0
	global	?_spistop
?_spistop:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?_myisr
?_myisr:	; 0 bytes @ 0x0
	global	??_myisr
??_myisr:	; 0 bytes @ 0x0
	global	?_spidelay
?_spidelay:	; 0 bytes @ 0x0
	global	?_xfer_byte
?_xfer_byte:	; 1 bytes @ 0x0
	ds	4
	global	spidelay@delay
spidelay@delay:	; 1 bytes @ 0x4
	ds	1
	global	??_xfer_byte
??_xfer_byte:	; 0 bytes @ 0x5
	ds	2
	global	xfer_byte@byte_out
xfer_byte@byte_out:	; 1 bytes @ 0x7
	ds	1
	global	xfer_byte@count
xfer_byte@count:	; 1 bytes @ 0x8
	ds	1
	global	xfer_byte@byte_in
xfer_byte@byte_in:	; 1 bytes @ 0x9
	ds	1
	global	?_xl362Write
?_xl362Write:	; 0 bytes @ 0xA
	global	xl362Write@regaddr
xl362Write@regaddr:	; 1 bytes @ 0xA
	ds	1
	global	xl362Write@buf
xl362Write@buf:	; 1 bytes @ 0xB
	ds	1
	global	??_xl362Write
??_xl362Write:	; 0 bytes @ 0xC
	ds	1
	global	xl362Write@mybyte
xl362Write@mybyte:	; 1 bytes @ 0xD
	ds	1
	global	xl362Write@count
xl362Write@count:	; 1 bytes @ 0xE
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0xF
	ds	2
;;Data sizes: Strings 0, constant 0, data 0, bss 8, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON           0      0       0
;; BANK0           66     17      25

;;
;; Pointer list with targets:

;; xl362Write@buf	PTR unsigned char  size(1) Largest target is 8
;;		 -> buffer(BANK0[8]), 
;;


;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _myisr in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_xl362Write
;;   _xl362Write->_xfer_byte
;;   _spistop->_spidelay
;;   _xfer_byte->_spidelay
;;   _spistart->_spidelay
;;
;; Critical Paths under _myisr in BANK0
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 2, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 2     2      0     277
;;                                             15 BANK0      2     2      0
;;                         _xl362Write
;; ---------------------------------------------------------------------------------
;; (1) _xl362Write                                           5     3      2     277
;;                                             10 BANK0      5     3      2
;;                           _spistart
;;                          _xfer_byte
;;                            _spistop
;; ---------------------------------------------------------------------------------
;; (2) _spistop                                              0     0      0      23
;;                           _spidelay
;; ---------------------------------------------------------------------------------
;; (2) _xfer_byte                                            5     5      0     161
;;                                              5 BANK0      5     5      0
;;                           _spidelay
;; ---------------------------------------------------------------------------------
;; (2) _spistart                                             0     0      0      23
;;                           _spidelay
;; ---------------------------------------------------------------------------------
;; (3) _spidelay                                             1     1      0      23
;;                                              4 BANK0      1     1      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (4) _myisr                                                4     4      0       0
;;                                              0 BANK0      4     4      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 4
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _xl362Write
;;     _spistart
;;       _spidelay
;;     _xfer_byte
;;       _spidelay
;;     _spistop
;;       _spidelay
;;
;; _myisr (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            0      0       0       0        0.0%
;;EEDATA              40      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;COMMON               0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       3       2        0.0%
;;BANK0               42     11      19       3       37.9%
;;ABS                  0      0      19       4        0.0%
;;BITBANK0            42      0       0       5        0.0%
;;DATA                 0      0      1C       6        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 36 in file "C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       2
;;      Totals:         0       2
;;Total ram usage:        2 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_xl362Write
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
	line	36
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 4
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	37
	
l1736:	
;xl362_tilt_main.c: 37: OPTION_REG = 0x40 ;
	movlw	(040h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(129)^080h	;volatile
	line	40
;xl362_tilt_main.c: 40: buffer[7] = 255;
	movlw	(0FFh)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+07h
	line	41
;xl362_tilt_main.c: 41: while(buffer[7]--);
	goto	l1738
	
l172:	
	goto	l1738
	
l171:	
	
l1738:	
	movlw	low(01h)
	subwf	0+(_buffer)+07h,f
	movf	(0+(_buffer)+07h),w
	xorlw	0FFh
	skipz
	goto	u2321
	goto	u2320
u2321:
	goto	l1738
u2320:
	goto	l1740
	
l173:	
	line	43
	
l1740:	
;xl362_tilt_main.c: 43: buffer[0] = 0x52;
	movlw	(052h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_buffer)
	line	44
	
l1742:	
;xl362_tilt_main.c: 44: xl362Write(1,0x1f,buffer);
	movlw	(01Fh)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(?_xl362Write)
	movlw	(_buffer)&0ffh
	movwf	(??_main+1)+0
	movf	(??_main+1)+0,w
	movwf	(0+?_xl362Write+01h)
	movlw	(01h)
	fcall	_xl362Write
	line	47
	
l1744:	
;xl362_tilt_main.c: 47: buffer[7] = 255;
	movlw	(0FFh)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+07h
	line	48
;xl362_tilt_main.c: 48: while(buffer[7]--);
	goto	l1746
	
l175:	
	goto	l1746
	
l174:	
	
l1746:	
	movlw	low(01h)
	subwf	0+(_buffer)+07h,f
	movf	(0+(_buffer)+07h),w
	xorlw	0FFh
	skipz
	goto	u2331
	goto	u2330
u2331:
	goto	l1746
u2330:
	goto	l1748
	
l176:	
	line	51
	
l1748:	
;xl362_tilt_main.c: 51: buffer[0] = 105;
	movlw	(069h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_buffer)
	line	52
	
l1750:	
;xl362_tilt_main.c: 52: buffer[1] = 0 ;
	clrf	0+(_buffer)+01h
	line	53
;xl362_tilt_main.c: 53: buffer[2] = 3 ;
	movlw	(03h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+02h
	line	54
;xl362_tilt_main.c: 54: buffer[3] = 105;
	movlw	(069h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+03h
	line	55
	
l1752:	
;xl362_tilt_main.c: 55: buffer[4] = 0 ;
	clrf	0+(_buffer)+04h
	line	56
;xl362_tilt_main.c: 56: buffer[5] = 37 ;
	movlw	(025h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+05h
	line	57
	
l1754:	
;xl362_tilt_main.c: 57: buffer[6] = 0 ;
	clrf	0+(_buffer)+06h
	line	60
;xl362_tilt_main.c: 58: buffer[7] =
;xl362_tilt_main.c: 59: 0x01 | 0x02 | 0x04
;xl362_tilt_main.c: 60: | 0x08 | 0x10 | 0x20;
	movlw	(03Fh)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+07h
	line	61
	
l1756:	
;xl362_tilt_main.c: 61: xl362Write(8,0x20,buffer);
	movlw	(020h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(?_xl362Write)
	movlw	(_buffer)&0ffh
	movwf	(??_main+1)+0
	movf	(??_main+1)+0,w
	movwf	(0+?_xl362Write+01h)
	movlw	(08h)
	fcall	_xl362Write
	line	64
	
l1758:	
;xl362_tilt_main.c: 64: buffer[0] = 0 ;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(_buffer)
	line	65
	
l1760:	
;xl362_tilt_main.c: 65: buffer[1] = 0x40 ;
	movlw	(040h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+01h
	line	67
	
l1762:	
;xl362_tilt_main.c: 66: buffer[2] =
;xl362_tilt_main.c: 67: 0x00 | 0x00;
	clrf	0+(_buffer)+02h
	line	69
	
l1764:	
;xl362_tilt_main.c: 68: buffer[3] =
;xl362_tilt_main.c: 69: 0x02 | 0x00;
	movlw	(02h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	0+(_buffer)+03h
	line	70
	
l1766:	
;xl362_tilt_main.c: 70: xl362Write(4,0x2a,buffer);
	movlw	(02Ah)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(?_xl362Write)
	movlw	(_buffer)&0ffh
	movwf	(??_main+1)+0
	movf	(??_main+1)+0,w
	movwf	(0+?_xl362Write+01h)
	movlw	(04h)
	fcall	_xl362Write
	goto	l1768
	line	73
;xl362_tilt_main.c: 73: while(1){
	
l177:	
	line	74
	
l1768:	
# 74 "C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
sleep ;#
psect	maintext
	goto	l1768
	line	75
	
l178:	
	line	73
	goto	l1768
	
l179:	
	line	76
	
l180:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_xl362Write
psect	text230,local,class=CODE,delta=2
global __ptext230
__ptext230:

;; *************** function _xl362Write *****************
;; Defined at:
;;		line 46 in file "C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
;; Parameters:    Size  Location     Type
;;  count           1    wreg     unsigned char 
;;  regaddr         1   10[BANK0 ] unsigned char 
;;  buf             1   11[BANK0 ] PTR unsigned char 
;;		 -> buffer(8), 
;; Auto vars:     Size  Location     Type
;;  count           1   14[BANK0 ] unsigned char 
;;  mybyte          1   13[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       2
;;      Locals:         0       2
;;      Temps:          0       1
;;      Totals:         0       5
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_spistart
;;		_xfer_byte
;;		_spistop
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text230
	file	"C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
	line	46
	global	__size_of_xl362Write
	__size_of_xl362Write	equ	__end_of_xl362Write-_xl362Write
	
_xl362Write:	
	opt	stack 4
; Regs used in _xl362Write: [wreg-fsr0h+status,2+status,0+pclath+cstack]
;xl362Write@count stored from wreg
	line	48
	bcf	status, 5	;RP0=0, select bank0
	movwf	(xl362Write@count)
	
l1726:	
;xl362_io_pic.c: 47: char mybyte;
;xl362_io_pic.c: 48: spistart();
	fcall	_spistart
	line	49
;xl362_io_pic.c: 49: mybyte = xfer_byte(0x0a);
	movlw	(0Ah)
	fcall	_xfer_byte
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_xl362Write+0)+0
	movf	(??_xl362Write+0)+0,w
	movwf	(xl362Write@mybyte)
	line	50
;xl362_io_pic.c: 50: mybyte = xfer_byte(regaddr);
	movf	(xl362Write@regaddr),w
	fcall	_xfer_byte
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_xl362Write+0)+0
	movf	(??_xl362Write+0)+0,w
	movwf	(xl362Write@mybyte)
	line	51
;xl362_io_pic.c: 51: while(count--) {
	goto	l1732
	
l373:	
	line	52
	
l1728:	
;xl362_io_pic.c: 52: mybyte = xfer_byte(*buf);
	movf	(xl362Write@buf),w
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	fcall	_xfer_byte
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_xl362Write+0)+0
	movf	(??_xl362Write+0)+0,w
	movwf	(xl362Write@mybyte)
	line	53
	
l1730:	
;xl362_io_pic.c: 53: buf++;
	movlw	(01h)
	movwf	(??_xl362Write+0)+0
	movf	(??_xl362Write+0)+0,w
	addwf	(xl362Write@buf),f
	goto	l1732
	line	54
	
l372:	
	line	51
	
l1732:	
	movlw	low(01h)
	subwf	(xl362Write@count),f
	movf	((xl362Write@count)),w
	xorlw	0FFh
	skipz
	goto	u2311
	goto	u2310
u2311:
	goto	l1728
u2310:
	goto	l1734
	
l374:	
	line	55
	
l1734:	
;xl362_io_pic.c: 54: }
;xl362_io_pic.c: 55: spistop();
	fcall	_spistop
	line	56
	
l375:	
	return
	opt stack 0
GLOBAL	__end_of_xl362Write
	__end_of_xl362Write:
;; =============== function _xl362Write ends ============

	signat	_xl362Write,12408
	global	_spistop
psect	text231,local,class=CODE,delta=2
global __ptext231
__ptext231:

;; *************** function _spistop *****************
;; Defined at:
;;		line 97 in file "C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       0
;;      Totals:         0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_spidelay
;; This function is called by:
;;		_xl362Write
;;		_xl362Read
;;		_xl362FifoRead
;; This function uses a non-reentrant model
;;
psect	text231
	file	"C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
	line	97
	global	__size_of_spistop
	__size_of_spistop	equ	__end_of_spistop-_spistop
	
_spistop:	
	opt	stack 4
; Regs used in _spistop: [wreg+status,2+status,0+pclath+cstack]
	line	98
	
l1722:	
;xl362_io_pic.c: 98: CSN=1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(51/8),(51)&7
	line	99
	
l1724:	
;xl362_io_pic.c: 99: spidelay();
	fcall	_spidelay
	line	100
	
l399:	
	return
	opt stack 0
GLOBAL	__end_of_spistop
	__end_of_spistop:
;; =============== function _spistop ends ============

	signat	_spistop,88
	global	_xfer_byte
psect	text232,local,class=CODE,delta=2
global __ptext232
__ptext232:

;; *************** function _xfer_byte *****************
;; Defined at:
;;		line 102 in file "C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
;; Parameters:    Size  Location     Type
;;  byte_out        1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  byte_out        1    7[BANK0 ] unsigned char 
;;  byte_in         1    9[BANK0 ] unsigned char 
;;  count           1    8[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       3
;;      Temps:          0       2
;;      Totals:         0       5
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_spidelay
;; This function is called by:
;;		_xl362Write
;;		_xl362Read
;;		_xl362FifoRead
;; This function uses a non-reentrant model
;;
psect	text232
	file	"C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
	line	102
	global	__size_of_xfer_byte
	__size_of_xfer_byte	equ	__end_of_xfer_byte-_xfer_byte
	
_xfer_byte:	
	opt	stack 4
; Regs used in _xfer_byte: [wreg+status,2+status,0+pclath+cstack]
;xfer_byte@byte_out stored from wreg
	line	104
	bcf	status, 5	;RP0=0, select bank0
	movwf	(xfer_byte@byte_out)
	
l1688:	
;xl362_io_pic.c: 103: char count;
;xl362_io_pic.c: 104: char byte_in =0;
	clrf	(xfer_byte@byte_in)
	line	105
	
l1690:	
;xl362_io_pic.c: 105: for(count=8;count>0;count--) {
	movlw	(08h)
	movwf	(??_xfer_byte+0)+0
	movf	(??_xfer_byte+0)+0,w
	movwf	(xfer_byte@count)
	
l1692:	
	movf	(xfer_byte@count),f
	skipz
	goto	u2271
	goto	u2270
u2271:
	goto	l402
u2270:
	goto	l1718
	
l1694:	
	goto	l1718
	
l402:	
	line	106
;xl362_io_pic.c: 106: if(byte_out & 0x80) {
	btfss	(xfer_byte@byte_out),(7)&7
	goto	u2281
	goto	u2280
u2281:
	goto	l404
u2280:
	line	107
	
l1696:	
;xl362_io_pic.c: 107: MOSI = 1;
	bsf	(49/8),(49)&7
	line	108
;xl362_io_pic.c: 108: } else{
	goto	l1698
	
l404:	
	line	109
;xl362_io_pic.c: 109: MOSI = 0;
	bcf	(49/8),(49)&7
	goto	l1698
	line	110
	
l405:	
	line	111
	
l1698:	
;xl362_io_pic.c: 110: }
;xl362_io_pic.c: 111: spidelay();
	fcall	_spidelay
	line	112
	
l1700:	
;xl362_io_pic.c: 112: byte_out = byte_out <<1;
	bcf	status, 5	;RP0=0, select bank0
	movf	(xfer_byte@byte_out),w
	movwf	(??_xfer_byte+0)+0
	addwf	(??_xfer_byte+0)+0,w
	movwf	(??_xfer_byte+1)+0
	movf	(??_xfer_byte+1)+0,w
	movwf	(xfer_byte@byte_out)
	line	113
	
l1702:	
;xl362_io_pic.c: 113: byte_in = byte_in <<1;
	movf	(xfer_byte@byte_in),w
	movwf	(??_xfer_byte+0)+0
	addwf	(??_xfer_byte+0)+0,w
	movwf	(??_xfer_byte+1)+0
	movf	(??_xfer_byte+1)+0,w
	movwf	(xfer_byte@byte_in)
	line	114
	
l1704:	
;xl362_io_pic.c: 114: SCLK = 1;
	bsf	(50/8),(50)&7
	line	115
	
l1706:	
;xl362_io_pic.c: 115: if(MISO) byte_in +=1;
	btfss	(48/8),(48)&7
	goto	u2291
	goto	u2290
u2291:
	goto	l1710
u2290:
	
l1708:	
	movlw	(01h)
	movwf	(??_xfer_byte+0)+0
	movf	(??_xfer_byte+0)+0,w
	addwf	(xfer_byte@byte_in),f
	goto	l1710
	
l406:	
	line	116
	
l1710:	
;xl362_io_pic.c: 116: spidelay();
	fcall	_spidelay
	line	117
	
l1712:	
;xl362_io_pic.c: 117: SCLK = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(50/8),(50)&7
	line	105
	
l1714:	
	movlw	low(01h)
	subwf	(xfer_byte@count),f
	
l1716:	
	movf	(xfer_byte@count),f
	skipz
	goto	u2301
	goto	u2300
u2301:
	goto	l402
u2300:
	goto	l1718
	
l403:	
	line	119
	
l1718:	
;xl362_io_pic.c: 118: }
;xl362_io_pic.c: 119: return(byte_in);
	movf	(xfer_byte@byte_in),w
	goto	l407
	
l1720:	
	line	120
	
l407:	
	return
	opt stack 0
GLOBAL	__end_of_xfer_byte
	__end_of_xfer_byte:
;; =============== function _xfer_byte ends ============

	signat	_xfer_byte,4217
	global	_spistart
psect	text233,local,class=CODE,delta=2
global __ptext233
__ptext233:

;; *************** function _spistart *****************
;; Defined at:
;;		line 88 in file "C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       0
;;      Totals:         0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_spidelay
;; This function is called by:
;;		_xl362Write
;;		_xl362Read
;;		_xl362FifoRead
;; This function uses a non-reentrant model
;;
psect	text233
	file	"C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
	line	88
	global	__size_of_spistart
	__size_of_spistart	equ	__end_of_spistart-_spistart
	
_spistart:	
	opt	stack 4
; Regs used in _spistart: [wreg+status,2+status,0+pclath+cstack]
	line	89
	
l1684:	
;xl362_io_pic.c: 89: SCLK = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(50/8),(50)&7
	line	90
;xl362_io_pic.c: 90: SCLK_TRIS = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1074/8)^080h,(1074)&7
	line	91
;xl362_io_pic.c: 91: CSN = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(51/8),(51)&7
	line	92
;xl362_io_pic.c: 92: CSN_TRIS = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1075/8)^080h,(1075)&7
	line	93
;xl362_io_pic.c: 93: MISO_TRIS = 1;
	bsf	(1072/8)^080h,(1072)&7
	line	94
;xl362_io_pic.c: 94: MOSI_TRIS = 0;
	bcf	(1073/8)^080h,(1073)&7
	line	95
	
l1686:	
;xl362_io_pic.c: 95: spidelay();
	fcall	_spidelay
	line	96
	
l396:	
	return
	opt stack 0
GLOBAL	__end_of_spistart
	__end_of_spistart:
;; =============== function _spistart ends ============

	signat	_spistart,88
	global	_spidelay
psect	text234,local,class=CODE,delta=2
global __ptext234
__ptext234:

;; *************** function _spidelay *****************
;; Defined at:
;;		line 84 in file "C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  delay           1    4[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       1
;;      Temps:          0       0
;;      Totals:         0       1
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_spistart
;;		_spistop
;;		_xfer_byte
;; This function uses a non-reentrant model
;;
psect	text234
	file	"C:\projects\xl362_examples\lib\src\xl362_io_pic.c"
	line	84
	global	__size_of_spidelay
	__size_of_spidelay	equ	__end_of_spidelay-_spidelay
	
_spidelay:	
	opt	stack 4
; Regs used in _spidelay: [wreg+status,2+status,0]
	line	85
	
l1680:	
;xl362_io_pic.c: 85: char delay =1;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(spidelay@delay)
	bsf	status,0
	rlf	(spidelay@delay),f
	line	86
;xl362_io_pic.c: 86: while(--delay != 0)continue;
	goto	l1682
	
l391:	
	goto	l1682
	
l390:	
	
l1682:	
	movlw	low(01h)
	subwf	(spidelay@delay),f
	btfss	status,2
	goto	u2261
	goto	u2260
u2261:
	goto	l1682
u2260:
	goto	l393
	
l392:	
	line	87
	
l393:	
	return
	opt stack 0
GLOBAL	__end_of_spidelay
	__end_of_spidelay:
;; =============== function _spidelay ends ============

	signat	_spidelay,88
	global	_myisr
psect	text235,local,class=CODE,delta=2
global __ptext235
__ptext235:

;; *************** function _myisr *****************
;; Defined at:
;;		line 79 in file "C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       4
;;      Totals:         0       4
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text235
	file	"C:\projects\xl362_examples\pic_tilt\xl362_tilt_main.c"
	line	79
	global	__size_of_myisr
	__size_of_myisr	equ	__end_of_myisr-_myisr
	
_myisr:	
	opt	stack 4
; Regs used in _myisr: []
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_myisr+0)
	movf	fsr0,w
	movwf	(??_myisr+1)
	movf	pclath,w
	movwf	(??_myisr+2)
	movf	btemp+1,w
	movwf	(??_myisr+3)
	ljmp	_myisr
psect	text235
	line	80
	
i1l1658:	
;xl362_tilt_main.c: 80: INTF=0;
	bcf	(89/8),(89)&7
	line	81
	
i1l183:	
	movf	(??_myisr+3),w
	movwf	btemp+1
	movf	(??_myisr+2),w
	movwf	pclath
	movf	(??_myisr+1),w
	movwf	fsr0
	swapf	(??_myisr+0)^00h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_myisr
	__end_of_myisr:
;; =============== function _myisr ends ============

	signat	_myisr,88
psect	text236,local,class=CODE,delta=2
global __ptext236
__ptext236:
	global	btemp
	btemp set 04Eh

	DABS	1,78,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
