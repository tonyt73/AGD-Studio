; ------------------------------------------------------------------------------------------------------------------------------------------
; Game engine code 
; Arcade Game Designer
; (C) 2008 - 2018 Jonathan Cauldwell
; ZX Spectrum Engine v0.7
; converted to 6809 by Pere Serrat
; debugged and enhanced by Kees van Oss and Pere Serrat - vU8B4 - 2019-01-04
; ------------------------------------------------------------------------------------------------------------------------------------------
; Conditional compilation flags
; Code is installed if flag is set
; Flags are set in commandline assembly or by the compiler
; ------------------------------------------------------------------------------------------------------------------------------------------
; Flags set by AGD compiler
;	mflag  		; MENU + INV
;	pflag 		; particle engine
;	sflag 		; scrollytext
;	dflag 		; digging mode
;	cflag			; collectable blocks
;	oflag			; objects
;	lflag			; ladders
; ------------------------------------------------------------------------------------------------------------------------------------------
; Flags set manually
;	aflag			; adventure mode
;	bflag			; big sprites (16x24)
;	gflag			; graphic colour mode
;	hflag			; hidden sprite mode
;	iflag			; invert mode
;	rflag			; RAM ShiftTables
; ------------------------------------------------------------------------------------------------------------------------------------------
;	if mflag 
;	.out "- MEN/INV enabled"  
;	endif
;	if pflag 
;	.out "- Particles enabled" 
;	endif
;	if sflag 
;	.out "- Scrolling enabled" 
;	endif
;	if dflag
;	.out "- Digging enabled" 
;	endif
;	if cflag
;	.out "- Collectable blocks enabled" 
;	endif
;	if oflag
;	.out "- Objects enabled" 
;	endif
;	if lflag
;	.out "- Ladders enabled" 
;	endif
;	if aflag
;	.out "- Adventure mode enabled" 
;	endif
;	if bflag
;	.out "- Big Sprites (16x24) enabled" 
;	endif
;	if gflag
;	.out "- Colourmode enabled" 
;	endif
;	if hflag
;	.out "- Hidden sprites/foregroundblocks enabled" 
;	endif
;	if iflag
;	.out "- Invert mode enabled" 
;	endif
; ------------------------------------------------------------------------------------------------------------------------------------------
; macro to create the better jump code for any possible case
; ------------------------------------------------------------------------------------------------------------------------------------------
com_bra	equ	$20
com_brn	equ	$21
com_bhi	equ	$22
com_bls	equ	$23
com_bcc	equ	$24
com_bhs	equ	$24
com_bcs	equ	$25
com_blo	equ	$25
com_bne	equ	$26
com_beq	equ	$27
com_bvc	equ	$28
com_bvs	equ	$29
com_bpl	equ	$2a
com_bmi	equ	$2b
com_bge	equ	$2c
com_blt	equ	$2d
com_bgt	equ	$2e
com_ble	equ	$2f
; ------------------------------------------------------------------------------------------------------------------------------------------
CONDJMP	MACRO
	IF	(((\2 - *) >= 0) && ((\2 - *) <= 131)) || (((* - \2) > 0) && ((* - \2) <= 126))
			fcb	com_\1
			fcb	\2 - * - 1
	ELSE
		IF (\1 == "bra")
			fcb	$16
		ELSE
			fcb	$10,com_\1
		ENDIF
			fdb	\2 - * - 2
	ENDIF
			ENDM
; ------------------------------------------------------------------------------------------------------------------------------------------
; Global definitions.																				; Global definitions.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; SIMASK equ 248					; SPRITEINK mask - allows users to set BRIGHT/FLASH/CLUT as well.
sprTab	equ	$d4d9							; d4d9-d5c4 - 204 bytes=12 sprites x 17 bytes	; sprtab	fcb 204 values $ff
sSprit	equ	$d5a5							; d5a5-d5b5 - 17 bytes for spare sprite			; ssprit fcb 17 values
eop		equ	$d5b6							; d5b6-d8b5 - for adventure mode (768 bytes)
SHRAPN	equ	$d8b6							; d8b6-d9ff - uses NUMSHR*SHRSIZ=55*6=330		; SHRAPN equ 63926            ; shrapnel table, just below screen address table.
SCADTB	equ	$da00							; da00-dbff - uses 256*2=512 bytes					; SCADTB equ 64256            ; screen address table, just below map.
MAP		equ	$dc00							; dc00-deff - uses 768 bytes							; MAP    equ 64768            ; properties map buffer.
													; 					24 rows 32 chars -> 768
ENDMAP	equ	$df00							; end of MAP
;Font		equ	$df00							; df00-e1ff - game fonts (768 bytes )
shift0	equ	$e200							; e200-e5ff - Preshifted tables (4 x 256)
ENDXXX	equ	$e600							; *must* be $e600 for graphics screen									
; ------------------------------------------------------------------------------------------------------------------------------------------
; Variables put into 1st RAM PAGE to allow for direct addressing mode
; ------------------------------------------------------------------------------------------------------------------------------------------
joyVal	equ	$00							; fcb	$00											; joy/Keybd reading				; joyval defb 0              ; joystick reading.
frmNo		equ	$01							; fcb	$00											; selected frame					; frmno  defb 0              ; selected frame.
loopA		equ	$02							; fcb	$00											; variable counterA				; loopa  equ 23681           ; loop counter system variable.
loopB		equ	$03							; fcb $00											; loopb  equ 23728            ; loop counter system variable.
llopC		equ	$04							; fcb $00											; loopc  equ 23729            ; loop counter system variable.
varA		equ	$05							; fcb	$00											; variable							; vara   defb 0              ; general-purpose variable.
varB		equ	$06							; fcb $00											; varb   defb 0               ; general-purpose variable.
varC		equ	$07							; fcb	$00											; variable							; varc   defb 0              ; general-purpose variable.
varD		equ	$08							; fcb	$00											; variable							; vard   defb 0              ; general-purpose variable.
varE		equ	$09							; fcb	$00											; variable							; vare   defb 0              ; general-purpose variable.
varF		equ	$0a							; fcb	$00											; variable							; varf   defb 0              ; general-purpose variable.
varG		equ	$0b							; fcb	$00											; variable							; varg   defb 0              ; general-purpose variable.
varH		equ	$0c							; fcb	$00											; variable							; varh   defb 0              ; general-purpose variable.
varI		equ	$0d							; fcb	$00											; variable							; vari   defb 0              ; general-purpose variable.
varJ		equ	$0e							; fcb	$00											; varj   defb 0               ; general-purpose variable.
varK		equ	$0f							; fcb	$00											; number of crystals				; vark   defb 0              ; general-purpose variable.
varL		equ	$10							; fcb	$00											; variable							; varl   defb 0              ; general-purpose variable.
varM		equ	$11							; fcb $00											; varm   defb 0               ; general-purpose variable.
varN		equ	$12							; fcb	$00											; varn   defb 0               ; general-purpose variable.
varO		equ	$13							; fcb	$00											; variable							; varo   defb 0              ; general-purpose variable.
varP		equ	$14							; fcb	$00											; variable							; varp   defb 0              ; general-purpose variable.
varQ		equ	$15							; fcb	$00											; varq   defb 0               ; general-purpose variable.
varR		equ	$16							; fcb	$00											; varr   defb 0               ; general-purpose variable.
varS		equ	$17							; fcb $00											; vars   defb 0               ; general-purpose variable.
varT		equ	$18							; fcb	$00											; vart   defb 0               ; general-purpose variable.
varU		equ	$19							; fcb	$00											; varu   defb 0               ; general-purpose variable.
varV		equ	$1a							; fcb	$00											; varv   defb 0               ; general-purpose variable.
varW	 	equ	$1b							; fcb	$00											; varw   defb 0               ; general-purpose variable.
varZ		equ	$1c							; fcb	$00											; varz   defb 0               ; general-purpose variable.
contrl	equ	$1d							; fcb	$00											; control, 0=KBd, 1=JoyStck	; contrl defb 0              ; control, 0 = keyboard, 1 = Kempston, 2 = Sinclair, 3 = Mouse.
charX		equ	$1e							; fcb	$00           								; cursor X position.				; charx  defb 0              ; cursor x position.
charY		equ	$1f							; fcb	$00           								; cursor Y position.				; chary  defb 0              ; cursor y position.
clock		equ	$20							; fcb	$00											; last clock value read			; clock  defb 0              ; last clock reading.
nexLev	equ	$21							; fcb	$00             							; next level flag.				; nexlev defb 0              ; next level flag.
restFl	equ	$22							; fcb	$00             							; restart screen flag			; restfl defb 0              ; restart screen flag.
deadF		equ	$23							; fcb	$00            							; dead flag.						; deadf  defb 0              ; dead flag.
gamWon	equ	$24							; fcb	$00											; game won flag.					; gamwon defb 0              ; game won flag.
dispX		equ	$25							; fcb	$00											; screen X position.				; dispx  defb 0              ; cursor x position.
dispY		equ	$26							; fcb	$00											; screen Y position.				; dispy  defb 0              ; cursor y position.
bWid		equ	$27							; fcb	$00											; box/menu width.					; bwid   defb 0              ; box/menu width.
bLen		equ	$28							; fcb	$00											; box/menu height					; blen   defb 0              ; box/menu height.
bTop		equ	$29							; fcb	$00											; box coordinates					; btop   defb 0              ; box coordinates.
bLft		equ	$2a							; fcb	$00											; box/menu left					; blft   defb 0
sndTyp	equ	$2b							; fcb	$00											; type of sound to be produced; sndtyp defb 0
comByt	equ	$2c							; fcb	$00											; byte type compressed			; combyt defb 0              ; byte type compressed.
comCnt	equ	$2d							; fcb	$00											; compression counter			; comcnt defb 0              ; compression counter.
subUnit	equ	$2e							; fcb	$00											; value to be subtracted
cocoFlg	equ	$2f							; fcb	$00											; CoCo machine flag
scanOff	equ	$30							; fcb	$00											; offset to add to pointer while scanning keyboard
seed		equ	$31							; fcb $00											; seed   defb 0              	; seed for random numbers.
seed3		equ	$32							; fcb $00											; seed3  defb 0
colPatt	equ	$33							; fcb	$00
sprShft	equ	$34							; fcb $00
readVar	equ	$35							; fcb $00
gPalet	equ	$36							; fcb $00											; graphic palette (0 - 255)
prtMod	equ	$37							; fcb	$00											; print mode, 0 = std, 1 = double-height.	; prtmod defb 0            ; print mode, 0 = standard, 1 = double-height.
NUMVAR	equ	prtMod+1
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
grBase	equ	$50							; fdb	$0000											; graphics (posx, posy)			; grbase defw 15360          ; graphics base address.
pbPtr		equ	$52							; fdb	$0000											; Add a new variable putblock pointer		; pbptr    = $96            
tmp		equ	$54							; fdb	$0000											; used in Adventure mode
ogPtr		equ	$56							; fdb	$0000											; pointer to sprite table		; ogptr  defw 0              ; original sprite pointer.
fontPtr	equ	$58							; fdb	$0000											; pointer to font table - (23606) in ZX-Spectrum
spPtr		equ	$5a							; fdb $0000	- spawned sprite pointer		; spptr  defw 0              ; spawned sprite pointer.
skPtr		equ	$5c							; fdb	$0000											; skptr  defw 0              ; search pointer.
bufAddr	equ	$5e							; fdb $0000 - new sprites routine buffer address
; ------------------------------------------------------------------------------------------------------------------------------------------
;	*** THESE ARE ASSIGNED A VALUE IN INITIALIZATION ROUTINE ***
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Pixel versions of wintop, winlft, winhgt, winwid.
wnTopX	equ	$6a							; fcb (8 * WINDOWTOP)																	; wntopx defb (8 * WINDOWTOP)
wnLftX 	equ	$6b							; fcb (8 * WINDOWLFT)																	; wnlftx defb (8 * WINDOWLFT)
wnBotX 	equ	$6c							; fcb ((WINDOWTOP * 8) + (WINDOWHGT * 8) - 16)									; wnbotx defb ((WINDOWTOP * 8) + (WINDOWHGT * 8) - 16)
wnRgtX 	equ	$6d							; fcb ((WINDOWLFT * 8) + (WINDOWWID * 8) - 16)									; wnrgtx defb ((WINDOWLFT * 8) + (WINDOWWID * 8) - 16)
scNo		equ	$6e							; fcb	$00							; present screen number							; scno   defb 0              ; present screen number.
varOpt	equ	$6f							; fcb	$ff							; last option chosen from menu				; varopt defb 255            ; last option chosen from menu.
numLif	equ	$70							; fcb	$03							; number of lives									; numlif defb 3              ; number of lives.
varRnd	equ	$71							; fcb 255																					; varrnd defb 255            ; last random number.
varObj	equ	$72							; fcb	254							; last object number								; varobj defb 254            ; last object number.
varBlk	equ	$73							; fcb	255																					; varblk defb 255            ; block type.
roomTb	equ	$74							; fcb	34								; room number										; roomtb defb 34             ; room number.
txtBit	equ	$75							; fcb	128																					; txtbit defb 128            ; bit to write.
txtWid	equ	$76							; fcb	16																						; txtwid defb 16             ; width of ticker message.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; Don't change the order of these four.  Menu routine relies on winlft following wintop.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
winTop	equ	$77							; fcb	WINDOWTOP					; top of window									; wintop defb WINDOWTOP      ; top of window.
winLft	equ	$78							; fcb	WINDOWLFT					; left edge											; winlft defb WINDOWLFT      ; left edge.
winHgt	equ	$79							; fcb	WINDOWHGT					; window height									; winhgt defb WINDOWHGT      ; window height.
winWid	equ	$7a							; fcb	WINDOWWID					; window width										; winwid defb WINDOWWID      ; window width.
numOb		equ	$7b							; fcb	NUMOBJ         			; number of objects in game.					; numob  defb NUMOBJ         ; number of objects in game.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; Make sure pointers are arranged in the same order as the data itself.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
frmPtr	equ	$7c							; fdb	frmLst         			; sprite frames									; frmptr defw frmlst         ; sprite frames.
blkPtr	equ	$7e							; fdb	chgFx							; block graphics									; blkptr defw chgfx          ; block graphics.
																																					; colptr defw bcol           ; address of char colours.
proPtr	equ	$80							; fdb	bProp							; address of char properties					; proptr defw bprop          ; address of char properties.
scrPtr	equ	$82							; fdb	scDat							; address of screens								; scrptr defw scdat          ; address of screens.
nmePtr	equ	$84							; fdb	nmeDat         			; enemy start positions							; nmeptr defw nmedat         ; enemy start positions.
andeor	equ	$86							; fdb	$ff00							; values to use in AND - EOR
txtPos	equ	$88							; fdb	msgDat																				; txtpos defw msgdat
zero16b	equ	$8a							; *** system 16 bits zero
txtIni	equ	$8c							; fdb	msgDat																				; txtini defw msgdat
txtScr	equ	$8e							; fdb	SCRBEG																				; txtscr defw 16406
scr_l		equ	$90							; fdb	$0000
scr_r		equ	$92							; fdb	$0000
scr_Txt	equ	$94							; fdb	$0000
; ------------------------------------------------------------------------------------------------------------------------------------------
dNotUs	equ	$97							; *** used for debouncing
dNotUz	equ	$98							; *** the keyboard using jsr [$A000]
; ------------------------------------------------------------------------------------------------------------------------------------------
reg_AF	equ	$a0							; pseudo AF'($a0-a1)
reg_A		equ	reg_AF						; pseudo A' ($a0)
reg_F		equ	reg_AF+1						; pseudo F' ($a1)
reg_BC	equ	$a2							; pseudo BC ($a2-a3)
reg_B		equ	reg_BC						; 1st byte of BC
reg_C		equ	reg_BC+1						; 2nd byte of BC
reg_DE	equ   $a4     						; pseudo DE ($a4-a5)
reg_D		equ	reg_DE						; 1st byte of DE
reg_E		equ	reg_DE+1						; 2nd byte of DE
reg_HL	equ	$a6							; pseudo HL ($a6-a7)
reg_H		equ	reg_HL						; 1st byte of HL
reg_L		equ	reg_HL+1						; 2nd byte of HL
reg_IX	equ	$a8							; pseudo IX ($a8-a9)
reg_IY	equ	$aa							; pseudo IY ($aa-ab)
reg_AX	equ	reg_IY						; re-use pseudo reg
reg_AY	equ	reg_IY+1						; re-use pseudo reg
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
esp_BC	equ	$b0							; mirror register for reg_BC ($b0-b1)
esp_B		equ	esp_BC						; mirror register for reg_B
esp_C		equ	esp_BC+1						; mirror register for reg_C
esp_DE	equ	$b2							; mirror register for reg_DE ($b2-b3)
esp_HL	equ	$b4							; mirror register for reg_HL ($b4-b5)
esp_H		equ	esp_HL						; mirror register for reg_H
esp_L		equ	esp_HL+1						; mirror register for reg_L
; ------------------------------------------------------------------------------------------------------------------------------------------
; Block characteristics.																			; Block characteristics.
; ------------------------------------------------------------------------------------------------------------------------------------------
PLATFM equ 1               				; platform.											; PLATFM equ 1               ; platform.
WALL   equ PLATFM + 1      				; solid wall.										; WALL   equ PLATFM + 1      ; solid wall.
LADDER equ WALL + 1        				; ladder.											; LADDER equ WALL + 1        ; ladder.
FODDER equ LADDER + 1      				; fodder block.									; FODDER equ LADDER + 1      ; fodder block.
DEADLY equ FODDER + 1      				; deadly block.									; DEADLY equ FODDER + 1      ; deadly block.
CUSTOM equ DEADLY + 1      				; custom block.									; CUSTOM equ DEADLY + 1      ; custom block.
WATER  equ CUSTOM + 1      				; water block.										; WATER  equ CUSTOM + 1      ; water block.
COLECT equ WATER + 1       				; collectable block.								; COLECT equ WATER + 1       ; collectable block.
NUMTYP equ COLECT + 1      				; number of types.								; NUMTYP equ COLECT + 1      ; number of types.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Sprites																								; Sprites.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF BFLAG
SPR_HGT	equ	24
SPR_WID	equ	16
NUMSPR	equ	8	              			; number of sprites								; NUMSPR equ 12              ; number of sprites.
	ELSE
SPR_HGT	equ	16
SPR_WID	equ	16
NUMSPR	equ	12              			; number of sprites								; NUMSPR equ 12              ; number of sprites.
	ENDIF

TABSIZ	equ	17              			; size of each entry								; TABSIZ equ 17              ; size of each entry.
SPRBUF	equ	NUMSPR * TABSIZ 			; size of entire table							; SPRBUF equ NUMSPR * TABSIZ ; size of entire table.
NMESIZ	equ	4               			; bytes stored in nmetab for each sprite	; NMESIZ equ 4               ; bytes stored in nmetab for each sprite.
Xval		equ	8								; new x coordinate of sprite					; X      equ 8               ; new x coordinate of sprite.
Yval		equ	Xval+1						; new y coordinate of sprite					; Y      equ X + 1           ; new y coordinate of sprite.
PAM1ST	equ	5               			; first sprite parameter, old x (ix+5)		; PAM1ST equ 5               ; first sprite parameter, old x (ix+5).
; ------------------------------------------------------------------------------------------------------------------------------------------
; Particle engine																						; Particle engine.
; ------------------------------------------------------------------------------------------------------------------------------------------
NUMSHR	equ	55								; pieces of shrapnel.							; NUMSHR equ 55              ; pieces of shrapnel.
SHRSIZ	equ	6								; bytes per particle.							; SHRSIZ equ 6               ; bytes per particle.
; ------------------------------------------------------------------------------------------------------------------------------------------
													; Game starts here.  No reason why screen data couldn't go between start and contrl to put them in
													; contended RAM, leaving the code and rest of the game in uncontended memory at 32768 and beyond.
; ------------------------------------------------------------------------------------------------------------------------------------------
			org	$0e00							; make it CoCo compatible						; 		 org 32000
Start		orcc	#$50							; disable interrupts								; start  equ $
			jsr	SwMap1						; go MAP1 to access 64K of RAM
			jsr   Set6309						; set native mode if a HD6309 is found
NewGame	lds	#$03d6						; set stack to end of Buffer for List		; Set up the font.
			ldx	#font-256					; point to font table (-256)					; 		 ld hl,font-256      ; address of font.
			stx	<fontPtr						; save into variable								; 		 ld (23606),hl       ; set up game font.
			jsr	SetVars						; set initial values for some variables
			jmp	Game							; start the game									; 		 jp game             ; start the game.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Assorted game routines which can go in contended memory.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Modify for inventory																				; Modify for inventory.
; received message number in regA
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF MFLAG
MInve		
	IF GFLAG
			ldx	#$ffaa						; yellow over blue for list, blue on yellow for selected choice
			stx	<andeor
	ENDIF
			ldx	#InvDis						; selfmodify										; minve  ld hl,invdis        ; routine address.
			stx	Mod0+1						; some												; 		 ld (mod0+1),hl      ; set up menu routine.
			stx	Mod2+1						; points												; 		 ld (mod2+1),hl      ; set up count routine.
			ldx	#FOpt							; of													; 		 ld hl,fopt          ; find option from available objects.
			stx	Mod1+1						; program											; 		 ld (mod1+1),hl      ; set up routine.
			bra	DBox							; show data											; 		 jr dbox             ; do menu routine.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Modify for menu.
; ------------------------------------------------------------------------------------------------------------------------------------------
; converted for TESTMENU
MMenu		ldx	#Always																				; mmenu  ld hl,always        ; routine address.
			stx	Mod0+1																				; 		 ld (mod0+1),hl      ; set up routine.
			stx	Mod2+1																				; 		 ld (mod2+1),hl      ; set up count routine.
			ldx	#FStd																					; 		 ld hl,fstd          ; standard option selection.
			stx	Mod1+1																				; 		 ld (mod1+1),hl      ; set up routine.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Drop through into box routine																	; Drop through into box routine.
; Work out size of box for message or menu													; Work out size of box for message or menu.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; ;dbox   ld hl,nummsg        ; total messages.
																											; ;       cp (hl)             ; does this one exist?
																											; ;       ret nc              ; no, nothing to display.
DBox		ldx	#font-256					; ensure
			stx	<fontPtr						; font access
			ldx	#msgDat						; point to messaqes								; dbox   ld hl,msgdat        ; pointer to messages.
			stx	<reg_HL						; put into pseudoreg
			jsr	GetWrd						; point to text for that message				; 		 call getwrd         ; get message number.
			pshs	x								; save pointer to that message				; 		 push hl             ; store pointer to message.
			ldd	#$0100						; height and max width							; 		 ld d,1              ; height.
			std	<reg_DE						; into pseudoreg									; 		 xor a               ; start at object zero.
			stb	<comByt						; first object (zero)							; 		 ld (combyt),a       ; store number of object in combyt.
																											; 		 ld e,a              ; maximum width.
DBox5		clr	<reg_B						; clear width counter							; dbox5  ld b,0              ; this line's width.
Mod2		jsr	Always						; selfmodified code (calls InvDis)			; mod2   call always         ; item in player's possession?
			bne	DBox6							; not in pocket? skip next						; 		 jr nz,dbox6         ; not in inventory, skip this line.
			inc	<reg_D						; add to list										; 		 inc d               ; add to tally.
DBox6		lda	,x+							; get a char, point to next					; dbox6  ld a,(hl)           ; get character.
																											; 		 inc hl              ; next character.
			cmpa	#','							; is it ','?										; 		 cp ','              ; reached end of line?
			beq	DBox3							; yes, skip section								; 		 jr z,dbox3          ; yes.
			cmpa	#13							; is it enter?										; 		 cp 13               ; reached end of line?
			beq	DBox3							; skip two											; 		 jr z,dbox3          ; yes.
			inc	<reg_B						; increment width counter						; 		 inc b               ; add to this line's width.
			tsta									; test read char									; 		 and a               ; end of message?
			bmi	DBox4							; if end of message, skip section			; 		 jp m,dbox4          ; yes, end count.
			bra	DBox6							; loop for next char								; 		 jr dbox6            ; repeat until we find the end.
DBox3		lda	<reg_E						; get max width									; dbox3  ld a,e              ; maximum line width.
			cmpa	<reg_B						; is current width greater?					; 		 cp b                ; have we exceeded longest so far?
			bcc	DBox5							; no, keep on looking							; 		 jr nc,dbox5         ; no, carry on looking.
			ldb	<reg_B						; update
			stb	<reg_E						; max width											; 		 ld e,b              ; make this the widest so far.
			bra	DBox5							; loop for next item								; 		 jr dbox5            ; keep looking.
DBox4		lda	<reg_E						; get max width									; dbox4  ld a,e              ; maximum line width.
			cmpa	<reg_B						; is curent width greater?						; 		 cp b                ; have we exceeded longest so far?
			bcc	DBox8							; no, skip update									; 		 jr nc,dbox8         ; no, carry on looking.
			ldb	<reg_B						; update
			stb	<reg_E						; max width											; 		 ld e,b              ; final line is the longest so far.
DBox8		dec	<reg_D						; decrement number of items found			; dbox8  dec d               ; decrement items found.
			lbeq	DBox15						; if zero exit										; 		 jp z,dbox15         ; total was zero.
			lda	<reg_E						; get max width									; 		 ld a,e              ; longest line.
																											; 		 and a               ; was it zero?
			lbeq	DBox15						; if zero exit										; 		 jp z,dbox15         ; total was zero.
			ldd	<reg_DE						; get height and width							; 		 ld (bwid),de        ; set up size.
			exg	a,b							; invert positions
			std	<bWid							; update bWid and bLen (height) 
; ------------------------------------------------------------------------------------------------------------------------------------------
; That's set up our box size																		; That's set up our box size.
; ------------------------------------------------------------------------------------------------------------------------------------------
			lda	<winHgt						; get window height								; 		 ld a,(winhgt)       ; window height in characters.
			suba	<reg_D						; subtract box height							; 		 sub d               ; subtract height of box.
			rora									; divide by 2										; 		 rra                 ; divide by 2.
			ldx	#winTop						; point to window top edge						; 		 ld hl,wintop        ; top edge of window.
			adda	,x								; add displacement								; 		 add a,(hl)          ; add displacement.
			sta	<bTop							; save as box top									; 		 ld (btop),a         ; set up box top.
			lda	<winWid						; get window width								; 		 ld a,(winwid)       ; window width in characters.
			suba	<reg_E						; subtract box width								; 		 sub e               ; subtract box width.
			rora									; divide by 2										; 		 rra                 ; divide by 2.
			leax	1,x							; point to window left edge					; 		 inc hl              ; left edge of window.
			adda	,x								; add displacement								; 		 add a,(hl)          ; add displacement.
			sta	<bLft							; save as box left								; 		 ld (blft),a         ; box left.
																											; 		 ld hl,(23606)       ; font.
																											; 		 ld (grbase),hl      ; set up for text display.
			puls	x								; get pointer to text							; 		 pop hl              ; restore message pointer.
			lda	<bTop							; set box top										; 		 ld a,(btop)         ; box top.
			sta	<dispY						; as Y coordinate									; 		 ld (dispx),a        ; set display coordinate.
																											; 		 xor a               ; start at object zero.
			clr	<comByt						; start at object zero							; 		 ld (combyt),a       ; store number of object in combyt.
DBox2		lda	<comByt						; get object number								; dbox2  ld a,(combyt)       ; get object number.
Mod0		jsr	Always						; selfmodified code (calls InvDis)			; mod0   call always         ; check inventory for display.
			lbne	DBox13						; object not in Inv, go for next one		; 		 jp nz,dbox13        ; not in inventory, skip this line.
; ------------------------------------------------------------------------------------------------------------------------------------------
			lda	<bLft							; get box left										; 		 ld a,(blft)         ; box left.
			sta	<dispX						; set as X coordinate							; 		 ld (dispy),a        ; set left display position.
			lda	<bWid							; get box width									; 		 ld a,(bwid)         ; box width.
			sta	<reg_B						; put in reg_B										; 		 ld b,a              ; store width.
DBox0		lda	,x								; get a char										; dbox0  ld a,(hl)           ; get character.
			cmpa	#','							; is it ','?										; 		 cp ','              ; end of line?
			beq	DBox1							; yes, skip it										; 		 jr z,dbox1          ; yes, next one.
			cmpa	#13							; is it Enter?										; 		 cp 13               ; end of option?
			beq	DBox1							; go for next one									; 		 jr z,dbox1          ; yes, on to next.
			dec	<reg_B						; decrement width counter						; 		 dec b               ; one less to display.
			anda	#127							; remove bit7										; 		 and 127             ; remove terminator.
			ldu	<reg_BC						; get pseudoreg									; 		 push bc             ; store characters remaining.
			pshs	x,u							; push onto stack									; 		 push hl             ; store address on stack.
																											; 		 push af             ; store character.
													; no													; 		 call gaadd          ; get attribute address.
													; colours											; 		 ld a,(23693)        ; current colour.
													; by now												; 		 ld (hl),a           ; set attribute.
																											; 		 pop af              ; restore character.
			jsr	PChr0							; show char as Text (from fonts)				; 		 call pchr           ; display on screen.
			puls	x,u							; restore pointers								; 		 pop hl              ; retrieve address of next character.
			stu	<reg_BC						; into pseudoreg									; 		 pop bc              ; chars left for this line.
			lda	,x+							; get a char, point to next					; 		 ld a,(hl)           ; get character.
																											; 		 inc hl              ; next character.
			cmpa	#128							; is end of message?								; 		 cp 128              ; end of message?
			bcc	DBox7							; yes, exit message printing					; 		 jp nc,dbox7         ; yes, job done.
			lda	<reg_B						; get remaining chars number					; 		 ld a,b              ; chars remaining.
																											; 		 and a               ; are any left?
			bne	DBox0							; not yet done? loopback						; 		 jr nz,dbox0         ; yes, continue.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Reached limit of characters per line															; Reached limit of characters per line.
; ------------------------------------------------------------------------------------------------------------------------------------------
DBox9		lda	,x+							; get a char, point to next					; dbox9  ld a,(hl)           ; get character.
																											; 		 inc hl              ; next one.
			cmpa	#','							; is it ','?										; 		 cp ','              ; another line?
			beq	DBox10						; yes, go next line								; 		 jr z,dbox10         ; yes, do next line.
			cmpa	#13							; is it Enter?										; 		 cp 13               ; another line?
			beq	DBox10						; yes, go next line								; 		 jr z,dbox10         ; yes, on to next.
			cmpa	#128							; is end of message?								; 		 cp 128              ; end of message?
			bcc	DBox11						; yes, finish mesage								; 		 jr nc,dbox11        ; yes, finish message.
			bra	DBox9							; loopback for next char						; 		 jr dbox9
; ------------------------------------------------------------------------------------------------------------------------------------------
; Fill box to end of line																			; Fill box to end of line.
; ------------------------------------------------------------------------------------------------------------------------------------------
DBoxf		ldu	<reg_BC						; get pseudoreg BC								; dboxf  push hl             ; store address on stack.
			pshs	x,u							; push onto stack									; 		 push bc             ; store characters remaining.
																											; 		 call gaadd          ; get attribute address.
																											; 		 ld a,(23693)        ; current colour.
																											; 		 ld (hl),a           ; set attribute.
			lda	#32							; get a 'space char'								; 		 ld a,32             ; space character.
			jsr	PChr0							; Show char											; 		 call pchr           ; display character.
			puls	x,u							; restore pointers								; 		 pop bc              ; retrieve character count.
			stu	<reg_BC						; into peuodreg									; 		 pop hl              ; retrieve address of next character.
			dec	<reg_B						; decrement line chars pending counter
			bne	DBoxf							; not yet done? loopback						; 		 djnz dboxf          ; repeat for remaining chars on line.
			rts									; return												; 		 ret
DBox1		leax	1,x							; skip read char									; dbox1  inc hl              ; skip character.
			jsr	DBoxf							; fill box till end of right side			; 		 call dboxf          ; fill box out to right side.
DBox10																									; dbox10 ld a,(dispx)        ; x coordinate.
																											; 		 inc a               ; down a line.
			inc	<dispY						; increment Y coordinate						; 		 ld (dispx),a        ; next position.
			bra	DBox2							; go for next line								; 		 jp dbox2            ; next line.
DBox7		lda	<reg_B						; get remaining chars							; dbox7  ld a,b              ; chars remaining.
																											; 		 and a               ; are any left?
			beq	DBox11						; already done? skip next						; 		 jr z,dbox11         ; no, nothing to draw.
			jsr	DBoxf							; fill line 										; 		 call dboxf          ; fill message to line.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Drawn the box menu, now select option														; Drawn the box menu, now select option.
; ------------------------------------------------------------------------------------------------------------------------------------------
DBox11	lda	<bTop							; get box top										; dbox11 ld a,(btop)         ; box top.
			sta	<dispY						; put as Y coordinate							; 		 ld (dispx),a        ; set bar position.
DBox14	jsr	VSync							; read joystick-keyboard
			lda	<joyVal						; get result
			anda	#95							; anything pressed?								; 		 and 31              ; anything pressed?
			bne	DBox14						; yes, debounce it								; 		 jr nz,dbox14        ; yes, debounce it.
			jsr	DBar							; draw bar											; 		 call dbar           ; draw bar.
DBox12	jsr	VSync							; read joystick-keyboard
			lda	<joyVal						; get result
			bita	#64							; is 'I' pressed?
			lbne	ReDraw						; yes, exit inventory (do nothing)
			anda	#28							; pressed Up-Down-Fire?							; 		 and 28              ; anything pressed?
			beq	DBox12						; no, wait for order								; 		 jr z,dbox12         ; no, nothing.
			anda	#16							; was it fire?										; 		 and 16              ; fire button pressed?
			beq	1f								; no, verify moves U-D
Mod1		jmp	FStd							; selfmodified code	(calls FOpt = exit)	; mod1   jp nz,fstd          ; yes, job done.
1			jsr	DBar							; delete bar										; 		 call dbar           ; delete bar.
			lda	<joyVal						; get selected choice							; 		 ld a,(joyval)       ; joystick reading.
			anda	#8								; was Up?											; 		 and 8               ; going up?
			bne	DBoxu							; yes, go Up										; 		 jr nz,dboxu         ; yes, go up.
			lda	<dispY						; get bar vertical position					; 		 ld a,(dispx)        ; vertical position of bar.
			inca									; look next one									; 		 inc a               ; look down.
			ldx	#bTop							; point to box top								; 		 ld hl,btop          ; top of box.
			suba	,x								; subtract											; 		 sub (hl)            ; find distance from top.
			leax	-1,x							; point to bLen (height)						; 		 dec hl              ; point to height.
			cmpa	,x								; are we at the end?								; 		 cp (hl)             ; are we at end?
			beq	DBox14						; yes, discard command							; 		 jp z,dbox14         ; yes, go no further.
																											; 		 ld hl,dispx         ; coordinate.
			inc	<dispY						; move bar down									; 		 inc (hl)            ; move bar.
			bra	DBox14						; loopback											; 		 jr dbox14           ; continue.
DBoxu		lda	<dispY						; get bar vertical position					; dboxu  ld a,(dispx)        ; vertical position of bar.
																											; 		 ld hl,btop          ; top of box.
			cmpa	<bTop							; are we at top?									; 		 cp (hl)             ; are we at the top?
			beq	DBox14						; yes, discard command							; 		 jp z,dbox14         ; yes, go no further.
																											; 		 ld hl,dispx         ; coordinate.
			dec	<dispY						; move bar up										; 		 dec (hl)            ; move bar.
			bra	DBox14						; loopback											; 		 jr dbox14           ; continue.
FStd		lda	<dispY						; get bar vertical position					; fstd   ld a,(dispx)        ; bar position.
																											; 		 ld hl,btop          ; top of menu.
			suba	<bTop							; find selected option							; 		 sub (hl)            ; find selected option.
			sta	<varOpt						; store into variable							; 		 ld (varopt),a       ; store the option.
			lbra	ReDraw						; redraw screen														; 		 jp redraw           ; redraw the screen.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Option not available.  Skip this line														; Option not available.  Skip this line.
; ------------------------------------------------------------------------------------------------------------------------------------------
DBox13	lda	,x+							; get char, point to next						; dbox13 ld a,(hl)           ; get character.
																											; 		 inc hl              ; next one.
			cmpa	#','							; is it ','?										; 		 cp ','              ; another line?
			lbeq	DBox2							; yes, go for next line							; 		 jp z,dbox2          ; yes, do next line.
			cmpa	#13							; is it Enter?										; 		 cp 13               ; another line?
			lbeq	DBox2							; yes, go for next line							; 		 jp z,dbox2          ; yes, on to next line.
			tsta									; end of message?									; 		 and a               ; end of message?
			bmi	DBox11						; yes, end of message							; 		 jp m,dbox11         ; yes, finish message.
			bra	DBox13						; loop for next char								; 		 jr dbox13
DBox15	puls	x,pc							; restore pointer and return					; dbox15 pop hl              ; pop message pointer from the stack.
																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
DBar		lda	<bLft							; get box left										; dbar   ld a,(blft)         ; box left.
			sta	<dispX						; put as X coordinate							; 		 ld (dispy),a        ; set display coordinate.
			jsr	GPrad							; get printing address							; 		 call gprad          ; get printing address.
			ldx	<grBase						; get calculated pointer						; 		 ex de,hl            ; flip into hl register pair.
			stx	<reg_HL						; update pseudoreg
			lda	<bWid							; get box width									; 		 ld a,(bwid)         ; box width.
			sta	<reg_C						; store counter in pseudoreg					; 		 ld c,a              ; loop counter in c.
			ldb	<reg_H						; get screen high address byte
			stb	<reg_D						; put in pseuroreg D								; 		 ld d,h              ; store screen address high byte.
DBar1		ldb	#8								; pixels counter									; dbar1  ld b,8              ; pixel height in b.
DBar0		lda	,x								; get a screen byte								; dbar0  ld a,(hl)           ; get screen byte.
			coma									; reverse all bits								; 		 cpl                 ; reverse all bits.
			sta	,x								; update scrfeen									; 		 ld (hl),a           ; write back to screen.
			leax	32,x							; point to next row down						; 		 inc h               ; next line down.
			decb									; decrement counter
			bne	DBar0							; not zero? loopback								; 		 djnz dbar0          ; draw rest of character.
			stx	<reg_HL						; update pseudoreg HL
			ldb	<reg_D						; restore
			stb	<reg_H						; screen address									; 		 ld h,d              ; rsetore screen address.
			inc	<reg_L						; one char right									; 		 inc l               ; one char right.
			ldx	<reg_HL						; get screen pointer
			dec	<reg_C						; decrement counter								; 		 dec c               ; decrement character counter.
			bne	DBar1							; not done? same for whole line				; 		 jr nz,dbar1         ; repeat for whole line.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; called from DBox5 - Mod2
; ------------------------------------------------------------------------------------------------------------------------------------------
InvDis	ldu	<reg_DE						; get pseudoreg DE (again)						; invdis push hl             ; store message text pointer.
			pshs	x,u							; push pointers									; 		 push de             ; store de pair for line count.
																											; 		 ld hl,combyt        ; object number.
			lda	<comByt						; get object number								; 		 ld a,(hl)           ; get object number.
			inc	<comByt						; increment it (for next time)				; 		 inc (hl)            ; ready for next one.
			jsr	GotOb							; check we have the object (regA)			; 		 call gotob          ; check if we have object.
			tfr	cc,b							; save result (flags)
			puls	x,u							; restore pointers								; 		 pop de              ; retrieve de pair from stack.
			stu	<reg_DE						; put into pseudoreg								; 		 pop hl              ; retrieve text pointer.
			tfr	b,cc							; set result flags
			rts									; return												; 		 ret
																											; ;always xor a               ; set zero flag.
																											; ;       ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Find option selected																				; Find option selected.
; ------------------------------------------------------------------------------------------------------------------------------------------
FOpt		lda	<dispY						; get Y coordinate								; fopt   ld a,(dispx)
																											; 		 ld hl,btop          ; top of menu.
			suba	<bTop							; subtract the one for the top element		; 		 sub (hl)            ; find selected option.
			inca									; increment (0->1)								; 		 inc a               ; object 0 needs one iteration, 1 needs 2 and so on.
			sta	<reg_B						; save in reg_B									; 		 ld b,a              ; option selected in b register.
																											; 		 ld hl,combyt        ; object number.
			clr	<comByt						; point to first object							; 		 ld (hl),0           ; set to first item.
FOpt0		ldd	<reg_BC						; get reg_BC
			pshs	d								; save it to stack								; fopt0  push bc             ; store option counter in b register.
			bsr	FObj							; find next object in inventory				; 		 call fobj           ; find next object in inventory.
			puls	d								; restore counter									; 		 pop bc              ; restore option counter.
			std	<reg_BC						; to pseudoreg
			dec	<reg_B						; decrement counter
			bne	FOpt0							; not zero? loopback								; 		 djnz fopt0          ; repeat for relevant steps down the list.
			lda	<comByt						; get option										; 		 ld a,(combyt)       ; get option.
			deca									; decrement											; 		 dec a               ; one less, due to where we increment combyt.
			sta	<varOpt						; store in variable (chosen object)			; 		 ld (varopt),a       ; store the option.
			lbra	ReDraw						; redraw screen									; 		 jp redraw           ; redraw the screen.
																											; 
FObj																										; fobj   ld hl,combyt        ; object number.
			lda	<comByt						; get counter										; 		 ld a,(hl)           ; get object number.
			inc	<comByt						; increment it										; 		 inc (hl)            ; ready for next item.
			beq	FOptEx						; if zero, return									; 		 ret z               ; in case we loop back to zero.
			jsr	GotOb							; verify if we hace this object				; 		 call gotob          ; do we have this item?
																											; 		 ret z               ; yes, it's on the list.
																											; 		 jr fobj             ; repeat until we find next item in pockets.
			bne	FObj							; no, next one. Optimizing jumps				; 		 jr fobj             ; repeat until we find next item in pockets.
FOptEx	rts									; return
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Wait for keypress.																					; Wait for keypress.
; ------------------------------------------------------------------------------------------------------------------------------------------
PrsKey																									; prskey call debkey         ; debounce key.
			jsr	VSync							; synchronice with FS							; prsky0 call vsync          ; vertical synch.
			jsr	ReadK							; read keyboard									; 		 call 654            ; return keyboard state in e.
																											; 		 inc e               ; is it 255?
			beq	PrsKey						; if no key, loopback							; 		 jr z,prsky0         ; yes, repeat until key pressed.
													; Debounce keypress.																	; Debounce keypress
																											; debkey call vsync          ; update scrolling, sounds etc.
																											; 		 call 654            ; d=shift, e=key.
																											; 		 inc e               ; is it 255?
																											; 		 jr nz,debkey        ; no - loop until key is released.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Delay routine																						; Delay routine.
; register B contains de number of loops to be done
; ------------------------------------------------------------------------------------------------------------------------------------------
Delay		ldx	<reg_IX						; get pseudo register
			pshs	x								; save onto stack
Delay1	pshs	b								; save counter										; delay  push bc             ; store loop counter.
			jsr	VSync							; wait for FS interrupt							; 		 call vsync          ; wait for interrupt.
			puls	b								; restore counter									; 		 pop bc              ; restore counter.
			decb									; decrement it			
			bne	Delay1						; not zero, loopback								; 		 djnz delay          ; repeat.
			puls	x								; restore pseudo register
			stx	<reg_IX						; update it
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Clear sprite table.																				; Clear sprite table.
; ------------------------------------------------------------------------------------------------------------------------------------------
XSpr		ldx	#sprTab						; point to sprites table						; xspr   ld hl,sprtab        ; sprite table.
			ldb	#SPRBUF+17					; get table length plus spare sprite		; 		 ld b,SPRBUF         ; length of table.
			lda	#255							; value to clean table							; xspr0  ld (hl),255         ; clear one byte.
XSpr0		sta	,x+							; clean one byte									; 		 inc hl              ; move to next byte.
			decb									; decrement counter
			bne	XSpr0							; not yet done? loopback						; 		 djnz xspr0          ; repeat for rest of table.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; silenc call silen1         ; silence channel 1.
;																											; 		 call silen2         ; silence channel 2.
;																											; 		 call silen3         ; silence channel 3.
;																											; 		 jp plsnd            ; play all channels to switch them off.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Initialise all objects.																			; Initialise all objects.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF OFLAG
IniOb		ldx	#objDta+36					; point to Object data table					; iniob  ld ix,objdta        ; objects table.
			ldb	<numOb						; number of objects								; 		 ld a,(numob)        ; number of objects in the game.
																											; 		 ld b,a              ; loop counter.
																											; 		 ld de,39            ; distance between objects.
IniOb0	lda	,x								; start screen										; iniob0 ld a,(ix+36)        ; start screen.
			sta	-3,x							; set start screen								; 		 ld (ix+33),a        ; set start screen.
			lda	1,x							; get start X										; 		 ld a,(ix+37)        ; find start x.
			sta	-2,x							; set start X										; 		 ld (ix+34),a        ; set start x.
			lda	2,x							; get initial Y									; 		 ld a,(ix+38)        ; get initial y.
			sta	-1,x							; set it												; 		 ld (ix+35),a        ; set y coord.
			leax	39,x							; point to next object							; 		 add ix,de           ; point to next object
			decb									; decrement counter
			bne	IniOb0						; not yet done? loopback						; 		 djnz iniob0         ; repeat.
			rts									; return												; 		 ret
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Screen synchronisation.																			; Screen synchronisation.
;  - read joystick/keyboard																		;  - read joystick/keyboard
;  - handle sound																						;  - handle sound
;  - sync framerate with clock																	;  - sync framerate with clock
;  - handle shrapnel																					;  - handle shrapnel
; ------------------------------------------------------------------------------------------------------------------------------------------
VSync		jsr 	JoyKey						; read joystick/keyboard						; vsync  call joykey         ; read joystick/keyboard.
			lda	<sndTyp						; get sound type									; 		 ld a,(sndtyp)       ; sound to play.
			bmi	VSync6						; if negative go play white noise			; 		 and a               ; any sound?
			beq	VSync1						; if none, exit sound section					; 		 jp z,vsync1         ; no.
			sta	<reg_B						; save as outer loop								; 		 ld b,a              ; outer loop.
																											; 		 ld a,(23624)        ; border colour.
																											; 		 rra                 ; put border bits into d0, d1 and d2.
																											; 		 rra
			clra									; get min value for DAC (1st value)			; 		 rra
																											; 		 ld c,a              ; first value to write to speaker.
																											; 		 ld a,b              ; sound.
																											; 		 and a               ; test it.
																											; 		 jp m,vsync6         ; play white noise.
VSync2																									; vsync2 ld a,c            ; get speaker value.
			sta	$ff20							; send to DAC										; 		 out (254),a         ; write to speaker.
			eora	#%11111100					; invert value										; 		 xor 248             ; toggle all except the border bits.
			ldb	<reg_B						; get loop counter								; 		 ld c,a              ; store value for next time.
			stb	<reg_D						; save in reg_D									; 		 ld d,b              ; store loop counter.
VSync3	ldb	TIMER							; get current clock								; vsync3 ld hl,clock       ; previous clock setting.
			cmpb	<clock						; compare to previous clock value			; 		 ld a,(23672)        ; current clock setting.
			blo	VSync4						; if clock is greater exit loop (never)	; 		 cp (hl)             ; subtract last reading.
													; was bne, later brn to avoid effect
			dec	<reg_B						; decrement inner loop							; 		 jp nz,vsync4        ; yes, no more processing please.
			bne	VSync3						; not zero? loopback								; 		 djnz vsync3         ; loop.
			ldb	<reg_D						; get outer loop counter
			stb	<reg_B						; restore in reg_B								; 		 ld b,d              ; restore loop counter.
 			dec	<reg_B						; decrment outer loop
 			bne	VSync2						; not zero? continue sound						; 		 djnz vsync2         ; continue noise.
VSync4	lda	<reg_D						; get last used outer counter					; vsync4 ld a,d            ; where we got to.
VSynca	sta	<sndTyp						; save for next time								; vsynca ld (sndtyp),a     ; remember for next time.
VSync1																									; vsync1 ld a,(23672)      ; clock low.
																											; 		 rra                 ; rotate bit into carry.
			jsr	VSync5						; go for shrapnel									; 		 call c,vsync5       ; time to play sound and do shrapnel/ticker stuff.
																											; 		 ld hl,clock         ; last clock reading.
VSync0	lda	TIMER							; get actual timer								; vsync0 ld a,(23672)      ; current clock reading.
			cmpa	<clock						; compare to last read							; 		 cp (hl)             ; are they the same?
			beq	VSync0						; yes, wait until clock changes				; 		 jr z,vsync0         ; yes, wait until clock changes.
			sta	<clock						; update last read value						; 		 ld (hl),a           ; set new clock reading.
			rts									; return												; 		 ret
																											; ;vsync5 call plsnd       ; play sound.
VSync5	jmp	ProShr						; shrapnel and others							; vsync5 jp proshr         ; shrapnel and stuff.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Play white noise.																					; Play white noise.
; ------------------------------------------------------------------------------------------------------------------------------------------
VSync6	pshs	b								; save parameter									; vsync6 ld a,b            ; 128 - 255.
			subb	#127							; convert to positive							; 		 sub 127
																											; 		 ld b,a
																											; 		 ld hl,clock         ; previous clock setting.
VSync7	jsr	Random						; get a random number							; vsync7 ld a,r              ; get random speaker value.
																											; 		 and 248             ; only retain the speaker/earphone bits.
																											; 		 or c                ; merge with border colour.
			anda	#%11111100					; clear unused 2 low bits
			sta	$ff20							; send to DAC										; 		 out (254),a         ; write to speaker.
			lda	TIMER							; get actual timer								; 		 ld a,(23672)        ; current clock setting.
			cmpa	<clock						; same than last one								; 		 cp (hl)             ; subtract last reading.
			bne	VSync8						; no, exit loop									; 		 jp nz,vsync8        ; yes, no more processing please.
			lda	,s								; get parameter again							; 		 ld a,b
			anda	#127							; reset bit 7 (negative)						; 		 and 127
			inca									; increment it										; 		 inc a
VSync9	deca									; decrement it										; vsync9 dec a
			bne	VSync9						; not yet zero? loopback						; 		 jr nz,vsync9        ; loop.
			dec	,s								; decrement parameter in stack
			bne	VSync7						; not yet zero? loopback						; 		 djnz vsync7         ; continue noise.
VSync8	leas	1,s							; clean stack										; vsync8 xor a
			clra									; get value zero (not sound)					
			bra	VSynca						; exit via VSynca									; 		 jr vsynca
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
																											; ;clock  defb 0              ; last clock reading.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Redraw the screen																					; Redraw the screen.
; Remove old copy of all sprites for redraw													; Remove old copy of all sprites for redraw.
; ------------------------------------------------------------------------------------------------------------------------------------------
ReDraw	
	IF GFLAG
			ldx	#$ff00						; avoid changing received colours
			stx	<andeor						; to masks
	ENDIF
			ldx	<reg_IX						; get pseudo reg
			pshs	x								; push onto stack									; redraw push ix             ; place sprite pointer on stack.
			jsr	DRoom							; Show screen layout (blocks)					; 		 call droom          ; show screen layout.
	IF OFLAG
			jsr	ShwOb							; draw OBjects										; 		 call shwob          ; draw objects.
	ENDIF
NumSp0	ldb	#NUMSPR						; sprites to draw									; numsp0 ld b,NUMSPR         ; sprites to draw.
			ldx	#sprTab						; point to sprites data table					; 		 ld ix,sprtab        ; sprite table.
			stx	<reg_IX						; update pseudoreg
ReDrw0	lda	,x								; get old sprite type							; redrw0 ld a,(ix+0)         ; old sprite type.
			inca									; is enabled?										; 		 inc a               ; is it enabled?
			beq	ReDrw1						; no, go for next one							; 		 jr z,redrw1         ; no, find next one.
			lda	3,x							; get Y coordinate								; 		 ld a,(ix+3)         ; sprite x.
			cmpa	#177							; beyond maximum?									; 		 cp 177              ; beyond maximum?
			bcc	ReDrw1						; yes, do not draw								; 		 jr nc,redrw1        ; yes, nothing to draw.
			pshs	b,x							; put registers onto stack						; 		 push bc             ; store sprite counter.
			jsr	SSpriA						; show sprite										; 		 call sspria         ; show single sprite.
			puls	b,x							; restore registers								; 		 pop bc              ; retrieve sprite counter.
ReDrw1																									; redrw1 ld de,TABSIZ        ; distance to next odd/even entry.
			leax	TABSIZ,x						; point to next sprite							; 		 add ix,de           ; next sprite.
			decb									; decrement counter
			bne	ReDrw0						; not yet done? go for next one				; 		 djnz redrw0         ; repeat for remaining sprites.
Rpblc1
	IF PFLAG
			jsr	DShrp							; redraw Shrapnel									; rpblc1 call dshrp          ; redraw shrapnel.
	ENDIF
	IF AFLAG
			jsr	RBloc							; draw blocks for this screen
	ENDIF	
			puls	x								; restore pointer									; 		 pop ix              ; retrieve sprite pointer.
			stx	<reg_IX						; put into pseudoreg
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Clear screen routine																				; Clear screen routine
; uses *always* the background colour (andeor+1)
; ------------------------------------------------------------------------------------------------------------------------------------------
Cls																										; cls  ld hl,16384         ; screen address.
																											; 		 ld (hl),l           ; blank first byte.
			lda	<andeor+1					; create a 											; 		 ld (hl),l           ; blank first byte.
																											; 		 ld de,16385         ; second byte.
			tfr	a,b							; 16 bits background value						; 		 ld de,16385         ; second byte.
			ldx	#SCRBEG						; point to beginning of screen
Cls01		std	,x++							; paint 2 bytes									; 		 ld bc,6144          ; bytes to copy.
			cmpx	#SCREND						; end of screen?									; 		 ldir                ; blank them all.
			bcs	Cls01							; no, loopback										; 		 ld a,(23693)        ; fetch attributes.
																											; 		 ld (hl),a           ; set first attribute cell.
																											; 		 ld bc,767           ; number of attributes.
																											; 		 ldir                ; set all attributes.
																											; 		 ld hl,0             ; set hl to origin (0, 0).
																											; 		 ld (charx),hl       ; reset coordinates.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; Set palette routine and data.
;																											; Palette.
;																											; 48955 = register select port.
;																											; 65339 = data read/write port.
;																											;
;																											; 48955 = write to register:
;																											; d0-d5 : select register sub-group.
;																											; d6-d7 : select register group.
;																											;         00 = sub-group determines entry in palette table.
;																											;         64 = mode select, write d0 to 65339 to toggle mode on/off.
;																											;
;																											; 65339 = data read/write:
;																											; d0-d1 : blue intensity (last bit duplicated so Bb is Bbb)
;																											; d2-d4 : red intensity
;																											; d5-d7 : green intensity
; ------------------------------------------------------------------------------------------------------------------------------------------
; 													NOT NEEDED - palette is static in MC6847
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; setpal ld bc,48955         ; register select.
;																											; 		 ld a,64             ; mode select.
;																											; 		 out (c),a           ; set ULAplus mode.
;																											; 		 ld b,255            ; data write.
;																											; 		 ld a,1              ; mode on.
;																											; 		 out (c),a           ; switch on ULAplus.
;																											; 		 ld b,64             ; number of palette table entries to write.
;																											; setpa1 ld hl,palett        ; palette we want.
;																											; 		 ld e,0              ; register number.
;																											; setpa0 push bc             ; store counter.
;																											; 		 ld b,191            ; register select.
;																											; 		 ld a,e              ; register number to write.
;																											; 		 out (c),a           ; write to port.
;																											; 		 ld b,255            ; data select.
;																											; 		 ld a,(hl)           ; get colour data from table.
;																											; 		 out (c),a           ; write to port.
;																											; 		 inc e               ; next clut entry.
;																											; 		 inc hl              ; next table entry.
;																											; 		 pop bc              ; restore counter from stack.
;																											; 		 djnz setpa0         ; set rest of palette.
;																											; 		 ret
;																											; endpal equ $
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #11 - T01A - DONE
	IF PFLAG+DFLAG
FdChk		lda	,x								; get cell code									; fdchk  ld a,(hl)           ; fetch cell.
			cmpa	#FODDER						; is it FODDER?									; 		 cp FODDER           ; is it fodder?
			bne	FdChkEx						; no, return										; 		 ret nz              ; no.
			clr	,x								; delete fodder to code $00					; 		 ld (hl),0           ; rewrite block type.
			pshs	x								; save MAP pointer								; 		 push hl             ; store pointer to block.
			tfr	x,d							; pass address to regD							; 		 ld de,MAP           ; address of map.
			subd	#MAP							; subtract MAP beginning						; 		 and a               ; clear carry flag for subtraction.
			tfr	d,x							; send block offset to regX					; 		 sbc hl,de           ; find simple displacement for block.
													; low byte is X coordinate						; 		 ld a,l              ; low byte is y coordinate.
			andb	#31							; ensure valid value								; 		 and 31              ; column position 0 - 31.
			stb	<dispX						; to variable for coord X						; 		 ld (dispy),a        ; set up y position.
			tfr	x,d							; get offset again
			lslb									; multiply											; 		 add hl,hl           ; multiply displacement by 8.
			rola									; displacement
			lslb									; by													; 		 add hl,hl
			rola									; eight
			lslb									;														; 		 add hl,hl
			rola									; Y coordinate										; 		 ld a,h              ; x coordinate now in h.
			sta	<dispY						; into variable 									; 		 ld (dispx),a        ; set the display coordinate.
			clra									; set null block code							; 		 xor a               ; block to write.
			jsr	PAttr							; write it											; 		 call pattr          ; write block.
			puls	x								; restore MAP pointer							; 		 pop hl              ; restore block pointer.
FdChkEx	rts									; return												; 		 ret
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Colour a sprite																						; Colour a sprite.
; ------------------------------------------------------------------------------------------------------------------------------------------
;													; NO sprite painting!!!							; cspr   ld a,(ix+8)         ; look at the vertical first.
;																											; 		 cp 177              ; is it out-of-range?
;																											; 		 ret nc              ; yes, can't colour it.
;																											; 		 rlca                ; divide by 64.
;																											; 		 rlca                ; quicker than 6 rrca operations.
;																											; 		 ld l,a              ; store in e register for now.
;																											; 		 and 3               ; mask to find segment.
;																											; 		 add a,88            ; attributes start at 88*256=22528.
;																											; 		 ld h,a              ; that's our high byte sorted.
;																											; 		 ld a,l              ; vertical/64 - same as vertical*4.
;																											; 		 and 224             ; want a multiple of 32.
;																											; 		 ld l,a              ; vertical element calculated.
;																											; 		 ld a,(ix+9)         ; get horizontal position.
;																											; 		 rra                 ; divide by 8.
;																											; 		 rra
;																											; 		 rra
;																											; 		 and 31              ; want result in range 0-31.
;																											; 		 add a,l             ; add to existing low byte.
;																											; 		 ld l,a              ; that's the low byte done.
;																											; 		 ld de,30            ; distance to next line down.
;																											; 		 ld a,(ix+8)         ; x coordinate.
;																											; cspr2  ld b,3              ; default rows to write.
;																											; 		 and 7               ; does x straddle cells?
;																											; 		 jr nz,cspr0         ; yes, loop counter is good.
;																											; 		 dec b               ; one less row to write.
;																											; cspr0  ld a,(hl)           ; get attributes.
;																											; cspr3  and SIMASK          ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; 		 inc l               ; next cell.
;																											; 		 ld a,(hl)           ; get attributes.
;																											; cspr4  and SIMASK          ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; 		 inc l               ; next cell.
;																											; 		 ld a,(ix+9)         ; y coordinate.
;																											; 		 and 7               ; straddling cells?
;																											; 		 jr z,cspr1          ; no, only 2 wide.
;																											; 		 ld a,(hl)           ; get attributes.
;																											; cspr5  and SIMASK          ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; cspr1  add hl,de           ; next row.
;																											; 		 djnz cspr0
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Specialist routines																				; Specialist routines.
; Process shrapnel																					; Process shrapnel.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #13 - VSync - DONE
ProShr
	IF PFLAG
			pshs	y								; save sprite pointer
			ldy	#SHRAPN						; point to table beginning						; proshr ld ix,SHRAPN      ; table.
			ldb	#NUMSHR						; number of pieces								; 		 ld b,NUMSHR         ; shrapnel pieces to process.
																											; 		 ld de,SHRSIZ        ; distance to next.
ProSh0	lda	,y								; get on-off/type flag							; prosh0 ld a,(ix+0)       ; on/off marker.
			rola									; is it off?										; 		 rla                 ; check its status.
ProShx	bcs	ProShy						; yes, skip next									; proshx call nc,prosh1    ; on, so process it.
ProShmod	jsr	ProSh1						; process it
ProShy	leay	SHRSIZ,y						; point to next slot								; 		 add ix,de           ; point there.
			decb									; decrement counter
			bne	ProSh0						; not yet done, loop								; 		 djnz prosh0         ; round again.
			puls	y								; restore sprite pointer
	ENDIF
			lda	TIMER							; get timer value
			anda	#1								; is it odd?
	IF SFLAG
			lbne	Scrly							; yes, call Scroller routine					; 		 jp scrly
	ENDIF
			rts									; no, return
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	IF PFLAG
ProSh1	pshs	b								; save counter										; prosh1 push bc           ; store counter.
			jsr	Plot							; delete pixel										; 		 call plot           ; delete the pixel.
			lda	,y								; get type											; 		 ld a,(ix+0)         ; restore shrapnel type.
			ldx	#shrPtr						; point to routines table						; 		 ld hl,shrptr        ; shrapnel routine pointers.
			jsr	ProSh2						; execute the requested one					; 		 call prosh2         ; run the routine.
			jsr	ChkXY							; verify coordinates and display				; 		 call chkxy          ; check x and y are good before we redisplay.
			puls	b								; restore counter									; 		 pop bc              ; restore counter.
																											; 		 ld de,SHRSIZ        ; distance to next.
			rts									; return												; 		 ret
ProSh2	asla									; double to calc offset							; prosh2 rlca              ; 2 bytes per address.
																											; 		 ld e,a              ; copy to de.
																											; 		 add hl,de           ; point to address of routine.
																											; 		 ld a,(hl)           ; get address low.
																											; 		 inc hl              ; point to second byte.
																											; 		 ld h,(hl)           ; fetch high byte from table.
																											; 		 ld l,a              ; put low byte in l.
			jmp	[a,x]							; execute sobroutine								; 		 jp (hl)             ; jump to routine.
; ------------------------------------------------------------------------------------------------------------------------------------------
shrPtr	fdb	Laser							; offset 0 - 0										; shrptr defw laser        ; laser.
			fdb	Trail							; offset 2 - 1										; 		 defw trail          ; vapour trail.
			fdb	Shrap 						; offset 4 - 2										; 		 defw shrap          ; shrapnel from explosion.
			fdb	DotL  						; offset 6 - 3										; 		 defw dotl           ; horizontal starfield left.
			fdb	DotR  						; offset 8 - 4										; 		 defw dotr           ; horizontal starfield right.
			fdb	DotU  						; offset a - 5										; 		 defw dotu           ; vertical starfield up.
			fdb	DotD  						; offset c - 6										; 		 defw dotd           ; vertical starfield down.
			fdb	PtcUsr						; offset e - 7										; 		 defw ptcusr         ; user particle.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Explosion shrapnel																					; Explosion shrapnel.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - T03-4-5-6-7 - DONE
Shrap		ldb	1,y							; angle is steps of 4 (offset)				; shrap  ld e,(ix+1)         ; get the angle.
																											; 		 ld d,0              ; no high byte.
			ldx	#shrSin						; point to table beginning						; 		 ld hl,shrsin        ; shrapnel sine table.
			abx									; now to sine of desired offset				; 		 add hl,de           ; point to sine.
																											; 		 ld e,(hl)           ; fetch value from table.
																											; 		 inc hl              ; next byte of table.
																											; 		 ld d,(hl)           ; fetch value from table.
																											; 		 inc hl              ; next byte of table.
																											; 		 ld c,(hl)           ; fetch value from table.
																											; 		 inc hl              ; next byte of table.
																											; 		 ld b,(hl)           ; fetch value from table.
			ldb	2,y							; get decimals of Y coordinate				; 		 ld l,(ix+2)         ; x coordinate in hl.
			lda	3,y							; get Y coordinate								; 		 ld h,(ix+3)
			addd	,x								; add sine,decimals								; 		 add hl,de           ; add sine.
			stb	2,y							; update decimals of Y cordinate				; 		 ld (ix+2),l         ; store new coordinate.
			sta	3,y							; update Y coordinate							; 		 ld (ix+3),h
			ldb	4,y							; get decimals of X coordinate				; 		 ld l,(ix+4)         ; y coordinate in hl.
			lda	5,y							; get X coordinate								; 		 ld h,(ix+5)
			addd	2,x							; add cosine,decimals							; 		 add hl,bc           ; add cosine.
			stb	4,y							; update decimals of X coordinate			; 		 ld (ix+4),l         ; store new coordinate.
			sta	5,y							; update X coordinate							; 		 ld (ix+5),h
			rts									; return												; 		 ret
DotL		dec	5,y																					; dotl   dec (ix+5)          ; move left.
			rts																							; 		 ret
DotR		inc	5,y																					; dotr   inc (ix+5)          ; move right.
			rts																							; 		 ret
DotU		dec	3,y																					; dotu   dec (ix+3)          ; move up.
			rts																							; 		 ret
DotD		inc	3,y																					; dotd   inc (ix+3)          ; move down.
			rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check coordinates are good before redrawing at new position							; Check coordinates are good before redrawing at new position.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #01C1 - DONE - OK
ChkXY		ldx	#wnTopX																				; chkxy  ld hl,wntopx        ; window top.
			lda	3,y							; get Y coord										; 		 ld a,(ix+3)         ; fetch shrapnel coordinate.
			cmpa	,x																						; 		 cp (hl)             ; compare with top window limit.
			bcs	KilShr						; out of screen, stop it						; 		 jr c,kilshr         ; out of window, kill shrapnel.
			leax	1,x							; point to Left edge								; 		 inc hl              ; left edge.
			lda	5,y							; get X coord										; 		 ld a,(ix+5)         ; fetch shrapnel coordinate.
			cmpa	,x																						; 		 cp (hl)             ; compare with left window limit.
			bcs	KilShr						; out of screen, stop it						; 		 jr c,kilshr         ; out of window, kill shrapnel.
			leax	1,x							; point to bottom edge							; 		 inc hl              ; point to bottom.
			lda	,x								; get it												; 		 ld a,(hl)           ; fetch window limit.
			adda	#15							; add height of sprite							; 		 add a,15            ; add height of sprite.
			cmpa	3,y							; compare to Y coord								; 		 cp (ix+3)           ; compare with shrapnel x coordinate.
			bcs	KilShr						; out of screen, stop it						; 		 jr c,kilshr         ; off screen, kill shrapnel.
			leax	1,x							; point to right edge							; 		 inc hl              ; point to right edge.
			lda	,x								; get it												; 		 ld a,(hl)           ; fetch shrapnel y coordinate.
			adda	#15							; add width of sprite							; 		 add a,15            ; add width of sprite.
			cmpa	5,y							; compare to X coord								; 		 cp (ix+5)           ; compare with window limit.
			bcs	KilShr						; out of screen, stop it						; 		 jr c,kilshr         ; off screen, kill shrapnel.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Drop through																							; Drop through.
; Display shrapnel																					; Display shrapnel.
; ------------------------------------------------------------------------------------------------------------------------------------------
; 						- continues from previous part
; CONVERTED FOR SHRAPNEL - #01C1 - DONE
Plot		lda	3,y							; high byte	(Y coord)							; plot   ld l,(ix+3)         ; x integer.
			ldb	5,y							; low byte (X coord)								; 		 ld h,(ix+5)         ; y integer.
			std	<reg_HL						; Y - X
			exg	a,b							; regD= X - Y (added again)
			std	<dispX						; 3,y -> dispX										; 		 ld (dispx),hl       ; workspace coordinates.
			lda	,y								; get type											; 		 ld a,(ix+0)         ; type.
																											; 		 and a               ; is it a laser?
			beq	Plot1							; if zero, draw laser							; 		 jr z,plot1          ; yes, draw laser instead.
Plot0		lda	<reg_L					   ; 4,y (dispX)	(original)						; plot0  ld a,h              ; which pixel within byte do we
			anda	#7								; low byte of DE									; 		 and 7               ; want to set first?
			clr	<reg_D																				; 		 ld d,0              ; no high byte.
																											; 		 ld e,a              ; copy to de.
			ldx	#dots							; pointer											; 		 ld hl,dots          ; table of small pixel positions.
			leax	a,x							; add 1 byte offset								; 		 add hl,de           ; hl points to values we want to POKE to screen.
			lda	,x								; get byte from table							; 		 ld e,(hl)           ; get value.
			sta	<reg_E						; to pseudoreg
			jsr	ScAdd							; get screen address								; 		 call scadd          ; screen address.
			lda	,x								; get what is there in screen					; 		 ld a,(hl)           ; see what's already there.
			eora	<reg_E						; merge pixels										; 		 xor e               ; merge with pixels.
			sta	,x								; update screen									; 		 ld (hl),a           ; put back on screen.
			rts									; return												; 		 ret
Plot1		jsr	ScAdd							; get screen address								; plot1  call scadd          ; screen address.
																											; 		 ld a,(hl)           ; fetch byte there.
			com	,x								; toggle all bits									; 		 cpl                 ; toggle all bits.
																											; 		 ld (hl),a           ; new byte.
			rts									; return												; 		 ret
KilShr	lda	#128							; set bit7											; kilshr ld (ix+0),128       ; switch off shrapnel.
			sta	,y								; to disable shrapnel piece
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; ;explc  defb 0              ; explosion counter.
shrSin 	fdb	0,1024,391,946,724,724,946,391												; shrsin defw 0,1024,391,946,724,724,946,391
			fdb	1024,0,946,65144,724,64811,391,64589										; 		 defw 1024,0,946,65144,724,64811,391,64589
			fdb	0,64512,65144,64589,64811,64811,64589,65144								; 		 defw 0,64512,65144,64589,64811,64811,64589,65144
			fdb	64512,0,64589,391,64811,724,65144,946										; 		 defw 64512,0,64589,391,64811,724,65144,946
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - T02 - DONE
Trail		dec	1,y							; get time remaining (?)						; trail  dec (ix+1)          ; time remaining.
			beq	TrailK						; if zero, set it out of  screen				; 		 jp z,trailk         ; time to switch it off.
			jsr	QRand							; get a random	number							; 		 call qrand          ; get a random number.
			rora									; see bit0											; 		 rra                 ; x or y axis?
			bcs	TrailV						; if set, move vertically						; 		 jr c,trailv         ; use x.
			rora									; see bit1														; 		 rra                 ; which direction?
			bcs	TrailL						; if set, go left									; 		 jr c,traill         ; go left.
			inc	5,y							; else go right (inc X)							; 		 inc (ix+5)          ; go right.
			rts									; return												; 		 ret
TrailL	dec	5,y							; go left (dec X)									; traill dec (ix+5)          ; go left.
			rts									; return												; 		 ret
TrailV	rora									; see bit1											; trailv rra                 ; which direction?
			bcs	TrailU						; if set, go up									; 		 jr c,trailu         ; go up.
			inc	3,y							; else go down (inc Y)							; 		 inc (ix+3)          ; go down.
			rts									; return												; 		 ret
TrailU	dec	3,y							; go up (dec Y)									; trailu dec (ix+3)          ; go up.
			rts									; return												; 		 ret
TrailK	lda	#200 							; set it												; trailk ld (ix+3),200       ; set off-screen to kill vapour trail.
			sta	3,y							; out of screen
TrailEx	rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - T01 - DONE
Laser		lda	1,y							; get direction									; laser  ld a,(ix+1)         ; direction.
			rora									; see bit0											; 		 rra                 ; left or right?
			bcc	LaserL						; if not set, move left							; 		 jr nc,laserl        ; move left.
			ldb	#8								; distance to travel								; 		 ld b,8              ; distance to travel.
			bra	LaserM						; move laser (right)								; 		 jr laserm           ; move laser.
LaserL	ldb	#248							; get value -8										; laserl ld b,248            ; distance to travel.
LaserM	lda	5,y							; get actual position							; laserm ld a,(ix+5)         ; y position.
			stb	<reg_B						; save displacement								; 		 add a,b             ; add distance.
			adda	<reg_B						; add to position
			sta	5,y							; update X coord									; 		 ld (ix+5),a         ; set new y coordinate.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Test new block																						; Test new block.
; ------------------------------------------------------------------------------------------------------------------------------------------
			sta	<dispY						; set new X coordinate							; 		 ld (dispy),a        ; set y for block collision detection purposes.
			lda	3,y							; get Y coordinate								; 		 ld a,(ix+3)         ; get x.
			sta	<dispX						; put into disp variable						; 		 ld (dispx),a        ; set coordinate for collision test.
			jsr	TstBl							; get block at this coords						; 		 call tstbl          ; get block type there.
			cmpa	#WALL							; is a wall?										; 		 cp WALL             ; is it solid?
			beq	TrailK						; yes, put laser out of screen				; 		 jr z,trailk         ; yes, it cannot pass.
	IF PFLAG+DFLAG
			cmpa	#FODDER						; is it fodder?									; 		 cp FODDER           ; is it fodder?
			bne	TrailEx						; no, set it out of screen						; 		 ret nz              ; no, ignore it.
			jsr	FdChk							; remove fodder block							; 		 call fdchk          ; remove fodder block.
			bra	TrailK						; destroy laser									; 		 jr trailk           ; destroy laser.
	ELSE
			rts
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
dots		fcb	128,64,32,16,8,4,2,1																; dots   defb 128,64,32,16,8,4,2,1
; ------------------------------------------------------------------------------------------------------------------------------------------
; Plot, preserving reg_DE																			; Plot, preserving de.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #121 - DONE
PlotDE	ldd	<reg_DE						; get reg_DE										; plotde push de             ; put de on stack.
			pshs	d								; save into stack
			jsr	Plot							; plot pixel										; 		 call plot           ; plot pixel.
			puls	d								; restore											; 		 pop de              ; restore de from stack.
			std	<reg_DE						; reg_DE
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Shoot a laser																						; Shoot a laser.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #01 - DONE
													; receives regA=01 to fire a Laser to the right
Shoot		sta	<reg_C						; save direction									; shoot  ld c,a              ; store direction in c register.
			ldb	8,y							; low byte (Y coord)								; 		 ld a,(ix+8)         ; x coordinate.
Shoot1	addb	#(SPR_HGT/2-1)								; move it down 7 pixels							; shoot1 add a,7             ; down 7 pixels.
			lda	9,y							; high byte (X coord)							; 		 ld l,a              ; puty x coordinate in l.
			std	<reg_HL						; HL=XY coords										; 		 ld h,(ix+9)         ; y coordinate in h.
			pshs	y								; save pointer										; 		 push ix             ; store pointer to sprite.
			jsr	FPSlot						; find particle slot								; 		 call fpslot         ; find particle slot.
			bcc	Vapou2						; not found, restore ix							; 		 jr nc,vapou2        ; failed, restore ix.
			clr	,y								; set up a laser									; 		 ld (ix+0),0         ; set up a laser.
			lda	<reg_C						; get requested direction
			sta	1,y							; set direction									; 		 ld (ix+1),c         ; set the direction.
			lda	<reg_L						; get Y coordinate
			sta	3,y							; set it												; 		 ld (ix+3),l         ; set x coordinate.
			ror	<reg_C						; check direction									; 		 rr c                ; check direction we want.
			bcs	Shootr						; if set, shoot right							; 		 jr c,shootr         ; shoot right.
			lda	<reg_H						; get X coord										; 		 ld a,h              ; y position.
																											; ;       dec a               ; left a pixel.
Shoot0	anda	#248							; #%11111000 align to char						; shoot0 and 248             ; align on character boundary.
			sta	5,y							; set X coordinate								; 		 ld (ix+5),a         ; set y coordinate.
			bra	Vapou0						; go plot it										; 		 jr vapou0           ; draw first image.
Shootr	lda	<reg_H						; get X coord										; shootr ld a,h              ; y position.
			adda	#15							; point to the right								; 		 add a,15            ; look right.
			bra	Shoot0						; go back to plot it								; 		 jr shoot0           ; align and continue.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Create a bit of vapour trail																	; Create a bit of vapour trail.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #10 - Script - DONE
Vapour	pshs	y								; save pointer										; vapour push ix             ; store pointer to sprite.
			ldd	8,y							; Y-X													; 		 ld l,(ix+8)         ; x coordinate.
			exg	a,b							; X-Y
			tfr	d,x							; send to HL (X-Y)								; 		 ld h,(ix+9)         ; y coordinate.
Vapou3	leax	(SPR_HGT/2-1)*256+(SPR_HGT/2-1),x						
													; mid-point of sprite							; vapou3 ld de,7*256+7       ; mid-point of sprite.
			stx	<reg_HL						; update pseudo-register						; 		 add hl,de           ; point to centre of sprite.
			jsr	FPSlot						; find a free slot								; 		 call fpslot         ; find particle slot.
			bcs	Vapou1						; found one, use it								; 		 jr c,vapou1         ; no, we can use it.
; CONVERTED FOR SHRAPNEL - #01B - DONE
Vapou2	puls	y								; restore pointer									; vapou2 pop ix              ; restore sprite pointer.
			rts									; and exit											; 		 ret                 ; out of slots, can't generate anything.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - Script01 - DONE
Vapou1	ldd	<reg_HL						; get coordinates	(X-Y)							; vapou1 ld (ix+3),l         ; set up x.
			stb	3,y							; set Y coord
			sta	5,y							; and  X coord										; 		 ld (ix+5),h         ; set up y coordinate.
			jsr	QRand							; get a random number							; 		 call qrand          ; get quick random number.
			anda	#15							; limit to 4 bits									; 		 and 15              ; random time.
			adda	#15							; minimum value (time)							; 		 add a,15            ; minimum time on screen.
			sta	1,y							; set time on screen								; 		 ld (ix+1),a         ; set time on screen.
			lda	#1								; value to
			sta	,y								; set it as particle trail						; 		 ld (ix+0),1         ; define particle as vapour trail.
; CONVERTED FOR SHRAPNEL - #01C - DONE
Vapou0	jsr	ChkXY							; plot first position							; vapou0 call chkxy          ; plot first position.
			bra	Vapou2						; exit												; 		 jr vapou2
; ------------------------------------------------------------------------------------------------------------------------------------------
; Create a user particle																			; Create a user particle.
; parameter in register A is the timer for the particle
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR USER PARTICLE
PtUsr		sta	<reg_A						; save timer parameter							; ptusr  ex af,af'           ; store timer.
			ldx	8,y							; get Y,X coordinates from current sprite ; 		 ld l,(ix+8)         ; x coordinate.
																											; 		 ld h,(ix+9)         ; y coordinate.
																											; 		 ld de,7*256+7       ; mid-point of sprite.
			leax	$0707,x						; point to sprite center						; 		 add hl,de           ; point to centre of sprite.
			jsr	FPSlot						; find a free slot for particle (regY)		; 		 call fpslot         ; find particle slot.
			bcs	PtUsr1						; found one, use it								; 		 jr c,ptusr1         ; no, we can use it.
			rts									; no free slots, exit							; 		 ret                 ; out of slots, can't generate anything.
PtUsr1	tfr	x,d							; pass coordinates to regD						; ptusr1 ld (ix+3),l         ; set up x.
			sta	3,y							; fill particle Y coordinate
			stb	5,y							; and particle X									; 		 ld (ix+5),h         ; set up y coordinate.
			lda	<reg_A						; restore timer									; 		 ex af,af'           ; restore timer.
			sta	1,y							; put in direction								; 		 ld (ix+1),a         ; set time on screen.
			lda	#7								; define particle
			sta	,y								; as user type										; 		 ld (ix+0),7         ; define particle as user particle.
			lbra	ChkXY							; plot first position							; 		 jp chkxy            ; plot first position.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Create a vertical or horizontal star															; Create a vertical or horizontal star.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #02 - DONE
Star		pshs	y								; save pointer										; star   push ix             ; store pointer to sprite.
			bsr	FPSlot						; find a slot										; 		 call fpslot         ; find particle slot.
			bcs	Star7							; if found, use it								; 		 jp c,star7          ; found one we can use.
Star0		puls	y								; else restore pointer							; star0  pop ix              ; restore sprite pointer.
			rts									; return												; 		 ret                 ; out of slots, can't generate anything.
Star7		lda	<reg_C						; get direction									; star7  ld a,c              ; direction.
			anda	#3								; is if left (0)?									; 		 and 3               ; is it left?
			beq	Star1							; yes, go there									; 		 jr z,star1          ; yes, it's horizontal.
			deca									; is it right (1)?								; 		 dec a               ; is it right?
			beq	Star2							; yes, go there									; 		 jr z,star2          ; yes, it's horizontal.
			deca									; is it up (2)?									; 		 dec a               ; is it up?
			beq	Star3							; yes, go there									; 		 jr z,star3          ; yes, it's vertical.
			lda	<wnTopX						; get top edge of screen						; 		 ld a,(wntopx)       ; get edge of screen.
			inca									; down one pixel									; 		 inc a               ; down one pixel.
Star8		sta	3,y							; set Y coord										; star8  ld (ix+3),a         ; set x coord.
			jsr	QRand							; get radom number								; 		 call qrand          ; get quick random number.
Star9		sta	5,y							; set as X coord									; star9  ld (ix+5),a         ; set y position.
			lda	<reg_C						; get direction									; 		 ld a,c              ; direction.
			anda	#3								; use 2 lower bits								; 		 and 3               ; zero to three.
			adda	#3								; values 3-4-5-6 to starfield					; 		 add a,3             ; 3 to 6 for starfield.
			sta	,y								; define particle as star						; 		 ld (ix+0),a         ; define particle as star.
			jsr	ChkXY							; plot 1st position								; 		 call chkxy          ; plot first position.
			bra	Star0							; exit												; 		 jp star0
Star1		jsr	QRand							; Left. get a random number					; star1  call qrand          ; get quick random number.
			sta	3,y							; set Y coord										; 		 ld (ix+3),a         ; set x coord.
			lda	<wnRgtX						; get right edge of screen						; 		 ld a,(wnrgtx)       ; get edge of screen.
			adda	#15							; add sprite width minus one					; 		 add a,15            ; add width of sprite minus 1.
			bra	Star9							; set X coord										; 		 jp star9
Star2		jsr	QRand							; Right. get a random number					; star2  call qrand          ; get quick random number.
			sta	3,y							; set Y coord										; 		 ld (ix+3),a         ; set x coord.
			lda	<wnLftX						; get left edge of screen						; 		 ld a,(wnlftx)       ; get edge of screen.
			bra	Star9							; set X coord										; 		 jp star9
Star3		lda	<wnBotX						; Up. get bottom edge of screen				; star3  ld a,(wnbotx)       ; get edge of screen.
			adda	#15							; add height of sprite minus one				; 		 add a,15            ; height of sprite minus one pixel.
			bra	Star8							; set Y coord										; 		 jp star8
; ------------------------------------------------------------------------------------------------------------------------------------------
; Find particle slot for lasers or vapour trail												; Find particle slot for lasers or vapour trail.
; Can't use alternate accumulator																; Can't use alternate accumulator.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #01A - DONE
FPSlot	ldy	#SHRAPN						; point to table beginning						; fpslot ld ix,SHRAPN        ; shrapnel table.
																											; 		 ld de,SHRSIZ        ; size of each particle.
			ldb	#NUMSHR						; number of pieces								; 		 ld b,NUMSHR         ; number of pieces in table.
FPSlt0	lda	,y								; get type											; fpslt0 ld a,(ix+0)         ; get type.
			rola									; is slot free ($ff)?							; 		 rla                 ; is this slot in use?
			bcs	FPSltEx						; yes, use it										; 		 ret c               ; no, we can use it.
			leay	SHRSIZ,y						; point to next slot								; 		 add ix,de           ; point to more shrapnel.
			decb									; decrement counter
			bne	FPSlt0						; not the end? loopback							; 		 djnz fpslt0         ; repeat for all shrapnel.
FPSltEx	rts									; return												; 		 ret                 ; out of slots, can't generate anything.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Create an explosion at sprite position														; Create an explosion at sprite position.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #04 - DONE
Explod	sta	<reg_C						; save number of particles to be created	; explod ld c,a              ; particles to create.
			pshs	y								; save sprite pointer							; 		 push ix             ; store pointer to sprite.
			ldd	8,y							; get Y - X coords								; 		 ld l,(ix+8)         ; x coordinate.
			std	<reg_HL						; Y - X												; 		 ld h,(ix+9)         ; y coordinate.
			ldy	#SHRAPN						; point to shrapnel data table				; 		 ld ix,SHRAPN        ; shrapnel table.
																											; 		 ld de,SHRSIZ        ; size of each particle.
			ldb	#NUMSHR						; get number of pieces							; 		 ld b,NUMSHR         ; number of pieces in table.
			stb	<reg_B						; into counter
Expld0	lda	,y								; get type											; expld0 ld a,(ix+0)         ; get type.
			rola									; see bit7, is it used?							; 		 rla                 ; is this slot in use?
			bcs	Expld1						; no, we can use it								; 		 jr c,expld1         ; no, we can use it.
Expld2	leay	SHRSIZ,y						; point to next table entry					; expld2 add ix,de           ; point to more shrapnel.
			dec	<reg_B						; decrement counter
			bne	Expld0						; not done? loopback								; 		 djnz expld0         ; repeat for all shrapnel.
Expld3	puls	y								; restore pointer									; expld3 pop ix              ; restore sprite pointer.
			rts									; return												; 		 ret                 ; out of slots, can't generate any more.
Expld1	lda	<reg_C						; get number of particles						; expld1 ld a,c              ; shrapnel counter.
			anda	#15							; limit to 15										; 		 and 15              ; 0 to 15.
			adda	<reg_H						; add Y coord										; 		 add a,l             ; add to x.
			sta	3,y							; set Y coord										; 		 ld (ix+3),a         ; x coord.
			lda	<seed3						; read last random number						; 		 ld a,(seed3)        ; crap random number.
			anda	#15							; limit to 0-15									; 		 and 15              ; 0 to 15.
			adda	<reg_L						; add X coord										; 		 add a,h             ; add to y.
			sta	5,y							; set X coord										; 		 ld (ix+5),a         ; y coord.
			lda	#2								; switch
			sta	,y								; shrapnel on										; 		 ld (ix+0),2         ; switch it on.
			jsr	do_exx						; store BC, DE, HL								; 		 exx                 ; store coordinates.
			jsr	ChkXY							; plot 1st position								; 		 call chkxy          ; plot first position.
			jsr	QRand							; get a random number							; 		 call qrand          ; quick random angle.
			anda	#60							; keep into angle range (0-60)				; 		 and 60              ; keep within range.
			sta	1,y							; put at offset 1									; 		 ld (ix+1),a         ; angle.
			jsr	do_exx						; restore old values								; 		 exx                 ; restore coordinates.
			dec	<reg_C						; decrement counter								; 		 dec c               ; one less piece of shrapnel to generate.
			bne	Expld2						; not done? loopback								; 		 jr nz,expld2        ; back to main explosion loop.
			bra	Expld3						; exit restoring pointer						; 		 jr expld3           ; restore sprite pointer and exit.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #02A - DONE
QRand		
																											; qrand  ld a,(seed3)        ; random seed.
																											; 		 ld l,a              ; low byte.

																											; 		 ld h,0              ; no high byte.

																											; 		 ld a,r              ; r register.
																											; 		 xor (hl)            ; combine with seed.
			jsr	Random						; get a Random number
			eora	<seed3						; merge with old seed
			sta	<seed3						; update seed										; 		 ld (seed3),a        ; new seed.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display all shrapnel																				; Display all shrapnel.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #12 - ReDraw - DONE
DShrp		ldx	#PlotDE						; get routine address							; dshrp  ld hl,plotde        ; display routine.
			stx	ProShmod+1					; change called one								; 		 ld (proshx+1),hl    ; modify routine.
			jsr	ProShr						; call 'caller'									; 		 call proshr         ; process shrapnel.
			ldx	#ProSh1						; get default routine address					; 		 ld hl,prosh1        ; processing routine.
			stx	ProShmod+1					; restore it										; 		 ld (proshx+1),hl    ; modify the call.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Particle engine																						; Particle engine
; ------------------------------------------------------------------------------------------------------------------------------------------
IniShr	ldx	#SHRAPN						; point to shrapnel table						; inishr ld hl,SHRAPN        ; table.
			ldb	#NUMSHR						; get number of pieces							; 		 ld b,NUMSHR         ; shrapnel pieces to process.
			lda	#$ff							; value to be set									; 		 ld de,SHRSIZ        ; distance to next.
IniSh0	sta	,x								; set one element									; inish0 ld (hl),255         ; kill the shrapnel.
			leax	SHRSIZ,x						; point to next element							; 		 add hl,de           ; point there.
			decb									; decrement counter	
			bne	IniSh0						; not yet done, loop								; 		 djnz inish0         ; round again.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check for collision between laser and sprite												; Check for collision between laser and sprite.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #05 - DONE
LCol		ldx	#SHRAPN						; point to table beginning						; lcol   ld hl,SHRAPN        ; shrapnel table.
																											; 		 ld de,SHRSIZ        ; size of each particle.
			ldb	#NUMSHR						; number of pieces								; 		 ld b,NUMSHR         ; number of pieces in table.
LCol0		lda	,x								; get type											; lcol0  ld a,(hl)           ; get type.
																											; 		 and a               ; is this slot a laser?
			beq	LCol1							; if zero is a laser, check collision		; 		 jr z,lcol1          ; yes, check collision.
LCol3		leax	SHRSIZ,x						; point to next table entry					; lcol3  add hl,de           ; point to more shrapnel.
			decb									; decrement counter
			bne	LCol0							; not done? loopback								; 		 djnz lcol0          ; repeat for all shrapnel.
			andcc	#%11111110					; clear carry
			rts									; return NO collision							; 		 ret                 ; no collision, carry not set.
LCol1		
 			pshs	x								; (added again)														; lcol1  push hl             ; store pointer to laser.
																											; 		 inc hl              ; direction.
																											; 		 inc hl              ; not used.
																											; 		 inc hl              ; x position.
			lda	3,x							; get shrapnel Y coord							; 		 ld a,(hl)           ; get x.
			suba	Xval,y						; subtract sprite Y coord						; 		 sub (ix+X)          ; subtract sprite x.
LColh		cmpa	#SPR_HGT							; within range?									; lcolh  cp 16               ; within range?
			bcc	LCol2							; no, missed										; 		 jr nc,lcol2         ; no, missed.
																											; 		 inc hl              ; not used.
																											; 		 inc hl              ; y position.
			lda	5,x							; get shrapnel X coord							; 		 ld a,(hl)           ; get y.
			suba	Yval,y						; subtract sprite X coord						; 		 sub (ix+Y)          ; subtract sprite y.
			cmpa	#16							; within range?									; 		 cp 16               ; within range?
			bcs	LCol4							; yes, collision detected						; 		 jr c,lcol4          ; yes, collision occurred.
LCol2		
			puls	x								; (added again)														; lcol2  pop hl              ; restore laser pointer from stack.
			bra	LCol3							; look for next piece							; 		 jr lcol3
LCol4		
 		   puls	x								; (added again)									; lcol4  pop hl              ; restore laser pointer.
			rts									; return												; 		 ret                 ; return with carry set for collision.
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Main game engine code starts here																; Main game engine code starts here
; ------------------------------------------------------------------------------------------------------------------------------------------
Game																										; game   equ $
																											; Set up screen address table.
Setsat	ldd	#SCRBEG						; get screen beginning							; setsat ld hl,16384       ; start of screen.
			ldu	#SCADTB						; point to table									; 		 ld de,SCADTB        ; screen address table.
			clr	,-s							; number of entries (256)						; 		 ld b,0              ; vertical lines on screen.
																											; setsa0 ex de,hl          ; flip table and screen address.
																											; 		 ld (hl),d           ; write high byte.
Setsa0	std	,u++							; write word entry, inc pointer				; 		 ld (hl),d           ; write high byte.
																											; 		 inc h               ; second table.
																											; 		 ld (hl),e           ; write low byte.
																											; 		 dec h               ; back to first table.
																											; 		 inc l               ; next position in table.
																											; 		 ex de,hl            ; flip table and screen address back again.
																											; 		 call nline          ; next line down.
			addd	#32							; add 32 to go byte below
			cmpa	#$fe							; end of screen?
			bcs	Setsa1						; no, skip next
			lda	#$80							; point to ROM (now in RAM)
Setsa1	dec	,s								; decrement counter
			bne	Setsa0						; not yet done? loopback						; 		 djnz setsa0         ; repeat for all lines.
			leas	1,s							; clean stack
			jsr	SetPMode						; set desired PMode								; Init graphics mode
													; not needed for 6847							; 		 call setpal         ; set up ULAplus palette.
			jsr	CfgHdw						; config Sound and Interrupts
	IF PFLAG
			jsr	IniShr						; initialise particle engine					; rpblc2 call inishr       ; initialise particle engine.
	ENDIF
			jsr	Evnt12						; call intro/menu event							; evintr call evnt12       ; call intro/menu event.
			ldx	#MAP							; point to MAP										; 		 ld hl,MAP           ; block properties.
			lda	#WALL							; get value for WALL								; 		 ld de,MAP+1         ; next byte.
FillMap1	sta	,x+							; put into MAP										; 		 ld bc,767           ; size of property map.
			cmpx	#ENDMAP						; filled all MAP?									; 		 ld (hl),WALL        ; write default property.
			blo	FillMap1						; no, loopback										; 		 ldir
	IF OFLAG
			jsr	IniOb							; initialize objects								; 		 call iniob          ; initialise objects.
	ENDIF
																											; 		 xor a               ; put zero in accumulator.
			clr	<gamWon						; reset game won flag							; 		 ld (gamwon),a       ; reset game won flag.
			ldx	#score						; point to score									; 		 ld hl,score         ; score.
			jsr	IniSc							; init the score									; 		 call inisc          ; init the score.
MapSt		lda	stMap							; get position on map							; mapst  ld a,(stmap)      ; start position on map.
			sta	roomTb						; put into table									; 		 ld (roomtb),a       ; set up position in table, if there is one.
IniPbl	
	IF AFLAG																								; .if aflag
			ldd	#eop            			; reset blockpointer								; lda #<eop        
			std	<pbPtr   					; put at write pointer							; sta pbptr
						    																				; lda #>eop
							  																				; sta pbptr+1
	ENDIF																									; .endif
			jsr	InitSc						; setup 1st screen number						; inipbl call initsc       ; set up first screen.
			ldx	#sSprit						; point to spare sprite							; 		 ld ix,ssprit        ; default to spare sprite in table.
EvIni		jsr	Evnt13						; Initialisation									; evini  call evnt13       ; initialisation.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Two restarts																							; Two restarts.
; First restart - clear all sprites and initialise everything							; First restart - clear all sprites and initialise everything.
; ------------------------------------------------------------------------------------------------------------------------------------------
RstRt		jsr	RsEvt							; restart events									; rstrt  call rsevt        ; restart events.
			jsr	XSpr							; clear sprite table								; 		 call xspr           ; clear sprite table.
			jsr	SprLst						; fetch pointer to screen sprites			; 		 call sprlst         ; fetch pointer to screen sprites.
			jsr	ISpr							; initialise sprite table						; 		 call ispr           ; initialise sprite table.
			bra	RstRt0						; setup player and sprites						; 		 jr rstrt0
; ------------------------------------------------------------------------------------------------------------------------------------------
; Second restart - clear all but player, and don't initialise him						; Second restart - clear all but player, and don't initialise him.
; ------------------------------------------------------------------------------------------------------------------------------------------
RstRtn	jsr	RsEvt							; restart events									; rstrtn call rsevt        ; restart events.
			jsr	NSpr							; clear all non-player sprites				; 		 call nspr           ; clear all non-player sprites.
			jsr	SprLst						; fetch pointer to screen sprites			; 		 call sprlst         ; fetch pointer to screen sprites.
			jsr	KSpr							; initialise sprite table, no more players; 		 call kspr           ; initialise sprite table, no more players.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Set up the player and/or enemy sprites														; Set up the player and/or enemy sprites.
; ------------------------------------------------------------------------------------------------------------------------------------------
RstRt0	clra									; value zero										; rstrt0 xor a             ; zero in accumulator.
			sta	<nexLev						; reset next level flag							; 		 ld (nexlev),a       ; reset next level flag.
			sta	<restFl						; reset restart flag								; 		 ld (restfl),a       ; reset restart flag.
			sta	<deadF						; reset dead flag									; 		 ld (deadf),a        ; reset dead flag.
			jsr	DRoom							; show screen layout								; 		 call droom          ; show screen layout.
RpBlc0	
	IF PFLAG																								; .if pflag
			jsr	IniShr						; initialise particle engine					; rpblc0 call inishr       ; initialise particle engine.
	ENDIF																									; .endif
	IF AFLAG																								; .if aflag
			jsr	RBloc         				; draw blocks for this screen					; jsr rbloc        
	ENDIF																									; .endif
	IF OFLAG
			jsr	ShwOb							; show Objects										; 		 call shwob          ; draw objects.
	ENDIF
																											; 		 ld ix,sprtab        ; address of sprite table, even sprites.
																											; 		 call dspr           ; display sprites.
																											; 		 ld ix,sprtab+TABSIZ ; address of first odd sprite.
																											; 		 call dspr           ; display sprites.
; ------------------------------------------------------------------------------------------------------------------------------------------
MLoop		jsr	VSync							; synchronize with display						; mloop  call vsync        ; synchronise with display.
			ldx	#sprTab						; point to sprites Table						; 		 ld ix,sprtab        ; address of sprite table, even sprites.
			jsr	DSpr							; show sprites (even ones)						; 		 call dspr           ; display even sprites.
																											; ;       call plsnd       ; play sounds.
			jsr	VSync							; synchronize with display						; 		 call vsync          ; synchronise with display.
			ldx	#sprTab+TABSIZ				; point to first odd sprite					; 		 ld ix,sprtab+TABSIZ ; address of first odd sprite.
			jsr	DSpr							; show sprites (odd ones)						; 		 call dspr           ; display odd sprites.
			ldx	#sSprit																				; 		 ld ix,ssprit        ; point to spare sprite for spawning purposes.
			stx	<reg_IX
EvLp1		jsr	Evnt10						; call event10										; evlp1  call evnt10       ; called once per main loop.
			jsr	PSpr							; process sprites									; 		 call pspr           ; process sprites.

; ------------------------------------------------------------------------------------------------------------------------------------------
; Main loop events																					; Main loop events.
; ------------------------------------------------------------------------------------------------------------------------------------------
			ldy	#sSprit						; point to spare sprite data					; 		 ld ix,ssprit        ; point to spare sprite for spawning purposes.
EvLp2		jsr	Evnt11						; process event 11								; evlp2  call evnt11       ; called once per main loop.
			lda	<nexLev						; next level flag?								; 		 ld a,(nexlev)       ; finished level flag.
																											; 		 and a               ; has it been set?
			bne	NewLev						; yes, go to next	one							; 		 jr nz,newlev        ; yes, go to next level.
			lda	<gamWon						; game finished?									; 		 ld a,(gamwon)       ; finished game flag.
																											; 		 and a               ; has it been set?
			bne	EvWon							; yes, end game									; 		 jr nz,evwon         ; yes, finish the game.
			lda	<restFl						; restart flag?									; 		 ld a,(restfl)       ; finished level flag.
			deca									; was it set (=1)?								; 		 dec a               ; has it been set?
			beq	RstRt							; yes, restart										; 		 jr z,rstrt          ; yes, go to next level.
			deca									; was restart =2?									; 		 dec a               ; has it been set?
			beq	RstRtn						; yes, do this restart							; 		 jr z,rstrtn         ; yes, go to next level.
			lda	<deadF						; dead flag?										; 		 ld a,(deadf)        ; dead flag.
																											; 		 and a               ; is it non-zero?
			bne	PDead							; yes, go player dead							; 		 jr nz,pdead         ; yes, player dead.
																											; 		 ld hl,frmno         ; game frame.
			inc	<frmNo						; increment frame number						; 		 inc (hl)            ; advance the frame.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; inc clock (ONLY for THE ATOM, not Z80)
			bra	MLoop							; loopback											; qoff   jp mloop          ; switched to a jp nz,mloop during test mode.
																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF AFLAG																								; .if aflag
RBloc																										; rbloc:
			ldd	#eop							; reset temp blockpointer    					; lda #<eop        ; reset temp blockpointer
			std	<tmp    						; store in tmp pointer (reset it)			; sta tmp
																											; lda #>eop
																											; sta tmp+1
RBloc2																									; rbloc2:
			ldd	<tmp							; get last block 									; lda tmp            ; check for last block
			cmpd 	<pbPtr						; compare to write pointer						; cmp pbptr
			bne	RBloc1						; not equal? process it							; bne rbloc1
																											; lda tmp+1
																											; cmp pbptr+1
																											; bne rbloc1
			rts									; return												; rts
RBloc1											; READ BLOCK										; rbloc1:
			ldx	<tmp							; get pointer										; ldy #0
			lda	,x								; get block room number			    			; lda (tmp),y        ; check if block for this scno
			cmpa	<scNo							; matches current room?							; cmp scno
			bne	RBloc0						; not, skip											; bne rbloc0        ; if not, skip
																											; iny
			lda	1,x							; get y												; lda (tmp),y        ; get y
			sta	<dispY						; put into variable								; sta dispy
				    																						; iny
			lda	2,x							; get x												; lda (tmp),y        ; get x
			sta	<dispX						; put into variable								; sta dispx
																											; iny
			lda	3,x							; get blocknr										; lda (tmp),y        ; get blocknr
			jsr	PAttr2						; draw block (uses regX)						; jsr pattr2        ; draw block
RBloc0																									; rbloc0:
																				    						; clc            ; point to next block
			ldd	<tmp							; get pointer										; lda tmp
			addd	#4								; point to next block entry					; adc #4
																											; sta tmp
																											; bcc rbloc2zzz
			std	<tmp							; update pointer									; inc tmp+1
			bra	RBloc2						; loopback											; jmp rbloc2
	ENDIF																									; .endif
; ------------------------------------------------------------------------------------------------------------------------------------------
NewLev	lda	<scNo																					; newlev ld a,(scno)       ; current screen.
																											; 		 ld hl,numsc         ; total number of screens.
			inca																							; 		 inc a               ; next screen.
			cmpa	numSc																					; 		 cp (hl)             ; reached the limit?
			bcc	EvWon																					; 		 jr nc,evwon         ; yes, game finished.
			sta	<scNo																					; 		 ld (scno),a         ; set new level number.
;;O			lbra	RstRt																					; 		 jp rstrt            ; restart, clearing all aliens.
			CONDJMP "bra", RstRt																		; 		 jp rstrt            ; restart, clearing all aliens.
EvWon		jsr	Evnt18																				; evwon  call evnt18       ; game completed.
			bra	TidyUp																				; 		 jp tidyup           ; tidy up and return to BASIC/calling routine.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Player dead																							; Player dead.
; ------------------------------------------------------------------------------------------------------------------------------------------
PDead		ldy	<reg_IX																				; pdead  xor a             ; zeroise accumulator.
			clr	<deadF																					; 		 ld (deadf),a        ; reset dead flag.
EvDie		jsr	Evnt16																				; evdie  call evnt16       ; death subroutine.
			lda	<numLif																				; 		 ld a,(numlif)       ; number of lives.
																											; 		 and a               ; reached zero yet?
			lbne	RstRt																					; 		 jp nz,rstrt         ; restart game.
EvFail	jsr	Evnt17																				; evfail call evnt17         ; failure event.
TidyUp	ldx	#hiScor																				; tidyup ld hl,hiscor        ; high score.
			ldu	#score																				; 		 ld de,score         ; player's score.
			ldb	#6																						; 		 ld b,6              ; digits to check.
TidyU2	lda	,u+																					; tidyu2 ld a,(de)           ; get score digit.
			cmpa	,x+																					; 		 cp (hl)             ; are we larger than high score digit?
			bcs	TidyU0																				; 		 jr c,tidyu0         ; high score is bigger.
			bne	TidyU1																				; 		 jr nz,tidyu1        ; score is greater, record new high score.
																											; 		 inc hl              ; next digit of high score.
			decb																							; 		 inc de              ; next digit of score.
			bne	TidyU2						; restart Game										; 		 djnz tidyu2         ; repeat for all digits.
TidyU0																									; tidyu0 ld hl,10072         ; BASIC likes this in alternate hl.
																											; 		 exx                 ; flip hl into alternate registers.
																											; 		 ld bc,score         ; return pointing to score.
			jsr	PrsKey						; wait for a keypress
			cmpa	#3								; was it Break?
			lbeq	ExitGame						; yes, end game and reset machine
			jmp	NewGame						; start new game									; 		 ret
TidyU1	ldx	#score																				; tidyu1 ld hl,score         ; score.
			ldu	#hiScor																				; 		 ld de,hiscor        ; high score.
			ldb	#6																						; 		 ld bc,6             ; digits to copy.
1			lda	,x+
			sta	,u+
			decb
			bne	1b																						; 		 ldir                ; copy score to high score.
EvNewH	jsr	Evnt19																				; evnewh call evnt19         ; new high score event.
			bra	TidyU0																				; 		 jr tidyu0           ; tidy up.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Restart event																						; Restart event.
; ------------------------------------------------------------------------------------------------------------------------------------------
RsEvt		ldx	#sSprit						; point to spare sprite							; rsevt  ld ix,ssprit        ; default to spare element in table.
Evrs		jmp	Evnt14						; there is an RTS all alone					; evrs   jp evnt14           ; call restart event.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Copy number passed in A to string position bc, right-justified.						; Copy number passed in a to string position bc, right-justified.
; regU contains the pointer to the destination string
; regA contains the number to convert
; ------------------------------------------------------------------------------------------------------------------------------------------
Num2Ch	ldb	#100							; do hundreds										; num2ch ld l,a              ; put accumulator in l.
			stb	<subUnit						; save into variable								; 		 ld h,0              ; blank high byte of hl.
			ldb	#32							; for leading spaces								; 		 ld a,32             ; leading spaces.
																											; numdg3 ld de,100           ; hundreds column.
NumDg3	bsr	NumDg							; calculate digit for hundreds				; 		 call numdg          ; show digit.
			stb	<reg_B						; save regB
NumDg2	ldb	#10							; do tens											; numdg2 ld de,10            ; tens column.
			stb	<subUnit						; save into variable
			ldb	<reg_B						; restore regB
			bsr	NumDg							; calculate digit for tens						; 		 call numdg          ; show digit.
			orb	#16							; to force last digit to be shown			; 		 or 16               ; last digit is always shown.
			stb	<reg_B						; save regB
			ldb	#1								; do units											; 		 ld de,1             ; units column.
			stb	<subUnit						; save into variable
			ldb	<reg_B						; restore regB
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
NumDg		andb	#48							; clear carry and previous digit				; numdg  and 48              ; clear carry, clear digit.
NumDg1	suba	<subUnit						; subtract unit (100,10,1)						; numdg1 sbc hl,de           ; subtract from column.
			bcs	NumDg0						; if negative, exit loop						; 		 jr c,numdg0         ; nothing to show.
			orb	#16							; convert to ASCII digit						; 		 or 16               ; something to show, make it a digit.
			incb									; increment digit									; 		 inc a               ; increment digit.
			bra	NumDg1						; loopback											; 		 jr numdg1           ; repeat until column is zero.
NumDg0	adda	<subUnit						; covert to positive again						; numdg0 add hl,de           ; restore total.
			cmpb	#32							; was char equal to space?						; 		 cp 32               ; leading space?
			beq	NumDEx						; yes, exit											; 		 ret z               ; yes, don't write that.
			stb	,u+							; no, save digit, advance pointer			; 		 ld (bc),a           ; write digit to buffer.
																											; 		 inc bc              ; next buffer position.
NumDEx	rts									; return												; 		 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; CONVERTED FOR TESTDISPLAY
Num2dd	ldu	#dispL0						; keep number in register A					; num2dd ld l,a              ; put accumulator in l.
																											; 		 ld h,0              ; blank high byte of hl.
																											; 		 ld a,32             ; leading spaces.
			ldb	#100							; for hundreds										; 		 ld de,100           ; hundreds column.
			stb	<subUnit						; save into variable
			ldb	#32							; for leading spaces
			bsr	NumDg							; show digit										; 		 call numdg          ; show digit.
			orb	#16							; force digit to be shown						; 		 or 16               ; second digit is always shown.
			stb	<reg_B						; save regB
			bra	NumDg2						; show number										; 		 jr numdg2
Num2td	ldu	#dispL0						; keep number in register A					; num2td ld l,a              ; put accumulator in l.
			ldb	#100							; for hundreds										; 		 ld h,0              ; blank high byte of hl.
			stb	<subUnit						; save into variable
			ldb	#48							; leading spaces									; 		 ld a,48             ; leading spaces.
			bra	NumDg3						; show number										; 		 jr numdg3
; ------------------------------------------------------------------------------------------------------------------------------------------
IniSc		ldd	#'0'*256+6					; '0' char and numbytes to write				; inisc  ld b,6              ; digits to initialise.
IniSc0	sta	,x+							; put one											; inisc0 ld (hl),'0'         ; write zero digit.
			decb									; decrement counter								; 		 inc hl              ; next column.
			bne	IniSc0						; if not done, loop								; 		 djnz inisc0         ; repeat for all digits.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Multiply h by d and return in hl																; Multiply h by d and return in hl.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR TESTMUL - #09 - DONE
IMul																										; imul   ld e,d              ; HL = H * D
																											; 		 ld c,h              ; make c first multiplier.
			mul									; multiply parameters							; imul0  ld hl,0             ; zeroise total.
			std	<reg_HL						; result into reg_HL								; 		 ld d,h              ; zeroise high byte.
																											; 		 ld b,8              ; repeat 8 times.
																											; imul1  rr c                ; rotate rightmost bit into carry.
																											; 		 jr nc,imul2         ; wasn't set.
																											; 		 add hl,de           ; bit was set, so add de.
																											; 		 and a               ; reset carry.
																											; imul2  rl e                ; shift de 1 bit left.
																											; 		 rl d
																											; 		 djnz imul1          ; repeat 8 times.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Divide d by e and return in d, remainder in a												; Divide d by e and return in d, remainder in a.
; ------------------------------------------------------------------------------------------------------------------------------------------
IDiv		sta	<reg_E						; save divisor
			stb	<reg_D						; save dividend
			clra									; reset remainder									; idiv   xor a
			ldb	#8								; bits to shift									; 		 ld b,8              ; bits to shift.
IDiv0		asl	<reg_D						; multiply by 2									; idiv0  sla d               ; multiply d by 2.
			rola									; carry to remainder								; 		 rla                 ; shift carry into remainder.
			cmpa	<reg_E						; reaminder greater than divisor?			; 		 cp e                ; test if e is smaller.
			bcs	IDiv1							; no, skip two										; 		 jr c,idiv1          ; e is greater, no division this time.
			suba	<reg_E						; subtract divisor								; 		 sub e               ; subtract it.
			inc	<reg_D						; increment result								; 		 inc d               ; rotate into d.
IDiv1		decb									; decrement bit counter							; idiv1  djnz idiv0
			bne	IDiv0							; not yet done, loopback													
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Initialise a sound.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; isnd   ld de,(ch1ptr)      ; first pointer.
;																											; 		 ld a,(de)           ; get first byte.
;																											; 		 inc a               ; reached the end?
;																											; 		 jr z,isnd1          ; that'll do.
;																											; 		 ld de,(ch2ptr)      ; second pointer.
;																											; 		 ld a,(de)           ; get first byte.
;																											; 		 inc a               ; reached the end?
;																											; 		 jr z,isnd2          ; that'll do.
;																											; 		 ld de,(ch3ptr)      ; final pointer.
;																											; 		 ld a,(de)           ; get first byte.
;																											; 		 inc a               ; reached the end?
;																											; 		 jr z,isnd3          ; that'll do.
;																											; 		 ret
;																											; isnd1  ld (ch1ptr),hl      ; set up the sound.
;																											; 		 ret
;																											; isnd2  ld (ch2ptr),hl      ; set up the sound.
;																											; 		 ret
;																											; isnd3  ld (ch3ptr),hl      ; set up the sound.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; ch1ptr defw spmask
;																											; ch2ptr defw spmask
;																											; ch3ptr defw spmask
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plsnd  call plsnd1         ; first channel.
;																											; 		 call plsnd2         ; second one.
;																											; 		 call plsnd3         ; final channel.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; Write the contents of our AY buffer to the AY registers.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; w8912  ld hl,snddat        ; start of AY-3-8912 register data.
;																											; 		 ld de,14*256        ; start with register 0, 14 to write.
;																											; 		 ld c,253            ; low byte of port to write.
;																											; w8912a ld b,255            ; port 65533=select soundchip register.
;																											; 		 out (c),e           ; tell chip which register we're writing.
;																											; 		 ld a,(hl)           ; value to write.
;																											; 		 ld b,191            ; port 49149=write value to register.
;																											; 		 out (c),a           ; this is what we're putting there.
;																											; 		 inc e               ; next sound chip register.
;																											; 		 inc hl              ; next byte to write.
;																											; 		 dec d               ; decrement loop counter.
;																											; 		 jp nz,w8912a        ; repeat until done.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; snddat defw 0              ; tone registers, channel A.
;																											; 		 defw 0              ; channel B tone registers.
;																											; 		 defw 0              ; as above, channel C.
;																											; sndwnp defb 0              ; white noise period.
;																											; sndmix defb 60             ; tone/noise mixer control.
;																											; sndv1  defb 0              ; channel A amplitude/envelope generator.
;																											; sndv2  defb 0              ; channel B amplitude/envelope.
;																											; sndv3  defb 0              ; channel C amplitude/envelope.
;																											; 		 defw 0              ; duration of each note.
;																											; 		 defb 0
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plwn   inc hl              ; next byte of sound.
;																											; 		 and 56              ; check if we're bothering with white noise.
;																											; 		 ret nz              ; we're not.
;																											; 		 ld a,(hl)           ; fetch byte.
;																											; 		 ld (sndwnp),a       ; set white noise period.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plsnd2 call cksnd2         ; check sound for first channel.
;																											; 		 cp 255              ; reached end?
;																											; 		 jr z,silen2         ; silence this channel.
;																											; 		 and 15              ; sound bits.
;																											; 		 ld (sndv2),a        ; set volume for channel.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 and 237             ; remove bits for this channel.
;																											; 		 ld b,a              ; store in b register.
;																											; 		 call plmix          ; fetch mixer details.
;																											; 		 and 18              ; mixer bits we want.
;																											; 		 or b                ; combine with mixer bits.
;																											; 		 ld (sndmix),a       ; new mixer value.
;																											; 		 call plwn           ; white noise check.
;																											; 		 inc hl              ; tone low.
;																											; 		 ld e,(hl)           ; fetch value.
;																											; 		 inc hl              ; tone high.
;																											; 		 ld d,(hl)           ; fetch value.
;																											; 		 ld (snddat+2),de    ; set tone.
;																											; 		 inc hl              ; next bit of sound.
;																											; 		 ld (ch2ptr),hl      ; set pointer.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plsnd3 call cksnd3         ; check sound for first channel.
;																											; 		 cp 255              ; reached end?
;																											; 		 jr z,silen3         ; silence last channel.
;																											; 		 and 15              ; sound bits.
;																											; 		 ld (sndv3),a        ; set volume for channel.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 and 219             ; remove bits for this channel.
;																											; 		 ld b,a              ; store in b register.
;																											; 		 call plmix          ; fetch mixer details.
;																											; 		 and 36              ; mixer bits we want.
;																											; 		 or b                ; combine with mixer bits.
;																											; 		 ld (sndmix),a       ; new mixer value.
;																											; 		 call plwn           ; white noise check.
;																											; 		 inc hl              ; tone low.
;																											; 		 ld e,(hl)           ; fetch value.
;																											; 		 inc hl              ; tone high.
;																											; 		 ld d,(hl)           ; fetch value.
;																											; 		 ld (snddat+4),de    ; set tone.
;																											; 		 inc hl              ; next bit of sound.
;																											; 		 ld (ch3ptr),hl      ; set pointer.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plmix  ld a,(hl)           ; fetch mixer byte.
;																											; 		 and 192             ; mix bits are d6 and d7.
;																											; 		 rlca                ; rotate into d0 and d1.
;																											; 		 rlca
;																											; 		 ld e,a              ; displacement in de.
;																											; 		 ld d,0
;																											; 		 push hl             ; store pointer on stack.
;																											; 		 ld hl,mixtab        ; mixer table.
;																											; 		 add hl,de           ; point to mixer byte.
;																											; 		 ld a,(hl)           ; fetch mixer value.
;																											; 		 pop hl              ; restore pointer.
;																											; 		 ret
;																											; mixtab defb 63,56,7,0      ; mixer byte settings.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; silen1 xor a               ; zero.
;																											; 		 ld (sndv1),a        ; sound off.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 or 9                ; mix bits off.
;																											; 		 ld (sndmix),a       ; mixer setting for channel.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; silen2 xor a               ; zero.
;																											; 		 ld (sndv2),a        ; sound off.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 or 18               ; mix bits off.
;																											; 		 ld (sndmix),a       ; mixer setting for channel.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; silen3 xor a               ; zero.
;																											; 		 ld (sndv3),a        ; sound off.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 or 36               ; mix bits off.
;																											; 		 ld (sndmix),a       ; mixer setting for channel.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; cksnd1 ld hl,(ch1ptr)      ; pointer to sound.
;																											; 		 ld a,(hl)           ; fetch mixer/flag.
;																											; 		 ret
;																											; cksnd2 ld hl,(ch2ptr)      ; pointer to sound.
;																											; 		 ld a,(hl)           ; fetch mixer/flag.
;																											; 		 ret
;																											; cksnd3 ld hl,(ch3ptr)      ; pointer to sound.
;																											; 		 ld a,(hl)           ; fetch mixer/flag.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; plsnd1 call cksnd1         ; check sound for first channel.
;																											; 		 cp 255              ; reached end?
;																											; 		 jr z,silen1         ; silence first channel.
;																											; 		 and 15              ; sound bits.
;																											; 		 ld (sndv1),a        ; set volume for channel.
;																											; 		 ld a,(sndmix)       ; mixer byte.
;																											; 		 and 246             ; remove bits for this channel.
;																											; 		 ld b,a              ; store in b register.
;																											; 		 call plmix          ; fetch mixer details.
;																											; 		 and 9               ; mixer bits we want.
;																											; 		 or b                ; combine with mixer bits.
;																											; 		 ld (sndmix),a       ; new mixer value.
;																											; 		 call plwn           ; white noise check.
;																											; 		 inc hl              ; tone low.
;																											; 		 ld e,(hl)           ; fetch value.
;																											; 		 inc hl              ; tone high.
;																											; 		 ld d,(hl)           ; fetch value.
;																											; 		 ld (snddat),de      ; set tone.
;																											; 		 inc hl              ; next bit of sound.
;																											; 		 ld (ch1ptr),hl      ; set pointer.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; Objects handling.
;																											; 32 bytes for image
;																											; 1 for colour
;																											; 3 for room, x and y
;																											; 3 for starting room, x and y.
;																											; 254 = disabled.
;																											; 255 = object in player's pockets.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Show items present																					; Show items present.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF OFLAG
ShwOb		ldx	#objDta+33					; point to objects table room number		; shwob  ld hl,objdta        ; objects table.
																											; 		 ld de,33            ; distance to room number.
																											; 		 add hl,de           ; point to room data.
			ldb	<numOb						; number of objects in the game				; 		 ld a,(numob)        ; number of objects in the game.
																											; 		 ld b,a              ; loop counter.
ShwOb0																									; shwob0 push bc             ; store count.
																											; 		 push hl             ; store item pointer.
			lda	<scNo							; get current location							; 		 ld a,(scno)         ; current location.
			cmpa	,x								; same as pointed object?						; 		 cp (hl)             ; same as an item?
			bne	ShwOb1						; no, skip next
			pshs	b,x							; save registers
			jsr	DObjc							; show Object										; 		 call z,dobjc        ; yes, display object in colour.
			puls	b,x							; restore objects									; 		 pop hl              ; restore pointer.
ShwOb1																									; 		 pop bc              ; restore counter.
																											; 		 ld de,39            ; distance to next item.
			leax	39,x							; point to next object							; 		 add hl,de           ; point to it.
			decb									; decrement counter
			bne	ShwOb0						; not yet done? loopback						; 		 djnz shwob0         ; repeat for others.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display object																						; Display object.
; regX points to object's room number															; hl must point to object's room number.
; ------------------------------------------------------------------------------------------------------------------------------------------
DObj																										; dobj   inc hl              ; point to x.
			ldd	1,x							; get coordinates									; dobj0  ld de,dispx         ; coordinates.
			std	<dispX						; put into variables X,Y						; 		 ldi                 ; transfer x coord.
																											; 		 ldi                 ; transfer y too.
																											; 		 ld de,65500         ; minus 36.
			leax	-33,x							; point to object image							; 		 add hl,de           ; point to image.
DObj1		ldd	<dispX
			sta	<dispY
			stb	<dispX
DObjX		jmp	Sprite						; draw object as sprite							; dobj1  jp sprite           ; draw this sprite.
																											; 
DObjc		bsr	DObj							; display object									; dobjc  call dobj           ; display object.
																											; 		 ld c,(hl)           ; put ink in c register.
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Need to write attribute routine here.
													; NO colours to set in 6809					; set up colour in c register first.
; ------------------------------------------------------------------------------------------------------------------------------------------
CObj																										; cobj   ld a,(hl)           ; get colour byte.
;																											; 		 and a               ; test it.
;																											; 		 ret m               ; colour not set.
;																											; 		 ld h,22             ; quarter of attrubte address.
;																											; 		 ld a,(dispx)        ; x coord.
;																											; 		 and 248             ; only want multiple of 8.
;																											; 		 rla                 ; multiply by 4.
;																											; 		 rl h
;																											; 		 rla
;																											; 		 rl h                ; high byte now set up.
;																											; 		 ld l,a
;																											; 		 ld a,(dispy)        ; take y position.
;																											; 		 rra                 ; divide it by 8.
;																											; 		 rra
;																											; 		 rra
;																											; 		 and 31              ; remove unwanted bits.
;																											; 		 add a,l             ; add to low byte.
;																											; 		 ld l,a              ; low byte of address.
;																											; 		 ld de,30            ; distance to next line down.
;																											; 		 ld a,(dispx)        ; x coordinate.
;																											; 		 ld b,3              ; default rows to write.
;																											; 		 and 7               ; does x straddle cells?
;																											; 		 jr nz,cobj0         ; yes, loop counter is good.
;																											; 		 dec b               ; one less row to write.
;																											; cobj0  ld a,(hl)           ; get attributes.
;																											; 		 and 248             ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; 		 inc l               ; next cell.
;																											; 		 ld a,(hl)           ; get attributes.
;																											; 		 and 248             ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; 		 inc l               ; next cell.
;																											; 		 ld a,(dispy)        ; y coordinate.
;																											; 		 and 7               ; straddling cells?
;																											; 		 jr z,cobj1          ; no, only 2 wide.
;																											; 		 ld a,(hl)           ; get attributes.
;																											; 		 and 248             ; remove ink.
;																											; 		 or c                ; put in the new ink.
;																											; 		 ld (hl),a           ; write back again.
;																											; cobj1  add hl,de           ; next row.
;																											; 		 djnz cobj0
			rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Remove an object																					; Remove an object.
; ------------------------------------------------------------------------------------------------------------------------------------------
RemOb		cmpa	<numOb																				; remob  ld hl,numob         ; number of objects in game.
			bcc	RemObEx																				; 	 cp (hl)             ; are we checking past the end?
																											; 	 ret nc              ; yes, can't get non-existent item.
			pshs	a																						; 	 push af             ; remember object.
			jsr	GetOb																					; 	 call getob          ; pick it up if we haven't already got it.
			puls	a																						; 	 pop af              ; retrieve object number.
			jsr	GotOb																					; 	 call gotob          ; get its address.
			lda	#254																					; 	 ld (hl),254         ; remove it.
			sta	<numOb
RemObEx	rts																							; 	 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Pick up object number held in the accumulator												; Pick up object number held in the accumulator.
; ------------------------------------------------------------------------------------------------------------------------------------------
GetOb																										; getob  ld hl,numob         ; number of objects in game.
			cmpa	<numOb																					; 		 cp (hl)             ; are we checking past the end?
			bcc	GetObEx																				; 		 ret nc              ; yes, can't get non-existent item.
			jsr	GotOb																					; 		 call gotob          ; check if we already have it.
			beq	GetObEx																				; 		 ret z               ; we already do.
																											; 		 ex de,hl            ; object address in de.
			ldx	<reg_HL																				; 		 ld hl,scno          ; current screen.
			cmpa	<scNo																					; 		 cp (hl)             ; is it on this screen?
																											; 		 ex de,hl            ; object address back in hl.
			bne	GetOb0																				; 		 jr nz,getob0        ; not on screen, so nothing to delete.
			lda	#255																					; 		 ld (hl),255         ; pick it up.
			sta	,x+																					; 		 inc hl              ; point to x coord.
GetOb1	ldd	,x																						; getob1 ld e,(hl)           ; x coord.
																											; 		 inc hl              ; back to y coord.
																											; 		 ld d,(hl)           ; y coord.
			std	<dispX						; save inverted, DObj1 corrects it			; 		 ld (dispx),de       ; set display coords.
																											; 		 ld de,65501         ; minus graphic size.
			leax	-34,x																					; 		 add hl,de           ; point to graphics.
			
			jsr	DObj1							; delete collected object						; 		 call dobj1          ; delete object sprite.
																											; 		 ld a,(bcol)         ; first block colour.
																											; 		 and 7               ; only want ink attribute.
																											; 		 ld c,a              ; set up colour.
			jmp	CObj																					; 		 jp cobj             ; colour object's old position.
GetOb0	lda	#255
			sta	,x																						; getob0 ld (hl),255         ; pick it up.
GetObEx	rts																							; 		 ret
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Got object check																					; Got object check.
; Call with object in accumulator, returns zero set if in pockets						; Call with object in accumulator, returns zero set if in pockets.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF OFLAG+MFLAG
GotOb																										; gotob  ld hl,numob         ; number of objects in game.
			cmpa	<numOb						; are we checking past the end?				; 		 cp (hl)             ; are we checking past the end?
			bcc	GotOb0						; yes, we can't have a non-existent object; 		 jr nc,gotob0        ; yes, we can't have a non-existent object.
			jsr	FindOb						; find object										; 		 call findob         ; find the object.
GotOb1	cmpa	#255							; in pocket's?										; gotob1 cp 255              ; in pockets?
			rts									; return result in flags						; 		 ret
GotOb0	lda	#254							; disabled											; gotob0 ld a,254            ; missing.
			bra	GotOb1						; exit testing										; 		 jr gotob1
; ------------------------------------------------------------------------------------------------------------------------------------------
FindOb	pshs	x								; save working register
			ldx	#objDta						; point to objects table						; findob ld hl,objdta        ; objects.
																											; 		 ld de,39            ; size of each object.
			tsta									; received zero?									; 		 and a               ; is it zero?
			beq	FndOb1						; yes, skip loop									; 		 jr z,fndob1         ; yes, skip loop.
											 																; 		 ld b,a              ; loop counter in b.
FndOb2	leax	39,x							; point to next object							; fndob2 add hl,de           ; point to next one.
			deca									; decrement number of Object
			bne	FndOb2						; not zero, loopback								; 		 djnz fndob2         ; repeat until we find address.
FndOb1																									; fndob1 ld e,33             ; distance to room it's in.
			leax	33,x							; point to room where object is				; 		 add hl,de           ; point to room.
			stx	<reg_HL						; save pointer
			lda	,x								; get status 										; 		 ld a,(hl)           ; fetch status.
			puls	x,pc							; restore register and return					; 		 ret
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Drop object number at (dispx, dispy)															; Drop object number at (dispx, dispy).
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF OFLAG
DrpOb																										; drpob  ld hl,numob         ; number of objects in game.
			cmpa	<numOb						; are we checking past the end?				; 		 cp (hl)             ; are we checking past the end?
			bcc	DrpOEx						; yes, can't drop non-existent item			; 		 ret nc              ; yes, can't drop non-existent item.
			jsr	GotOb							; make sure object is in inventory			; 		 call gotob          ; make sure object is in inventory.
			ldx	<reg_HL						; returns location number in reg_HL
			lda	<scNo							; get screen number								; 		 ld a,(scno)         ; screen number.
			cmpa	,x								; already on this screen?						; 		 cp (hl)             ; already on this screen?
			beq	DrpOEx						; yes, exit											; 		 ret z               ; yes, nothing to do.
DisObj	ldb	#$00							; flag for disabling an object
			beq	DrpOb1						; not set) show object
			dec	,x								; convert 255 (in pocket) to disabled
			bra	DrpOEx						; exit
DrpOb1	sta	,x								; update location									; 		 ld (hl),a           ; bring onto screen.
																											; 		 inc hl              ; point to x coord.
			lda	<dispY						; get sprite x coordinate						; 		 ld a,(dispx)        ; sprite x coordinate.
			sta	2,x							; set x coord										; 		 ld (hl),a           ; set x coord.
																											; 		 inc hl              ; point to object y.
			lda	<dispX						; get sprite y coordinate						; 		 ld a,(dispy)        ; sprite y coordinate.
			sta	1,x							; set y coord										; 		 ld (hl),a           ; set the y position.
																											; 		 ld de,65501         ; minus graphic size (35)
			leax	-33,x							; point to object beginning					; 		 add hl,de           ; point to graphics.
			stx	<reg_HL						; update register
			jsr	DObj1							; delete object sprite							; 		 call dobj1          ; delete object sprite.
																											; 		 ld c,(hl)           ; put ink in c register.
DrpOEx	clr	DisObj+1						; reset to enable objects
			jmp	CObj							; no colors - delete old sprite				; 		 jp cobj             ; colour the object.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Seek objects at sprite position																; Seek objects at sprite position.
; ------------------------------------------------------------------------------------------------------------------------------------------
SkObj		ldx	#objDta																				; skobj  ld hl,objdta        ; pointer to objects.
																											; 		 ld de,33            ; distance to room number.
			leax	33,x																					; 		 add hl,de           ; point to room data.
																											; 		 ld de,39            ; size of each object.
			lda	<numOb																				; 		 ld a,(numob)        ; number of objects in game.
			sta	<reg_B																				; 		 ld b,a              ; set up the loop counter.
SkObj0	lda	<scNo																					; skobj0 ld a,(scno)         ; current room number.
			cmpa	,x																						; 		 cp (hl)             ; is object in here?
			bne	SkObjZ
			jsr	SkObj1																				; 		 call z,skobj1       ; yes, check coordinates.
SkObjZ	leax	39,x																					; 		 add hl,de           ; point to next object in table.
			dec	<reg_B
			bne	SkObj0																				; 		 djnz skobj0         ; repeat for all objects.
			lda	#255																					; 		 ld a,255            ; end of list and nothing found, return 255.
			rts																							; 		 ret
SkObj1	leax	1,x																					; skobj1 inc hl              ; point to x coordinate.
			lda	,x																						; 		 ld a,(hl)           ; get coordinate.
			suba	8,y																					; 		 sub (ix+8)          ; subtract sprite x.
			adda	#15																					; 		 add a,15            ; add sprite height minus one.
			cmpa	#31																				; 		 cp 31               ; within range?
			bcc	SkObj2																				; 		 jp nc,skobj2        ; no, ignore object.
			leax	1,x																					; 		 inc hl              ; point to y coordinate now.
			lda	,x																						; 		 ld a,(hl)           ; get coordinate.
			suba	9,y																					; 		 sub (ix+9)          ; subtract the sprite y.
			adda	#15																					; 		 add a,15            ; add sprite width minus one.
			cmpa	#31																				; 		 cp 31               ; within range?
			bcc	SkObj3																				; 		 jp nc,skobj3        ; no, ignore object.
			leas	2,s																					; 		 pop de              ; remove return address from stack.
			lda	<numOb																				; 		 ld a,(numob)        ; objects in game.
			suba	<reg_B																				; 		 sub b               ; subtract loop counter.
			rts																							; 		 ret                 ; accumulator now points to object.
SkObj3	leax	-1,x																					; skobj3 dec hl              ; back to y position.
SkObj2	leax	-1,x																					; skobj2 dec hl              ; back to room.
			rts																							; 		 ret
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Spawn a new sprite																					; Spawn a new sprite.
; from AGD script receives:  ImageNumber in <regB  
; 								and  SpriteType  in <reg_C
; ------------------------------------------------------------------------------------------------------------------------------------------
Spawn		ldx	#sprTab						; point to sprites data table					; spawn  ld hl,sprtab        ; sprite table.
NumSp1	lda	#NUMSPR						; number of sprites								; numsp1 ld a,NUMSPR         ; number of sprites.
			sta	<reg_AF						; save counter										; 		 ld de,TABSIZ        ; size of each entry.
Spaw0																										; spaw0  ex af,af'           ; store loop counter.
			lda	,x								; get type											; 		 ld a,(hl)           ; get sprite type.
			inca									; is it unused (255)?							; 		 inc a               ; is it an unused slot?
			beq	Spaw1							; yes, use it										; 		 jr z,spaw1          ; yes, we can use this one.
			leax	TABSIZ,x						; point to next entry							; 		 add hl,de           ; point to next sprite in table.
			dec	<reg_AF						; decrement counter								; 		 ex af,af'           ; restore loop counter.
														 													; 		 dec a               ; one less iteration.
			bne	Spaw0							; not done? loopback								; 		 jr nz,spaw0         ; keep going until we find a slot.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Didn't find one but drop through and set up a dummy sprite instead					; Didn't find one but drop through and set up a dummy sprite instead.
; pointers: Y points to actual 'old' sprite.  X points to new spawned sprite
; ------------------------------------------------------------------------------------------------------------------------------------------
Spaw1		pshs	y								; save hit 'old sprite' pointer				; spaw1  push ix             ; existing sprite address on stack.
			stx	<spPtr						; save 'new sprite' pointer					; 		 ld (spptr),hl       ; store spawned sprite address.
			lda	<reg_C						; get sprite type									; 		 ld (hl),c           ; set the type.
			sta	,x								; put as old type									; 		 inc hl              ; point to image.
			lda	<reg_B						; get image number								; 		 ld (hl),b           ; set the image.
			sta	1,x							; set as old image number						; 		 inc hl              ; next byte.
																											; 		 ld (hl),0           ; frame zero.
			clr	2,x							; set old frame to 0								; 		 inc hl              ; next byte.
			lda	Xval,y						; get hit sprite Y coordinate					; 		 ld a,(ix+X)         ; x coordinate.
			sta	3,x							; set as old Y coord								; 		 ld (hl),a           ; set sprite coordinate.
																											; 		 inc hl              ; next byte.
			lda	Yval,y						; get hit sprite X coordinate					; 		 ld a,(ix+Y)         ; y coordinate.
			sta	4,x							; set as old X coord								; 		 ld (hl),a           ; set sprite coordinate.
																											; 		 inc hl              ; next byte.
																											; 		 ex de,hl            ; swap address into de.
																											; 		 ld hl,(spptr)       ; restore address of details.
			ldb	#5								; bytes to copy									; 		 ld bc,5             ; number of bytes to duplicate.
SpawCpy	lda	,x+							; get a byte from old data area				; 		 ldir                ; copy first version to new version.
			sta	4,x							; copy into new data area
			decb									; decrement counter
			bne	SpawCpy						; not done? copy next byte
													; regX points to offset +5
			leax	5,x							; now points to offset +10 
																											; 		 ex de,hl            ; swap address into de.
			lda	10,y							; get direction of 'old sprite'				; 		 ld a,(ix+10)        ; direction of original.
			sta	,x+							; set the same for new one						; 		 ld (hl),a           ; set the direction.
																											; 		 inc hl              ; next byte.
			clra									; zero												; 		 ld (hl),b           ; reset parameter.
			std	,x++							; set as PARAM1-PARAM2							; 		 inc hl              ; next byte.
																											; 		 ld (hl),b           ; reset parameter.
																											; 		 inc hl              ; next byte.
			std	,x								; and as jump pointer (low-high bytes)		; 		 ld (hl),b           ; reset parameter.
																											; 		 inc hl              ; next byte.
																											; 		 ld (hl),b           ; reset parameter.
RtsSp		ldy	<spPtr						; get pointer to beginning of new sprite	; rtssp  ld ix,(spptr)       ; address of new sprite.
Evis1		jsr	Evnt09						; initializes Sprite								; evis1  call evnt09         ; call sprite initialisation event.
			ldx	<spPtr						; regX *must* point to sprite data			; 		 ld ix,(spptr)       ; address of new sprite.
			jsr	SSpriA						; display the new Sprite old coord			; 		 call sspria         ; display the new sprite.
			puls	y								; restore 'old sprite' pointe					; 		 pop ix              ; address of original sprite.
			sty	<reg_IX						; update pseudoregister
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
score		fcc	/000000/						; player's score									; score  defb '000000'       ; player's score.
hiScor	fcc 	/000000/						; high score										; hiscor defb '000000'       ; high score.
bonus		fcc	/000000/						; bonus												; bonus  defb '000000'       ; bonus.
; ------------------------------------------------------------------------------------------------------------------------------------------
; verify if inside screen window																	; verify if inside screen window
; ------------------------------------------------------------------------------------------------------------------------------------------
CheckX	lda	<dispY						; get Y position									; checkx ld a,e              ; x position.
			cmpa	#24							; out of screen?									; 		 cp 24               ; off screen?
			blo	Check1						; no, skip next									; 		 ret c               ; no, it's okay.
			puls	x								; remove return address from stack			; 		 pop hl              ; remove return address from stack.
Check1	rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Displays the High score
; ------------------------------------------------------------------------------------------------------------------------------------------
; ADDED FOR TESTSCORE.AGD
DHiSc		ldx	#hiScor						; point to hhigh score
			bra	Dscor1						; show it
; ------------------------------------------------------------------------------------------------------------------------------------------
; Displays the current score																		; Displays the current score.
; Parameter: reg_B *must* contain the number of digits to be displayed
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #08 - DONE - VERIFIED - MODIFIED FOR TESTSCORE
Dscor		ldx	#score						; point to string to be shown
Dscor1	jsr	PrePrt						; fontPtr->grBase - charXY->dispXY			; dscor  call preprt         ; set up font and print position.
			jsr	CheckX						; Y must be < 24 or aborts						; 		 call checkx         ; make sure we're in a printable range.
			ldb	#6								; subtract
			subb	<reg_B						; number of digits from maximum
			abx									; offset to begin reading
			ldb	<reg_B						; get number of digits again
			lda	<prtMod						; numbers size										; 		 ld a,(prtmod)       ; get print mode.
																											; 		 and a               ; standard size text?
			bne	Bscor0						; if not zero, use big digits					;		 jp nz,bscor0        ; no, show double-height.
Dscor0	pshs	b,x							; save counter										; dscor0 push bc             ; place counter onto the stack.
													; and pointer										; 		 push hl
			lda	,x								; get a digit										; 		 ld a,(hl)           ; fetch character.
			jsr	PChar							; show it											; 		 call pchar          ; display character.
													; no attributes									; 		 call gaadd          ; get attribute address.
													; no colours										; 		 ld a,(23693)        ; current cell colours.
													;														; 		 ld (hl),a           ; write to attribute cell.
			inc	<dispX						; point to next row								; 		 ld hl,dispy         ; y coordinate.
																											; 		 inc (hl)            ; move along one.
			puls	b,x							; restore pointer and counter					; 		 pop hl
			leax	1,x							; point to next digit							; 		 inc hl              ; next score column.
			decb									; decrement counter								; 		 pop bc              ; retrieve character counter.
			bne	Dscor0						; not done, loop									; 		 djnz dscor0         ; repeat for all digits.
			ldx	blkPtr						; get blocks address								; 		 ld hl,(blkptr)      ; blocks.
			stx	grBase						; pass to pointer									; 		 ld (grbase),hl      ; set graphics base.
Dscor2	ldx	<dispX						; get screen position (X,Y)					; dscor2 ld hl,(dispx)       ; general coordinates.
			stx	<charX						; save for next time								; 		 ld (charx),hl       ; set up display coordinates.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Displays the current score in double-height characters									; Displays the current score in double-height characters.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #081 - DONE
Bscor0	pshs	b,x							; save counter										; bscor0 push bc             ; place counter onto the stack.
													; and pointer										; 		 push hl
			lda	,x								; get character									; 		 ld a,(hl)           ; fetch character.
			jsr	Bchar							; print it											; 		 call bchar          ; display big char.
			puls	b,x							; restore counter and pointer					; 		 pop hl
			leax	1,x							; point to next char								; 		 inc hl              ; next score column.
			decb									; decrement counter								; 		 pop bc              ; retrieve character counter.
			bne	Bscor0						; not done? loopback								; 		 djnz bscor0         ; repeat for all digits.
			bra	Dscor2						; exit												; 		 jp dscor2           ; tidy up line and column variables.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Adds number in the hl pair to the score														; Adds number in the hl pair to the score.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #07 - DONE - VERIFIED
AddSc		ldx	<reg_HL						; get value to be added
			ldu	#score+1						; poit to 2nd digit by the left				; addsc  ld de,score+1       ; ten thousands column.
			ldd	#10000						; D=$2710											; 		 ld bc,10000         ; amount to add each time.
			bsr	IncSc							; process tens of thousands					; 		 call incsc          ; add to score.
			leau	1,u							; point to thousands								; 		 inc de              ; thousands column.
			ldd	#1000							; D=3e8												; 		 ld bc,1000          ; amount to add each time.
			bsr	IncSc							; process thousands								; 		 call incsc          ; add to score.
			leau	1,u							; point to hundreds								; 		 inc de              ; hundreds column.
			ldd	#100							; D=$64												; 		 ld bc,100           ; amount to add each time.
			bsr	IncSc							; process hundreds								; 		 call incsc          ; add to score.
			leau	1,u							; point to tens									; 		 inc de              ; tens column.
			ldd	#10							; D=$0a												; 		 ld bc,10            ; amount to add each time.
			bsr	IncSc							; process tens										; 		 call incsc          ; add to score.
			leau	1,u							; point to units									; 		 inc de              ; units column.
			ldd	#1								; D=$01												; 		 ld bc,1             ; units.
IncSc		pshs	x,d							; save total, partial							; incsc  push hl             ; store amount to add.
																											; 		 and a               ; clear the carry flag.
			tfr	x,d							; D=64 (not yet added)							; 		 sbc hl,bc           ; subtract from amount to add.
			subd	,s								; subtract param regD
			bcs	IncSc0						; if carry, restore X							; 		 jr c,incsc0         ; too much, restore value.
																											; 		 pop af              ; delete the previous amount from the stack.
			tfr	d,x							; update amount not yet added
			pshs	u								; save column pointer							; 		 push de             ; store column position.
			bsr	IncSc2						; update current digit (=1)					; 		 call incsc2         ; do the increment.
			puls	u								; restore column pointer						; 		 pop de              ; restore column.
			puls	d								; get parcial in use
			leas	2,s							; get rid of regX
			bra	IncSc							; try again											; 		 jp incsc            ; repeat until all added.
IncSc0	puls	x,d							; restore pushed registers						; incsc0 pop hl              ; restore previous value.
			rts									; ended digit control							; 		 ret
IncSc2	pshs	d								; save curent result
IncSc2a	lda	,u								; get current digit								; incsc2 ld a,(de)           ; get amount.
			inca									; increment it										; 		 inc a               ; add one to column.
			sta	,u								; update digit										; 		 ld (de),a           ; write new column total.
			cmpa	#'9'+1						; exceeded '9'?									; 		 cp '9'+1            ; gone beyond range of digits?
			bcs	IncEx							; no, so ok, exit									; 		 ret c               ; no, carry on.
			lda	#'0'							; yes, put a '0'									; 		 ld a,'0'            ; make it zero.
			sta	,u								; update digit										; 		 ld (de),a           ; write new column total.
			leau	-1,u							; point to letf digit							; 		 dec de              ; back one column.
			bra	IncSc2a						; go increment it									; 		 jr incsc2
IncEx		puls	d,pc							; clean stack and return
; ------------------------------------------------------------------------------------------------------------------------------------------
; Add bonus to score																					; Add bonus to score.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED for TESTSCORE
AddBo		pshs	x,u							; save working registers						; addbo  ld de,score+5       ; last score digit.
			ldu	#score+5						; point to score units
			ldx	#bonus+5						; point to bonust units							; 		 ld hl,bonus+5       ; last bonus digit.
			andcc	#%11111110					; clear carry										; 		 and a               ; clear carry.
			ldd	#$0630						; 6 digits - ascii for '0'						; 		 ld bc,6*256+48      ; 6 digits to add, ASCII '0' in c.
			std	<reg_BC						; into reg_BC
AddBo0	lda	,u								; get digit from score							; addbo0 ld a,(de)           ; get score.
			adca	,x								; add with carry bonus							; 		 adc a,(hl)          ; add bonus.
			suba	<reg_C						; convert to binary								; 		 sub c               ; 0 to 18.
			stb	,x								; zero to used bonus digit						; 		 ld (hl),c           ; zeroise bonus.
			leax	-1,x							; point one digit to the left					; 		 dec hl              ; next bonus.
			cmpa	#58							; more than 9?										; 		 cp 58               ; carried?
			bcs	AddBo1						; no, skip next two								; 		 jr c,addbo1         ; no, do next one.
			suba	#10							; yes, subtract 10								; 		 sub 10              ; subtract 10.
AddBo1	sta	,u								; update score digit								; addbo1 ld (de),a           ; write new score.
			leau	-1,u							; point one digit to the left					; 		 dec de              ; next score digit.
			andcc	#%11111110					; clear carry for next digit					; 		 ccf                 ; set carry for next digit.
			dec	<reg_B						; decrement digits counter
			bne	AddBo0						; not done? loopback								; 		 djnz addbo0         ; repeat for all 6 digits.
			puls	x,u,pc						; restore registers and return				; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Swap score and bonus																				; Swap score and bonus.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR TESTSCORE
SwpSB		pshs	x,u																					; swpsb  ld de,score         ; first score digit.
			ldu	#score
			ldx	#bonus																				; 		 ld hl,bonus         ; first bonus digit.
			ldb	#6																						; 		 ld b,6              ; digits to add.
			stb	<reg_B
SwpSB0	lda	,u																						; swpsb0 ld a,(de)           ; get score and bonus digits.
			ldb	,x																						; 		 ld c,(hl)
			sta	,x+																					; 		 ex de,hl            ; swap pointers.
			stb	,u+																					; 		 ld (hl),c           ; write bonus and score digits.
																											; 		 ld (de),a
																											; 		 inc hl              ; next score and bonus.
			dec	<reg_B																				; 		 inc de
			bne	SwpSB0																				; 		 djnz swpsb0         ; repeat for all 6 digits.
			puls	x,u,pc																				; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get print address																					; Get print address
; ------------------------------------------------------------------------------------------------------------------------------------------
GPrad		clra																							; gprad:
			ldb	<dispX																				;     lda dispx        ; get x
			stb	<grBase+1					; save low byte									;     sta scraddr        ; store lb address
																											;     lda dispx        ; Add Column/32
			lslb																							;     rol a
			rola																							;     rol tmp
			lslb																							;     rol a
			rola																							;     rol tmp
			lslb																							;     rol a
			rola																							;     rol tmp
																											;     lda tmp
			anda	#7								; use only 3 lower bits							;     and #7
																											;     sta tmp
																											; 
			tst	prtMod																				;     lda prtmod        ; If double heigth text
			beq	1f																						;     beq :+            ; multiply by 2
			asla									; multiply by two									;     asl tmp
1																											; :
																											;     lda tmp
																											;     clc
			adda	<dispY						; add Y cordinate									;     adc dispy        ; get y
			addd	#SCRBEG						; add screen beginning							;     ora #$80        ; add $80
			sta	<grBase						; store address									;     sta scraddr+1        ; store hb address
			rts									; return												;     rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get property buffer address of char at (dispx, dispy) in hl							; Get property buffer address of char at (dispx, dispy) in hl
; receives in regA byte number. Returns address in regX
; ------------------------------------------------------------------------------------------------------------------------------------------
PrAdd		pshs	a,b							; save registers
			lda	<dispY						; get coordinate Y								; pradd  ld a,(dispx)        ; x coordinate.
			ldb	#32							; multiply											; 		 rrca                ; multiply by 32.
			mul									; by 32												; 		 rrca
																											; 		 rrca
																											; 		 ld l,a              ; store shift in l.
																											; 		 and 3               ; high byte bits.
			ldx	#MAP							; start of properties map						; 		 add a,253           ; 253 * 256 = 64768, start of properties map.
			leax	d,x							; add Y offset										; 		 ld h,a              ; that's our high byte.
								 																			; 		 ld a,l              ; restore shift result.
																											; 		 and 224             ; only want low bits.
																											; 		 ld l,a              ; put into low byte.
			ldb	<dispX						; get coordinate X								; 		 ld a,(dispy)        ; fetch y coordinate.
			andb	#31							; keep into 0-31 range							; 		 and 31              ; should be in range 0 - 31.
			abx									; add X offset										; 		 add a,l             ; add to low byte.
																											; 		 ld l,a              ; new low byte.
			puls	a,b,pc						; restore registers and return				; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Get attribute address of char at (dispx, dispy) in hl.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; gaadd  ld a,(dispx)        ; x coordinate.
;																											; 		 rrca                ; multiply by 32.
;																											; 		 rrca
;																											; 		 rrca
;																											; 		 ld l,a              ; store shift in l.
;																											; 		 and 3               ; high byte bits.
;																											; 		 add a,88            ; 88 * 256 = 22528, start of screen attributes.
;																											; 		 ld h,a              ; that's our high byte.
;																											; 		 ld a,l              ; restore shift result.
;																											; 		 and 224             ; only want low bits.
;																											; 		 ld l,a              ; put into low byte.
;																											; 		 ld a,(dispy)        ; fetch y coordinate.
;																											; 		 and 31              ; should be in range 0 - 31.
;																											; 		 add a,l             ; add to low byte.
;																											; 		 ld l,a              ; new low byte.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display character in A at dispx,dispy.														; Display character in A at dispx,dispy.
; ------------------------------------------------------------------------------------------------------------------------------------------
PChar		ldb	#8								; to multiply by 8								; pchar  rlca                ; multiply char by 8.		
			mul									; calculate offset 16 bits						; 		 rlca
			ldu	<fontPtr						; get font table beginning						; 		 rlca
			leau	d,u							; add offset										; 		 ld e,a              ; store shift in e.
PChark	jsr	GPrad							; get screen address.							; 		 and 7               ; only want high byte bits.
			ldx	<grBase						; point to screen (destination)				; 		 ld d,a              ; store in d.
			ldb	#8								; lines to write									; 		 ld a,e              ; restore shifted value.
PChar0	lda	,u+							; get char row byte								; 		 and 248             ; only want low byte bits.
	IF GFLAG
			anda	<andeor
			eora	<andeor+1
	ENDIF
			sta	,x								; put on screen									; 		 ld e,a              ; that's the low byte.
			leax	32,x							; point to next row								; 		 ld hl,(grbase)      ; address of graphics.
			decb									; decrement counter								; 		 add hl,de           ; add displacement.
			bne	PChar0						; not done? loopback								; pchark call gprad          ; get screen address.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; 		 ld a,(hl)      																						; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; ;       dec de              ; back again.
																											; ;       inc d               ; next screen row down.
																											; ;       ldi                 ; transfer byte.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
																											; 		 inc hl              ; next image byte.
																											; 		 inc d               ; next screen row down.
																											; 		 ld a,(hl)           ; get image byte.
																											; 		 ld (de),a           ; copy to screen.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Print attributes, properties and pixels														; Print attributes, properties and pixels.
; receives cellnum(block) in regA and repetitions in comCnt
; ------------------------------------------------------------------------------------------------------------------------------------------
pbPAttr	ldx  <charX							; get entered variables
			stx  <dispX							; to display ones
PAttr		
	IF AFLAG																								; .if aflag
			pshs	a,x							; save block number								; pha
			jsr	WBloc            	      ; save blockinfo									; jsr wbloc 
			puls	a,x							; restore block number							; pla
	ENDIF																									; .endif
PAttr2																									; pattr2:
			sta	<reg_B						; save block number								; pattr  ld b,a              ; store cell in b register for now.
																											; 		 ld e,a              ; displacement in e.
																											; 		 ld d,0              ; no high byte.
			ldx	<proPtr						; point to properties table					; 		 ld hl,(proptr)      ; pointer to properties.
																											; 		 add hl,de           ; property cell address.
			clra									; high byte to zero
			ldb	<reg_B						; use value as low byte							; 		 ld c,(hl)           ; fetch byte.
			ldb	d,x							; fetch byte at 16 bits offset				; 		 ld c,(hl)           ; fetch byte.
			cmpb	#COLECT						; is it a collectable block?
			bne	PAttr3						; no, skip next
			lda	<reg_B						; restore received block number
			sta	<colPatt						; save collectable block number
PAttr3	jsr	PrAdd		 					; get property buffer address					; 		 call pradd          ; get property buffer address.
			stb	,x								; write property									; 		 ld (hl),c           ; write property.
			lda	<reg_B						; restore cell										; 		 ld a,b              ; restore cell.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;													; No Attributes in 6809							; Print attributes, no properties.
;																											; panp   ld e,a              ; displacement in e.
;																											; 		 ld d,0              ; no high byte.
;																											; 		 ld hl,(colptr)      ; pointer to colours.
;																											; 		 add hl,de           ; colour cell address.
;																											; 		 ld c,(hl)           ; fetch byte.
;																											; 		 call gaadd          ; get attribute address.
;																											; 		 ld (hl),c           ; write colour.
;																											; 		 ld a,b              ; restore cell.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
																											; Print character pixels, no more.
PChr		ldx	<blkPtr						; get blocks pointer
			stx	<fontPtr						; pass to used variable
PChr0		jsr	PChar							; print char in regA								; pchr   call pchar          ; show character in accumulator.
			ldx	#font-256					; point to fonts table																	
			stx	<fontPtr						; save into pointer								; 		 ld hl,dispy         ; y coordinate.
			inc	<dispX						; move to next char								; 		 inc (hl)            ; move along one.
			inc	<charX						; move to next char								; 		 inc (hl)            ; move along one.
			rts									; return												; 		 ret

	IF AFLAG																								; .if aflag
WBloc												; Write BLOCK										; wbloc:
			ldx	<pbPtr						; get write pointer								; ldy	#3
			sta	3,x							; store block number								; sta	(pbptr),y        ; store block number
																											; dey
			lda	<dispX						; get Y position									; lda	dispx
			sta	2,x							; write Y block position						; sta	(pbptr),y        ; write x position of block.
																											; dey
			lda	<dispY						; get X position									; lda	dispy
			sta	1,x							; write X block position						; sta	(pbptr),y        ; write y position of block.
																											; dey
			lda	<scNo							; get screen number								; lda	scno
			sta	,x								; write screen number							; sta	(pbptr),y        ; write screen.
																											; clc            ; point to next free location
																											; lda	pbptr
			leax	4,x							; point to next bloc								; adc	#4
																											; sta	pbptr
																											; bcc	:
			stx	<pbPtr						; update pointer									; inc	pbptr+1
			rts									; return												;:			rts
	ENDIF																									; .endif
; ------------------------------------------------------------------------------------------------------------------------------------------
; Shifter sprite routine for objects															; Shifter sprite routine for objects.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF OFLAG
Sprit7	eora	#7								; invert thre low bits							; sprit7 xor 7
			inca									; add one											; 		 inc a
Sprit3	rol	<reg_L						; shift into position							; sprit3 rl l                ; shift into position.
			rol	<reg_C						; the 3												; 		 rl c
			rol	<reg_H						; bytes												; 		 rl h
			deca									; decrement counter								; 		 dec a               ; one less iteration.
			bne	Sprit3						; not zero, shift again							; 		 jp nz,sprit3
			lda	<reg_L						; get reg_L											; 		 ld a,l
			ldb	<reg_C						; pass reg_C
			stb	<reg_L						; to reg_L											; 		 ld l,c
			ldb	<reg_H						; pass reg_H
			stb	<reg_C						; to reg_C											; 		 ld c,h
			sta	<reg_H						; save to reg_H									; 		 ld h,a
			bra	Sprit0						; apply to screen									; 		 jp sprit0           ; now apply to screen.
; ------------------------------------------------------------------------------------------------------------------------------------------
Sprite	pshs	x								; save graphic address							; sprite push hl             ; store sprite graphic address.
			jsr	ScAdd							; get screen address in regX					; 		 call scadd          ; get screen address in hl.
			leau	,x								; pass to regU										; 		 ex de,hl            ; switch to de.
			puls	x								; restore regX										; 		 pop hl              ; restore graphic address.
			lda	<dispX						; get posY											; 		 ld a,(dispy)        ; y position.
			anda	#7								; use only 3 low bits							; 		 and 7               ; position straddling cells.
			sta	<reg_B						; save in reg_B									; 		 ld b,a              ; store in b register.
			lda	#16							; number of rows									; 		 ld a,16             ; pixel height.
Sprit1	sta	<reg_AF						; save to reg_A									; sprit1 ex af,af'
			lda	,x+							; fetch 1st byte									; 		 ld c,(hl)           ; fetch first byte.
			sta	<reg_C						; to reg_C											; 		 inc hl              ; next byte.
			pshs	x								; save regX into stack							; 		 push hl             ; store source address.
			ldb	,x								; get low byte										; 		 ld l,(hl)
			clra									; zero for high byte								; 		 ld h,0
			std	<reg_HL						; pass to reg_HL									; 		 ld a,b              ; position straddling cells.
			lda	<reg_B						; restore reg_B									; 		 and a               ; is it zero?
			beq	Sprit0						; if zero, apply to screen						; 		 jr z,sprit0         ; yes, apply to screen.
			cmpa	#5								; is it lower than 6?							; 		 cp 5
			bcc	Sprit7						; yes, go shift it								; 		 jr nc,sprit7
			andcc	#%11111110					; clear carry										; 		 and a               ; clear carry.
Sprit2	ror	<reg_C						; shift												; sprit2 rr c
			ror	<reg_L						; into												; 		 rr l
			ror	<reg_H						; position											; 		 rr h
			deca									; decrement counter								; 		 dec a
			bne	Sprit2						; not zero, shift again							; 		 jp nz,sprit2
Sprit0	lda	,u								; get byte from screen							; sprit0 ld a,(de)           ; fetch screen image.
			eora	<reg_C						; merge with graphic								; 		 xor c               ; merge with graphic.
			sta	,u+							; write to screen									; 		 ld (de),a           ; write to screen.
																											; 		 inc e               ; next screen byte.
			lda	,u								; fetch next screen byte						; 		 ld a,(de)           ; fetch screen image.
			eora	<reg_L						; merge with graphic								; 		 xor l               ; combine with graphic.
			sta	,u+							; write to screen									; 		 ld (de),a           ; write to screen.
																											; 		 inc de              ; next screen address.
			lda	,u								; fetch next screen byte						; 		 ld a,(de)           ; fetch screen image.
			eora	<reg_H						; merge with graphic								; 		 xor h               ; combine with graphic.
			sta	,u								; write to screen									; 		 ld (de),a           ; write to screen.
																											; 		 dec e               ; back to start byte.
			leau	32-2,u						; point to beginning of next row				; 		 inc d               ; increment line number.
													; no segments in 6809 Screen Map				; 		 ld a,d              ; segment address.
																											; 		 and 7               ; reached end of segment?
																											; 		 jp nz,sprit6        ; no, just do next line within cell.
																											; 		 ld a,e              ; low byte.
																											; 		 add a,32            ; look down.
																											; 		 ld e,a              ; new address.
																											; 		 jp c,sprit6         ; done.
																											; 		 ld a,d              ; high byte.
																											; 		 sub 8               ; start of segment.
																											; 		 ld d,a              ; new high byte.
Sprit6	puls	x								; restore graphic address						; sprit6 pop hl              ; restore source address.
			leax	1,x							; point to next source byte					; 		 inc hl              ; next source byte.
			lda	<reg_AF						; restore row counter							; 		 ex af,af'
			deca									; decrement it										; 		 dec a
			bne	Sprit1						; not zero, loopback								; 		 jp nz,sprit1
			rts									; return												; 		 ret
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Get room address																					; Get room address
; ------------------------------------------------------------------------------------------------------------------------------------------
GRoom		lda	<scNo							; get screen number								; groom  ld a,(scno)         ; screen number.
			pshs	a								; save in stack
GRoomX	ldu	#$0000						; value zero										; groomx ld de,0             ; start at zero.
			ldx	<scrPtr						; point to screens table						; 		 ld hl,(scrptr)      ; pointer to screens.
			tsta									; was the first room?							; 		 and a               ; is it the first one?
GRoom1	beq	GRoom0						; yes, skip no more screens					; groom1 jr z,groom0         ; no more screens to skip.
			ldd	,x++							; get screen size (16 bits)					; 		 ld c,(hl)           ; low byte of screen size.
																											; 		 inc hl              ; point to high byte.
																											; 		 ld b,(hl)           ; high byte of screen size.
																											; 		 inc hl              ; next address.
																											; 		 ex de,hl            ; put total in hl, pointer in de.
			leau	d,u							; add to regU										; 		 add hl,bc           ; skip a screen.
																											; 		 ex de,hl            ; put total in de, pointer in hl.
			dec	,s								; decrement room counter						; 		 dec a               ; one less iteration.
			bra	GRoom1						; loop back											; 		 jr groom1           ; loop until we reach the end.
GRoom0	ldx	<scrPtr						; point to screens table						; groom0 ld hl,(scrptr)      ; pointer to screens.
			tfr	u,d							; pass offset to regD
			leax	d,x							; add offset to pointer							; 		 add hl,de           ; add displacement.
			ldb	numSc							; get number of screens							; 		 ld a,(numsc)        ; number of screens.
			clra									; convert to 16 bits value						; 		 ld d,0              ; zeroise high byte.
																											; 		 ld e,a              ; displacement in de.
			leax	d,x							; skip the screens								; 		 add hl,de           ; add double displacement to address.
			leax	d,x							; length at the beginning						; 		 add hl,de
			puls	a,pc							; discard regA and return						; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Draw present room																					; Draw present room.
; ------------------------------------------------------------------------------------------------------------------------------------------
DRoom		lda	<winTop						; get top of window								; droom  ld a,(wintop)       ; window top.
			sta	<dispY						; put in Y coordinate							; 		 ld (dispx),a        ; set x coordinate.
DRoom2	ldx	<blkPtr						; point to blocks table							; droom2 ld hl,(blkptr)      ; blocks.
			stx	<grBase						; copy to variable								; 		 ld (grbase),hl      ; set graphics base.
			jsr	GRoom							; get address of current room					; 		 call groom          ; get address of current room.
			clra									; value zero										; 		 xor a               ; zero in accumulator.
			sta	<comCnt						; int compression counter						; 		 ld (comcnt),a       ; reset compression counter.
			lda	<winHgt						; get window height								; 		 ld a,(winhgt)       ; height of window.
DRoom0	pshs	a								; pass row counter into stack					; droom0 push af             ; store row counter.
			lda	<winLft						; get window left edge							; 		 ld a,(winlft)       ; window left edge.
			sta	<dispX						; put in X coordinate							; 		 ld (dispy),a        ; set cursor position.
			lda	<winWid						; get width of window							; 		 ld a,(winwid)       ; width of window.
DRoom1	pshs	a								; pass column counter into stack				; droom1 push af             ; store column counter.
			
			jsr	FlByt							; decompress next screen byte					; 		 call flbyt          ; decompress next byte on the fly.
			pshs	x								; save pointer										; 		 push hl             ; store address of cell.
			jsr	PAttr2						; show block (no attributes in 6809)		; 		 call pattr          ; show attributes and block.
			puls	x								; restore pointer									; 		 pop hl              ; restore cell address.
			puls	a								; restore column counter						; 		 pop af              ; restore loop counter.
			deca									; decrement it										; 		 dec a               ; one less column.
			bne	DRoom1						; not yet done? loop for next block			; 		 jr nz,droom1        ; repeat for entire line.
			inc	<dispY						; increment Y coordinate						; 		 ld a,(dispx)        ; x coord.
																											; 		 inc a               ; move down one line.
																											; 		 ld (dispx),a        ; set new position.
			puls	a								; restore row counter							; 		 pop af              ; restore row counter.
			deca									; decrement it										; 		 dec a               ; one less row.
			bne	DRoom0						; not yet done? loopback						; 		 jr nz,droom0        ; repeat for all rows.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Decompress bytes on-the-fly																		; Decompress bytes on-the-fly
; regX points to blocks  -  returns block in regA and repetitions in comCnt
; ------------------------------------------------------------------------------------------------------------------------------------------
FlByt		lda	<comCnt						; get compression counter						; flbyt  ld a,(comcnt)       ; compression counter.
																											; 		 and a               ; any more to decompress?
			bne	FlByt1						; if not zero, decompress and exit			; 		 jr nz,flbyt1        ; yes.
			lda	,x+							; else get a byte									; 		 ld a,(hl)           ; fetch next byte.
																											; 		 inc hl              ; point to next cell.
			cmpa	#255							; is a control code?								; 		 cp 255              ; is this byte a control code?
			bne	FlByEx						; no, exit, it is uncompressed				; 		 ret nz              ; no, this byte is uncompressed.
			lda	,x+							; get next byte									; 		 ld a,(hl)           ; fetch byte type.
			sta	<comByt						; save in variable								; 		 ld (combyt),a       ; set up the type.
																											; 		 inc hl              ; point to quantity.
			lda	,x+							; get next byte									; 		 ld a,(hl)           ; get quantity.
																											; 		 inc hl              ; point to next byte.
FlByt1	deca									; decrement byte value by one					; flbyt1 dec a               ; one less.
			sta	<comCnt						; save as number of repetitons				; 		 ld (comcnt),a       ; store new quantity.
			lda	<comByt						; get byte to be expanded						; 		 ld a,(combyt)       ; byte to expand.
FlByEx	rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Ladder down check																					; Ladder down check.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF LFLAG
LaddD		ldb	8,y																					; laddd  ld a,(ix+8)         ; x coordinate.
			andb	#254																					; 		 and 254             ; make it even.
			stb	8,y																					; 		 ld (ix+8),a         ; reset it.
			lda	9,y																					; 		 ld h,(ix+9)         ; y coordinate.
NumSp5	addb	#SPR_HGT																					; numsp5 add a,16            ; look down 16 pixels.
			std	<reg_HL																				; 		 ld l,a              ; coords in hl.
			bra	LaddV																					; 		 jr laddv
; ------------------------------------------------------------------------------------------------------------------------------------------
; Ladder up check																						; Ladder up check.
; ------------------------------------------------------------------------------------------------------------------------------------------
LaddU		ldb	8,y																					; laddu  ld a,(ix+8)         ; x coordinate.
			andb	#254																					; 		 and 254             ; make it even.
			stb	8,y																					; 		 ld (ix+8),a         ; reset it.
			lda	9,y																					; 		 ld h,(ix+9)         ; y coordinate.
NumSp6	addb	#SPR_HGT-2																					; numsp6 add a,14            ; look 2 pixels above feet.
			std	<reg_HL																				; 		 ld l,a              ; coords in hl.
LaddV		exg	a,b
			std	<dispX																					; laddv  ld (dispx),hl       ; set up test coordinates.
			jsr	TstBl																					; 		 call tstbl          ; get map address.
			jsr	LdChk																					; 		 call ldchk          ; standard ladder check.
			bne	LaddUEx																				; 		 ret nz              ; no way through.
			ldx	<reg_HL
			leax	1,x
			stx	<reg_HL																				; 		 inc hl              ; look right one cell.
			jsr	LdChk																					; 		 call ldchk          ; do the check.
			bne	LaddUEx																				; 		 ret nz              ; impassable.
			lda	<dispY																					; 		 ld a,(dispy)        ; y coordinate.
			anda	#7																						; 		 and 7               ; position straddling block cells.
			beq	LaddUEx																				; 		 ret z               ; no more checks needed.
			ldx	<reg_HL
			leax	1,x
			stx	<reg_HL																				; 		 inc hl              ; look to third cell.
			jsr	LdChk																					; 		 call ldchk          ; do the check.
LaddUEx	rts																							; 		 ret                 ; return with zero flag set accordingly.
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Can go up check																						; Can go up check.
; ------------------------------------------------------------------------------------------------------------------------------------------
CanGU		pshs	y
			ldy	<reg_IX
			ldb	8,y																					; cangu  ld a,(ix+8)         ; x coordinate.
			lda	9,y																					; 		 ld h,(ix+9)         ; y coordinate.
			subb	#2																						; 		 sub 2               ; look up 2 pixels.
			std	<reg_HL																				; 		 ld l,a              ; coords in hl.
			stb	<dispX																					; 		 ld (dispx),hl       ; set up test coordinates.
			sta	<dispY
			jsr	TstBl																					; 		 call tstbl          ; get map address.
			jsr	LRChk																					; 		 call lrchk          ; standard left/right check.
			bne	CanGUex																				; 		 ret nz              ; no way through.
			ldd	<reg_HL
			addd	#1																						; 		 inc hl              ; look right one cell.
			std	<reg_HL
			jsr	LRChk																					; 		 call lrchk          ; do the check.
			bne	CanGUex																				; 		 ret nz              ; impassable.
			lda	<dispY																					; 		 ld a,(dispy)        ; y coordinate.
			anda	#7																						; 		 and 7               ; position straddling block cells.
			beq	CanGUex																				; 		 ret z               ; no more checks needed.
			ldd	<reg_HL
			addd	#1																						; 		 inc hl              ; look to third cell.
			std	<reg_HL
			jsr	LRChk																					; 		 call lrchk          ; do the check.
CanGUex	puls	y,pc																					; 		 ret                 ; return with zero flag set accordingly.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Can go down check																					; Can go down check.
; here regX contains reg_IX
; ------------------------------------------------------------------------------------------------------------------------------------------
CanGD		pshs	y
			ldy	<reg_IX
			ldb	8,y																					; cangd  ld a,(ix+8)         ; x coordinate.
			lda	9,y																					; 		 ld h,(ix+9)         ; y coordinate.
NumSpr3
			addb	#SPR_HGT																					; numsp3 add a,16            ; look down 16 pixels.
			std	<reg_HL																				; 		 ld l,a              ; coords in hl.
			stb	<dispX																					; 		 ld (dispx),hl       ; set up test coordinates.
			sta	<dispY
			jsr	TstBl 																				; 		 call tstbl          ; get map address.
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
			bne	CanGDex																				; 		 ret nz              ; no way through.
			ldd	<reg_HL
			addd	#1																						; 		 inc hl              ; look right one cell.
			std	<reg_HL
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
			bne	CanGDex																				; 		 ret nz              ; impassable.
			lda	<dispY																					; 		 ld a,(dispy)        ; y coordinate.
			anda	#7																						; 		 and 7               ; position straddling block cells.
			beq	CanGDex																				; 		 ret z               ; no more checks needed.
			ldd	<reg_HL
			addd	#1																						; 		 inc hl              ; look to third cell.
			std	<reg_HL
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
CanGDex	puls	y,pc																					; 		 ret                 ; return with zero flag set accordingly.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Can go left check																					; Can go left check.
; ------------------------------------------------------------------------------------------------------------------------------------------
CanGL		pshs	y
			ldy	<reg_IX
			ldb	8,y																					; cangl  ld l,(ix+8)         ; x coordinate.
			lda	9,y																					; 		 ld a,(ix+9)         ; y coordinate.
			suba	#2																						; 		 sub 2               ; look left 2 pixels.
			std	<reg_HL																				; 		 ld h,a              ; coords in hl.
			bra	CanGH																					; 		 jr cangh            ; test if we can go there.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Can go right check																					; Can go right check.
; ------------------------------------------------------------------------------------------------------------------------------------------
CanGR		pshs	y
			ldy	<reg_IX
			ldb	8,y																					; cangr  ld l,(ix+8)         ; x coordinate.
			lda	9,y																					; 		 ld a,(ix+9)         ; y coordinate.
			adda	#16																					; 		 add a,16            ; look right 16 pixels.
			std	<reg_HL																				; 		 ld h,a              ; coords in hl.
CanGH		stb	<dispX																					; cangh  ld (dispx),hl       ; set up test coordinates.
			sta	<dispY
CanGh2	ldb	#(SPR_HGT/8+1)
			stb	<reg_B																				; cangh2 ld b,3              ; default rows to write.
			lda	<reg_L																				; 		 ld a,l              ; x position.
			anda	#7																						; 		 and 7               ; does x straddle cells?
			bne	CanGh0																				; 		 jr nz,cangh0        ; yes, loop counter is good.
			dec	<reg_B																				; 		 dec b               ; one less row to write.
CanGh0	jsr	TstBl																					; cangh0 call tstbl          ; get map address.
																											; 		 ld de,32            ; distance to next cell.
CanGh1	jsr	LRChk																					; cangh1 call lrchk          ; standard left/right check.
			bne	CanGRex																				; 		 ret nz              ; no way through.
			ldx	<reg_HL
			leax	32,x																					; 		 add hl,de           ; look down.
			stx	<reg_HL
			dec	<reg_B
			bne	CanGh1																				; 		 djnz cangh1
CanGRex	puls	y,pc																					; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check left/right movement is okay																; Check left/right movement is okay.
; ------------------------------------------------------------------------------------------------------------------------------------------
LRChk		lda	[reg_HL]																				; lrchk  ld a,(hl)           ; fetch map cell.
			cmpa	#WALL																					; 		 cp WALL             ; is it passable?
			beq	LRChkX																				; 		 jr z,lrchkx         ; no.
			cmpa	#FODDER																				; 		 cp FODDER           ; fodder has to be dug.
			beq	LRChkX																				; 		 jr z,lrchkx         ; not passable.
Always	clra																							; always xor a               ; report it as okay.
			rts																							; 		 ret
LRChkX	clra																							; lrchkx xor a               ; reset all bits.
			inca																							; 		 inc a
			rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check platform or solid item is not in way													; Check platform or solid item is not in way.
; ------------------------------------------------------------------------------------------------------------------------------------------
PlChk		lda	[reg_HL]																				; plchk  ld a,(hl)           ; fetch map cell.
			cmpa	#WALL																					; 		 cp WALL             ; is it passable?
			beq	LRChkX																				; 		 jr z,lrchkx         ; no.
	IF PFLAG+DFLAG
			cmpa	#FODDER																				; 		 cp FODDER           ; fodder has to be dug.
			beq	LRChkX																				; 		 jr z,lrchkx         ; not passable.
	ENDIF
			cmpa	#PLATFM																				; 		 cp PLATFM           ; platform is solid.
			beq	PlChkX																				; 		 jr z,plchkx         ; not passable.
	IF LFLAG
			cmpa	#LADDER																				; 		 cp LADDER           ; is it a ladder?
			beq	LRChkX																				; 		 jr z,lrchkx         ; on ladder, deny movement.
	ENDIF
PlChk0	clra																							; plchk0 xor a               ; report it as okay.
			rts																							; 		 ret
PlChkX	lda	<dispX																				; plchkx ld a,(dispx)        ; x coordinate.
			anda	#7																						; 		 and 7               ; position straddling blocks.
			beq	LRChkX																				; 		 jr z,lrchkx         ; on platform, deny movement.
			bra	PlChk0																				; 		 jr plchk0
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check ladder is available																		; Check ladder is available.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF LFLAG
LdChk		lda	[reg_HL]																				; ldchk  ld a,(hl)           ; fetch cell.
			cmpa	#LADDER																				; 		 cp LADDER           ; is it a ladder?
			rts																							; 		 ret                 ; return with zero flag set accordingly.
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Get collectables																					; Get collectables.
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF CFLAG
GetCol	ldb	#COLECT																				; getcol ld b,COLECT         ; collectable blocks.
			stb	<reg_B
			jsr	TDed																					; 		 call tded           ; test for collectable blocks.
			cmpa	<reg_B																				; 		 cp b                ; did we find one?
			bne	GetCEx																				; 		 ret nz              ; none were found, job done.
			bsr	GtBlk																					; 		 call gtblk          ; get block.
			jsr	Evnt20																				; 		 call evnt20         ; collected block event.
			bra	GetCol																				; 		 jr getcol           ; repeat until none left.
GetCEx	rts

; ------------------------------------------------------------------------------------------------------------------------------------------
; Get collectable block																				; Get collectable block.
; regX points to the MAP position for the Colectable block to be erased
; ------------------------------------------------------------------------------------------------------------------------------------------
GtBlk		clr	,x								; clean collectable block in map				;	gtblk  ld (hl),0           ; make it empty now.
			tfr	x,d							; pass pointer to regD							;		 ld de,MAP           ; map address.
			subd	#MAP							; subtract MAP origin							;		 and a               ; clear carry.
			pshs	d								; save cell number								;		 sbc hl,de           ; find cell number.
																											;		 ld a,l              ; get low byte of cell number.
			andb	#31							; column 0-31 (X)									;		 and 31              ; 0 - 31 is column.
			stb	<reg_E						; X coordinate										;		 ld d,a              ; store y in d register.
			ldd	,s								; get cell number														
			addd	,s								; duplicate value
			std	,s								; update into stack								;		 add hl,hl           ; multiply by 8.
			addd	,s								; double again = 4x							
			std	,s								; update into stack								;		 add hl,hl
			addd	,s++							; double again = 8x, clean stack				;		 add hl,hl           ; x is now in h.
			ldb	<reg_E						; Y-X coordinates in regD						;		 ld e,h              ; put x in e.
			stb	<dispX						; set display coordinates						;		 ld (dispx),de       ; set display coordinates.
			sta	<dispY						; but inverting bytes							;		 ld (dispx),de       ; set display coordinates.
			lda	<colPatt						; get block number								;		 ld a,(colpatt)
			asla									; multiply											;		 rlca                ; multiply char by 8.
			asla									; by													;		 rlca
			asla									; eight												;		 rlca
			tfr	a,b							; save shifted value								;		 ld e,a              ; store shift in e.
			anda	#7								; use 3 lower bits of regA (from regB)		;		 and 7               ; only want high byte bits.
																											;		 ld d,a              ; store in d.
																											;		 ld a,e              ; restore shifted value.
			andb	#%11111000					; use 5 upper bits								;		 and 248             ; only want low byte bits.
																											;		 ld e,a              ; that's the low byte.
			ldx	<blkPtr						; get graphics pointer							;		 ld hl,(blkptr)      ; address of graphics.
			leax	d,x							; add displacement								;		 add hl,de           ; add displacement.
			jsr	GPrad							; get screen address								;		 call gprad          ; get screen address.
			ldu	<grBase						; get pointer to screen							;
			ldb	#8								; rows counter
GtBl01	lda	,u								; get a char from screen						;		 ld a,(de)           ; get image byte.
			eora	,x+							; merge with block data							;		 xor (hl)
			sta	,u								; update cleaned block							;		 ld (de),a           ; copy to screen.
			leau	32,u							; point to screen row below					;		 inc hl              ; next image byte.
			decb									; decrement rows counter						;		 inc d               ; next screen row down.
			bne	GtBl01						; not done? loopback
			rts									; return												;		 ret
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Touched deadly block check																		; Touched deadly block check.
; Returns with DEADLY (must be non-zero) in accumulator if true						; Returns with DEADLY (must be non-zero) in accumulator if true.
; required block must be in reg_B
; ------------------------------------------------------------------------------------------------------------------------------------------
TDed		ldd	8,y																					; tded   ld l,(ix+8)         ; x coordinate.
			std	<dispX																				; 		 ld h,(ix+9)         ; y coordinate.
			exg	a,b							; dispX receives bytes inverted				; 		 ld (dispx),hl       ; set up test coordinates.
			std	<reg_HL
			jsr	TstBl																					; 		 call tstbl          ; get map address.
			ldu	#31																					; 		 ld de,31            ; default distance to next line down.
			stu	<reg_DE
			cmpa	<reg_B																				; 		 cp b                ; is this the required block?
			beq	TDedEx																				; 		 ret z               ; yes.
			ldx	<reg_HL
			leax	1,x																					; 		 inc hl              ; next cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch type.
			cmpa	<reg_B																				; 		 cp b                ; is this deadly/custom?
			beq	TDedEx																				; 		 ret z               ; yes.
			lda	<dispY																				; 		 ld a,(dispy)        ; horizontal position.
			sta	<reg_C																				; 		 ld c,a              ; store column in c register.
			anda	#7																						; 		 and 7               ; is it straddling cells?
			beq	TDed0																					; 		 jr z,tded0          ; no.
			leax	1,x																					; 		 inc hl              ; last cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch type.
			cmpa	<reg_B																				; 		 cp b                ; is this the block?
			beq	TDedEx																				; 		 ret z               ; yes.
			leau	-1,u																					; 		 dec de              ; one less cell to next row down.
			stu	<reg_DE
TDed0		ldd	<reg_DE
			leax	d,x																					; tded0  add hl,de           ; point to next row.
			lda	,x																						; 		 ld a,(hl)           ; fetch left cell block.
			cmpa	<reg_B																				; 		 cp b                ; is this fatal?
			beq	TDedEx																				; 		 ret z               ; yes.
			leax	1,x																					; 		 inc hl              ; next cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch type.
			cmpa	<reg_B																				; 		 cp b                ; is this fatal?
			beq	TDedEx																				; 		 ret z               ; yes.
			lda	<reg_C																				; 		 ld a,c              ; horizontal position.
			anda	#7																						; 		 and 7               ; is it straddling cells?
			beq	TDed1																					; 		 jr z,tded1          ; no.
			leax	1,x																					; 		 inc hl              ; last cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch type.
			cmpa	<reg_B																				; 		 cp b                ; is this fatal?
			beq	TDedEx																				; 		 ret z               ; yes.
TDed1		lda	<dispX																				; tded1  ld a,(dispx)        ; vertical position.
			anda	#7																						; 		 and 7               ; is it straddling cells?
			beq	TDedEx																				; 		 ret z               ; no, job done.
			ldd	<reg_DE
			leax	d,x																					; 		 add hl,de           ; point to next row.
			lda	,x																						; 		 ld a,(hl)           ; fetch left cell block.
			cmpa	<reg_B																				; 		 cp b                ; is this fatal?
			beq	TDedEx																				; 		 ret z               ; yes.
			leax	1,x																					; 		 inc hl              ; next cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch type.
			cmpa	<reg_B																				; 		 cp b                ; is this fatal?
			beq	TDedEx																				; 		 ret z               ; yes.
			lda	<reg_C																				; 		 ld a,c              ; horizontal position.
			anda	#7																						; 		 and 7               ; is it straddling cells?
			beq	TDedEx																				; 		 ret z               ; no.
			leax	1,x																					; 		 inc hl              ; last cell.
			lda	,x																						; 		 ld a,(hl)           ; fetch final type.
TDedEx	stx	<reg_HL
			rts																							; 		 ret                 ; return with final type in accumulator.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Fetch block type at (dispx, dispy)															; Fetch block type at (dispx, dispy).
; ------------------------------------------------------------------------------------------------------------------------------------------
TstBl		lda	<dispX																				; tstbl  ld a,(dispx)        ; fetch x coord.
			lsla									; to avoid bit7 being the same				; 		 rlca                ; divide by 8,
													; was asla before
			bcc	TstBl1
			ora	#1
TstBl1	lsla									; to avoid bit7 being the same				; 		 rlca                ; and multiply by 32.
													; was asla before
			bcc	TstBl2
			ora	#1
TstBl2	sta	<reg_D																				; 		 ld d,a              ; store in d.
			anda	#224							; %11100000	- mask off LOW bits				; 		 and 224             ; mask off high bits.
			sta	<reg_E																				; 		 ld e,a              ; low byte.
			lda	<reg_D																				; 		 ld a,d              ; restore shift result.
			anda	#3								; %00000011 - mask off HIGH bits				; 		 and 3               ; high bits.
			sta	<reg_D																				; 		 ld d,a              ; got displacement in de.
			lda	<dispY																				; 		 ld a,(dispy)        ; y coord.
			rora																							; 		 rra                 ; divide by 8.
			rora																							; 		 rra
			rora																							; 		 rra
			anda	#31																					; 		 and 31              ; only want 0 - 31.
			adda	<reg_E																				; 		 add a,e             ; add to displacement.
			sta	<reg_E																				; 		 ld e,a              ; displacement in de.
			ldx	#MAP																					; 		 ld hl,MAP           ; position of dummy screen.
			ldd	<reg_DE																				; 		 add hl,de           ; point to address.
			leax	d,x																					
			stx	<reg_HL
			lda	,x																						; 		 ld a,(hl)           ; fetch byte there.
			rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Jump - if we can.
																											; Requires initial speed to be set up in accumulator prior to call.
; ------------------------------------------------------------------------------------------------------------------------------------------
Jump		nega																							; jump   neg                 ; switch sign so we jump up.
			sta	<reg_C																				; 		 ld c,a              ; store in c register.
																											; ;       ld a,(ix+8)         ; x coordinate.
																											; ;       ld h,(ix+9)         ; y coordinate.
																											; ;numsp4 add a,16            ; look down 16 pixels.
																											; ;       ld l,a              ; coords in hl.
																											; ;       and 7               ; are we on platform boundary?
																											; ;       ret nz              ; no, cannot jump.
																											; ;       ld (dispx),hl       ; set up test coordinates.
																											; ;       ld b,a              ; copy to b register.
																											; ;       call tstbl          ; get map address.
																											; ;       call plchk          ; block, platform check.
																											; ;       jr nz,jump0         ; it's solid, we can jump.
																											; ;       inc hl              ; look right one cell.
																											; ;       call plchk          ; block, platform check.
																											; ;       jr nz,jump0         ; it's solid, we can jump.
																											; ;       ld a,b              ; y coordinate.
																											; ;       and 7               ; position straddling block cells.
																											; ;       ret z               ; no more checks needed.
																											; ;       inc hl              ; look to third cell.
																											; ;       call plchk          ; block, platform check.
																											; ;       ret z               ; not solid, don't jump.
Jump0		lda	13,y
																											; jump0  ld a,(ix+13)        ; jumping flag.
																											; 		 and a               ; is it set?
			bne	JumpEx																				; 		 ret nz              ; already in the air.
			inc	13,y																					; 		 inc (ix+13)         ; set it.
			lda	<reg_C																				; 		 ld (ix+14),c        ; set jump height.
			sta	14,y
JumpEx	rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
Hop		tst	13,y																					; hop    ld a,(ix+13)        ; jumping flag.
																											; 		 and a               ; is it set?
			bne	HopEx																					; 		 ret nz              ; already in the air.
			ldd	#$ff00																				; 		 ld (ix+13),255      ; set it.
			std	13,y																					; 		 ld (ix+14),0        ; set jump table displacement.
HopEx		rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Random numbers code.
																											; Pseudo-random number generator, 8-bit.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR SHRAPNEL - #06 - DONE
Random	
																											; random ld hl,seed          ; set up seed pointer.
																											; 		 ld a,(hl)           ; get last random number.
																											; 		 ld b,a              ; copy to b register.
																											; 		 rrca                ; multiply by 32.



																											; 		 rrca



																											; 		 rrca



																											; 		 xor 31
																											; 		 add a,b
																											; 		 sbc a,255
																											; 		 ld (hl),a           ; store new seed.
																											; 		 ld (varrnd),a       ; return number in variable.
			lda	<seed
			beq	doEor
			lsla
			beq	noEor
			bcc	noEor
doEor		eora	#$1d
noEor		sta	<seed
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Keyboard test routine. 																			; Keyboard test routine.
; ------------------------------------------------------------------------------------------------------------------------------------------
KTest		sta	$ff02							; send to keyboard								; ktest  ld c,a              ; key to test in c.
			lda	$ff00							; read rows											; 		 and 7               ; mask bits d0-d2 for row.
			ldb	<scanOff						; get offset to codes							; 		 inc a               ; in range 1-8.
			bita	b,x							; is that bit zero (key pressed)?			; 		 ld b,a              ; place in b.
			bne	ScanK01						; no, clear carry									; 		 srl c               ; divide c by 8
			orcc	#%00000001					; yes, set carry									; 		 srl c               ; to find position within row.
			rts									; return												; 		 srl c
ScanK01	andcc	#%11111110					; reset carry flag								; 		 ld a,5              ; only 5 keys per row.
																											; 		 sub c               ; subtract position.
																											; 		 ld c,a              ; put in c.
																											; 		 ld a,254            ; high byte of port to read.
																											; ktest0 rrca                ; rotate into position.
																											; 		 djnz ktest0         ; repeat until we've found relevant row.
																											; 		 in a,(254)          ; read port (a=high, 254=low).
																											; ktest1 rra                 ; rotate bit out of result.
																											; 		 dec c               ; loop counter.
																											; 		 jp nz,ktest1        ; repeat until bit for position in carry.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Joystick and keyboard reading routines (Joystick if regA=1, else Keyboard) 		; Joystick and keyboard reading routines
; ------------------------------------------------------------------------------------------------------------------------------------------
JoyKey	lda	<contrl						; get kind of control							; joykey ld a,(contrl)       ; control flag.
			deca									; is it 1?											; 		 dec a               ; is it the keyboard?
			beq	JoyJoy						; yes, process Joystick							; 		 jr z,joyjoy         ; no, it's Kempston joystick.
													; only one kind of Joystick					; 		 dec a               ; Sinclair?
																											; 		 jr z,joysin         ; read Sinclair joystick.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; Keyboard controls.																					; Keyboard controls.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			ldb	#7								; number of keys to be read
			pshs	b								; pshs counter
			ldx	#keys+6+1					; point to last key in table					; 		 ld hl,keys+6        ; address of last key.
JoyNoCC	clr	<reg_E						; reset bits in output register				; 		 ld e,0              ; zero reading.
																											; 		 ld d,7              ; keys to read.
JoyKe0	lda	,-x							; get value from table							; joyke0 ld a,(hl)           ; get key from table.
			bsr	KTest																					; 		 call ktest          ; being pressed?
		 	rol	<reg_E						; shift into output register																											; 		 ccf                 ; complement the carry.
																											; 		 rl e                ; rotate into reading.
			dec	,s								; done all keys?									; 		 dec d               ; one less to do.
			bne	JoyKe0						; no, loopback										; 		 jp nz,joyke0        ; repeat for all keys.
			leas	1,s							; get rid of counter
			bra	JoyJo1						; go store value									; 		 jr joyjo1           ; store the value.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; This table is added by the compiler at the end of the user code. Here just for help
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;					 P	  O	A	 Q	 spc  Z	 I	  1	2	 3	  4
;keys		fcb	$fe,$7f,$fd,$fd,$7f,$fb,$fd,$fd,$fb,$f7,$ef		; mask to the keyboard columns (only one zero)
;keysD	fcb	$10,$08,$04,$10,$20,$20,$08,$01,$01,$01,$01		; expected bit to be zero (Dragon)
;keysC	fcb	$04,$02,$01,$04,$08,$08,$02,$10,$10,$10,$10		; expected bit to be zero (CoCo)
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; Joystick controls	- special for 6809 machines (using 6 bit DAC)
; besides the 2 axis (UD, LR) and button, KEYS 'Z' and 'I' must be checked
; defines three zones: UP or LEFT  	 (00-07) - 12,5%
;							  NEUTRAL    	 (08-55) - 75%
;							  DOWN or RIGHT (56-63) - 12,5% 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
LeftJoy	equ	$015e							; first byte past Left joystick variables
MaskLB	equ	$02
												; fills variables $015c-$015d (X - Y axis left joystick)
JoyJoy	lbsr	AudiOff						; turn off audio
			ldx	#LeftJoy						; point to end of left joystick table
			ldb	#$03							; bits to read left joystick axis
			stb	<readVar						; save as counter too
RdJyAx	bsr	MuxBits						; set both bits
			ldb	#55*4							; looking for 56 or greater
			stb	$ff20							; send 'start' to DAC
			tst	$ff00							; read data from joystick
			bmi	SetVal63						; data sent too low, so use maxValue
			ldb	#07*4							; looking for 7 or lower
			stb	$ff20							; send 'start' to DAC
			tst	$ff00							; read data from joystick
			bpl	SetVal00						; data sent equal or too high, so use minValue
SetVal32	ldb	#32							; else asume center value (no move)
			bra	RdSame						; go use it
SetVal00	clrb									; get minimum value
			bra	RdSame						; go use it
SetVal63	ldb	#63							; get maximum value
RdSame	stb	,-x							; save value in table
			dec	<readVar						; number of axis
			ldb	<readVar						; get value
			cmpb	#1								; already done both axis?
			bne	RdJyAx						; no, do next one
			clr	$ff20							; avoid sound spikes
			clrb									; set bits to zero
			bsr	MuxBits						; select Audio DAC channel
			bsr	AudiOn						; set audio on again
			clr	<reg_E						; result to zero
												; process special keys 'I','Z'
			ldx	#keys+6						; point to values table
			lda	,x								; get column value for 'I' (64)
			bsr	KTest							; test for it
		 	rol	<reg_E						; shift into output register
		 	lda	,-x							; get colun value for 'Z' (32)
			bsr	KTest							; test for it
		 	rol	<reg_E						; shift into output register
		 										; process button 
			andcc	#%11111110					; clear carry
			lda	$ff00							; is button of right Joystick pressed (16)?
			bita	#MaskLB						; bit1 is the value (0=YES)
			bne	PutButt						; not pressed
			orcc	#%00000001					; set carry (button is pressed)
PutButt	rol	<reg_E						; shift into output register
												; process 2 axis
JoyAxis	lda	>LeftJoy-1					; get Y axis value
			cmpa	#8								; is it move Up?
			rol	<reg_E						; puts 1 if it was up (08)
			lda	#55							; is it Down?
			cmpa	>LeftJoy-1					; compare to Y axis
			rol	<reg_E						; puts 1 if it was down (04)
			lda	>LeftJoy-2					; get X axis value
			cmpa	#8								; is it move Left?
			rol	<reg_E						; puts 1 if it was right (02)
			lda	#55							; is it move Right?
			cmpa	>LeftJoy-2					; compare to X axis
			rol	<reg_E						; puts 1 if it was right (01)
JoyJo1	lda	<reg_E						; get result							
JoyJo2	sta	<joyVal						; save into variable								
			rts									; return												
; ------------------------------------------------------------------------------
; INPUT: two lower bits in regB -> mutiplex bits									
; ------------------------------------------------------------------------------
MuxBits	ldu	#$ff01						; point to PIA0 CRA
			bsr	MuxB01						; set/reset CA2
MuxB01	lda	,u								; get value from CRA - CRB
			anda	#$f7							; set to zero CA2 - CB2
			rorb									; send bit to carry
			bcc	MuxB02						; not set?
			ora	#8								; set to 1 CA2 - CB2
MuxB02	sta	,u++							; save value, point to CRB
			rts									; return
; ------------------------------------------------------------------------------
AudiOff	clra									; bit 3 of ACCA = 0 disable analog MUX
			fcb	$8c							; skip next
AudiOn	lda	#8								; bit 3 of ACA = 1 enable analog MUX
			sta	,-s							; save on stack
			lda	$ff23							; get ctrl register of PIA1 side-B
			anda	#$f7							; reset bit 3
			ora	,s+							; set desired status
			sta	$ff23							; update PIA
			rts
; ------------------------------------------------------------------------------
;													; NOT USED FOR 6809								; Kempston joystick controls.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;																											; joyjoy ld bc,31            ; port for Kempston interface.
;																											; 		 in a,(c)            ; read it.
;																											; joyjo3 ld e,a              ; copy to e register.
;																											; 		 ld a,(keys+5)       ; key six.
;																											; 		 call ktest          ; being pressed?
;																											; 		 jr c,joyjo0         ; not pressed.
;																											; 		 set 5,e             ; set bit d5.
;																											; joyjo0 ld a,(keys+6)       ; key seven.
;																											; 		 call ktest          ; being pressed?
;																											; 		 jr c,joyjo1         ; not pressed.
;																											; 		 set 6,e             ; set bit d6.
;																											; joyjo1 ld a,e              ; copy e register to accumulator.
;																											; joyjo2 ld (joyval),a       ; remember value.
;																											; 		 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
; 													; NOT USED FOR 6809								; Sinclair joystick controls.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;																											; joysin ld bc,61438         ; port for Sinclair 2.
;																											; 		 in a,(c)            ; read joystick.
;																											; 		 ld d,a              ; clear values.
;																											; 		 xor a               ; clear accumulator.
;																											; 		 ld e,16             ; Kempston fire bit value.
;																											; 		 bit 0,d             ; fire bit pressed?
;																											; 		 call z,joysi0       ; add bit.
;																											; 		 ld e,1              ; Kempston bit value.
;																											; 		 bit 3,d             ; fire bit pressed?
;																											; 		 call z,joysi0       ; add bit.
;																											; 		 ld e,2              ; Kempston bit value.
;																											; 		 bit 4,d             ; fire bit pressed?
;																											; 		 call z,joysi0       ; add bit.
;																											; 		 ld e,8              ; Kempston bit value.
;																											; 		 bit 1,d             ; fire bit pressed?
;																											; 		 call z,joysi0       ; add bit.
;																											; 		 ld e,4              ; Kempston bit value.
;																											; 		 bit 2,d             ; fire bit pressed?
;																											; 		 call z,joysi0       ; add bit.
;																											; 		 jr joyjo3           ; read last 2 keys a la Kempston.
;																											; joysi0 add a,e           ; add bit value.
;																											; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display message																						; Display message
; Input:  regA = message number
; ------------------------------------------------------------------------------------------------------------------------------------------
Dmsg																										; ;dmsg   ld hl,nummsg     ; total messages.
																											; ;       cp (hl)          ; does this one exist?
																											; ;       ret nc           ; no, nothing to display.
	 		ldx	#msgDat						; point to messages table						; dmsg   ld hl,msgdat      ; pointer to messages.
	 		jsr	GetWrd						; get word											; 		 call getwrd         ; get message number.
Dmsg3		jsr	PrePrt						; pre-printing stuff								; dmsg3  call preprt       ; pre-printing stuff.
			jsr	CheckX						; make sure we're in a printable range		; 		 call checkx         ; make sure we're in a printable range.
			lda	<prtMod						; get print mode									; 		 ld a,(prtmod)       ; print mode.
																											; 		 and a               ; standard size?
			bne	Bmsg1							; if not zero, go double-height text		; 		 jp nz,bmsg1         ; no, double-height text.
Dmsg0		pshs	x								; save string pointer in stack				; dmsg0  push hl             ; store string pointer.
			lda	,x								; fetch byte to display							; 		 ld a,(hl)           ; fetch byte to display.
			anda	#127							; remove any end marker							; 		 and 127             ; remove any end marker.
			cmpa	#13							; is Intro?											; 		 cp 13               ; newline character?
			beq	Dmsg1							; yes, go for next row							; 		 jr z,dmsg1
			jsr	PChar							; display character								; 		 call pchar          ; display character.
																											; 		 call gaadd          ; get attribute address.
																											; 		 ld a,(23693)        ; current cell colours.
																											; 		 ld (hl),a           ; write to attribute cell.
			jsr	NexPos 						; next display position							; 		 call nexpos         ; display position.
			bne	Dmsg2							; if not on a new line skip next				; 		 jr nz,dmsg2         ; not on a new line.
			jsr	NexLin						; next line down									; 		 call nexlin         ; next line down.
Dmsg2		puls	x								; restore pointer									; dmsg2  pop hl
																											; 		 ld a,(hl)           ; fetch last character.
			lda 	,x								; fetch last character.							; 		 rla                 ; was it the end?
			lbmi 	Dscor2						; if it is the end, exit						; 		 jp c,dscor2         ; yes, job done.
			leax	1,x							; next character to display					; 		 inc hl              ; next character to display.
			bra 	Dmsg0							; go process it									;		 jr dmsg0
Dmsg1		inc	<dispY						; increment to next line						; dmsg1  ld hl,dispx         ; x coordinate.
			lda	<dispY						; get line pos										; 		 inc (hl)            ; newline.
			cmpa	#24							; is it last one?									; 		 ld a,(hl)           ; fetch position.
			bcs	Dmsg4							; no, skip next									; 		 cp 24               ; past screen edge?
			clr	<dispY						; yes, set 1st row								; 		 jr dmsg2
																											; 		 ld (hl),0           ; restart at top.
Dmsg4		clr	<dispX						; set first column								; dmsg4  inc hl              ; y coordinate.
																											; 		 ld (hl),0           ; carriage return.
			bra	Dmsg2							; process next char								;      jr dmsg2
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display message in BIG text																		; Display message in BIG text
; Input: regX = string pointer
; ------------------------------------------------------------------------------------------------------------------------------------------
Bmsg1		pshs	x
			lda	,x 							; get character to display						; bmsg1  ld a,(hl)           ; get character to display.
			anda	#127							; remove any end marker							; 		 push hl             ; store pointer to message.
			cmpa	#13							; is Intro?											; 		 and 127             ; only want 7 bits.
			beq	Bmsg2							; yes, go for next row							; 		 cp 13               ; newline character?
			jsr	Bchar 						; display big char								; 		 jr z,bmsg2
																											; 		 call bchar          ; display big char.
Bmsg3		puls	x
			lda	,x+ 							; fetch last character							; bmsg3  pop hl              ; retrieve message pointer.
			bpl	Bmsg1							; if not terminator flag, loopback			; 		 ld a,(hl)           ; look at last character.
																											; 		 inc hl              ; next character in list.
																											; 		 rla                 ; was terminator flag set?
																											; 		 jr nc,bmsg1         ; no, keep going.
			rts									; return												; 		 ret
Bmsg2		clr	<dispX						; column zero										; bmsg2  ld hl,charx         ; x coordinate.
			inc	<dispY						; add two											; 		 inc (hl)            ; newline.
			inc	<dispY						; rows												; 		 inc (hl)            ; newline.
			lda	<dispY						; get value											; 		 ld a,(hl)           ; fetch position.
			cmpa	#23  							; past screen end?								; 		 cp 23               ; past screen edge?
			bcs	Bmsg3							; no, go for next char							; 		 jr c,bmsg3          ; no, it's okay.
			clr	<dispY						; go first row										; 		 ld (hl),0           ; restart at top.
																											; 		 inc hl              ; y coordinate.
																											; 		 ld (hl),0           ; carriage return.
			bra	Bmsg3							; go for next char								; 		 jr bmsg3
; ------------------------------------------------------------------------------------------------------------------------------------------
; Big character display.																			; Big character display.
; Input: regA = character
; ------------------------------------------------------------------------------------------------------------------------------------------
Bchar		pshs	x
			ldb	#8								; to multiply by 8								; 		 rlca
			mul									; calculate offset 16 bits						; 		 rlca
			ldu	<fontPtr						; get font table beginning						; 		 ld e,a              ; store shift in e.
			leau	d,u							; add offset										; 		 and 7               ; only want high byte bits.
			jsr	GPrad							; get screen address.							; 		 ld d,a              ; store in d.
			ldx	<grBase						; point to screen (destination)				; 		 ld a,e              ; restore shifted value.
			ldb	#8								; lines to write									; 		 and 248             ; only want low byte bits.
Bchar0	lda	,u+							; get char row byte								; 		 ld e,a              ; that's the low byte.
			
	IF GFLAG
			anda	<andeor
			eora	<andeor+1
	ENDIF

			sta	,x								; put on screen									; 		 ld hl,(23606)       ; address of font.
			sta	32,x							; and on next row									; 		 add hl,de           ; add displacement.
			leax	64,x							; point two rows below							; 		 call gprad          ; get screen address.
			decb									; decrement counter								; 		 ex de,hl            ; font in de, screen address in hl.
			bne	Bchar0						; not done? loopback								; 		 ld b,8              ; height of character in font.
																											; bchar0 ld a,(de)           ; get a bit of the font.
																											; 		 inc de              ; next line of font.
																											; 		 ld (hl),a           ; write to screen.	
																											; 		 inc h               ; down a line.	
																											; 		 ld (hl),a           ; write to screen.	
																											; 		 call nline          ; next line down.	
																											; 		 djnz bchar0         ; repeat.	
																											; 		 call gaadd          ; get attribute address.
																											; 		 ld a,(23693)        ; current colour.
																											; 		 ld (hl),a           ; set attribute.
																											; 		 ld c,a              ; copy colour to c.
																											; 		 ld de,32            ; distance to next line.
																											; 		 add hl,de           ; point to second cell.
																											; 		 ld a,h              ; high byte of address.
																											; 		 cp 91               ; past edge of screen?
																											; 		 jr nc,bchar1        ; yes, don't write to printer buffer/sysvars.
																											; 		 ld (hl),c           ; set second cell's attributes.
Bchar1	jsr	NexPos						; display position.								; bchar1 call nexpos         ; display position.
			bne	Bchar2 						; not on a new line.								; 		 jp nz,bchar2        ; not on a new line.
Bchar3	inc	<dispY						; increment Y										; bchar3 inc (hl)            ; newline.
			jsr	NexLin 						; next line check									; 		 call nexlin         ; next line check.
Bchar2	puls	x
			jmp	Dscor2						; exit												; bchar2 jp dscor2           ; tidy up line and column variables.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display a character																				; Display a character.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED for CHR COMMAND
AChar		pshs	x								; it is pulled on BChar exit					; achar  ld b,a            ; copy to b.
			sta	<reg_B																				; 		 call preprt         ; get ready to print.
			jsr	PrePrt																				; 		 ld a,(prtmod)       ; print mode.
			lda	<reg_B																				; 		 and a               ; standard size?
			tst	<prtMod																				; 		 ld a,b              ; character in accumulator.
			bne	Bchar																					; 		 jp nz,bchar         ; no, double-height text.
			jsr	PChar																					; 		 call pchar          ; display character.
													; no 													; 		 call gaadd          ; get attribute address.
													; colours											; 		 ld a,(23693)        ; current cell colours.
													; here												; 		 ld (hl),a           ; write to attribute cell.
			bsr	NexPos																				; 		 call nexpos         ; display position.
			beq	Bchar3																				; 		 jp z,bchar3         ; next line down.
			bra	Bchar2																				; 		 jp bchar2           ; tidy up.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get next print column position.																; Get next print column position.
; ------------------------------------------------------------------------------------------------------------------------------------------
NexPos	inc	<dispX						; move along one position						; nexpos ld hl,dispy         ; display position.
			lda	<dispX 						; get coordinate									; 		 ld a,(hl)           ; get coordinate.
																											; 		 inc a               ; move along one position.
																											; 		 and 31              ; reached edge of screen?
																											; 		 ld (hl),a           ; set new position.
																											; 		 dec hl              ; point to x now.
			rts 									; return with status in zero flag			; 		 ret                 ; return with status in zero flag.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get next print line position.																	; Get next print line position.
; ------------------------------------------------------------------------------------------------------------------------------------------
NexLin	lda	<dispY 						; get vertical position							; nexlin inc (hl)            ; newline.
			inca									; increment											; 		 ld a,(hl)           ; vertical position.
			cmpa	#24							; past screen edge?								; 		 cp 24               ; past screen edge?
			bcs	NL01							; no, exit updating								; 		 ret c               ; no, still okay.
			clra									; restart at top.									; 		 ld (hl),0           ; restart at top.
NL01		sta	<dispY						; update variable									; 		 ret
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; Pre-print preliminaries.																			; Pre-print preliminaries.
; ------------------------------------------------------------------------------------------------------------------------------------------
PrePrt	ldd	<fontPtr						; get font pointer.								; preprt ld de,(23606)       ; font pointer.
			std	<grBase						; put into graphics base.						; 		 ld (grbase),de      ; set up graphics base.
Prescr	ldd	<charX 						; get display coordinates.						; prescr ld de,(charx)       ; display coordinates.
			std	<dispX						; update general coordinates.			 		; 		 ld (dispx),de       ; set up general coordinates.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Return message pointer in regX
; Input: regX = pointer to message list beginning 											; On entry: hl points to word list
;  		regA = message number 																	;           a contains word number.
; ------------------------------------------------------------------------------------------------------------------------------------------
GetWrd	tsta									; first message?									; getwrd and a               ; first word in list?
			beq	GetWd1						; yes, exit											; 		 ld b,a
																											; getwd0 ld a,(hl)
GetWd0	tst	,x+							; found end?			 							; 		 inc hl
			bpl 	GetWd0						; no, carry on										; 		 cp 128              ; found end?
			deca									; decrement mesg counter		 				; 		 jr c,getwd0         ; no, carry on.
			bne 	GetWd0						; not done? loop									; 		 djnz getwd0         ; until we have right number.
GetWd1	rts									; return												;      ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Process sprites																						; Process sprites.
; ------------------------------------------------------------------------------------------------------------------------------------------
PSpr		ldb 	#NUMSPR						; number of sprites to precess (12)			; pspr   ld b,NUMSPR         ; sprites to process.
			ldx	#sprTab						; point to sprite table beginning			; 		 ld ix,sprtab        ; sprite table.
			pshs	b								; save counter										; pspr1  push bc             ; store loop counter for now.
PSpr1		lda	,x								; get sprite type									; 		 ld a,(ix+0)         ; fetch sprite type.
			cmpa	#9								; less than 9?										; 		 cp 9                ; within range of sprite types?
			bcc	PSprNo						; no, skip next
			jsr	PSpr2							; process that sprite							; 		 call c,pspr2        ; yes, process this one.
PSprNo																									; 		 ld de,TABSIZ        ; distance to next odd/even entry.
			leax	TABSIZ,x						; point to next sprite entry					; 		 add ix,de           ; next sprite.
			dec	,s								; decrement counter								; 		 pop bc              ; retrieve loop counter.
			bne	PSpr1							; not zero? try this one						; 		 djnz pspr1          ; repeat for remaining sprites.
			leas	1,s							; clean stack
			rts									; return												; 		 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
PSpr2		stx	<ogPtr						; save pointer										; pspr2  ld (ogptr),ix       ; store original sprite pointer.
			stx	<reg_IX
			jsr	PSpr3							; execute the proper routine					; 		 call pspr3          ; do the routine.
RtOrg		ldx	<ogPtr						; restore pointer									; rtorg  ld ix,(ogptr)       ; restore original pointer to sprite.
RtOrg0	rts									; return												; rtorg0 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
PSpr3		ldx	#EvTyp0						; point to sprite's events list				; pspr3  ld hl,evtyp0        ; sprite type events list.
PSpr4		asla									; calculate offset in table					; pspr4  add a,a             ; double accumulator.
																											; 		 ld e,a              ; copy to de.
																											; 		 ld d,0              ; no high byte.
																											; 		 add hl,de           ; point to address of routine.
																											; 		 ld e,(hl)           ; address low.
																											; 		 inc hl              ; next byte of address.
																											; 		 ld d,(hl)           ; address high.
			ldy	<reg_IX																				; 		 ex de,hl            ; swap address into hl.
			jmp	[a,x]							; jump to calculated routine					; 		 jp (hl)             ; go there.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
																											; Address of each sprite type's routine.
EvTyp0	fdb	Evnt00						; defined by game designer						; evtyp0 defw evnt00
EvTyp1	fdb	Evnt01						; defined by game designer						; evtyp1 defw evnt01
EvTyp2	fdb	Evnt02						; defined by game designer						; evtyp2 defw evnt02
EvTyp3	fdb	Evnt03						; defined by game designer						; evtyp3 defw evnt03
EvTyp4	fdb	Evnt04						; defined by game designer						; evtyp4 defw evnt04
EvTyp5	fdb	Evnt05						; defined by game designer						; evtyp5 defw evnt05
EvTyp6	fdb	Evnt06						; defined by game designer						; evtyp6 defw evnt06
EvTyp7	fdb	Evnt07						; defined by game designer						; evtyp7 defw evnt07
EvTyp8	fdb	Evnt08						; defined by game designer						; evtyp8 defw evnt08
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display sprites																						; Display sprites.
; regX takes the rol of IX
; ------------------------------------------------------------------------------------------------------------------------------------------
DSpr		stx	<reg_IX
			ldb	#NUMSPR/2					; number of sprites to display				; dspr   ld b,NUMSPR/2       ; number of sprites to display.
DSpr0		pshs	b								; save counter										; dspr0  push bc             ; store loop counter for now.
			lda	,x								; get a sprite byte								; 		 ld a,(ix+0)         ; get sprite type.
			inca									; is it enabled?									; 		 inc a               ; is it enabled?
			bne	DSpr1							; yes, needs deleting							; 		 jr nz,dspr1         ; yes, it needs deleting.
DSpr5		lda	5,x							; get new type value								; dspr5  ld a,(ix+5)         ; new type.
			inca									; is it enabled?									; 		 inc a               ; is it enabled?
			bne	DSpr3							; yes, needs drawing								; 		 jr nz,dspr3         ; yes, it needs drawing.
DSpr2		ldx	<reg_IX																				; dspr2  push ix             ; put ix on stack.
																											; 		 pop hl              ; pop into hl.
																											; 		 ld e,l              ; copy to de.
																											; 		 ld d,h
																											; ;dspr2  ld e,ixl            ; copy ix to de.
																											; ;       ld d,ixh
																											; ;       ld l,e              ; copy to hl.
																											; ;       ld h,d
													; copy 5 bytes from new to old				; 		 ld bc,5             ; distance to new type.
			ldd	5,x							; get new type and image						; 		 add hl,bc           ; point to new properties.
			std	,x								; copy to old positions							; 		 ldi                 ; copy to old positions.
			ldd	7,x							; get new frame and pos Y
			std	2,x							; to old
			lda	9,x							; and pos X
			sta	4,x							; to old
			ldb	#TABSIZ*2					; to skip over two sprites						; 		 ld c,TABSIZ*2       ; distance to next odd/even entry.
			leax	b,x							; point to next odd/even sprite				; 		 add ix,bc           ; next sprite.
			stx	<reg_IX						; update pseudo register
			puls	b								; restore counter									; 		 pop bc              ; retrieve loop counter.
			decb									; decrement
			bne	DSpr0							; not zero, loopback								; 		 djnz dspr0          ; repeat for remaining sprites.
			rts									; return												; 		 ret
																											; ;dspr1  ld a,(ix+3)         ; old x coord.
																											; ;       cp 177              ; beyond maximum?
																											; ;       jr nc,dspr5         ; yes, don't delete it.
DSpr1		lda	5,x							; get new type										; dspr1  ld a,(ix+5)         ; type of new sprite.
			inca									; is it enabled?									; 		 inc a               ; is this enabled?
			bne	DSpr4							; yes, display both								; 		 jr nz,dspr4         ; yes, display both.
DSpr6		jsr	SSpriA						; show a single sprite							; dspr6  call sspria         ; show single sprite.
			bra	DSpr2							; loopback											; 		 jp dspr2
; ------------------------------------------------------------------------------------------------------------------------------------------
; Displaying two sprites.  Don't bother redrawing if nothing has changed			; Displaying two sprites.  Don't bother redrawing if nothing has changed.
; ------------------------------------------------------------------------------------------------------------------------------------------
DSpr4		ldd	3,x							; get Y and X old Pos							; dspr4  ld a,(ix+4)         ; old y.
			cmpd	8,x							; are equal to new  Y and X?					; 		 cp (ix+9)           ; compare with new value.
			bne	DSpr7							; no, need to redraw								; 		 jr nz,dspr7         ; they differ, need to redraw.
																											; 		 ld a,(ix+3)         ; old x.
																											; 		 cp (ix+8)           ; compare against new value.
																											; 		 jr nz,dspr7         ; they differ, need to redraw.

			ldd	1,x							; get old imagea and frame						; 		 ld a,(ix+2)         ; old frame.
			cmpd	6,x							; are equal to new ones?						; 		 cp (ix+7)           ; compare against new value.
																											; 		 jr nz,dspr7         ; they differ, need to redraw.
																											; 		 ld a,(ix+1)         ; old image.
																											; 		 cp (ix+6)           ; compare against new value.
			beq	DSpr2							; yes, so NO redrawing							; 		 jp z,dspr2          ; everything is the same, don't redraw.
DSpr7		jsr	SSpriC						; delete old, draw new							; dspr7  call sspric         ; delete old sprite, draw new one simultaneously.
			bra	DSpr2							; loopback											; 		 jp dspr2
DSpr3		stx	<reg_IX
			jsr	SSpriB						; draw a single sprite							; dspr3  call ssprib         ; show single sprite.
			bra	DSpr2							; loopback											; 		 jp dspr2
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get sprite address calculations																; Get sprite address calculations.
; gspran = new sprite, gsprad = old sprite													; gspran = new sprite, gsprad = old sprite.
; regX = IX
; ------------------------------------------------------------------------------------------------------------------------------------------
GSprAN	ldu	<reg_IX						; regU=IX
			ldb	8,u							; get new coordinates							; gspran ld l,(ix+8)         ; new x coordinate.
			lda	9,u							; inverted											; 		 ld h,(ix+9)         ; new y coordinate.
			std	<dispX						; put into variables								; 		 ld (dispx),hl       ; set display coordinates.
			lda	6,u							; get new image									; 		 ld a,(ix+6)         ; new sprite image.
			jsr	GFrm							; fetch start frame in regX					; 		 call gfrm           ; fetch start frame for this sprite.
			lda	,x								; get frame											; 		 ld a,(hl)           ; frame in accumulator.
			adda	7,u							; add new frame									; 		 add a,(ix+7)        ; new add frame number.
			bra	GSprA0						; skip section										; 		 jp gspra0
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF RFLAG										; if REDUCED SPRITES
; ------------------------------------------------------------------------------------------------------------------------------------------
; Calculate old sprite address																	; Calculate old sprite address
; Input:																									; Input:
;  regX must arrive as IX (sprite address)													;  IX = sprite address
; Output:																								; Output:
; 																											;  B  = right byte mask
; returns reg_BC = right-left byte mask 														;  C  = left byte mask
;  		 reg_DE = spriteframe address															;  DE = spriteframe address
;         reg_HL (regX) = screenaddress(dispx,dispy) via ScAdd							;  scraddr = screenaddress(dispx,dispy)
; ------------------------------------------------------------------------------------------------------------------------------------------
GSprAd	leau	,x								; regU takes the rol of reg_IX				; gsprad:
			stu	<reg_IX						; save reg_IX for later use					; 	ldy #var_Y
			ldd	3,u							; get old posXY									; 	lda (z80_ix),y			; y coordinate.
			sta	<dispY						; put into											; 	sta dispy
																											; 	ldy #var_X
																											; 	lda (z80_ix),y			; x coordinate.
			stb	<dispX						; variables											; 	sta dispx
																											; 	ldy #var_Image
			lda	1,u							; get old image									; 	lda (z80_ix),y 		; sprite image.
			jsr	GFrm							; fetch start frame in regX					; 	jsr gfrm 				; fetch start frame for this sprite.
																											; 	ldy #0
			lda	,x								; get frame											; 	lda (z80_hl),y 		; frame in accumulator.
																											; 	ldy #var_Frame
																											; 	clc
			adda	2,u							; add old frame									; 	adc (z80_ix),y 		; add frame number.
GSprA0																									; gspra0:
	IF BFLAG										; reg_DE = reg_AF is frame*48 or 32			; .if 0
			ldb	#48							; multiply by 192/4 (shiftTables)			; 	lsr a	  					; multiply by 128.
	ELSE																									; 	sta z80_d 				; store in d.
			ldb	#32							; multiply by 128/4 (shiftTables)			; 	lda #0	
	ENDIF																									; 	ror a
			mul									; multiply. Result in reg_D					; 	sta z80_e 				; got low byte.
																											; .else
																											; 	sta z80_e
																											; 	lda #0
																											; 	sta z80_d
																											; 	asl z80_e
																											; 	rol z80_d
																											; 	asl z80_e
																											; 	rol z80_d
																											; 	asl z80_e
																											; 	rol z80_d
																											; 	asl z80_e
																											; 	rol z80_d
																											; 	asl z80_e
																											; 	rol z80_d
																											; .endif
																											; 	clc 						; address of play sprites.
																											; 	lda z80_e
			ldx	#sprGfx							; point to sprites data beginning		; 	adc #<sprgfx
			leax	d,x								; point to right frame						; 	sta z80_e
																											; 	lda z80_d
																											; 	adc #>sprgfx
																											; 	sta z80_d
			ldb	<dispX							; get Y coordinate							; 	lda dispx 				; y coordinate.
			andb	#%00000110						; position within byte boundary			; 	and #6 					; position within byte boundary.
			asrb										; calculate table number (0-1-2-3)		; 	tax	 					; low byte of table displacement.
			stb	<sprShft							; low byte of table displacement			; 	stx sprshft
																											; 
																											; .if 0
																											; 	asl a	  					; multiply by 32.
																											; 	asl a  					; already a multiple
																											; 	asl a  					; of 2, so just 4
																											; 	asl a  					; shifts needed.
																											; 	clc 						; add to sprite address.
			stx	<reg_DE						; save into reg_DE								; 	adc z80_e
																											; 	sta z80_e
																											; 	bcc :+
																											; 	inc z80_d
																											; :
			ldx	#spMask						; point to mask table							; .endif
			aslb									; calculate the right offset (2x)			; 	lda spmask,x		 	; pointer to mask table.
			ldd	b,x							; get masks											; 	sta z80_c 				; left mask.
			sta	<reg_C						; save left mask									; 	lda spmask+1,x
			stb	<reg_B						; and right mask									; 	sta z80_b 				; right mask.
												; Drop into screen address routine				; Drop into screen address routine.
												; bra	ScAdd	exists immediately below here		; 	jmp scadd
; ------------------------------------------------------------------------------------------------------------------------------------------
	ELSE											; NORMAL sprites (4 frames per sprite)
; ------------------------------------------------------------------------------------------------------------------------------------------
; here regX must arrive as IX (sprite address)
; returns reg_BC=right-left byte mask - reg_DE=spriteframe address
;         regX   = screenaddress(dispx,dispy)														;  scraddr = screenaddress(dispx,dispy)
; ------------------------------------------------------------------------------------------------------------------------------------------
GSprAd	leau	,x								; regU takes the rol of reg_IX
			stu	<reg_IX						; save reg_IX for later use
			ldd	3,u							; get old posXY									; gsprad ld l,(ix+3)         ; x coordinate.
			sta	<dispY						; put into											; 	 ld h,(ix+4)         ; y coordinate.
			stb	<dispX						; variables											; 	 ld (dispx),hl       ; set display coordinates.
			lda	1,u							; get old image									; 	 ld a,(ix+1)         ; sprite image.
			jsr	GFrm							; fetch start frame in regX					; 	 call gfrm           ; fetch start frame for this sprite.
			lda	,x								; get frame											; 	 ld a,(hl)           ; frame in accumulator.
			adda	2,u							; add old frame									; 	 add a,(ix+2)        ; add frame number.
GSprA0											; reg_DE = reg_AF is frame*128
	IF BFLAG
			ldb	#192							; multiply by 192
	ELSE
			ldb	#128							; multiply by 128									; gspra0 rrca                ; multiply by 128.
	ENDIF
			mul									; multiply. Result in reg_D					; 		 ld d,a              ; store in d.
																											; 		 and 128             ; low byte bit.
																											; 		 ld e,a              ; got low byte.
																											; 		 ld a,d              ; restore result.
																											; 		 and 127             ; high byte bits.
																											; 		 ld d,a              ; displacement high byte.
			ldx	#sprGfx						; point to sprites data beginning			; 	 ld hl,sprgfx        ; address of play sprites.
			leax	d,x							; point to right frame							; 	 add hl,de           ; point to frame.
			ldb	<dispX						; get Y coordinate								; 	 ld a,(dispy)        ; y coordinate.
			andb	#%00000110					; position within byte boundary				; 	 and 6               ; position within byte boundary.
			stb	<reg_C						; low byte of table displacement				; 	 ld c,a              ; low byte of table displacement.
	IF BFLAG
			lda	#24							; x 48 (already even, so just by 24)
	ELSE
			lda	#16							; x 32 (already even, so just by 16)
	ENDIF
			mul									; multiply. Result in reg_D
																											; 		 rlca                ; multiply by 32.
																											; 		 rlca                ; already a multiple
																											; 		 rlca                ; of 2, so just 4
																											; 		 rlca                ; shifts needed.
																											; 		 ld e,a              ; put displacement in low byte of de.
																											; 		 ld d,0              ; zero the high byte.
																											; 		 ld b,d              ; no high byte for mask displacement either.
			leau	d,x							; add to sprite address, change to regU	; 		 add hl,de           ; add to sprite address.
			stu	<reg_DE						; save into reg_DE								; 		 ex de,hl            ; need it in de for now.
			ldx	#spMask						; point to mask table							; 		 ld hl,spmask        ; pointer to mask table.
			ldb	<reg_C						; get saved low byte
			abx									; add to pointer
			ldd	,x								; get masks
			sta	<reg_C						; save left mask									; 		 add hl,bc           ; add displacement to pointer.
			stb	<reg_B						; and right mask									; 		 ld c,(hl)           ; left mask.
																											; 		 inc hl
																											; 		 ld b,(hl)				; right mask.
; ------------------------------------------------------------------------------------------------------------------------------------------
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Drop into screen address routine.																; Drop into screen address routine.
; This routine returns a screen address for (dispx, dispy) in hl						; This routine returns a screen address for (dispx, dispy) in hl.
; when used for Objects, posY and dispX arrive INVERTED!
; but for Sprites arrive NORAML
; ------------------------------------------------------------------------------------------------------------------------------------------
ScAdd		ldb	<dispY						; get posY											; scadd  ld a,(dispx)        ; coordinate.
			ldx	#SCADTB						; point to table									; 		 ld l,a              ; low byte of table.
			abx									; add offset twice
			abx									; as entries are words
			ldx	,x								; fetch address of mostleft byte in row	; 		 ld a,(hl)           ; fetch high byte.
			ldb	<dispX						; get posX											; 		 ld h,a              ; hl points to start of line.
			lsrb									; divide												; 		 ld a,(dispy)        ; y pixel coordinate.
			lsrb									; by													; 		 rrca                ; divide by 8.
			lsrb									; 8													; 		 rrca
			andb	#31							; values 0-31 accepted							; 		 rrca
			abx									; add to complete address
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
spMask	fcb	255,0,63,192,15,240,3,252														; spmask defb 255,0,63,192,15,240,3,252
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF RFLAG										; if REDUCED SPRITES
; ------------------------------------------------------------------------------------------------------------------------------------------
; These are the sprite routines																	; These are the sprite routines.
; sspria = single sprite, old (ix)																; sspria = single sprite, old (ix).
; ssprib = single sprite, new (ix+5)															; ssprib = single sprite, new (ix+5).
; sspric = both sprites, old (ix) and new (ix+5)											; sspric = both sprites, old (ix) and new (ix+5).
; ------------------------------------------------------------------------------------------------------------------------------------------
; regU is used as pointer to 'new/old' sprite
; So no need for self modifying code
; ------------------------------------------------------------------------------------------------------------------------------------------
SSpriA																									; sspria:
			jsr	GSprAd						; get old sprite address						; 	jsr gsprad					; get old sprite address.
													; returns reg_BC=right-left byte mask 		;
													; and reg_DE=spriteframe address				;
SSpri2	stx	<reg_HL						; save screen address							; sspri2:
																											; 	lda z80_e					; 3c
																											; 	sta dline_spraddr1+1		; 4c
																											; 	sta dline_spraddr2+1		; 4c
			ldu	<reg_DE						; regU is sprite data pointer
																											; 	lda z80_d					; 3c
																											; 	sta dline_spraddr1+2		; 4c
																											; 	sta dline_spraddr2+2		; 4c
			ldb	<sprShft						; get shift table number						; 	ldx sprshft
			addb	#shift0/256					; add to first one								; 	sta dline_spraddr2+2		; 4c
																											; 	lda shift_table,x
																											; 	sta dline_shift1+1
																											; 	sta dline_shift2+1
																											; 	lda shift_table+1,x
			stb	DLine_Shift1+1				; update shift high byte						; 	sta dline_shift1+2
			stb	DLine_Shift2+1				; update shift high byte						; 	sta dline_shift2+2
			clrb									; vertical lines drawn							; 	ldx #0						; vertical lines.
SSpri0																									; sspri0:
			jsr	DLine							; draw a line										; 	jsr dline					; draw a line.
	IF BFLAG										; big sprites(16x24)	
			cmpb	#48							; got to sprite end?								; 	cpx #48
	ELSE
			cmpb	#32							; got to sprite end?								; 	cpx #32
	ENDIF
			bne	SSpri0						; not yet, do next line							; 	bne sspri0					; repeat 16 times x 2 bytes
			rts									; return												; 	rts
; ------------------------------------------------------------------------------------------------------------------------------------------
	ELSE											; NORMAL sprites (4 frames per sprite)
; ------------------------------------------------------------------------------------------------------------------------------------------
; These are the sprite routines.														; These are the sprite routines.
; sspria = single sprite, old (ix).													; sspria = single sprite, old (ix).
; ssprib = single sprite, new (ix+5).												; ssprib = single sprite, new (ix+5).
; sspric = both sprites, old (ix) and new (ix+5).								; sspric = both sprites, old (ix) and new (ix+5).
; ------------------------------------------------------------------------------------------------------------------------------------------
; regU is used as pointer to 'new/old' sprite
; So no need for self modifying code
; ------------------------------------------------------------------------------------------------------------------------------------------
SSpriA											;											sspria:
			jsr	GSprAd						; get old sprite address				jsr gsprad			; get old sprite address.
													; returns reg_BC=right-left byte mask 
													; and reg_DE=spriteframe address
SSpri2	stx	<reg_HL						; save screen address						
													; draw the sprite							sspri2:
													;												lda z80_e
													;												sta dline1+1		; Set spritedata address
			ldu	<reg_DE						; get old sprite address				lda z80_e
													;												sta dline2+1
													; already									lda z80_d
													; done										sta dline1+2
													; above										sta dline2+2
													; not needed								stx xtmp
			clrb									; vertical lines drawn					ldx #0				; vertical lines.
SSpri0											;											sspri0:
			jsr	DLine							; draw a line								jsr dline			; draw a line.
													; not needed								cpx #16				; detect block boundery
													; not needed								bne :+				; skip if not
													; not needed								inc scraddr+1		; jump to next blockline
													; not needed								:
	IF BFLAG										; big sprites(16x24)						.if bflag			
			cmpb	#48							; got to sprite end?						cpx #48				; check finished
	ELSE
			cmpb	#32							; got to sprite end?						cpx #32				; check finished
													
	ENDIF
			bne	SSpri0						; not yet, do next line					bne sspri0			; no, repeat
													;												ldx xtmp
			rts									; return										rts
; ------------------------------------------------------------------------------------------------------------------------------------------
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Here reg X arrives as reg_IX (sprite pointer)
; ------------------------------------------------------------------------------------------------------------------------------------------
SSpriB											;											ssprib:
			jsr	GSprAN						; get new sprite address				jsr gspran 			; get new sprite address.
													; returns reg_BC=right-left byte mask 
													; and reg_DE=spriteframe address
			jmp	SSpri2						; go draw it								jmp sspri2
; ------------------------------------------------------------------------------------------------------------------------------------------
; interchanges contents of registers BC and HL with their mirrors (Z80 exx opcode)
; ------------------------------------------------------------------------------------------------------------------------------------------
do_rexx	pshs	x								; save register							exx:
			ldx	<reg_BC						; get register BC							lda z80_c
			stx	<esp_BC						; put register into mirror				sty z80_c
			ldx	<reg_HL						; get register HL							lda scraddr
			stx	<esp_HL						; put register into mirror				sty scraddr
			puls	x,pc							; restore registers and return		rts
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF RFLAG										; if REDUCED SPRITES
; ------------------------------------------------------------------------------------------------------------------------------------------
; regU is used as pointer to 'new' sprite
; regY is used as pointer to 'old' sprite
; So no need for self modifying code
; ------------------------------------------------------------------------------------------------------------------------------------------
SSpriC																									; sspric:
			jsr	GSprAd						; get old sprite address						; 	jsr gsprad 					; get old sprite address.
													; returns reg_BC=right-left byte mask 
													; and reg_DE=spriteframe address
			stx	<reg_HL						; save screen address
			ldy	<reg_DE						; regY is old sprite data pointer			; 	lda z80_e					; 3c
																											; 	sta ddline_spraddr3+1	; 4c
																											; 	sta ddline_spraddr4+1	; 4c
																											; 	lda z80_d					; 3c
																											; 	sta ddline_spraddr3+2	; 4c
																											; 	sta ddline_spraddr4+2	; 4c
			ldb	<sprShft						; get shift table number						; 	ldx sprshft
			addb	#shift0/256					; add to first one		
																											; 	lda shift_table,x
																											; 	sta ddline_shift3+1
																											; 	sta ddline_shift4+1
																											; 	lda shift_table+1,x
			stb	DdLine_Shift3+1			; update shift high byte						; 	sta ddline_shift3+2
			stb	DdLine_Shift4+1			; update shift high byte						; 	sta ddline_shift4+2
			jsr	do_rexx						; save old sprite pointers						; 	jsr exx  					; store addresses.
			jsr	GSprAN						; get new sprite address						; 	jsr gspran 					; get new sprite addresses.
			stx	<reg_HL						; save screen address
			ldu	<reg_DE						; regU is new sprite data pointer			; 	lda z80_e					; 3c
																											; 	sta ddline_spraddr1+1	; 4c
																											; 	sta ddline_spraddr2+1	; 4c
																											; 	lda z80_d					; 3c
																											; 	sta ddline_spraddr1+2	; 4c
																											; 	sta ddline_spraddr2+2	; 4c
																											; 	ldx sprshft
			ldb	<sprShft						; get shift table number						; 	lda shift_table,x
			addb	#shift0/256					; add to first one	
																											; 	sta ddline_shift1+1
																											; 	sta ddline_shift2+1
																											; 	lda shift_table+1,x
			stb	DdLine_Shift1+1			; update shift high byte						; 	sta ddline_shift1+2
			stb	DdLine_Shift2+1			; update shift high byte						; 	sta ddline_shift2+2
			clrb									; vertical lines drawn							; 	ldx #0
Lloop																										; lloop:
			jsr	DdLine						; erase and draw line							; 	jsr ddline 					; draw a line.

	IF BFLAG										; big sprites(16x24)
			cmpb	#48							; got to sprite end?								; 	cpx #48
	ELSE
			cmpb	#32							; got to sprite end?								; 	cpx #32
	ENDIF
			bne	Lloop							; not yet, do next line							; 	bne lloop
			rts									; return												; 	rts
; ------------------------------------------------------------------------------------------------------------------------------------------
;	This tables *must* be aligned to 256 bytes boundary
;	shift_Table																							; shift_table:
;			fdb	shift0																				; .word shift0
;			fdb	shift2																				; .word shift2
;			fdb	shift4																				; .word shift4
;			fdb	shift6																				; .word shift6
; ------------------------------------------------------------------------------------------------------------------------------------------
; Input:																									; Input:
;  B  = right mask																					;  B  = right mask
;  C  = left mask																						;  C  = left mask
;  DE = spriteaddress																				;  DE = spriteaddress
;  reg_HL (regX) = screen address																;  scraddr = screen address
; ------------------------------------------------------------------------------------------------------------------------------------------
; must preserve 6809 register B (number of drawn lines counter)
; so regB = Atom reg X.  Atom reg Y is not used
; regU is used as pointer to sprite data
; ------------------------------------------------------------------------------------------------------------------------------------------
DLine																										; dline:
			ldx	<reg_HL						; get screen Address for new sprite
			lda	<reg_H						; get high byte of screen Address
			cmpa	#$e6							; is it out of screen (above)?
			blo	1f								; yes, skip it
			coma									; was it $ff? (out of screen)
			bne	DLine_SprAddr1				; no, draw it
1			addb	#2								; increment counter
			rts									; return
DLine_SprAddr1																							; dline_spraddr1:
			lda	b,u							; get one sprite byte							; 	ldy $ffff,x 		; graphic data.
			sta	DLine_Shift1+2				; set as shift low byte
DLine_Shift1																							; dline_shift1:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF						; save in pseudoreg								; 	sta sprtmp
			anda	<reg_C						; mask away unwanted								; 	and z80_c 			; mask away what's not needed.
																											; 	ldy #0
			eora	,x								; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	,x								; update screen									; 	sta (scraddr),y 	; bung it in.
												; carry to new screen byte							; carry to next screen byte
			lda	<reg_AF						; get preshifted value from presudoreg		; 	lda sprtmp			; fetch data.
			anda	<reg_B						; mask away unwanted								; 	and z80_b 			; mask away unwanted
			sta	<reg_AF						; save again in pseudoreg						; 	sta sprtmp
												; middle screen byte									; middle screen byte
			incb									; increment sprite byte							; 	inx
DLine_SprAddr2																							; dline_spraddr2:
			lda	b,u							; get next sprite byte							; 	ldy $ffff,x 		; second bit of data.
			sta	DLine_Shift2+2				; set as shift low byte
DLine_Shift2																							; dline_shift2:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF+1					; save in pseudoreg								; 	sta sprtmp2
			anda	<reg_C						; mask away unwanted								; 	and z80_c 			; mask away what's not needed.
			ora	<reg_AF						; add to previous part							; 	ora sprtmp
																											; 	ldy #8
			eora	1,x							; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	1,x							; update screen									; 	sta (scraddr),y 	; bung it in.
												; carry to last screen byte						; carry to last screen byte
			lda	<reg_AF+1					; get preshifted value from presudoreg		; 	lda sprtmp2
			anda	<reg_B						; mask away unwanted								; 	and z80_b 			; mask away unwanted
																											; 	ldy #16
			eora	2,x							; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	2,x							; update screen									; 	sta (scraddr),y 	; bung it in.
			leax	32,x							; point to next row		
			stx	<reg_HL						; update screen pointer	
DLEx01	incb									; increment sprite byte							; 	inx
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; Line drawn, now work out next target address												; Line drawn, now work out next target address.
; _BEEB screen arrangement																			; _BEEB screen arrangement
; ------------------------------------------------------------------------------------------------------------------------------------------
;																											; nline:
;																											; 	lda scraddr 		; get low byte of address.
;																											; 	and #7				
;																											; 	cmp #7				; is this last line of row?
;																											; 	beq beeb_next_row
;																											; 	; within same row
;																											; 	inc scraddr			; new low byte of address.
;																											; 	rts
;																											; beeb_next_row:
;																											; 	clc
;																											; 	lda scraddr
;																											; 	adc #<(ScreenRowBytes-7)
;																											; 	sta scraddr			; new low byte of address.
;																											; 	lda scraddr+1
;																											; 	adc #>(ScreenRowBytes-7)
;																											; 	sta scraddr+1		; new high byte of address.
;																											; 	rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; Input:																									; Input:
;  B  = right mask																					;  B  = right mask
;  C  = left mask																						;  C  = left mask
;  DE = spriteaddress																				;  DE = spriteaddress
;  HL (regX) = screen address																		;  scraddr = screen address
; ------------------------------------------------------------------------------------------------------------------------------------------
; must preserve 6809 register B (number of drawn lines counter)
; so regB = Atom reg X.  Atom reg Y is not used
; regU is used as pointer to NEW sprite data
; regY is used as pointer to OLD sprite data
; ------------------------------------------------------------------------------------------------------------------------------------------
DdLine																									; ddline:
			ldx	<reg_HL						; get screen Address for new sprite
			lda	<reg_H						; get screen address high byte
			cmpa	#$e6							; is it out of screen (above)?
			blo	1f								; yes, skip it
			coma									; was it $ff? (out of screen)
			bne	DdLine_SprAddr1			; no, draw it
1			incb									; increment counter
			bra	DdLEx01						; go do old sprite
												; NEW SPRITE											; NEW SPRITE
												; first screen byte									; first screen byte
DdLine_SprAddr1																						; dline_spraddr1:
			lda	b,u							; get one sprite byte							; 	ldy $ffff,x 		; graphic data.
			sta	DdLine_Shift1+2			; set as shift low byte
DdLine_Shift1																							; ddline_shift1:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF						; save in pseudoreg								; 	sta sprtmp
			anda	<reg_C						; mask away unwanted								; 	and z80_c 			; mask away what's not needed.
																											; 	ldy #0
			eora	,x								; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	,x								; update screen									; 	sta (scraddr),y 	; bung it in.
												; carry to next screen byte						; carry to next screen byte
			lda	<reg_AF						; get preshifted value from presudoreg		; 	lda sprtmp			; fetch data.
			anda	<reg_B						; mask away unwanted								; 	and z80_b 			; mask away unwanted
			sta	<reg_AF						; save again in pseudoreg						; 	sta sprtmp
												; middle screen byte									; middle screen byte
			incb									; increment counter								; 	inx
DdLine_SprAddr2																						; ddline_spraddr2:
			lda	b,u							; get next sprite byte							; 	ldy $ffff,x 		; second bit of data.
			sta	DdLine_Shift2+2			; set as shift low byte
DdLine_Shift2																							; ddline_shift2:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF+1					; save in pseudoreg								; 	sta sprtmp2
			anda	<reg_C						; mask away unwanted								; 	and z80_c 			; mask away what's not needed.
			ora	<reg_AF						; add to previous part							; 	ora sprtmp
																											; 	ldy #8
			eora	1,x							; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	1,x							; update screen									; 	sta (scraddr),y 	; bung it in.
												; carry to last screen byte						; carry to last screen byte
			lda	<reg_AF+1					; get preshifted value from pseudoreg		; 	lda sprtmp2
			anda	<reg_B						; mask away unwanted								; 	and z80_b 			; mask away unwanted
																											; 	ldy #16
			eora	2,x							; merge bits										; 	eor (scraddr),y 	; XOR with what's there.
			sta	2,x							; update screen									; 	sta (scraddr),y 	; bung it in.
												; 6809 next row										; _BEEB next row
			leax	32,x							; point to next row								; 	lda scraddr 		; get low byte of address.
			stx	<reg_HL						; update screen pointer							; 	and #7				
																											; 	cmp #7				; is this last line of row?
																											; 	beq :+
																											; within same row can't increment page
																											; 	inc scraddr			; new low byte of address.
																											; 	bne ddline2
																											; :
																											; 	clc
																											; 	lda scraddr
																											; 	adc #<(ScreenRowBytes-7)
																											; 	sta scraddr			; new low byte of address.
																											; 	lda scraddr+1
																											; 	adc #>(ScreenRowBytes-7)
DdLEx01											; end of New Sprite								; 	sta scraddr+1		; new high byte of address.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
												; OLD SPRITE											; OLD SPRITE
			ldx	<esp_HL						; get screen Address for old sprite
			lda	<esp_HL						; get screen address high byte
			cmpa	#$e6							; is it out of screen (above)?
			blo	DdLEx02						; yes, skip it
			coma									; was it $ff? (out of screen)
			beq	DdLEx02						; yes, go do old sprite
DdLine2																									; ddline2
												; still first row but different data!			; still first row but different data!
			decb									; decrement counter								; 	dex
												; first screen byte									; first screen byte
DdLine_SprAddr3																						; ddline_spraddr3:
			lda	b,y							; get one sprite byte							; 	ldy $ffff,x			; graphic data.
			sta	DdLine_Shift3+2			; set as shift low byte
DdLine_Shift3																							; ddline_shift3:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF						; save in pseudoreg								; 	sta sprtmp
			anda	<esp_C						; mask away unwanted								; 	and z80_cp 			; mask away what's not needed.
																											; 	ldy #0
			eora	,x								; merge bits										; 	eor (z80_hlp),y 	; XOR with what's there.
			sta	,x								; update screen									; 	sta (z80_hlp),y 	; bung it in.
												; carry to next screen byte						; carry to next screen byte
			lda	<reg_AF						; get reshifted value from pseudoreg		; 	lda sprtmp
			anda	<esp_B						; mask away unwanted								; 	and z80_bp 			; mask away unwanted
			sta	<reg_AF						; save again in pseudoreg						; 	sta sprtmp
												; middle screen byte									; middle screen byte
			incb									; increment counter								; 	inx
DdLine_SprAddr4																						; ddline_spraddr4:
			lda	b,y							; get next sprite byte							; 	ldy $ffff,x 		; second bit of data.
			sta	DdLine_Shift4+2			; set as shift low byte
DdLine_Shift4																							; ddline_shift4:
			lda	>$0000						; get preshifted value							; 	lda $ffff,y
			sta	<reg_AF+1					; save in pseudoreg								; 	sta sprtmp2
			anda	<esp_C						; mask away unwanted								; 	and z80_cp 			; mask away what's not needed.
			ora	<reg_AF						; add to previous part							; 	ora sprtmp
																											; 	ldy #8
			eora	1,x							; merge bits										; 	eor (z80_hlp),y 	; XOR with what's there.
			sta	1,x							; update screen									; 	sta (z80_hlp),y 	; bung it in.
												; last screen byte									; last screen byte
			lda	<reg_AF+1					; get preshifted value from pseudoreg		; 	lda sprtmp2			; fetch data.
			anda	<esp_B						; mask away unwanted								; 	and z80_bp 			; mask away unwanted
																											; 	ldy #16
			eora	2,x							; merge bits										; 	eor (z80_hlp),y 	; XOR with what's there.
			sta	2,x							; update screen									; 	sta (z80_hlp),y 	; bung it in.
												; neext row of sprite data							; next row of sprite data
DdLEx02	incb									; increment counter								; 	inx
												; end of Old Sprite
												; 6809 screen arrangement							; _BEEB screen arrangement
			leax	32,x							; point to next row								; 	lda z80_lp 			; get low byte of address.
			stx	<esp_HL						; update screen pointer							; 	and #7				
																											; 	cmp #7				; is this last line of row?
																											; 	beq :+
																											; within same row can't increment page
																											; 	inc z80_lp			; new low byte of address.
																											; 	rts
																											; :
																											; 	clc
																											; 	lda z80_lp
																											; 	adc #<(ScreenRowBytes-7)
																											; 	sta z80_lp			; new low byte of address.
																											; 	lda z80_lp+1
																											; 	adc #>(ScreenRowBytes-7)
																											; 	sta z80_lp+1		; new high byte of address.
			rts									; return												; 	rts
; ------------------------------------------------------------------------------------------------------------------------------------------
	ELSE											; NORMAL sprites (4 frames per sprite)
; ------------------------------------------------------------------------------------------------------------------------------------------
; regY is used as pointer to 'old' sprite
; regU is used as pointer to 'new' sprite
; So no need for self modifying code
; ------------------------------------------------------------------------------------------------------------------------------------------
SSpriC											;											sspric:
			jsr	GSprAd						; get old sprite address				jsr gsprad 			; get old sprite address.
													; returns reg_BC=right-left byte mask 
													; and reg_DE=spriteframe address
			stx	<reg_HL						; save screen address						
													;												lda z80_e
													;												sta ddline1+1		; Set spritedata address
			ldy	<reg_DE						; get address								lda z80_e
													;												sta ddline2+1
													; already									lda z80_d
													; done										sta ddline1+2
													; above										sta ddline2+2
			jsr	do_rexx						; save old sprite pointers				jsr exx  			; store addresses.
			jsr	GSprAN						; get new sprite address				jsr gspran 			; get new sprite addresses.
			stx	<reg_HL						; save screen address						
													;												lda z80_e
													;												sta dline1+1		; Set spritedata address
			ldu	<reg_DE						; get address								lda z80_e
													; 												sta dline2+1
													; already									lda z80_d
													; done										sta dline1+2
													; above										sta dline2+2
													; not needed								stx xtmp
			clrb									; vertical lines drawn					ldx #0				; vertical lines.
Lloop												;											lloop:
			jsr	DLine							; draw a line of new sprite			jsr dline 			; draw a line.
													;												dex
			subb	#2								; decrement counter twice				dex
			jsr	DdLine						; draw, so delete old sprite line	jsr ddline 			; delete a line.
													; not needed								cpx #16				; detect block boundery
													; not needed								bne :+				; skip if not
													; not needed								inc scraddr+1		; jump to next blockline
													; not needed								inc z80_hlp+1		; jump to next blockline
													; not needed							:
	IF BFLAG										; big sprites(16x24)						.if bflag
			cmpb	#48							; got to sprite end?	
	ELSE
			cmpb	#32							; got to sprite end?						cpx #32				; check finished
	ENDIF
													
			bne	Lloop							; not yet, do next line					bne lloop			; no, repeat
			rts									; return										rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; must preserve 6809 register B (number of drawn lines counter)
; so regB = Atom reg X.  Atom reg Y is not used
; regU is used as a discretional pointer, so saved/restored too
; ------------------------------------------------------------------------------------------------------------------------------------------
DLine												;											dline:
			ldx	<reg_HL						; get screen Address for new sprite
			lda	<reg_H						; get high byte of screen Address
			cmpa	#$e6							; is it out of screen?
			blo	1f								; yes, skip it
			coma									; was it $ff (out of screen)?
			bne	DLine1						; no, draw it
1			addb	#2								; increment counter
			rts									; return
													; not used									ldy sprline,x		; point to screenleft
DLine1											;											dline1:
			lda	b,u							; get byte at this offset				lda objdta,x		; fetch spriteleft byte
			sta	<reg_AF						; save read byte							sta z80_a			; save spriteright byte
													; not used									ldy ytmp
													; regA already has read byte			lda z80_a
			anda	<reg_C						; mask left									and z80_c			; mask left
			eora	,x								; merge bits								eor (scraddr),y	; merge with screenleft
			sta	,x								; update screen							sta (scraddr),y	; write screenleft
SLine												;											sline:
			incb									; increment Atom x (sprite byte)		inx					; next spritebyte
													; not needed								iny					; point to screenmiddle
DLine2											;											dline2:
													;												lda objdta,x		; fetch spritemiddle byte
													; to point to sprite data
			lda	b,u							; get byte at this offset
			eora	1,x							; merge bits								eor (scraddr),y	; merge with screenmiddle
			sta	1,x							; update screen							sta (scraddr),y	; write screenmiddle
SLine2											;											sline2:
													; not needed								iny					; point to screenright	
			lda	<reg_AF						; get saved read byte					lda z80_a			; fetch spriteright byte
			anda	<reg_B						; mask right								and z80_b			; mask right
			eora	2,x							; merge bits								eor (scraddr),y	; merge with screenright
			sta	2,x							; update screen							sta (scraddr),y	; write screenright
SLine3											;											sline3:
			leax	32,x							; point to next row
			stx	<reg_HL						; update screen pointer
DLEx01	incb									; increment Atom x (sprite byte)		inx					; next spritebyte
			rts									; return										rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; must preserve 6809 register B (number of drawn lines counter)
; so regB = Atom reg X.  Atom reg Y is not used
; regU is used as a discretional pointer, so saved/restored too
; ------------------------------------------------------------------------------------------------------------------------------------------
DdLine											; 											ddline:
			ldx	<esp_HL						; get screen Address for old sprite
			lda	<esp_H						; get high byte of screen Address
			cmpa	#$e6							; is it out of screen?
			blo	1f								; yes, skip it
			coma									; is it out of screen?
			bne	DdLine1						; no, draw line
1			addb	#2								; increment counter
			rts									; return
DdLine1											;											ddline1:
			lda	b,y							; get byte at this offset				lda objdta,x		; fetch spriteleft byte
			sta	<reg_AF						; save read byte							sta z80_a			; save spriteright byte
													; not used									ldy ytmp
													; regA already has read byte			lda z80_a
			anda	<esp_C						; mask left									and z80_cp			; mask left
			eora	,x								; merge bits								eor (z80_hlp),y	; merge with screenleft
			sta	,x								; update screen							sta (z80_hlp),y	; write screenleft
DsLine											;											dsline:
			incb									; increment Atom x (sprite byte)			inx					; next spritebyte
													; not needed								iny					; point to screenmiddle
DdLine2											;											ddline2:
													;												lda objdta,x		; fetch spritemiddle byte
													; to point to sprite data
			lda	b,y							; get byte at this offset
			eora	1,x							; merge bits								eor (z80_hlp),y	; merge with screenmiddle
			sta	1,x							; update screen							sta (z80_hlp),y	; write screenmiddle
DsLine2											;											dsline2:
													; not needed									iny					; point to screenright	
			lda	<reg_AF						; get saved read byte					lda z80_a			; fetch spriteright byte
			anda	<esp_B						; mask right								and z80_bp			; mask right
			eora	2,x							; merge bits								eor (z80_hlp),y	; merge with screenright
			sta	2,x							; update screen							sta (z80_hlp),y	; write screenright
DsLine3											;											dsline3:
			leax	32,x							; point to next row
			stx	<esp_HL						; update screen pointer
DdLEx01	incb									; increment Atom x (sprite byte)		inx					; next spritebyte
			rts									; return										rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; Line drawn, now work out next target address.									; Line drawn, now work out next target address.
; ------------------------------------------------------------------------------------------------------------------------------------------
;																								nline:
;																									clc
;																									lda scraddr 		; get low byte of address.
;																									adc #$20
;
;
;
;																									sta scraddr 		; new low byte of address.
;																									bcc :+
;																									inc scraddr+1 		; new high byte of address.
;																								:
;																									rts
; ------------------------------------------------------------------------------------------------------------------------------------------
	ENDIF
; ------------------------------------------------------------------------------------------------------------------------------------------
; Animates a sprite																					; Animates a sprite.
; ------------------------------------------------------------------------------------------------------------------------------------------
AnimSp																									; animsp ld hl,frmno         ; game frame.
			anda	<frmNo																				; 		 and (hl)            ; is it time to change the frame?
			bne	AnimSpex																				; 		 ret nz              ; not this frame.
			ldy	<reg_IX
			lda	6,y																					; 		 ld a,(ix+6)         ; sprite image.
			jsr	GFrm							; returns regX as HL								; 		 call gfrm           ; get frame data.
			leax	1,x																					; 		 inc hl              ; point to frames.
			stx	<reg_HL
			lda	7,y																					; 		 ld a,(ix+7)         ; sprite frame.
			inca																							; 		 inc a               ; next one along.
			cmpa	,x																						; 		 cp (hl)             ; reached the last frame?
			bcs	AnimS0																				; 		 jr c,anims0         ; no, not yet.
			clra																							; 		 xor a               ; start at first frame.
AnimS0	sta	7,y																					; anims0 ld (ix+7),a         ; new frame.
AnimSpex	rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
AnimBk																									; animbk ld hl,frmno         ; game frame.
			anda	<frmNo																					; 		 and (hl)            ; is it time to change the frame?
			bne	AnimSpex																				; 		 ret nz              ; not this frame.
			ldy	<reg_IX
			lda	6,y																					; 		 ld a,(ix+6)         ; sprite image.
			jsr	GFrm																					; 		 call gfrm           ; get frame data.
			leax	1,x																					; 		 inc hl              ; point to frames.
			stx	<reg_HL
			lda	7,y																					; 		 ld a,(ix+7)         ; sprite frame.
																											; 		 and a               ; first one?
			bne	RTanb0																				; 		 jr nz,rtanb0        ; yes, start at end.
			lda	,x																						; 		 ld a,(hl)           ; last sprite.
RTanb0	deca																							; rtanb0 dec a               ; next one along.
			jsr	AnimS0																				; 		 jr anims0           ; set new frame.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Check for collision with other sprite, strict enforcement								; Check for collision with other sprite, strict enforcement.
; ------------------------------------------------------------------------------------------------------------------------------------------
SkTyp		ldx	#sprTab																				; sktyp  ld hl,sprtab        ; sprite table.
			stx	<reg_HL
NumSP2	lda	#NUMSPR																				; numsp2 ld a,NUMSPR         ; number of sprites.
SkTyp0	sta	<reg_AF																				; sktyp0 ex af,af'           ; store loop counter.
			stx	<skPtr																					; 		 ld (skptr),hl       ; store pointer to sprite.
			lda	,x																						; 		 ld a,(hl)           ; get sprite type.
			cmpa	<reg_B																				; 		 cp b                ; is it the type we seek?
			beq	ColTyp																				; 		 jr z,coltyp         ; yes, we can use this one.
SkTyp1	ldx	<skPtr																					; sktyp1 ld hl,(skptr)       ; retrieve sprite pointer.
			leax	TABSIZ,x																				; 		 ld de,TABSIZ        ; size of each entry.
			stx	<reg_HL																				; 		 add hl,de           ; point to next sprite in table.
			lda	<reg_AF																				; 		 ex af,af'           ; restore loop counter.
			deca																							; 		 dec a               ; one less iteration.
			bne	SkTyp0																				; 		 jp nz,sktyp0        ; keep going until we find a slot.
			ldd	#$0000																				; 		 ld hl,0             ; default to ROM address - no sprite.
			std	<skPtr																					; 		 ld (skptr),hl       ; store pointer to sprite.
			andcc	#%11111010					; clear zero and carry flags					; 		 or h                ; don't return with zero flag set.
			rts																							; 		 ret                 ; didn't find one.
; ------------------------------------------------------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------------------------------------------------------
ColTyp	lda	[reg_IX]																				; coltyp ld a,(ix+0)         ; current sprite type.
			cmpa	<reg_B																				; 		 cp b                ; seeking sprite of same type?
			beq	ColTy1																				; 		 jr z,colty1         ; yes, need to check we're not detecting ourselves.
ColTy0	ldx	<reg_HL																				; colty0 ld de,X             ; distance to x position in table.
			leax	Xval,x																				; 		 add hl,de           ; point to coords.
			ldd	,x+																					; 		 ld e,(hl)           ; fetch x coordinate.
			stb	<reg_D																				; 		 inc hl              ; now point to y.
			sta	<reg_E
			stx	<reg_HL																				; 		 ld d,(hl)           ; that's y coordinate.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Drop into collision detection																	; Drop into collision detection.
; ------------------------------------------------------------------------------------------------------------------------------------------
Colc16	ldy	<reg_IX
			lda	Xval,y																				; colc16 ld a,(ix+X)         ; x coord.
			suba	<reg_E																				; 		 sub e               ; subtract x.
			bcc	Colc1a																				; 		 jr nc,colc1a        ; result is positive.
			nega																							; 		 neg                 ; make negative positive.
Colc1a	cmpa	#16																					; colc1a cp 16               ; within x range?
			bcc	SkTyp1																				; 		 jr nc,sktyp1        ; no - they've missed.
			sta	<reg_C																				; 		 ld c,a              ; store difference.
			lda	Yval,y																				; 		 ld a,(ix+Y)         ; y coord.
			suba	<reg_D																				; 		 sub d               ; subtract y.
			bcc	Colc1b																				; 		 jr nc,colc1b        ; result is positive.
			nega																							; 		 neg                 ; make negative positive.
Colc1b	cmpa	#16																					; colc1b cp 16               ; within y range?
			bcc	SkTyp1																				; 		 jr nc,sktyp1        ; no - they've missed.
			adda	<reg_C																				; 		 add a,c             ; add x difference.
			cmpa	#26																					; 		 cp 26               ; only 5 corner pixels touching?
			bcc	SkTyp1																				; 		 ret c               ; carry set if there's a collision.
			rts																							; 		 jp sktyp1           ; try next sprite in table.
; ------------------------------------------------------------------------------------------------------------------------------------------
ColTy1	ldd	<reg_IX																				; colty1 push ix             ; base sprite address onto stack.
																											; 		 pop de              ; pop it into de.
																											; 		 ex de,hl            ; flip hl into de.
			cmpd	<reg_HL																				; 		 sbc hl,de           ; compare the two.
																											; 		 ex de,hl            ; restore hl.
			beq	SkTyp1																				; 		 jr z,sktyp1         ; addresses are identical.
			bra	ColTy0																				; 		 jp colty0
; ------------------------------------------------------------------------------------------------------------------------------------------
; Display number.	(regA=number to be converted)												; Display number.
; ------------------------------------------------------------------------------------------------------------------------------------------
Disply	ldu	#dispL0						; point to string area							; disply ld bc,displ0        ; display workspace.
			jsr	Num2Ch						; convert number to char						; 		 call num2ch         ; convert accumulator to string.
DispL1	lda	-1,u							; get last calculated digit					; displ1 dec bc              ; back one character.
																											; 		 ld a,(bc)           ; fetch digit.
			ora	#128							; raise bit 7 (end of string)					; 		 or 128              ; insert end marker.
			sta	-1,u							; update string									; 		 ld (bc),a           ; new value.
			ldx	#dispL0						; point to string									; 		 ld hl,displ0        ; display space.
			jmp	Dmsg3							; show it											; 		 jp dmsg3            ; display the string.
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
dispL0	fcb	0,0,0,13+128				; area for converted number					; displ0 defb 0,0,0,13+128
; ------------------------------------------------------------------------------------------------------------------------------------------
; Initialise screen.																					; Initialise screen.
; ------------------------------------------------------------------------------------------------------------------------------------------
InitSc	lda	roomTb						; get room number									; initsc ld a,(roomtb)       ; whereabouts in the map are we?
			jsr	TstSc							; find associated code							; 		 call tstsc          ; find displacement.
			bmi	InitSc1						; if out of map, return zero					; 		 cp 255              ; is it valid?
																											; 		 ret z               ; no, it's rubbish.
			sta	<scNo							; store code as present room					; 		 ld (scno),a         ; store new room number.
			rts									; return												; 		 ret
InitSc1	clra									; clear zero flag				
			rts									; return								
; ------------------------------------------------------------------------------------------------------------------------------------------
; Test screen.																							; Test screen.
; ------------------------------------------------------------------------------------------------------------------------------------------
TstSc		ldx	#mapDat-MAPWID				; start of MAP data								; tstsc  ld hl,mapdat-MAPWID ; start of map data, subtract width for negative.
			sta	<reg_B																				; 		 ld b,a              ; store room in b for now.
			adda	#MAPWID						; add MAPWID to skip negatives				; 		 add a,MAPWID        ; add width in case we're negative.
																											; 		 ld e,a              ; screen into e.
			leax	a,x																					; 		 ld d,0              ; zeroise d.
			stx	<reg_HL																				; 		 add hl,de           ; add displacement to map data.
			lda	,x								; get room number									; 		 ld a,(hl)           ; find room number there.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Screen left																							; Screen left.
; ------------------------------------------------------------------------------------------------------------------------------------------
ScrL		lda	roomTb																				; scrl   ld a,(roomtb)       ; present room table pointer.
			deca																							; 		 dec a               ; room left.
Scr10		jsr	TstSc																					; scrl0  call tstsc          ; test screen.
			inca																							; 		 inc a               ; is there a screen this way?
			beq	ScrLEx																				; 		 ret z               ; no, return to loop.
			lda	<reg_B																				; 		 ld a,b              ; restore room displacement.
			sta	roomTb																				; 		 ld (roomtb),a       ; new room table position.
Scr11		jsr	InitSc																				; scrl1  call initsc         ; set new screen.
			lda	#2																						; 		 ld hl,restfl        ; restart screen flag.
			sta	<restFl																				; 		 ld (hl),2           ; set it.
ScrLEx	rts																							; 		 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
ScrR		lda	roomTb																				; scrr   ld a,(roomtb)       ; room table pointer.
			inca																							; 		 inc a               ; room right.
			bra	Scr10																					; 		 jr scrl0
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
ScrU		lda	roomTb																				; scru   ld a,(roomtb)       ; room table pointer.
			suba	#MAPWID																				; 		 sub MAPWID          ; room up.
			bra	Scr10																					; 		 jr scrl0
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
ScrD		lda	roomTb																				; scrd   ld a,(roomtb)       ; room table pointer.
			adda	#MAPWID																				; 		 add a,MAPWID        ; room down.
			bra	Scr10																					; 		 jr scrl0
; ------------------------------------------------------------------------------------------------------------------------------------------
; Jump to new screen																					; Jump to new screen.
; ------------------------------------------------------------------------------------------------------------------------------------------
NwScr		ldx	#mapDat																				; nwscr  ld hl,mapdat        ; start of map data.
			ldb	#80																					; 		 ld bc,256*80        ; zero room count, 80 to search.
			clr	,-s
NwScr0	cmpa	,x+																					; nwscr0 cp (hl)             ; have we found a match for screen?
			beq	NwScr1																				; 		 jr z,nwscr1         ; yes, set new point in map.
																											; 		 inc hl              ; next room.
			inc	,s																						; 		 inc c               ; count rooms.
			decb
			bne	NwScr0																				; 		 djnz nwscr0         ; keep looking.
			puls	b,pc							; clean stack and return						; 		 ret
NwScr1	lda	,s+																					; nwscr1 ld a,c              ; room displacement.
			sta	roomTb																				; 		 ld (roomtb),a       ; set the map position.
			bra	Scr11																					; 		 jr scrl1            ; draw new room.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Gravity processing																					; Gravity processing.
; ------------------------------------------------------------------------------------------------------------------------------------------
Grav		lda	13,y 																					; grav   ld a,(ix+13)        ; in-air flag.
																											; 		 and a               ; are we in the air?
			beq	GravEx																				; 		 ret z               ; no we are not.
			inca																							; 		 inc a               ; increment it.
			beq	OGrv																					; 		 jp z,ogrv           ; set to 255, use old gravity.
			sta	13,y																					; 		 ld (ix+13),a        ; write new setting.
			rora																							; 		 rra                 ; every other frame.
			bcc	Grav0																					; 		 jr nc,grav0         ; don't apply gravity this time.
			lda	14,y																					; 		 ld a,(ix+14)        ; pixels to move.
			cmpa	#16																					; 		 cp 16               ; reached maximum?
			beq	Grav0																					; 		 jr z,grav0          ; yes, continue.
			inc	14,y																					; 		 inc (ix+14)         ; slow down ascent/speed up fall.
Grav0		lda	14,y																					; grav0  ld a,(ix+14)        ; get distance to move.
			asra																							; 		 sra a               ; divide by 2.
																											; 		 and a               ; any movement required?
			beq	GravEx																				; 		 ret z               ; no, not this time.
			cmpa	#128																					; 		 cp 128              ; is it up or down?
			bcc	GravU																					; 		 jr nc,gravu         ; it's up.
GravD		sta	<reg_B																				; gravd  ld b,a              ; set pixels to move.
GravD0	jsr	CanGD																					; gravd0 call cangd          ; can we go down?
			bne	GravSt																				; 		 jr nz,gravst        ; can't move down, so stop.
			inc	8,y																					; 		 inc (ix+8)          ; adjust new x coord.
			dec	<reg_B
			bne	GravD0																				; 		 djnz gravd0
			rts																							; 		 ret
GravU		nega																							; gravu  neg                 ; flip the sign so it's positive.
			sta	<reg_B																				; 		 ld b,a              ; set pixels to move.
GravU0	jsr	CanGU																					; gravu0 call cangu          ; can we go up?
			lbne	IFalls																				; 		 jp nz,ifalls        ; can't move up, go down next.
			dec	8,y																					; 		 dec (ix+8)          ; adjust new x coord.
			dec	<reg_B
			bne	GravU0																				; 		 djnz gravu0
			rts																							; 		 ret
GravSt	lda	14,y																					; gravst ld a,(ix+14)        ; jump pointer high.
			clr	13,y																					; 		 ld (ix+13),0        ; reset falling flag.
			clr	14,y																					; 		 ld (ix+14),0        ; store new speed.
			cmpa	#8																						; 		 cp 8                ; was speed the maximum?
EvFtf		lbeq	Evnt15																				; evftf  jp z,evnt15         ; yes, fallen too far.
GravEx	rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Old gravity processing for compatibility with 4.6 and 4.7								; Old gravity processing for compatibility with 4.6 and 4.7.
; ------------------------------------------------------------------------------------------------------------------------------------------
OGrv		ldb	14,y																					; ogrv   ld e,(ix+14)        ; get index to table.
																											; 		 ld d,0              ; no high byte.
			ldx	#jTab																					; 		 ld hl,jtab          ; jump table.
			abx																							; 		 add hl,de           ; hl points to jump value.
			lda	,x																						; 		 ld a,(hl)           ; pixels to move.
			cmpa	#99																					; 		 cp 99               ; reached the end?
			bne	OGrv0																					; 		 jr nz,ogrv0         ; no, continue.
			leax	-1,x																					; 		 dec hl              ; go back to previous value.
			lda	,x																						; 		 ld a,(hl)           ; fetch that from table.
			bra	OGrv1																					; 		 jr ogrv1
OGrv0		inc	14,y																					; ogrv0  inc (ix+14)         ; point to next table entry.
OGrv1		tsta																							; ogrv1  and a               ; any movement required?
			beq	OGrvEx																				; 		 ret z               ; no, not this time.
			cmpa	#128																					; 		 cp 128              ; is it up or down?
			bcc	OGrvU																					; 		 jr nc,ogrvu         ; it's up.
OGrvD		sta	<reg_B																				; ogrvd  ld b,a              ; set pixels to move.
OGrvD0	jsr	CanGD																					; ogrvd0 call cangd          ; can we go down?
			bne	OGrvSt																				; 		 jr nz,ogrvst        ; can't move down, so stop.
			inc	8,y																					; 		 inc (ix+8)          ; adjust new x coord.
			dec	<reg_B
			bne	OGrvD0																				; 		 djnz ogrvd0
			rts																							; 		 ret
OGrvU		nega																							; ogrvu  neg                 ; flip the sign so it's positive.
			sta	<reg_B																				; 		 ld b,a              ; set pixels to move.
OGrvU0	jsr	CanGU																					; ogrvu0 call cangu          ; can we go up?
			bne	OGrv2																					; 		 jr nz,ogrv2         ; can't move up, go down next.
			dec	8,y																					; 		 dec (ix+8)          ; adjust new x coord.
			dec	<reg_B	
			bne	OGrvU0																				; 		 djnz ogrvu0
			rts																							; 		 ret
OGrvSt	ldb	14,y																					; ogrvst ld e,(ix+14)        ; get index to table.
																											; 		 ld d,0              ; no high byte.
			ldx	#jTab																					; 		 ld hl,jtab          ; jump table.
			abx																							; 		 add hl,de           ; hl points to jump value.
			lda	,x																						; 		 ld a,(hl)           ; fetch byte from table.
			clr	13,y																					; 		 cp 99               ; is it the end marker?
			clr	14,y																					; 		 ld (ix+13),0        ; reset jump flag.
			cmpa	#99							; moved to avoid flag zero modified			; 		 ld (ix+14),0        ; reset pointer.
			bra	EvFtf																					; 		 jp evftf
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
OGrv2		ldx	#jTab																					; ogrv2  ld hl,jtab          ; jump table.
			clrb																							; 		 ld b,0              ; offset into table.
OGrv4		lda	,x																						; ogrv4  ld a,(hl)           ; fetch table byte.
			cmpa	#100																					; 		 cp 100              ; hit end or downward move?
			bcs	OGrv3																					; 		 jr c,ogrv3          ; yes.
			leax	1,x																					; 		 inc hl              ; next byte of table.
			incb																							; 		 inc b               ; next offset.
			bra	OGrv4																					; 		 jr ogrv4            ; keep going until we find crest/end of table.
OGrv3		stb	14,y																					; ogrv3  ld (ix+14),b        ; set next table offset.
OGrvEx	rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Initiate fall check																				; Initiate fall check.
; ------------------------------------------------------------------------------------------------------------------------------------------
IFall		lda	13,y																					; ifall  ld a,(ix+13)        ; jump pointer flag.
																											; 		 and a               ; are we in the air?
			bne	IFallEx																				; 		 ret nz              ; if set, we're already in the air.
			ldd	8,y							; inverted HL for dispX							; 		 ld h,(ix+9)         ; y coordinate.
NumSp7
			adda	#SPR_HGT																					; 		 ld a,16             ; look down 16 pixels.
			std	<dispX						; into dispXY										; 		 add a,(ix+8)        ; add x coordinate.
			exg	a,b							; invert bytes										; 		 ld l,a              ; coords in hl.
			tfr	d,x							; to regX											; 		 ld (dispx),hl       ; set up test coordinates.
			stx	<reg_HL						; and to pseudo register
			jsr	TstBl																					; 		 call tstbl          ; get map address.
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
			bne	IFallEx																				; 		 ret nz              ; it's solid, don't fall.
			leax	1,x																					; 		 inc hl              ; look right one cell.
			stx	<reg_HL
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
			bne	IFallEx																				; 		 ret nz              ; it's solid, don't fall.
			lda	<dispY																					; 		 ld a,(dispy)        ; y coordinate.
			anda	#7																						; 		 and 7               ; position straddling block cells.
			beq	IFalls																				; 		 jr z,ifalls         ; no more checks needed.
			leax	1,x																					; 		 inc hl              ; look to third cell.
			stx	<reg_HL
			jsr	PlChk																					; 		 call plchk          ; block, platform check.
			bne	IFallEx																				; 		 ret nz              ; it's solid, don't fall.
IFalls	inc	13,y																					; ifalls inc (ix+13)         ; set in air flag.
			clr	14,y																					; 		 ld (ix+14),0        ; initial speed = 0.
IFallEx	rts																							; 		 ret
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
TFall		lda	13,y																					; tfall  ld a,(ix+13)        ; jump pointer flag.
																											; 		 and a               ; are we in the air?
			bne	IFallEx																				; 		 ret nz              ; if set, we're already in the air.
			jsr	IFall																					; 		 call ifall          ; do fall test.
			lda	13,y																					; 		 ld a,(ix+13)        ; get falling flag.
																											; 		 and a               ; is it set?
			beq	IFallEx																				; 		 ret z               ; no.
			lda	#1
			sta	13,y																					; 		 ld (ix+13),255      ; we're using the table.
			jmp	OGrv2																					; 		 jr ogrv2            ; find position in table.
; ------------------------------------------------------------------------------------------------------------------------------------------
; Get frame data for a particular sprite														; Get frame data for a particular sprite.
; receives in regA frameNumber
; returns regX (HL)
; ------------------------------------------------------------------------------------------------------------------------------------------
GFrm		asla									; multiple of 2									; gfrm   rlca                ; multiple of 2.
			adca	#0								; pass bit7 to bit0
			tfr	a,b							; pass to low byte								; 		 ld e,a              ; copy to de.
			clra									; zero to high byte								; 		 ld d,0              ; no high byte as max sprite is 128.
			ldx	<frmPtr						; get frame pointer								; 		 ld hl,(frmptr)      ; frames used by game.
			leax	d,x							; apply offset										; 		 add hl,de           ; point to frame start.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Find sprite list for current room																; Find sprite list for current room.
; ------------------------------------------------------------------------------------------------------------------------------------------
SprLst	ldx	<nmePtr						; point to enemies array						; sprlst ld a,(scno)         ; screen number.
			ldb	<scNo							; get screen number								; sprls2 ld hl,(nmeptr)      ; pointer to enemies.
			beq	SprLsEx						; if zero, exit. Ptr OK							; 		 ld b,a              ; loop counter in b register.
																											; 		 and a               ; is it the first screen?
																											; 		 ret z               ; yes, don't need to search data.
																											; 		 ld de,NMESIZ        ; bytes to skip.
SprLs1	lda	,x								; get byte from array							; sprls1 ld a,(hl)           ; fetch type of sprite.
			inca									; was it 255?										; 		 inc a               ; is it an end marker?
			beq	SprLs0						; yes, go for next screen						; 		 jr z,sprls0         ; yes, end of this room.
			leax	NMESIZ,x						; no, point to next sprite in list			; 		 add hl,de           ; point to next sprite in list.
			bra	SprLs1						; loopback											; 		 jr sprls1           ; continue until end of room.
SprLs0	leax	1,x							; point to next screen 1st sprite			; sprls0 inc hl              ; point to start of next screen.
			decb									; decrement counter
			bne	SprLs1						; not yet done? loopback						; 		 djnz sprls1         ; continue until room found.
SprLsEx	rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Clear all but a single player sprite															; Clear all but a single player sprite.
; ------------------------------------------------------------------------------------------------------------------------------------------
NSpr		ldb	#NUMSPR																				; nspr   ld b,NUMSPR         ; sprite slots in table.
			ldy	#sprTab																				; 		 ld ix,sprtab        ; sprite table.
																											; 		 ld de,TABSIZ        ; distance to next odd/even entry.
NSpr0		lda	,y																						; nspr0  ld a,(ix+0)         ; fetch sprite type.
																											; 		 and a               ; is it a player?
			beq	NSpr1																					; 		 jr z,nspr1          ; yes, keep this one.
			lda	#255
			sta	,y																						; 		 ld (ix+0),255       ; delete sprite.
			sta	5,y																					; 		 ld (ix+5),255       ; remove next type.
			leay	TABSIZ,y																				; 		 add ix,de           ; next sprite.
			decb
			bne	NSpr0																					; 		 djnz nspr0          ; one less space in the table.
			rts																							; 		 ret
NSpr1		lda	#255
			sta	,y																						; nspr1  ld (ix+0),255       ; delete sprite.
			leay	TABSIZ,y																				; 		 add ix,de           ; point to next sprite.
			decb
			bne	NSpr2																					; 		 djnz nspr2          ; one less to do.
			rts																							; 		 ret
NSpr2		lda	#255	
			sta	,y																						; nspr2  ld (ix+0),255       ; delete sprite.
			sta	5,y																					; 		 ld (ix+5),255       ; remove next type.
			leay	TABSIZ,y																				; 		 add ix,de           ; next sprite.
			decb
			bne	NSpr2																					; 		 djnz nspr2          ; one less space in the table.
			rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Two initialisation routines.
; Initialise sprites - copy everything from list to table.								; Initialise sprites - copy everything from list to table.
; regX (HL) gets here pointing to the beginning of 1st sprite for that screen
; ------------------------------------------------------------------------------------------------------------------------------------------
ISpr		ldb	#NUMSPR						; number of sprites in table					; ispr   ld b,NUMSPR         ; sprite slots in table.
			ldy	#sprTab						; point to destination table					; 		 ld ix,sprtab        ; sprite table.
ISpr2		lda	,x								; get a byte from source						; ispr2  ld a,(hl)           ; fetch byte.
			cmpa	#255							; is it end marker?								; 		 cp 255              ; is it an end marker?
			beq	ISprEx						; yes, exit											; 		 ret z               ; yes, no more to do.
ISpr1		lda	,y								; get a byte from destination					; ispr1  ld a,(ix+0)         ; fetch sprite type.
			cmpa	#255							; is it enabled?									; 		 cp 255              ; is it enabled yet?
			bne	ISpr4							; yes, already in use, skip it				; 		 jr nz,ispr4         ; yes, try another slot.
			lda	5,y							; get 1st byte next sprite						; 		 ld a,(ix+5)         ; next type.
			cmpa	#255							; is it enabled?									; 		 cp 255              ; is it enabled yet?
			beq	ISpr3							; no, copy it										; 		 jr z,ispr3          ; no, process this one.
ISpr4		leay	TABSIZ,y						; point to next destination sprite			; ispr4  ld de,TABSIZ        ; distance to next odd/even entry.
			decb									; decrement counter								; 		 add ix,de           ; next sprite.
			bne	ISpr1							; not yet done? loopback						; 		 djnz ispr1          ; repeat for remaining sprites.
ISprEx	rts									; return												; 		 ret                 ; no more room in table.
ISpr3		jsr	CpSp							; Do copy sprite to destination				; ispr3  call cpsp           ; initialise a sprite.
			decb									; decrement counter
			bne	ISpr2							; not yet done? loopback						; 		 djnz ispr2          ; one less space in the table.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Initialise sprites - but not player, we're keeping the old one						; Initialise sprites - but not player, we're keeping the old one.
; ------------------------------------------------------------------------------------------------------------------------------------------
KSpr		ldb	#NUMSPR																				; kspr   ld b,NUMSPR         ; sprite slots in table.
			ldy	#sprTab																				; 		 ld ix,sprtab        ; sprite table.
KSpr2		lda	,x																						; kspr2  ld a,(hl)           ; fetch byte.
			cmpa	#255																					; 		 cp 255              ; is it an end marker?
			beq	KSprEx																				; 		 ret z               ; yes, no more to do.
			tsta																							; 		 and a               ; is it a player sprite?
			bne	KSpr1																					; 		 jr nz,kspr1         ; no, add to table as normal.
																											; 		 ld de,NMESIZ        ; distance to next item in list.
			leax	NMESIZ,x																				; 		 add hl,de           ; point to next one.
			bra	KSpr2																					; 		 jr kspr2
KSpr1		lda	,y																						; kspr1  ld a,(ix+0)         ; fetch sprite type.
			cmpa	#255																					; 		 cp 255              ; is it enabled yet?
			bne	KSpr4																					; 		 jr nz,kspr4         ; yes, try another slot.
			lda	5,y																					; 		 ld a,(ix+5)         ; next type.
			cmpa	#255																					; 		 cp 255              ; is it enabled yet?
			beq	KSpr3																					; 		 jr z,kspr3          ; no, process this one.
KSpr4																										; kspr4  ld de,TABSIZ        ; distance to next odd/even entry.
			leay	TABSIZ,y																				; 		 add ix,de           ; next sprite.
			decb
			bne	KSpr1																					; 		 djnz kspr1          ; repeat for remaining sprites.
			rts																							; 		 ret                 ; no more room in table.
KSpr3		jsr	CpSp																					; kspr3  call cpsp           ; copy sprite to table.
			decb
			bne	KSpr2																					; 		 djnz kspr2          ; one less space in the table.
KSprEx	rts																							; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Copy sprite from list to table																	; Copy sprite from list to table
; regB arrives with number of sprites to deal with (saved register)
; regX points to source of data. regY points to destination
; ------------------------------------------------------------------------------------------------------------------------------------------
CpSp		pshs	b								; save working register
			lda	,x+							; get a byte from source						; cpsp   ld a,(hl)           ; fetch byte from table.
			sta	,y								; save to destination							; 		 ld (ix+0),a         ; set up type.
			sta	PAM1ST,y						; set up type										; 		 ld (ix+PAM1ST),a    ; set up type.
																											; 		 inc hl              ; move to next byte.
			lda	,x+							; get 2nd byte										; 		 ld a,(hl)           ; fetch byte from table.
			sta	6,y							; set up image										; 		 ld (ix+6),a         ; set up image.
																											; 		 inc hl              ; move to next byte.
			ldd	,x++							; get 3rd and 4th byte							; 		 ld a,(hl)           ; fetch byte from table.
																											; 		 ld (ix+3),200       ; set initial coordinate off screen.
			std	8,y							; set up coordinates								; 		 ld (ix+8),a         ; set up coordinate.
			ldb	#200							; use this value to								; 		 inc hl              ; move to next byte.
			stb	3,y							; set initial coordinate						; 		 ld a,(hl)           ; fetch byte from table.
																											; 		 ld (ix+9),a         ; set up coordinate.
																											; 		 inc hl              ; move to next byte.
			clra									; value zero										; 		 xor a               ; zeroes in accumulator.
			sta	7,y							; reset frame number								; 		 ld (ix+7),a         ; reset frame number.
			sta	10,y							; reset direction									; 		 ld (ix+10),a        ; reset direction.
																											; ;       ld (ix+12),a        ; reset parameter B.
			sta	13,y							; reset jump pointer low						; 		 ld (ix+13),a        ; reset jump pointer low.
			sta	14,y							; reset jump pointer high.						; 		 ld (ix+14),a        ; reset jump pointer high.
			deca
			sta	16,y							; reset data pointer to auto-restore		; 		 ld (ix+16),255      ; reset data pointer to auto-restore.
			pshs	x,y							; save pointers									; 		 push ix             ; store ix pair.
																											; 		 push hl             ; store hl pair.
																											; 		 push bc
Evis0		jsr	Evnt09						; perform event									; evis0  call evnt09         ; perform event.
			puls	x,y							; restore pointers								; 		 pop bc
																											; 		 pop hl              ; restore hl.
																											; 		 pop ix              ; restore ix.
																											; 		 ld de,TABSIZ        ; distance to next odd/even entry.
			leay	TABSIZ,y						; poit to next sprite							; 		 add ix,de           ; next sprite.
			puls	b,pc							; restore counter and return					; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Clear the play area window																		; Clear the play area window.
; ------------------------------------------------------------------------------------------------------------------------------------------
ClW		ldd	<winTop						; get WinTop,winLft								; clw    ld hl,(wintop)      ; get coordinates of window.
			tfr	a,b							; A=Left(X), B=Top(Y)
			std	<dispX						; dispX=Left, dispY=Top							; 		 ld (dispx),hl       ; put into dispx for calculation.
			lda	<winHgt						; get window height								; 		 ld a,(winhgt)       ; height of window.
ClW3		pshs	a								; save row counter								; clw3   push bc             ; store lines on stack.
			lda	<winWid						; get window width								; 		 ld a,(winwid)       ; width of window.
ClW2		sta	<reg_A						; save column counter							; clw2   ex af,af'           ; store column counter.
			jsr	GPrad							; returns result in regD (grBase)			; 		 call gprad          ; get print address.
			tfr	d,x							; pass to screen pointer
			clra									; get a null byte									; 		 xor a               ; zero byute to write.
			ldb	#8								; number of pixel rows per char				; 		 ld b,8              ; pixel height of each cell.
ClW1		sta	,x								; clean one pixels row of the char			; clw1   ld (de),a           ; copy to screen.
			leax	32,x							; point to pixels row below					; 		 inc d               ; next screen row down.
			decb									; decrement pixels rows counter
			bne	ClW1							; not yet done? do next row (byte)			; 		 djnz clw1
													; no colour											; 		 call gaadd          ; get attribute address.
													; by now												; 		 ld a,(23693)        ; get colour.
													; here												; 		 ld (hl),a           ; write colour.
			inc	<dispX						; next column										; 		 ld hl,dispy         ; column position.
																											; 		 inc (hl)            ; next column.
			lda	<reg_A						; get column counter								; 		 ex af,af'           ; restore column counter.
			deca									; decrement it										; 		 dec a               ; one less to do.
			bne	ClW2							; not yet done? do next char in row			; 		 jr nz,clw2          ; repeat for remaining columns.
			lda	<winLft						; get left edge									; 		 ld a,(winlft)       ; get left edge.
			sta	<dispX						; reset X position								; 		 ld (dispy),a        ; reset y.
			inc	<dispY						; point to next char row						; 		 ld hl,dispx         ; line.
																											; 		 inc (hl)            ; next line down.
			puls	a								; get row counter									; 		 pop bc              ; restore line counter.
			deca									; decrement it
			bne	ClW3							; not yet done? do next row					; 		 djnz clw3           ; repeat down the screen.
			ldx	<winTop						; get coordinates of top-left					; 		 ld hl,(wintop)      ; get coordinates of window.
			tfr	a,b							; invert them
			stx	<charX						; put into variables								; 		 ld (charx),hl       ; put into display position.
			rts									; return												; 		 ret
; ------------------------------------------------------------------------------------------------------------------------------------------
; Effects code																							; Effects code.
; Called on each VSync for 6809 code															; Ticker routine is called 25 times per second.
; ------------------------------------------------------------------------------------------------------------------------------------------
; CONVERTED FOR TESTSCROLL - Only used one code line!
; regX = reg_HL
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF SFLAG
Scrly												;														scrly:
			rts									; will be a ldd txtScr								rts
			fdb	txtScr						; a=High, b=Low										.word txtscr         	; get left screen address.
													;															sta scr_l
													;															lda txtscr+1
			std	<scr_l						; left screen address								sta scr_l+1
													;															sta scr_r+1
													;															stx xtmp
													;															clc         		; get right screen address.
			addb	<txtWid						; add width of window								lda scr_l
			adca	#0								; pass carry											adc txtwid
			subd	#1								; subtract one											sta scr_r
			std	<scr_r						; right screen address								dec scr_r
			ldb	#8								; number of rows to work
			stb	<reg_B						; into pseudoreg
Scrly1											;														scrly1:
			ldb	<txtWid						; get window width									ldy txtwid		; set txtwide
			decb									; subtract one											dey
			andcc	#%11111110					; clear carry to enter zero by the right		clc
			ldx	<scr_l						; point to left screen address
Scrly0											;														scrly0:
			lda	b,x							; get byte												lda (scr_l),y		; scroll 1 line
			rola									; shift it left										rol a
			sta	b,x							; update screen										sta (scr_l),y
			decb									; decrement width counter							dey
			bpl	Scrly0						; not done? do next char							bpl scrly0
													;															clc			; point to next line
													;															lda scr_l
			leax	32,x							; point row below										adc #32
			stx	<scr_l						; update pointer										sta scr_l
			dec	<reg_B						; decrement row counter
			bne	Scrly1						; not done? do next one								bcc scrly1		; repeat 8 times
			ldx	<txtPos						; get text pointer									lda txtpos 		; get text pointer.
			stx	<scr_Txt						; put at screen pointer								sta scr_txt
													;															lda txtpos+1
													; points to screen pointer							sta scr_txt+1
													; 															ldy #0
			ldb	,x								; get char												lda (scr_txt),y 		; find character we're displaying.
			andb	#%01111111					; mask out bit 7										and #127 		; remove end marker bit if applicable.
			cmpb	#13							; is it Intro?											cmp #13			; is it newline?
			bne	Scrly5						; no, skip next										bne scrly5 		; no, it's okay.
			ldb	#32							; get space instead									lda #32			; convert to a space instead.
Scrly5											;														scrly5:
			clra									; multiply												sta fntaddr		; calculate char address
			aslb									; this 													lda #0
			rola									; value													sta fntaddr+1
			aslb									; by 8													asl fntaddr  		; multiply char by 8.
			rola									; to get													rol fntaddr+1
			aslb									; offset													asl fntaddr
			rola									; to desired char										rol fntaddr+1
													;															asl fntaddr
													;															rol fntaddr+1
													;															lda fntaddr
			ldx	#font-256					; point to FONT table -256							clc
			leax	d,x							; now to desired char								adc #<(FONT-256)
													;															sta scrly3+1		; that's the low byte.
													;															lda fntaddr+1
													;															adc #>(FONT-256)
			ldu	<scr_r						; point to SCREEN										sta scrly3+2		; add displacement.
			clrb									; reset char byte counter							ldx #0
Scrly3											;														scrly3:
			lda	b,x							; get byte from font table							lda $3333,x		; get image of char line.
			anda	<txtBit						; mask with bit value								and txtbit
			beq	Scrly2						; if zero don't plot pixel							beq scrly2		; don't plot pixel
													;															ldy scrline,x
													;															lda (scr_r),y
			lda	,u								; get byte at offset									lda (scr_r),y
													;															clc
			ora	#1								; set bit 0												ora #1
			sta	,u								; update that byte									sta (scr_r),y		; plot pixel
Scrly2	leau	32,u							; point to row below									scrly2:
			incb									; increment counter									inx			; next line of char.
			cmpb	#8								; already 8?											cpx #8
			bne	Scrly3						; no, get nex byte from table						bne scrly3
			lsr	<txtBit						; next bit to be displayed							lsr txtbit		; bit of text to display.
			bcs	1f								; if carry, skip next								bcs :+
			rts									; return													rts
1													;														:
			clrb									; clear counter										ldy #0
			ldx	<scr_Txt						; get text pointer
			lda	b,x							; get char												lda (scr_txt),y 	; what was the character?
			asla									; end of message?										asl a	  		; end of message?
			bcs	Scrly4						; yes, exit												bcs scrly4
			inc	<txtPos+1					; increment												inc txtpos
			bne	2f								; pointer												bne :+
			inc	<txtPos						; to text												inc txtpos+1
2													;														:
			bra	Scrly6						; loopback												jmp scrly6 		; not yet - continue.
Scrly4											;														scrly4:
			ldd	<txtIni						; get start of scrolling message					lda txtini 		; start of scrolling message.
			std	<txtPos						; put into	text position							sta txtpos
													;															lda txtini+1
													;															sta txtpos+1
Scrly6											;														scrly6:
			lda	#128							; set bit7												lda #128
			sta	<txtBit						; in bit variable										sta txtbit
													;															ldx xtmp
			rts									; return													rts
; ------------------------------------------------------------------------------------------------------------------------------------------
; NEVER CALLED IN 6809 ENGINE
IScrly	jsr	Prescr						; pass charXY to dispXY							; iscrly call prescr         ; set up display position.
			ldx	#msgDat						; point to messages beginning					; 		 ld hl,msgdat        ; text messages.
			lda	<reg_C						; get width (number of chars ?)				; 		 ld a,b              ; width.
			deca									; decrement it										; 		 dec a               ; subtract one.
			cmpa	#32							; is it between 1-31?							; 		 cp 32               ; is it between 1 and 32?
			bcs	1f								; if lower than 32 skip disabling
			lda	#$39							; code for rts
			bra	IScrl0						; to disable scrolling							; 		 jr nc,iscrl0        ; no, disable messages.
1			lda	<reg_B						; get message number								; 		 ld a,c              ; message number.
																											; 		 ld d,b              ; copy width to d.
			jsr	GetWrd						; find beginning of message					; 		 call getwrd         ; find message start.
																											; 		 ld b,d              ; restore width to b register.
			stx	<txtIni						; set pointer to text beginning				; 		 ld (txtini),hl      ; set initial text position.
			lda	#$fc							; code for "ldd" extended addressing		; 		 ld a,42             ; code for ld hl,(nn).
IScrl0	sta	Scrly							; modify code to enable routine				; iscrl0 ld (scrly),a        ; enable/disable scrolling routine.
			jsr	Prescr						; pre-print routine								; 		 call prescr         ; set up display position.
			jsr	GPrad							; get print address								; 		 call gprad          ; get print address.
													 		  												;		 ld l,b              ; width in b so copy to hl.
													 		 												;		 ld h,0              ; no high byte.
													 		 												;		 dec hl              ; width minus one.
													 		 												;		 add hl,de           ; add width.
			std	<txtScr						; set text screen pointer						; 		 ld (txtscr),hl      ; set text screen address.
			lda	<reg_C						; get width											; 		 ld a,b              ; width.
			sta	<txtWid						; into variable									; 		 ld (txtwid),a       ; set width in working storage.
																											; 		 ld hl,txtbit        ; bit of text to display.
			lda	#128							; set bit 7
			sta	<txtBit						; in that byte										; 		 ld (hl),128         ; start with leftmost bit.
			bra	Scrly4						; exit updating pointer							; 		 jr scrly4
	ENDIF

; ------------------------------------------------------------------------------------------------------------------------------------------
; Dig routine, conditional assembly depending on DFLAG
; register A arrives with the dig direction
; ------------------------------------------------------------------------------------------------------------------------------------------
	IF DFLAG																								; .if dflag
Dig		ldy	<reg_IX						; get sprite pointer								; dig:
			sta	<reg_A						; save move direction
			ldd	8,y							; get Y and X coordinates

			tst	<reg_A						; was 0?												; 	and #3
			beq	DigR							; yes, move right									; 	beq digr		; dig right
			dec	<reg_A						; was it 1?											; 	cmp #1
			beq	DigL							; yes, move left									; 	beq digl		; dig left
			dec	<reg_A						; was it 2?											; 	cmp #2
			beq	DigD							; yes, move down									; 	beq digd		; dig down
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
DigU												; it was 3, move up								; digu:				; dig up
																											; 	ldy #8
																											; 	lda (z80_ix),y
																											; 	sec
			suba	#2								; point 1st block above							; 	sbc #2
																											; 	sta dispy		; set y
																											; 	iny
																											; 	lda (z80_ix),y
																											; 	sta dispx		; set x
			bra	DigV							; go move vertically								; 	jmp digv
																											; 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
DigD																										; digd:
																											; 	ldy #9
																											; 	lda (z80_ix),y
																											; 	sta dispx		; set y
																											; 	dey
																											; 	clc
																											; 	lda (z80_ix),y
			adda	#16							; point to first block below					; 	adc #16
																											; 	sta dispy		; set y
																											; 	jmp digv
																											; 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
																											; ; Vertical digging
DigV																										; digv:
																											; 	jsr tstbl		; check blocktype in MAP
			std	<dispX						; update Y and X variables						; 	jsr fdchk		; test if FODDER
			bsr	TstFod
																											; 	clc
			lda	<dispY						; get X variable									; 	lda dispx		; look 1 cell down
			adda	#8								; point to block on the right					; 	adc #8
			sta	<dispY						; update X variable								; 	sta dispx
																											; 	jsr tstbl		; check blocktype in MAP
																											; 	jsr fdchk
			bsr	TstFod
			lda	<dispY						; get X variable									; 	lda dispx
			anda	#7								; test 3 lower bits								; 	and #7
			bne	DigV1							; if not zero skip next							; 	bne :+
			rts									; return												; 	rts
DigV1																										; :
																											; 	clc
			lda	<dispY						; get X variable									; 	lda dispx		; look 1 cell down
			adda	#8								; point to next block on the right			; 	adc #8
			sta	<dispY						; update X variable								; 	sta dispx
																											; 	jsr tstbl		; check blocktype in MAP
			bra	TstFod																				; 	jmp fdchk
		
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
DigL																										; digl:
																											; 	ldy #8
																											; 	lda (z80_ix),y
																											; 	sta dispy		; set y
																											; 	iny
																											; 	lda (z80_ix),y
																											; 	sec
			subb	#2								; point to 1st block on the left				; 	sbc #2			; x=x-2
																											; 	sta dispx		; set x
			bra	DigH							; go move horizontally							; 	jmp digh
																											; 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
DigR																										; digr:
																											; 	ldy #8
																											; 	lda (z80_ix),y
																											; 	sta dispy		; set y
																											; 	iny
																											; 	lda (z80_ix),y
																											; 	clc
			addb	#16							; point to 1st block on the right			; 	adc #16
																											; 	sta dispx		; set x+16
																											; 	jmp digh
																											; 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
																											; ; Horizontal digging
DigH																										; digh:
																											; 	jsr tstbl		; check blocktype in MAP
			std	<dispX						; update Y and X variables						; 	jsr fdchk		; test if FODDER
			bsr	TstFod
																											; 	clc
			lda	<dispX						; get Y variable									; 	lda dispy		; look 1 cell down
			adda	#8								; point to next block below					; 	adc #8
			sta	<dispX						; update Y variable								; 	sta dispy
																											; 	jsr tstbl		; check blocktype in MAP
																											; 	jsr fdchk
			bsr	TstFod
			lda	<dispX						; get Y variable									; 	lda dispy
			anda	#7								; test 3 lower bits								; 	and #7
			bne	DigH1							; if not zero skip next							; 	bne :+
			rts									; return												; 	rts
DigH1																										; :
																											; 	clc
			lda	<dispX						; get Y variable									; 	lda dispy		; look 1 cell down
			adda	#8								; point to next block below					; 	adc #8
			sta	<dispX						; update Y variable								; 	sta dispy
																											; 	jsr tstbl		; check blocktype in MAP
																											; 	jmp fdchk
																											; digcnt:	.byte 0
																											; 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
TstFod	ldd	<dispX						; get both variables
			pshs	d								; save onto stack
			jsr	TstBl							; check type of pointed block in map
			jsr	FdChk							; clean it if it is Fodder
			puls	d								; restore pushed values
			std	<dispX						; set variables again
			rts									; return
	ENDIF																									; .endif
; ------------------------------------------------------------------------------------------------------------------------------------------
																											; Sprite table.
																											; ix+0  = type.
																											; ix+1  = sprite image number.
																											; ix+2  = frame.
																											; ix+3  = x coord.
																											; ix+4  = y coord.

																											; ix+5  = new type.
																											; ix+6  = new image number.
																											; ix+7  = new frame.
																											; ix+8  = new x coord.
																											; ix+9  = new y coord.

																											; ix+10 = direction.
																											; ix+11 = parameter 1.
																											; ix+12 = parameter 2.
																											; ix+13 = jump pointer low.
																											; ix+14 = jump pointer high.
																											; ix+15 = data pointer low.
																											; ix+16 = data pointer high.
; ------------------------------------------------------------------------------------------------------------------------------------------
; User routine.  Put your own code in here to be called with USER instruction.
; if USER has an argument it will be passed in the accumulator.
; ------------------------------------------------------------------------------------------------------------------------------------------
User   rts
; ------------------------------------------------------------------------------------------------------------------------------------------
;  												END OF STD ENGINE ###1
; ------------------------------------------------------------------------------------------------------------------------------------------

; ------------------------------------------------------------------------------------------------------------------------------------------
; 													NEW functions added to the script AGD system ###2
; -----------------------------------------------------------------------	
; Sets the foreground mask at andeor so that foreground pixels 
; that are red designed do convert to the FG desired colour
; when finally eor BG mask is applied
; receives colour at register A (0-1-2-3)
; -----------------------------------------------------------------------	
SetFGcol	anda	#3								; avoid values greater than 3
			ldx	#codCol						; point to colour table
			ldb	a,x							; get its value
			bra	CalFGC						; calculate AND mask
; -----------------------------------------------------------------------	
; -----------------------------------------------------------------------	
; Sets the background mask at andeor+1 so that background pixels 
; that are green designed do convert to the BG desired colour
; At the same time corrects the mask for foreground colour
; receives colour at register A (0-1-2-3)
; -----------------------------------------------------------------------	
SetBGcol	anda	#3								; avoid values greater than 3
CalBGC	ldx	#codCol						; point to colours table
			lda	a,x							; get chosen one
			ldb	<andeor						; get value for FG colour
			eorb	<andeor+1					; calculate 'real' desired colour
			sta	<andeor+1					; set new value for Backgroud (EOR mask)
CalFGC	eorb	<andeor+1					; apply eor with current BG colour to current FG
			stb	<andeor						; save as value for Foreground (AND mask)
CalEx1	rts									; return
; -----------------------------------------------------------------------	
													; GREEN - YELLOW - BLUE - RED
codCol	fcb	$00,$55,$aa,$ff			; values for 4 pixels coloured 
; -----------------------------------------------------------------------	


; ------------------------------------------------------------------------------------------------------------------------------------------
; 													6809 Added constants, variables and subroutines ###3
; ------------------------------------------------------------------------------------------------------------------------------------------
READKEY		equ	$a000						; indirect call to read keyboard (both machines)
KEYMATRIX	equ	$0152
SCRBEG		equ	$e600						; to make it CoCo-Compatible (with discs)
SCREND		equ	SCRBEG+$1800			; $e600+6144=$fe00
	IF GFLAG
scrMode		equ	$e0						; $e0	PMODE3 green palete
													; $e8 PMODE3 buff palete
	ELSE
scrMode		equ	$f8						; $f8 PMODE4 artifacted colors
													; $f0 PMODE4 green monochrome
	ENDIF
setPIA 		equ	$ff22						; Screen selection address
SCRROWS		equ	192						; number of screen rows
TIMER			equ	$0113						; IRQ managed 1 byte timer
; ------------------------------------------------------------------------------------------------------------------------------------------
; switch to MAP1 copying only the Basic Interpreter, NO DOS
; ------------------------------------------------------------------------------------------------------------------------------------------
SwMap1	ldx	#$015e						; point to hooks beginning
			lda	#$39							; opcode for RTS
SwML01	sta	,x+							; disable hoop
			cmpx	#$1a9							; got to the end?
			blo	SwML01						; no, loopback
			ldx	#$8000						; point to std BASIC ROM
SwML02	sta	$ffde							; switch to MAP0 (RAM-ROM)
			ldd	,x								; get a word
			sta	$ffdf							; switch to MAP1 (all 64k RAM)
			std	,x++							; put at destination
			cmpx	#$c000 						; copied full ROMs?
			blo	SwML02						; no, loopback
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; exit the program and return to the Interpreter 
; ------------------------------------------------------------------------------------------------------------------------------------------
ExitGame	fcb	$11,$3d,$00					; ldmd #0 (enter emulation mode)
			clr	$71							; set cold restart
			sta	$ffde							; back to MAP0
			andcc	#$af							; enable interrupts
			jmp	[$fffe]						; restart computer
; ------------------------------------------------------------------------------------------------------------------------------------------
; reads keyboard returns keypress in A (zero or a column number)
;  changed to avoid last ROM call. Now 1st RAM page is free for variables!!
; ------------------------------------------------------------------------------------------------------------------------------------------
ReadK		jsr	[READKEY]					; system call to read keyboard
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; Sets the graphic Mode and points to the graph page beginning
; ------------------------------------------------------------------------------------------------------------------------------------------
SetPMode	sta	$ffc0							; set SAM
			sta	$ffc3							;   for 
			sta	$ffc5							;   PMODE4
			lda	#scrMode						; set PIA
			sta	setPIA						;   to PM4 green palete
												; set page = $e600/$200 = $73 = 115 = %1110011
			sta	$ffd3							; bit6 = 1
			sta	$ffd1							; bit5 = 1
			sta	$ffcf							; bit4 = 1
			sta	$ffcc							; bit3 = 0
			sta	$ffca							; bit2 = 0
			sta	$ffc9							; bit1 = 1
			sta	$ffc7							; bit0 = 1
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; config DAC sound and VSync detection at the end of frame
; ------------------------------------------------------------------------------------------------------------------------------------------
CfgHdw	clrb									; flag for Dragon machine
			lda	$fffe							; read high byte for Reset address
			cmpa	#$b3							; is it a Dragon? ($b3b4)
			beq	CfgHdw1						; yes, skip next
			incb									; set flag for CoCo machine
CfgHdw1	stb	<cocoFlg						; write to variable
			ldb	#keysD-keys					; get offset to Dragon codes
			tst	<cocoFlg						; is this a CoCo?
			beq	CfgNoCC						; no, skip next
			ldb	#keysC-keys					; get offset to CoCo codes
CfgNoCC	stb	<scanOff						; offset for scanning keys / joysticks
			lda	$ff01							; get config PIA0-SideA
			anda	#%11110100					; reset LSB of MUX. Disable HS IRQ to CPU
			sta	$ff01							; update config PIA0-SideA
			lda	$ff03							; get config PIA0-SideB
			anda	#%11110100					; reset MSB of MUX -> %00 select DAC sound. Flag set on falling edge
			ora	#%00000001					; Enable FS IRQ to CPU
			sta	$ff03							; update config PIA0-SideB
			clr	$ff20							; set zero sound volume
			lda	$ff23							; get config PIA1-SideB
			ora	#%00001000					; enable DAC sound
			sta	$ff23							; update config PIA1-SideB
			ldx	#IRQHndlr					; get new IRQ dispatcher address
			stx	$010d							; set in system hook
			andcc	#$ef							; allow IRQ			
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; new IRQ Handler (for Vertical Blanking interrupt)
; ------------------------------------------------------------------------------------------------------------------------------------------
IRQHndlr	lda	$ff03							; is an FS IRQ?
			bmi	IRQRcvd						; yes, skip next
			rti									; return from interrupt
IRQRcvd	lda	$ff02							; clear flag
			inc	TIMER							; increment counter
			rti									; return from interrupt
; ------------------------------------------------------------------------------------------------------------------------------------------
													; interchanges contents of registers BC, DE and HL with their mirrors (Z80 exx opcode)
													; here they are: reg_BC, reg_DE, reg_HL with esp_BC, esp_DE, esp_HL
do_exx	pshs	x,u							; save registers
			ldx	<reg_BC						; get register BC
			ldu	<esp_BC						; get mirror BC
			stx	<esp_BC						; put register into mirror
			stu	<reg_BC						; put mirror into register
			ldx	<reg_DE						; get register DE
			ldu	<esp_DE						; get mirror DE
			stx	<esp_DE						; put register into mirror
			stu	<reg_DE						; put mirror into register
			ldx	<reg_HL						; get register HL
			ldu	<esp_HL						; get mirror HL
			stx	<esp_HL						; put register into mirror
			stu	<reg_HL						; put mirror into register
			puls	x,u,pc						; restore registers and return
; ------------------------------------------------------------------------------------------------------------------------------------------
SetVars	ldx	#$0000						; poit to the beginning of variables - pointers
			ldb	#NUMVAR						; set counter
			clra									; create a 
SetMore	sta	,x+							; initialize 1 byte
			decb									; got past end?
			bne	SetMore						; no, loop
			ldx	#valTable					; point to values table
			ldy	#wnTopX						; point to first variable to be set
			ldb	#(endTabV-valTable)/2	; 10 words to be copied
GetVVal	ldu	,x++							; get one word	
			stu	,y++							; put into two variables or a pointer	
			decb									; decrement counter
			bne	GetVVal						; not yet done, loop
			rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; KeyGet - Calculates mask and value expected for row
; Input: <reg_A = index to choice to modify (0-10)
; Output: none
; Effect: modifies 2 tables: keys and (keysD or keysC (upon machine))
; at the requested index with calculated values on the key pressed
; ------------------------------------------------------------------------------------------------------------------------------------------
; offset from keys to keysD = +11, to keysC = +22
; <scanOff has the correct value for the machine being run
; ------------------------------------------------------------------------------------------------------------------------------------------
KGet		jsr	[READKEY]					; read keyboard
			beq	KGet							; no keypress? loopback
			lda	#$ff							; no column
			andcc	#%11111110					; clear carry. This is the zero to move left
			ldx	#KEYMATRIX					; point to 1st column
KGet01	rola									; create columns mask sequence: $FE-$FD-$FB-$F7-$EF-$DF-$BF-$7F
			ldb	,x+							; read this column result
			cmpb	#255							; any key pressed?
			bne	KGetFnd						; yes, process it
			cmpa	#$7f							; all columns verified?
			beq	KGetEx						; yes, exit. Should NEVER happen with 'normal' keystrokes
			orcc	#%00000001					; set carry. A one must enter by the right
			bra	KGet01						; read next column
KGetFnd	stb	<reg_B						; save column received value
			ldx	#keys							; point to offsets table
			ldb	<reg_A						; get offset to requested choice to be modified
			abx									; point to requested choice
			sta	,x								; update offset with calculated one
			ldb	#$ff							; get no key
			subb	<reg_B						; subtract received value. Result = expected value for key
			lda	<scanOff						; get offset to expected values for current computer
			stb	a,x							; update expected value. Only on table for the current computer
KGetEx	rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
; Initial values to be assigned to some variables 
; ------------------------------------------------------------------------------------------------------------------------------------------
valTable	fcb	8*WINDOWTOP,8*WINDOWLFT,WINDOWTOP*8+WINDOWHGT*8-16		; wnTopX,wnLftX,wnBotX
			fcb	WINDOWLFT*8+WINDOWWID*8-16										; wnRgtX
			fcb	$00,$ff,$03,255,254,255,34,128,16							; scNo,varOpt,numLif,varRnd,varObj,varBlk,roomTb,txtBit,txtWid
			fcb	WINDOWTOP,WINDOWLFT,WINDOWHGT,WINDOWWID,NUMOBJ		 	; winTop,winLft,winHgt,winWid,numOb
			fdb	frmLst,chgFx,bProp,scDat,nmeDat,$ff00						; frmPtr,blkPtr,proPtr,scrPtr,nmePtr,andeor
			fdb	msgDat,$0000,msgDat,SCRBEG										; txtPos,zero16b,tstIni,tstScr
endTabV	equ	*
; ------------------------------------------------------------------------------------------------------------------------------------------
Set6309	fcb   $10,$86,$55,$55			; ldw	#$5555 	(load the double register W = regE+regF)
			fcb   $1f,$61						; tfr	w,x	 	(transfer to regX)
			cmpx  #$ffff						; did it fail?	(will fail on a 6809)
			beq   ES6309						; yes, skip next						
			fcb   $11,$3d,$01	     			; ldmd  #$01 	(enter native mode)
ES6309 	rts									; return
; ------------------------------------------------------------------------------------------------------------------------------------------
EndMotor	equ	*
MotorLen	equ	EndMotor-Start
; ------------------------------------------------------------------------------------------------------------------------------------------
