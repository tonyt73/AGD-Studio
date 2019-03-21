;The problem is that if text passes column 31, a newline is executed.
;
;In the Spectrum AGD4.7 version no newline is executed because text is automatically 1 line down due to screen memory addresses.
;
;You can check the solution in the Atom engine in the gprad and nexpos routines. If DispX>31 then Y is incremented in address calculation, not DispY.
;Baby Monkey Alba 
; Flags set manually
;	aflag			; adventure mode
;	bflag			; big sprites (16x24)
;	pflag			; palette flag, 0: no palette change, 1: EP palette (8 colors+1 Bias), 2: 8 colors from ULA+ palette)

;Object detect problem
;Visual C++ 2015 x64 x86 cross Build Tools Command prompt
;cl /EHsc compileEP.c

; Game engine code --------------------------------------------------------------

; Arcade Game Designer.
; (C) 2008 - 2018 Jonathan Cauldwell.
; Enterprise Engine v0.7.

; Global definitions.

SIMASK equ 0f8h            ; SPRITEINK mask - allows users to set BRIGHT/FLASH/CLUT as well.
SHRAPN equ 0deb6h   ;63926 ; shrapnel table, just below screen address table. 0f9b6h
SCADTB equ 0fb00h   ;64256 ; screen address table, just below map.
MAP    equ 0fd00h   ;64768 ; properties map buffer.
loopa  equ 0100h    ;23681 ; loop counter system variable.
loopb  equ 0101h    ;23728 ; loop counter system variable.
loopc  equ 0102h    ;23729 ; loop counter system variable.

; Block characteristics.

PLATFM equ 1               ; platform.
WALL   equ PLATFM + 1      ; solid wall.
LADDER equ WALL + 1        ; ladder.
FODDER equ LADDER + 1      ; fodder block.
DEADLY equ FODDER + 1      ; deadly block.
CUSTOM equ DEADLY + 1      ; custom block.
WATER  equ CUSTOM + 1      ; water block.
COLECT equ WATER + 1       ; collectable block.
NUMTYP equ COLECT + 1      ; number of types.

; Sprites.
    if bflag 
SPR_HGT	equ 24               ; Sprite height
SPR_WID equ 16               ; Sprite width
NUMSPR	equ 8	               ; number of sprites.
    else	               ; 16x16 sprites
SPR_HGT equ 16               ; Sprite height
SPR_WID equ 16               ; Sprite width
NUMSPR	equ 12               ; number of sprites.
    endif

TABSIZ equ 17              ; size of each entry.
SPRBUF equ NUMSPR * TABSIZ ; size of entire table.
NMESIZ equ 4               ; bytes stored in nmetab for each sprite.
X      equ 8               ; new x coordinate of sprite.
Y      equ X + 1           ; new y coordinate of sprite.
PAM1ST equ 5               ; first sprite parameter, old x (ix+5).

; Particle engine.

NUMSHR equ 55              ; pieces of shrapnel.
SHRSIZ equ 6               ; bytes per particle.


; Game starts here.  No reason why screen data couldn't go between start and contrl to put them in
; contended RAM, leaving the code and rest of the game in uncontended memory at 32768 and beyond.

start  equ $

; Set up the font.

       ld hl,font-256      ; address of font.
       inc h
       jr z,nofont
       dec h
       ld (fontadr+1),hl   ; set up game font.  23606
nofont
       jp game             ; start the game.

joyval defb 0              ; joystick reading.
frmno  defb 0              ; selected frame.

; Don't change the order of these four.  Menu routine relies on winlft following wintop.

wintop defb WINDOWTOP      ; top of window.
winlft defb WINDOWLFT      ; left edge.
winhgt defb WINDOWHGT      ; window height.
winwid defb WINDOWWID      ; window width.

numob  defb NUMOBJ         ; number of objects in game.

; Variables start here.
; Pixel versions of wintop, winlft, winhgt, winwid.

wntopx defb (8 * WINDOWTOP)
wnlftx defb (8 * WINDOWLFT)
wnbotx defb ((WINDOWTOP * 8) + (WINDOWHGT * 8) - 16)
wnrgtx defb ((WINDOWLFT * 8) + (WINDOWWID * 8) - 16)
scno   defb 0              ; present screen number.
numlif defb 3              ; number of lives.
vara   defb 0              ; general-purpose variable.
varb   defb 0              ; general-purpose variable.
varc   defb 0              ; general-purpose variable.
vard   defb 0              ; general-purpose variable.
vare   defb 0              ; general-purpose variable.
varf   defb 0              ; general-purpose variable.
varg   defb 0              ; general-purpose variable.
varh   defb 0              ; general-purpose variable.
vari   defb 0              ; general-purpose variable.
varj   defb 0              ; general-purpose variable.
vark   defb 0              ; general-purpose variable.
varl   defb 0              ; general-purpose variable.
varm   defb 0              ; general-purpose variable.
varn   defb 0              ; general-purpose variable.
varo   defb 0              ; general-purpose variable.
varp   defb 0              ; general-purpose variable.
varq   defb 0              ; general-purpose variable.
varr   defb 0              ; general-purpose variable.
vars   defb 0              ; general-purpose variable.
vart   defb 0              ; general-purpose variable.
varu   defb 0              ; general-purpose variable.
varv   defb 0              ; general-purpose variable.
varw   defb 0              ; general-purpose variable.
varz   defb 0              ; general-purpose variable.
contrl defb 0              ; control, 0 = keyboard, 1 = Kempston, 2 = Sinclair, 3 = Mouse.
charx  defb 0              ; cursor x position.
chary  defb 0              ; cursor y position.
clock  defb 0              ; last clock reading.
varrnd defb 255            ; last random number.
varobj defb 254            ; last object number.
varopt defb 255            ; last option chosen from menu.
varblk defb 255            ; block type.
nexlev defb 0              ; next level flag.
restfl defb 0              ; restart screen flag.
deadf  defb 0              ; dead flag.
gamwon defb 0              ; game won flag.
dispx  defb 0              ; cursor x position.
dispy  defb 0              ; cursor y position.

; Make sure pointers are arranged in the same order as the data itself.

frmptr defw frmlst         ; sprite frames.
blkptr defw chgfx          ; block graphics.
colptr defw bcol           ; address of char colours.
proptr defw bprop          ; address of char properties.
scrptr defw scdat          ; address of screens.
nmeptr defw nmedat         ; enemy start positions.

; Assorted game routines which can go in contended memory.

; Modify for inventory.

minve  ld hl,invdis        ; routine address.
       ld (mod0+1),hl      ; set up menu routine.
       ld (mod2+1),hl      ; set up count routine.
       ld hl,fopt          ; find option from available objects.
       ld (mod1+1),hl      ; set up routine.
       jr dbox             ; do menu routine.

; Modify for menu.

mmenu  ld hl,always        ; routine address.
       ld (mod0+1),hl      ; set up routine.
       ld (mod2+1),hl      ; set up count routine.
       ld hl,fstd          ; standard option selection.
       ld (mod1+1),hl      ; set up routine.

; Drop through into box routine.

; Work out size of box for message or menu.

;dbox   ld hl,nummsg        ; total messages.
;       cp (hl)             ; does this one exist?
;       ret nc              ; no, nothing to display.
dbox   ld hl,msgdat        ; pointer to messages.
       call getwrd         ; get message number.
       push hl             ; store pointer to message.
       ld d,1              ; height.
       xor a               ; start at object zero.
       ld (combyt),a       ; store number of object in combyt.
       ld e,a              ; maximum width.
dbox5  ld b,0              ; this line's width.
mod2   call always         ; item in player's possession?
       jr nz,dbox6         ; not in inventory, skip this line.
       inc d               ; add to tally.
dbox6  ld a,(hl)           ; get character.
       inc hl              ; next character.
       cp ','              ; reached end of line?
       jr z,dbox3          ; yes.
       cp 13               ; reached end of line?
       jr z,dbox3          ; yes.
       inc b               ; add to this line's width.
       and a               ; end of message?
       jp m,dbox4          ; yes, end count.
       jr dbox6            ; repeat until we find the end.
dbox3  ld a,e              ; maximum line width.
       cp b                ; have we exceeded longest so far?
       jr nc,dbox5         ; no, carry on looking.
       ld e,b              ; make this the widest so far.
       jr dbox5            ; keep looking.
dbox4  ld a,e              ; maximum line width.
       cp b                ; have we exceeded longest so far?
       jr nc,dbox8         ; no, carry on looking.
       ld e,b              ; final line is the longest so far.
dbox8  dec d               ; decrement items found.
       jp z,dbox15         ; total was zero.
       ld a,e              ; longest line.
       and a               ; was it zero?
       jp z,dbox15         ; total was zero.
       ld (bwid),de        ; set up size.

; That's set up our box size.

       ld a,(winhgt)       ; window height in characters.
       sub d               ; subtract height of box.
       rra                 ; divide by 2.
       ld hl,wintop        ; top edge of window.
       add a,(hl)          ; add displacement.
       ld (btop),a         ; set up box top.
       ld a,(winwid)       ; window width in characters.
       sub e               ; subtract box width.
       rra                 ; divide by 2.
       inc hl              ; left edge of window.
       add a,(hl)          ; add displacement.
       ld (blft),a         ; box left.
       ld hl,(fontadr+1)   ; font.
       ld (grbase),hl      ; set up for text display.
       pop hl              ; restore message pointer.
       ld a,(btop)         ; box top.
       ld (dispx),a        ; set display coordinate.
       xor a               ; start at object zero.
       ld (combyt),a       ; store number of object in combyt.
dbox2  ld a,(combyt)       ; get object number.
mod0   call always         ; check inventory for display.
       jp nz,dbox13        ; not in inventory, skip this line.

       ld a,(blft)         ; box left.
       ld (dispy),a        ; set left display position.
       ld a,(bwid)         ; box width.
       ld b,a              ; store width.
dbox0  ld a,(hl)           ; get character.
       cp ','              ; end of line?
       jr z,dbox1          ; yes, next one.
       cp 13               ; end of option?
       jr z,dbox1          ; yes, on to next.
       dec b               ; one less to display.
       and 127             ; remove terminator.
       push bc             ; store characters remaining.
       push hl             ; store address on stack.
       push af             ; store character.
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; current colour.
       ld (hl),a           ; set attribute.
       pop af              ; restore character.
       call pchr           ; display on screen.
       pop hl              ; retrieve address of next character.
       pop bc              ; chars left for this line.
       ld a,(hl)           ; get character.
       inc hl              ; next character.
       cp 128              ; end of message?
       jp nc,dbox7         ; yes, job done.
       ld a,b              ; chars remaining.
       and a               ; are any left?
       jr nz,dbox0         ; yes, continue.

; Reached limit of characters per line.

dbox9  ld a,(hl)           ; get character.
       inc hl              ; next one.
       cp ','              ; another line?
       jr z,dbox10         ; yes, do next line.
       cp 13               ; another line?
       jr z,dbox10         ; yes, on to next.
       cp 128              ; end of message?
       jr nc,dbox11        ; yes, finish message.
       jr dbox9

; Fill box to end of line.

dboxf  push hl             ; store address on stack.
       push bc             ; store characters remaining.
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; current colour.
       ld (hl),a           ; set attribute.
       ld a,32             ; space character.
       call pchr           ; display character.
       pop bc              ; retrieve character count.
       pop hl              ; retrieve address of next character.
       djnz dboxf          ; repeat for remaining chars on line.
       ret
dbox1  inc hl              ; skip character.
       call dboxf          ; fill box out to right side.
dbox10 ld a,(dispx)        ; x coordinate.
       inc a               ; down a line.
       ld (dispx),a        ; next position.
       jp dbox2            ; next line.
dbox7  ld a,b              ; chars remaining.
       and a               ; are any left?
       jr z,dbox11         ; no, nothing to draw.
       call dboxf          ; fill message to line.

; Drawn the box menu, now select option.

dbox11 ld a,(btop)         ; box top.
       ld (dispx),a        ; set bar position.
dbox14 call joykey         ; get controls.
       and 31              ; anything pressed?
       jr nz,dbox14        ; yes, debounce it.
       call dbar           ; draw bar.
dbox12 call joykey         ; get controls.
       and 13h             ; anything pressed?
       jr z,dbox12         ; no, nothing.
       and 10h             ; fire button pressed?
mod1   jp nz,fstd          ; yes, job done.
       call dbar           ; delete bar.
       ld a,(joyval)       ; joystick reading.
       and 01h             ; going up?
       jr nz,dboxu         ; yes, go up.
       ld a,(dispx)        ; vertical position of bar.
       inc a               ; look down.
       ld hl,btop          ; top of box.
       sub (hl)            ; find distance from top.
       dec hl              ; point to height.
       cp (hl)             ; are we at end?
       jp z,dbox14         ; yes, go no further.
       ld hl,dispx         ; coordinate.
       inc (hl)            ; move bar.
       jr dbox14           ; continue.
dboxu  ld a,(dispx)        ; vertical position of bar.
       ld hl,btop          ; top of box.
       cp (hl)             ; are we at the top?
       jp z,dbox14         ; yes, go no further.
       ld hl,dispx         ; coordinate.
       dec (hl)            ; move bar.
       jr dbox14           ; continue.
fstd   ld a,(dispx)        ; bar position.
       ld hl,btop          ; top of menu.
       sub (hl)            ; find selected option.
       ld (varopt),a       ; store the option.
       jp redraw           ; redraw the screen.

; Option not available.  Skip this line.

dbox13 ld a,(hl)           ; get character.
       inc hl              ; next one.
       cp ','              ; another line?
       jp z,dbox2          ; yes, do next line.
       cp 13               ; another line?
       jp z,dbox2          ; yes, on to next line.
       and a               ; end of message?
       jp m,dbox11         ; yes, finish message.
       jr dbox13
dbox15 pop hl              ; pop message pointer from the stack.
       ret

dbar   ld a,(blft)         ; box left.
       ld (dispy),a        ; set display coordinate.
       call gprad          ; get printing address.
       ex de,hl            ; flip into hl register pair.
       ld a,(bwid)         ; box width.
       ld c,a              ; loop counter in c.
       ld d,h              ; store screen address high byte.
dbar1  ld b,8              ; pixel height in b.
dbar0  ld a,(hl)           ; get screen byte.
       cpl                 ; reverse all bits.
       ld (hl),a           ; write back to screen.
       inc h               ; next line down.
       djnz dbar0          ; draw rest of character.
       ld h,d              ; rsetore screen address.
       inc l               ; one char right.
       dec c               ; decrement character counter.
       jr nz,dbar1         ; repeat for whole line.
       ret

invdis push hl             ; store message text pointer.
       push de             ; store de pair for line count.
       ld hl,combyt        ; object number.
       ld a,(hl)           ; get object number.
       inc (hl)            ; ready for next one.
       call gotob          ; check if we have object.
       pop de              ; retrieve de pair from stack.
       pop hl              ; retrieve text pointer.
       ret
;always xor a               ; set zero flag.
;       ret

; Find option selected.

fopt   ld a,(dispx)
       ld hl,btop          ; top of menu.
       sub (hl)            ; find selected option.
       inc a               ; object 0 needs one iteration, 1 needs 2 and so on.
       ld b,a              ; option selected in b register.
       ld hl,combyt        ; object number.
       ld (hl),0           ; set to first item.
fopt0  push bc             ; store option counter in b register.
       call fobj           ; find next object in inventory.
       pop bc              ; restore option counter.
       djnz fopt0          ; repeat for relevant steps down the list.
       ld a,(combyt)       ; get option.
       dec a               ; one less, due to where we increment combyt.
       ld (varopt),a       ; store the option.
       jp redraw           ; redraw the screen.

fobj   ld hl,combyt        ; object number.
       ld a,(hl)           ; get object number.
       inc (hl)            ; ready for next item.
       ret z               ; in case we loop back to zero.
       call gotob          ; do we have this item?
       ret z               ; yes, it's on the list.
       jr fobj             ; repeat until we find next item in pockets.

bwid   defb 0              ; box/menu width.
blen   defb 0              ; box/menu height.
btop   defb 0              ; box coordinates.
blft   defb 0

; Wait for keypress.
allkeys ld      b,0ah
allkey1 ld      a,b
        dec     a
        out     (0b5h),a
        in      a,(0b5h)
        ld      e,a
        cp      0ffh
        ret     nz
        djnz    allkey1
        ret

getkeym ld      a,0f0h
getkm1  add     a,10h
        rr      e
        jr      c,getkm1
        add     a,b
        dec     a
        ret

prskey call debkey         ; debounce key.
prsky0 call vsync          ; vertical synch.
       call allkeys        ; return keyboard state in e.
       inc e               ; is it 255?
       jr z,prsky0         ; yes, repeat until key pressed.
       ret
; Debounce keypress.

debkey call vsync          ; update scrolling, sounds etc.
       call allkeys        ; return keyboard state in e.
       inc e               ; is it 255?
       jr nz,debkey        ; no - loop until key is released.
       ret

; Delay routine.

delay  push bc             ; store loop counter.
       call vsync          ; wait for interrupt.
       pop bc              ; restore counter.
       djnz delay          ; repeat.
       ret

; Clear sprite table.

xspr   ld hl,sprtab        ; sprite table.
       ld b,SPRBUF         ; length of table.
xspr0  ld (hl),255         ; clear one byte.
       inc hl              ; move to next byte.
       djnz xspr0          ; repeat for rest of table.
       ret

silenc call silen1         ; silence channel 1.
       call silen2         ; silence channel 2.
       call silen3         ; silence channel 3.
       jp plsnd            ; play all channels to switch them off.

; Initialise all objects.

iniob  ld ix,objdta        ; objects table.
       ld a,(numob)        ; number of objects in the game.
       ld b,a              ; loop counter.
       ld de,39            ; distance between objects.
iniob0 ld a,(ix+36)        ; start screen.
       ld (ix+33),a        ; set start screen.
       ld a,(ix+37)        ; find start x.
       ld (ix+34),a        ; set start x.
       ld a,(ix+38)        ; get initial y.
       ld (ix+35),a        ; set y coord.
       add ix,de           ; point to next object.
       djnz iniob0         ; repeat.
       ret

; Screen synchronisation.

vsync  call joykey         ; read joystick/keyboard.
       ld a,(sndtyp)       ; sound to play.
       and a               ; any sound?
       jp z,vsync1         ; no.
       ld b,a
;       and a               ; test it.
       jp m,vsync6         ; play white noise.
volval ld c,00h
vsync2 ld a,c              ; get speaker value.
       out (0ach),a        ; write to speaker.
       xor 0fh             ; toggle all except the border bits.
       ld c,a              ; store value for next time.
       ld d,b              ; store loop counter.
vsync3 ld hl,clock         ; previous clock setting.
       ld a,(curclk+1)     ; current clock setting.
       cp (hl)             ; subtract last reading.
       jp nz,vsync4        ; yes, no more processing please.
       djnz vsync3         ; loop.
       ld b,d              ; restore loop counter.
       djnz vsync2         ; continue noise.
vsync4 ;ld a,c
       ;ld (volval+1),a
       ld a,d              ; where we got to.
       ;dec a
vsynca ld (sndtyp),a       ; remember for next time.
vsync1 ld a,(curclk+1)     ; clock low.
       rra                 ; rotate bit into carry.
       call c,vsync5       ; time to play sound and do shrapnel/ticker stuff.
       ld hl,clock         ; last clock reading.
vsync0 ld a,(curclk+1)     ; current clock reading.
       cp (hl)             ; are they the same?
       jr z,vsync0         ; yes, wait until clock changes.
       ld (hl),a           ; set new clock reading.
       ret
;vsync5 call plsnd          ; play sound.
vsync5 jp proshr           ; shrapnel and stuff.

; Play white noise.

vsync6 ld a,b              ; 128 - 255.
       sub 127
       ld b,a
       ld hl,clock         ; previous clock setting.
vsync7 ld a,r              ; get random speaker value.
       and 0fh             ; only retain the speaker/earphone bits.
       out (0ach),a        ; write to speaker.
       ld a,(curclk+1)     ; current clock setting.
       cp (hl)             ; subtract last reading.
       jr nz,vsync8        ; yes, no more processing please.
       ld a,b
       and 127
       inc a
vsync9 dec a
       jr nz,vsync9        ; loop.
       djnz vsync7         ; continue noise.
vsync8 xor a
       jr vsynca
sndtyp defb 0
;clock  defb 0              ; last clock reading.

; Redraw the screen.

; Remove old copy of all sprites for redraw.

redraw push ix             ; place sprite pointer on stack.
       call droom          ; show screen layout.
       call shwob          ; draw objects.
numsp0 ld b,NUMSPR         ; sprites to draw.
       ld ix,sprtab        ; sprite table.
redrw0 ld a,(ix+0)         ; old sprite type.
       inc a               ; is it enabled?
       jr z,redrw1         ; no, find next one.
       ld a,(ix+3)         ; sprite x.
       cp 177              ; beyond maximum?
       jr nc,redrw1        ; yes, nothing to draw.
       push bc             ; store sprite counter.
       call sspria         ; show single sprite.
       pop bc              ; retrieve sprite counter.
redrw1 ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       djnz redrw0         ; repeat for remaining sprites.
rpblc1 call dshrp          ; redraw shrapnel.
    if aflag
       call rbloc          ; draw blocks for this screen
    endif

       pop ix              ; retrieve sprite pointer.
       ret

; Clear screen routine.

cls    ld hl,scraddr       ; screen address.
       ld (hl),l           ; blank first byte.
       ld de,scraddr+1     ; second byte.
       ld bc,1800h         ; bytes to copy.
       ldir                ; blank them all.
       ld a,(acolor+1)     ; fetch attributes.
       ld (hl),a           ; set first attribute cell.
       ld bc,767           ; number of attributes.
       ldir                ; set all attributes.
       ld hl,0             ; set hl to origin (0, 0).
       ld (charx),hl       ; reset coordinates.
       ret

; Set palette routine and data.
; Palette.
; 48955 = register select port.
; 65339 = data read/write port.

; 48955 = write to register:
; d0-d5 : select register sub-group.
; d6-d7 : select register group.
;         00 = sub-group determines entry in palette table.
;         64 = mode select, write d0 to 65339 to toggle mode on/off.

; 65339 = data read/write:
; d0-d1 : blue intensity (last bit duplicated so Bb is Bbb)
; d2-d4 : red intensity
; d5-d7 : green intensity

    if  pflag=1
setpal1 ld a,b
        cp 09h
        ret nc
        cp 08h
        jr z,setbias
        push hl
        push de
        ld l,b
        ld h,high lptaddr
        ld b,0c0h
        ld de,0010h
setpcl  ld (hl),c
        add hl,de
        djnz setpcl
        pop de
        pop hl
        ret

setbias ld a,c
speakrv or 00h
        out (80h),a
        ret

setpal ld de,lptaddr+8     ; colors in LPT
       ld a,24*8           ; number of pixel rows
       ld bc,0008h
setpa1 ld hl,palett        ; palette we want.
       ldir
       ex de,hl
       ld c,08h
       add hl,bc
       ex de,hl
       dec a
       jr nz,setpa1
       ld a,(hl)
       out (80h),a
       ret
    endif
    if  pflag=2
setpal1 ld a,b
        cp 10h
        ret c
        cp 18h
        ret nc
        and 0fh
        push hl
        push de
        ld e,b
        ld d,00h
        ld hl,ulacolp
        add hl,de
        ld l,(hl)
        ld h,high lptaddr
        ld a,c
        call clulac
        ld a,b
        ld b,0c0h
        ld de,0010h
setpcl  ld (hl),a
        add hl,de
        djnz setpcl
        pop de
        pop hl
        ret

ulacolp db 08h,0ch,09h,0dh,0ah,0eh,0bh,0fh

setpal ld hl,palett+10h    ; palette we want.
       call clulac
       ld de,0010h
       ld c,00h+08h
       call setpcol
       ld c,04h+08h
       call setpcol
       ld c,01h+08h
       call setpcol
       ld c,05h+08h
       call setpcol
       ld c,02h+08h
       call setpcol
       ld c,06h+08h
       call setpcol
       ld c,03h+08h
       call setpcol
       ld c,07h+08h
setpcol
       ld a,(hl)
       call clulac
       ld a,b
       push hl
       ld l,c
       ld h,high lptaddr
       ld b,24*8
setpcx ld (hl),a
       add hl,de
       djnz setpcx
       pop hl
       inc hl
       ret
clulac ld b,00h
       rrca
       jr nc,nblue0
       set 5,b
nblue0 rrca
       jr nc,nblue1
       set 2,b
nblue1 rrca
       jr nc,nred0
       set 6,b
nred0  rrca
       jr nc,nred1
       set 3,b
nred1  rrca
       jr nc,nred2
       set 0,b
nred2  rrca
       jr nc,ngrn0
       set 7,b
ngrn0  rrca
       jr nc,ngrn1
       set 4,b
ngrn1  rrca
       ret nc
       set 1,b
       ret
    endif
endpal equ $

fdchk  ld a,(hl)           ; fetch cell.
       cp FODDER           ; is it fodder?
       ret nz              ; no.
       ld (hl),0           ; rewrite block type.
       push hl             ; store pointer to block.
       ld de,MAP           ; address of map.
       and a               ; clear carry flag for subtraction.
       sbc hl,de           ; find simple displacement for block.
       ld a,l              ; low byte is y coordinate.
       and 31              ; column position 0 - 31.
       ld (dispy),a        ; set up y position.
       add hl,hl           ; multiply displacement by 8.
       add hl,hl
       add hl,hl
       ld a,h              ; x coordinate now in h.
       ld (dispx),a        ; set the display coordinate.
       xor a               ; block to write.
       call pattr          ; write block.
       pop hl              ; restore block pointer.
       ret

; Colour a sprite.

cspr   ld a,(ix+8)         ; look at the vertical first.
       cp 177              ; is it out-of-range?
       ret nc              ; yes, can't colour it.
       rlca                ; divide by 64.
       rlca                ; quicker than 6 rrca operations.
       ld l,a              ; store in e register for now.
       and 3               ; mask to find segment.
       add a,high attaddr  ; attributes start at 88*256=22528.
       ld h,a              ; that's our high byte sorted.
       ld a,l              ; vertical/64 - same as vertical*4.
       and 0e0h            ; want a multiple of 32.
       ld l,a              ; vertical element calculated.
       ld a,(ix+9)         ; get horizontal position.
       rra                 ; divide by 8.
       rra
       rra
       and 31              ; want result in range 0-31.
       add a,l             ; add to existing low byte.
       ld l,a              ; that's the low byte done.

       ld de,30            ; distance to next line down.
       ld a,(ix+8)         ; x coordinate.
cspr2  ld b,3              ; default rows to write.
       and 7               ; does x straddle cells?
       jr nz,cspr0         ; yes, loop counter is good.
       dec b               ; one less row to write.
cspr0  ld a,(hl)           ; get attributes.
cspr3  and SIMASK          ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
       inc l               ; next cell.
       ld a,(hl)           ; get attributes.
cspr4  and SIMASK          ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
       inc l               ; next cell.
       ld a,(ix+9)         ; y coordinate.
       and 7               ; straddling cells?
       jr z,cspr1          ; no, only 2 wide.
       ld a,(hl)           ; get attributes.
cspr5  and SIMASK          ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
cspr1  add hl,de           ; next row.
       djnz cspr0
       ret

; Scrolly text and puzzle variables.

txtbit defb 128            ; bit to write.
txtwid defb 16             ; width of ticker message.
txtpos defw msgdat
txtini defw msgdat
txtscr defw scraddr+16h

; Specialist routines.
; Process shrapnel.

proshr ld ix,SHRAPN        ; table.
       ld b,NUMSHR         ; shrapnel pieces to process.
       ld de,SHRSIZ        ; distance to next.
prosh0 ld a,(ix+0)         ; on/off marker.
       rla                 ; check its status.
proshx call nc,prosh1      ; on, so process it.
       add ix,de           ; point there.
       djnz prosh0         ; round again.
       jp scrly
prosh1 push bc             ; store counter.
       call plot           ; delete the pixel.
       ld a,(ix+0)         ; restore shrapnel type.
       ld hl,shrptr        ; shrapnel routine pointers.
       call prosh2         ; run the routine.
       call chkxy          ; check x and y are good before we redisplay.
       pop bc              ; restore counter.
       ld de,SHRSIZ        ; distance to next.
       ret
prosh2 rlca                ; 2 bytes per address.
       ld e,a              ; copy to de.
       add hl,de           ; point to address of routine.
       ld a,(hl)           ; get address low.
       inc hl              ; point to second byte.
       ld h,(hl)           ; fetch high byte from table.
       ld l,a              ; put low byte in l.
       jp (hl)             ; jump to routine.

shrptr defw laser          ; laser.
       defw trail          ; vapour trail.
       defw shrap          ; shrapnel from explosion.
       defw dotl           ; horizontal starfield left.
       defw dotr           ; horizontal starfield right.
       defw dotu           ; vertical starfield up.
       defw dotd           ; vertical starfield down.
       defw ptcusr         ; user particle.

; Explosion shrapnel.

shrap  ld e,(ix+1)         ; get the angle.
       ld d,0              ; no high byte.
       ld hl,shrsin        ; shrapnel sine table.
       add hl,de           ; point to sine.

       ld e,(hl)           ; fetch value from table.
       inc hl              ; next byte of table.
       ld d,(hl)           ; fetch value from table.
       inc hl              ; next byte of table.
       ld c,(hl)           ; fetch value from table.
       inc hl              ; next byte of table.
       ld b,(hl)           ; fetch value from table.
       ld l,(ix+2)         ; x coordinate in hl.
       ld h,(ix+3)
       add hl,de           ; add sine.
       ld (ix+2),l         ; store new coordinate.
       ld (ix+3),h
       ld l,(ix+4)         ; y coordinate in hl.
       ld h,(ix+5)
       add hl,bc           ; add cosine.
       ld (ix+4),l         ; store new coordinate.
       ld (ix+5),h
       ret

dotl   dec (ix+5)          ; move left.
       ret
dotr   inc (ix+5)          ; move left.
       ret
dotu   dec (ix+3)          ; move up.
       ret
dotd   inc (ix+3)          ; move down.
       ret

; Check coordinates are good before redrawing at new position.

chkxy  ld hl,wntopx        ; window top.
       ld a,(ix+3)         ; fetch shrapnel coordinate.
       cp (hl)             ; compare with top window limit.
       jr c,kilshr         ; out of window, kill shrapnel.
       inc hl              ; left edge.
       ld a,(ix+5)         ; fetch shrapnel coordinate.
       cp (hl)             ; compare with left window limit.
       jr c,kilshr         ; out of window, kill shrapnel.

       inc hl              ; point to bottom.
       ld a,(hl)           ; fetch window limit.
       add a,15            ; add height of sprite.
       cp (ix+3)           ; compare with shrapnel x coordinate.
       jr c,kilshr         ; off screen, kill shrapnel.
       inc hl              ; point to right edge.
       ld a,(hl)           ; fetch shrapnel y coordinate.
       add a,15            ; add width of sprite.
       cp (ix+5)           ; compare with window limit.
       jr c,kilshr         ; off screen, kill shrapnel.

; Drop through.
; Display shrapnel.

plot   ld a,(ix+3)         ; x integer.
       cp 192              ; are we off the bottom of the screen?
       ret nc              ; yes, don't plot.
       ld l,a              ; copy coordinate to l.
       ld h,(ix+5)         ; y integer.
       ld (dispx),hl       ; workspace coordinates.
       ld a,(ix+0)         ; type.
       and a               ; is it a laser?
       jr z,plot1          ; yes, draw laser instead.
       ld a,h              ; which pixel within byte do we
       and 7               ; want to set first?
       ld d,0              ; no high byte.
       ld e,a              ; copy to de.
       ld hl,dots          ; table of small pixel positions.
       add hl,de           ; hl points to values we want to POKE to screen.
       ld e,(hl)           ; get value.
       call scadd          ; screen address.
       ld a,(hl)           ; see what's already there.
       xor e               ; merge with pixels.
       ld (hl),a           ; put back on screen.
       ret
plot1  call scadd          ; screen address.
       ld a,(hl)           ; fetch byte there.
       cpl                 ; toggle all bits.
       ld (hl),a           ; new byte.
       ret

kilshr ld (ix+0),128       ; switch off shrapnel.
       ret

;explc  defb 0              ; explosion counter.

shrsin defw 0,1024,391,946,724,724,946,391
       defw 1024,0,946,65144,724,64811,391,64589
       defw 0,64512,65144,64589,64811,64811,64589,65144
       defw 64512,0,64589,391,64811,724,65144,946

trail  dec (ix+1)          ; time remaining.
       jp z,trailk         ; time to switch it off.
       call qrand          ; get a random number.
       rra                 ; x or y axis?
       jr c,trailv         ; use x.
       rra                 ; which direction?
       jr c,traill         ; go left.
       inc (ix+5)          ; go right.
       ret
traill dec (ix+5)          ; go left.
       ret
trailv rra                 ; which direction?
       jr c,trailu         ; go up.
       inc (ix+3)          ; go down.
       ret
trailu dec (ix+3)          ; go up.
       ret
trailk ld (ix+3),200       ; set off-screen to kill vapour trail.
       ret

laser  ld a,(ix+1)         ; direction.
       rra                 ; left or right?
       jr nc,laserl        ; move left.
       ld b,8              ; distance to travel.
       jr laserm           ; move laser.
laserl ld b,248            ; distance to travel.
laserm ld a,(ix+5)         ; y position.
       add a,b             ; add distance.
       ld (ix+5),a         ; set new y coordinate.

; Test new block.

       ld (dispy),a        ; set y for block collision detection purposes.
       ld a,(ix+3)         ; get x.
       ld (dispx),a        ; set coordinate for collision test.
       call tstbl          ; get block type there.
       cp WALL             ; is it solid?
       jr z,trailk         ; yes, it cannot pass.
       cp FODDER           ; is it fodder?
       ret nz              ; no, ignore it.
       call fdchk          ; remove fodder block.
       jr trailk           ; destroy laser.

dots   defb 128,64,32,16,8,4,2,1

; Plot, preserving de.

plotde push de             ; put de on stack.
       call plot           ; plot pixel.
       pop de              ; restore de from stack.
       ret

; Shoot a laser.

shoot  ld c,a              ; store direction in c register.
       ld a,(ix+8)         ; x coordinate.
shoot1 add a,SPR_HGT/2-1   ; down 7 pixels.
       ld l,a              ; puty x coordinate in l.
       ld h,(ix+9)         ; y coordinate in h.
       push ix             ; store pointer to sprite.
       call fpslot         ; find particle slot.
       jr nc,vapou2        ; failed, restore ix.
       ld (ix+0),0         ; set up a laser.
       ld (ix+1),c         ; set the direction.
       ld (ix+3),l         ; set x coordinate.
       rr c                ; check direction we want.
       jr c,shootr         ; shoot right.
       ld a,h              ; y position.
;       dec a               ; left a pixel.
shoot0 and 248             ; align on character boundary.
       ld (ix+5),a         ; set y coordinate.
       jr vapou0           ; draw first image.
shootr ld a,h              ; y position.
       add a,15            ; look right.
       jr shoot0           ; align and continue.

; Create a bit of vapour trail.

vapour push ix             ; store pointer to sprite.
       ld l,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
vapou3 ld de,7*256+SPR_HGT/2-1  ; mid-point of sprite.
       add hl,de           ; point to centre of sprite.
       call fpslot         ; find particle slot.
       jr c,vapou1         ; no, we can use it.
vapou2 pop ix              ; restore sprite pointer.
       ret                 ; out of slots, can't generate anything.

vapou1 ld (ix+3),l         ; set up x.
       ld (ix+5),h         ; set up y coordinate.
       call qrand          ; get quick random number.
       and 15              ; random time.
       add a,15            ; minimum time on screen.
       ld (ix+1),a         ; set time on screen.
       ld (ix+0),1         ; define particle as vapour trail.
vapou0 call chkxy          ; plot first position.
       jr vapou2

; Create a user particle.

ptusr  ex af,af'           ; store timer.
       ld l,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
       ld de,7*256+7       ; mid-point of sprite.
       add hl,de           ; point to centre of sprite.
       call fpslot         ; find particle slot.
       jr c,ptusr1         ; no, we can use it.
       ret                 ; out of slots, can't generate anything.

ptusr1 ld (ix+3),l         ; set up x.
       ld (ix+5),h         ; set up y coordinate.
       ex af,af'           ; restore timer.
       ld (ix+1),a         ; set time on screen.
       ld (ix+0),7         ; define particle as user particle.
       jp chkxy            ; plot first position.


; Create a vertical or horizontal star.

star   push ix             ; store pointer to sprite.
       call fpslot         ; find particle slot.
       jr c,star7          ; found one we can use.
star0  pop ix              ; restore sprite pointer.
       ret                 ; out of slots, can't generate anything.

star7  ld a,c              ; direction.
       and 3               ; is it left?
       jr z,star1          ; yes, it's horizontal.
       dec a               ; is it right?
       jr z,star2          ; yes, it's horizontal.
       dec a               ; is it up?
       jr z,star3          ; yes, it's vertical.

       ld a,(wntopx)       ; get edge of screen.
       inc a               ; down one pixel.
star8  ld (ix+3),a         ; set x coord.
       call qrand          ; get quick random number.
star9  ld (ix+5),a         ; set y position.
       ld a,c              ; direction.
       and 3               ; zero to three.
       add a,3             ; 3 to 6 for starfield.
       ld (ix+0),a         ; define particle as star.
       call chkxy          ; plot first position.
       jr star0
star1  call qrand          ; get quick random number.
       ld (ix+3),a         ; set x coord.
       ld a,(wnrgtx)       ; get edge of screen.
       add a,15            ; add width of sprite minus 1.
       jr star9
star2  call qrand          ; get quick random number.
       ld (ix+3),a         ; set x coord.
       ld a,(wnlftx)       ; get edge of screen.
       jr star9
star3  ld a,(wnbotx)       ; get edge of screen.
       add a,15            ; height of sprite minus one pixel.
       jr star8


; Find particle slot for lasers or vapour trail.
; Can't use alternate accumulator.

fpslot ld ix,SHRAPN        ; shrapnel table.
       ld de,SHRSIZ        ; size of each particle.
       ld b,NUMSHR         ; number of pieces in table.
fpslt0 ld a,(ix+0)         ; get type.
       rla                 ; is this slot in use?
       ret c               ; no, we can use it.
       add ix,de           ; point to more shrapnel.
       djnz fpslt0         ; repeat for all shrapnel.
       ret                 ; out of slots, can't generate anything.

; Create an explosion at sprite position.

explod ld c,a              ; particles to create.
       push ix             ; store pointer to sprite.
       ld l,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
       ld ix,SHRAPN        ; shrapnel table.
       ld de,SHRSIZ        ; size of each particle.
       ld b,NUMSHR         ; number of pieces in table.
expld0 ld a,(ix+0)         ; get type.
       rla                 ; is this slot in use?
       jr c,expld1         ; no, we can use it.
expld2 add ix,de           ; point to more shrapnel.
       djnz expld0         ; repeat for all shrapnel.
expld3 pop ix              ; restore sprite pointer.
       ret                 ; out of slots, can't generate any more.
expld1 ld a,c              ; shrapnel counter.
       and 15              ; 0 to 15.
       add a,l             ; add to x.
       ld (ix+3),a         ; x coord.
       ld a,(seed3)        ; crap random number.
       and 15              ; 0 to 15.
       add a,h             ; add to y.
       ld (ix+5),a         ; y coord.
       ld (ix+0),2         ; switch it on.
       exx                 ; store coordinates.
       call chkxy          ; plot first position.
       call qrand          ; quick random angle.
       and 60              ; keep within range.
       ld (ix+1),a         ; angle.
       exx                 ; restore coordinates.
       dec c               ; one less piece of shrapnel to generate.
       jr nz,expld2        ; back to main explosion loop.
       jr expld3           ; restore sprite pointer and exit.
qrand  ld a,(seed3)        ; random seed.
       ld l,a              ; low byte.
       ld h,0              ; no high byte.
       ld a,r              ; r register.
       xor (hl)            ; combine with seed.
       ld (seed3),a        ; new seed.
       ret
seed3  defb 0

; Display all shrapnel.

dshrp  ld hl,plotde        ; display routine.
       ld (proshx+1),hl    ; modify routine.
       call proshr         ; process shrapnel.
       ld hl,prosh1        ; processing routine.
       ld (proshx+1),hl    ; modify the call.
       ret

; Particle engine.

inishr ld hl,SHRAPN        ; table.
       ld b,NUMSHR         ; shrapnel pieces to process.
       ld de,SHRSIZ        ; distance to next.
inish0 ld (hl),255         ; kill the shrapnel.
       add hl,de           ; point there.
       djnz inish0         ; round again.
       ret

; Check for collision between laser and sprite.

lcol   ld hl,SHRAPN        ; shrapnel table.
       ld de,SHRSIZ        ; size of each particle.
       ld b,NUMSHR         ; number of pieces in table.
lcol0  ld a,(hl)           ; get type.
       and a               ; is this slot a laser?
       jr z,lcol1          ; yes, check collision.
lcol3  add hl,de           ; point to more shrapnel.
       djnz lcol0          ; repeat for all shrapnel.
       ret                 ; no collision, carry not set.
lcol1  push hl             ; store pointer to laser.
       inc hl              ; direction.
       inc hl              ; not used.
       inc hl              ; x position.
       ld a,(hl)           ; get x.
       sub (ix+X)          ; subtract sprite x.
lcolh  cp 16               ; within range?
       jr nc,lcol2         ; no, missed.
       inc hl              ; not used.
       inc hl              ; y position.
       ld a,(hl)           ; get y.
       sub (ix+Y)          ; subtract sprite y.
       cp SPR_HGT          ; within range?
       jr c,lcol4          ; yes, collision occurred.
lcol2  pop hl              ; restore laser pointer from stack.
       jr lcol3
lcol4  pop hl              ; restore laser pointer.
       ret                 ; return with carry set for collision.

; Main game engine code starts here.

game   equ $

; Set up screen address table.

setsat ld hl,scraddr       ; start of screen.
       ld de,SCADTB        ; screen address table.
       ld b,0              ; vertical lines on screen.
setsa0 ex de,hl            ; flip table and screen address.
       ld (hl),d           ; write high byte.
       inc h               ; second table.
       ld (hl),e           ; write low byte.
       dec h               ; back to first table.
       inc l               ; next position in table.
       ex de,hl            ; flip table and screen address back again.
       call nline          ; next line down.
       djnz setsa0         ; repeat for all lines.
    if pflag
       call setpal         ; set up ULAplus palette.
    endif
rpblc2 call inishr         ; initialise particle engine.
evintr call evnt12         ; call intro/menu event.

       ld hl,MAP           ; block properties.
       ld de,MAP+1         ; next byte.
       ld bc,767           ; size of property map.
       ld (hl),WALL        ; write default property.
       ldir
       call iniob          ; initialise objects.
       xor a               ; put zero in accumulator.
       ld (gamwon),a       ; reset game won flag.

       ld hl,score         ; score.
       call inisc          ; init the score.
mapst  ld a,(stmap)        ; start position on map.
       ld (roomtb),a       ; set up position in table, if there is one.
inipbl 
    if aflag
        ld hl,eop          ; reset blockpointer
        ld (pbptr+1),hl
    endif
       call initsc         ; set up first screen.
       ld ix,ssprit        ; default to spare sprite in table.
evini  call evnt13         ; initialisation.

; Two restarts.
; First restart - clear all sprites and initialise everything.

rstrt  call rsevt          ; restart events.
       call xspr           ; clear sprite table.
       call sprlst         ; fetch pointer to screen sprites.
       call ispr           ; initialise sprite table.
       jr rstrt0

; Second restart - clear all but player, and don't initialise him.

rstrtn call rsevt          ; restart events.
       call nspr           ; clear all non-player sprites.
       call sprlst         ; fetch pointer to screen sprites.
       call kspr           ; initialise sprite table, no more players.


; Set up the player and/or enemy sprites.

rstrt0 xor a               ; zero in accumulator.
       ld (nexlev),a       ; reset next level flag.
       ld (restfl),a       ; reset restart flag.
       ld (deadf),a        ; reset dead flag.
       call droom          ; show screen layout.
rpblc0 call inishr         ; initialise particle engine.
    if aflag
       call rbloc          ; draw blocks for this screen
    endif
       call shwob          ; draw objects.
       ld ix,sprtab        ; address of sprite table, even sprites.
       call dspr           ; display sprites.
       ld ix,sprtab+TABSIZ ; address of first odd sprite.
       call dspr           ; display sprites.

mloop  call vsync          ; synchronise with display.

       ld ix,sprtab        ; address of sprite table, even sprites.
       call dspr           ; display even sprites.

;       call plsnd          ; play sounds.
       call vsync          ; synchronise with display.
       ld ix,sprtab+TABSIZ ; address of first odd sprite.
       call dspr           ; display odd sprites.
       ld ix,ssprit        ; point to spare sprite for spawning purposes.
evlp1  call evnt10         ; called once per main loop.
       call pspr           ; process sprites.

; Main loop events.

       ld ix,ssprit        ; point to spare sprite for spawning purposes.
evlp2  call evnt11         ; called once per main loop.

bsortx call bsort          ; sort sprites.
       ld a,(nexlev)       ; finished level flag.
       and a               ; has it been set?
       jr nz,newlev        ; yes, go to next level.
       ld a,(gamwon)       ; finished game flag.
       and a               ; has it been set?
       jr nz,evwon         ; yes, finish the game.
       ld a,(restfl)       ; finished level flag.
       dec a               ; has it been set?
       jr z,rstrt          ; yes, go to next level.
       dec a               ; has it been set?
       jr z,rstrtn         ; yes, go to next level.

       ld a,(deadf)        ; dead flag.
       and a               ; is it non-zero?
       jr nz,pdead         ; yes, player dead.

       ld hl,frmno         ; game frame.
       inc (hl)            ; advance the frame.

; Back to start of main loop.

qoff   jp mloop            ; switched to a jp nz,mloop during test mode.
       ret

;----------------------------------------------------------
; Read blocks from list and update screen accordingly.
;----------------------------------------------------------

    if aflag
rbloc:

pbbuf
	ld de,eop             ; check for last block
rbloc2:
	ld hl,(pbptr+1)
	or a
    sbc hl,de
    ret z
rbloc1:
    ex de,hl
    ld a,(scno)
    cp (hl)                ;pbbuf
    jr nz,rbloc0
    push hl
    inc hl
    ld de,dispx
    ldi                    ;dispx
    ldi                    ;dispy
    ld a,(hl)
    call pattr2            ; draw block
    pop hl
rbloc0:
    ld de,0004h
    add hl,de              ; point to next block
    ex de,hl
    jr rbloc2
    endif

;----------------------------------------------------------
; New level
;----------------------------------------------------------

newlev ld a,(scno)         ; current screen.
       ld hl,numsc         ; total number of screens.
       inc a               ; next screen.
       cp (hl)             ; reached the limit?
       jr nc,evwon         ; yes, game finished.
       ld (scno),a         ; set new level number.
       jp rstrt            ; restart, clearing all aliens.
evwon  call evnt18         ; game completed.
       jp tidyup           ; tidy up and return to BASIC/calling routine.

; Player dead.

pdead  xor a               ; zeroise accumulator.
       ld (deadf),a        ; reset dead flag.
evdie  call evnt16         ; death subroutine.
       ld a,(numlif)       ; number of lives.
       and a               ; reached zero yet?
       jp nz,rstrt         ; restart game.
evfail call evnt17         ; failure event.
tidyup ld hl,hiscor        ; high score.
       ld de,score         ; player's score.
       ld b,6              ; digits to check.
tidyu2 ld a,(de)           ; get score digit.
       cp (hl)             ; are we larger than high score digit?
       jr c,tidyu0         ; high score is bigger.
       jr nz,tidyu1        ; score is greater, record new high score.
       inc hl              ; next digit of high score.
       inc de              ; next digit of score.
       djnz tidyu2         ; repeat for all digits.
tidyu0 ld hl,10072         ; BASIC likes this in alternate hl.
       exx                 ; flip hl into alternate registers.
       ld bc,score         ; return pointing to score.
       ;ret
       jp rpblc2
tidyu1 ld hl,score         ; score.
       ld de,hiscor        ; high score.
       ld bc,6             ; digits to copy.
       ldir                ; copy score to high score.
evnewh call evnt19         ; new high score event.
       jr tidyu0           ; tidy up.

; Restart event.

rsevt  ld ix,ssprit        ; default to spare element in table.
evrs   jp evnt14           ; call restart event.

; Copy number passed in a to string position bc, right-justified.

num2ch ld l,a              ; put accumulator in l.
       ld h,0              ; blank high byte of hl.
       ld a,32             ; leading spaces.
numdg3 ld de,100           ; hundreds column.
       call numdg          ; show digit.
numdg2 ld de,10            ; tens column.
       call numdg          ; show digit.
       or 16               ; last digit is always shown.
       ld de,1             ; units column.
numdg  and 48              ; clear carry, clear digit.
numdg1 sbc hl,de           ; subtract from column.
       jr c,numdg0         ; nothing to show.
       or 16               ; something to show, make it a digit.
       inc a               ; increment digit.
       jr numdg1           ; repeat until column is zero.
numdg0 add hl,de           ; restore total.
       cp 32               ; leading space?
       ret z               ; yes, don't write that.
       ld (bc),a           ; write digit to buffer.
       inc bc              ; next buffer position.
       ret
num2dd ld l,a              ; put accumulator in l.
       ld h,0              ; blank high byte of hl.
       ld a,32             ; leading spaces.
       ld de,100           ; hundreds column.
       call numdg          ; show digit.
       or 16               ; second digit is always shown.
       jr numdg2
num2td ld l,a              ; put accumulator in l.
       ld h,0              ; blank high byte of hl.
       ld a,48             ; leading spaces.
       jr numdg3

inisc  ld b,6              ; digits to initialise.
inisc0 ld (hl),'0'         ; write zero digit.
       inc hl              ; next column.
       djnz inisc0         ; repeat for all digits.
       ret


; Multiply h by d and return in hl.

imul   ld e,d              ; HL = H * D
       ld c,h              ; make c first multiplier.
imul0  ld hl,0             ; zeroise total.
       ld d,h              ; zeroise high byte.
       ld b,8              ; repeat 8 times.
imul1  rr c                ; rotate rightmost bit into carry.
       jr nc,imul2         ; wasn't set.
       add hl,de           ; bit was set, so add de.
       and a               ; reset carry.
imul2  rl e                ; shift de 1 bit left.
       rl d
       djnz imul1          ; repeat 8 times.
       ret

; Divide d by e and return in d, remainder in a.

idiv   xor a
       ld b,8              ; bits to shift.
idiv0  sla d               ; multiply d by 2.
       rla                 ; shift carry into remainder.
       cp e                ; test if e is smaller.
       jr c,idiv1          ; e is greater, no division this time.
       sub e               ; subtract it.
       inc d               ; rotate into d.
idiv1  djnz idiv0
       ret

; Initialise a sound.

isnd   ld de,(ch1ptr)      ; first pointer.
       ld a,(de)           ; get first byte.
       inc a               ; reached the end?
       jr z,isnd1          ; that'll do.
       ld de,(ch2ptr)      ; second pointer.
       ld a,(de)           ; get first byte.
       inc a               ; reached the end?
       jr z,isnd2          ; that'll do.
       ld de,(ch3ptr)      ; final pointer.
       ld a,(de)           ; get first byte.
       inc a               ; reached the end?
       jr z,isnd3          ; that'll do.
       ret
isnd1  ld (ch1ptr),hl      ; set up the sound.
       ret
isnd2  ld (ch2ptr),hl      ; set up the sound.
       ret
isnd3  ld (ch3ptr),hl      ; set up the sound.
       ret


ch1ptr defw spmask
ch2ptr defw spmask
ch3ptr defw spmask

plsnd  call plsnd1         ; first channel.
       call plsnd2         ; second one.
       call plsnd3         ; final channel.

; Write the contents of our AY buffer to the AY registers.

w8912  ld de,snddat        ; start of AY-3-8912 register data.
       ld bc,0e00h
writrg push bc
       call ayRegisterWriteDE
       pop bc
       djnz writrg
       ret

snddat defw 0              ; tone registers, channel A.
       defw 0              ; channel B tone registers.
       defw 0              ; as above, channel C.
sndwnp defb 0              ; white noise period.
sndmix defb 60             ; tone/noise mixer control.
sndv1  defb 0              ; channel A amplitude/envelope generator.
sndv2  defb 0              ; channel B amplitude/envelope.
sndv3  defb 0              ; channel C amplitude/envelope.
       defw 0              ; duration of each note.
       defb 0

plwn   inc hl              ; next byte of sound.
       and 56              ; check if we're bothering with white noise.
       ret nz              ; we're not.
       ld a,(hl)           ; fetch byte.
       ld (sndwnp),a       ; set white noise period.
       ret


plsnd2 call cksnd2         ; check sound for first channel.
       cp 255              ; reached end?
       jr z,silen2         ; silence this channel.
       and 15              ; sound bits.
       ld (sndv2),a        ; set volume for channel.
       ld a,(sndmix)       ; mixer byte.
       and 237             ; remove bits for this channel.
       ld b,a              ; store in b register.
       call plmix          ; fetch mixer details.
       and 18              ; mixer bits we want.
       or b                ; combine with mixer bits.
       ld (sndmix),a       ; new mixer value.
       call plwn           ; white noise check.
       inc hl              ; tone low.
       ld e,(hl)           ; fetch value.
       inc hl              ; tone high.
       ld d,(hl)           ; fetch value.
       ld (snddat+2),de    ; set tone.
       inc hl              ; next bit of sound.
       ld (ch2ptr),hl      ; set pointer.
       ret

plsnd3 call cksnd3         ; check sound for first channel.
       cp 255              ; reached end?
       jr z,silen3         ; silence last channel.
       and 15              ; sound bits.
       ld (sndv3),a        ; set volume for channel.
       ld a,(sndmix)       ; mixer byte.
       and 219             ; remove bits for this channel.
       ld b,a              ; store in b register.
       call plmix          ; fetch mixer details.
       and 36              ; mixer bits we want.
       or b                ; combine with mixer bits.
       ld (sndmix),a       ; new mixer value.
       call plwn           ; white noise check.
       inc hl              ; tone low.
       ld e,(hl)           ; fetch value.
       inc hl              ; tone high.
       ld d,(hl)           ; fetch value.
       ld (snddat+4),de    ; set tone.
       inc hl              ; next bit of sound.
       ld (ch3ptr),hl      ; set pointer.
       ret

plmix  ld a,(hl)           ; fetch mixer byte.
       and 192             ; mix bits are d6 and d7.
       rlca                ; rotate into d0 and d1.
       rlca
       ld e,a              ; displacement in de.
       ld d,0
       push hl             ; store pointer on stack.
       ld hl,mixtab        ; mixer table.
       add hl,de           ; point to mixer byte.
       ld a,(hl)           ; fetch mixer value.
       pop hl              ; restore pointer.
       ret
mixtab defb 63,56,7,0      ; mixer byte settings.

silen1 xor a               ; zero.
       ld (sndv1),a        ; sound off.
       ld a,(sndmix)       ; mixer byte.
       or 9                ; mix bits off.
       ld (sndmix),a       ; mixer setting for channel.
       ret
silen2 xor a               ; zero.
       ld (sndv2),a        ; sound off.
       ld a,(sndmix)       ; mixer byte.
       or 18               ; mix bits off.
       ld (sndmix),a       ; mixer setting for channel.
       ret
silen3 xor a               ; zero.
       ld (sndv3),a        ; sound off.
       ld a,(sndmix)       ; mixer byte.
       or 36               ; mix bits off.
       ld (sndmix),a       ; mixer setting for channel.
       ret
cksnd1 ld hl,(ch1ptr)      ; pointer to sound.
       ld a,(hl)           ; fetch mixer/flag.
       ret
cksnd2 ld hl,(ch2ptr)      ; pointer to sound.
       ld a,(hl)           ; fetch mixer/flag.
       ret
cksnd3 ld hl,(ch3ptr)      ; pointer to sound.
       ld a,(hl)           ; fetch mixer/flag.
       ret

plsnd1 call cksnd1         ; check sound for first channel.
       cp 255              ; reached end?
       jr z,silen1         ; silence first channel.
       and 15              ; sound bits.
       ld (sndv1),a        ; set volume for channel.
       ld a,(sndmix)       ; mixer byte.
       and 246             ; remove bits for this channel.
       ld b,a              ; store in b register.
       call plmix          ; fetch mixer details.
       and 9               ; mixer bits we want.
       or b                ; combine with mixer bits.
       ld (sndmix),a       ; new mixer value.
       call plwn           ; white noise check.
       inc hl              ; tone low.
       ld e,(hl)           ; fetch value.
       inc hl              ; tone high.
       ld d,(hl)           ; fetch value.
       ld (snddat),de      ; set tone.
       inc hl              ; next bit of sound.
       ld (ch1ptr),hl      ; set pointer.
       ret

; =============================================================================
; =============================================================================
; 2-5: use 6 VINT LPBs, with 51-line VINT pulse after line 34, 86, 138, or 190
ENABLE_300HZ_IRQ        equ     0
; if enabled then AY is on Speccy speed, if disabled then on CPC
AY_ZX                   equ     1
; if enabled, channel A is played at the left, channel B at center,
; and channel C at right
ENABLE_STEREO           equ     0
; the border color is set to red while the IRQ routine is running if this
; is enabled (for debugging only)
IRQ_BORDER_FX           equ     1
; envelope sample rate = 1000 / ENV_SRATE_DIV Hz (increase this for lower
; quality and CPU usage)
ENV_SRATE_DIV           equ     2 ;1
; minimum envelope frequency value (should be at least 26 * ENV_SRATE_DIV,
; and less than 256)
MIN_ENV_FREQVAL         equ     26 * ENV_SRATE_DIV
; if non-zero, the envelope generator is stopped in modes 8, 10, 12, and 14
; when the envelope enable bits in registers 8 to 10 are changed to disabled
; on all channels (NOTE: continuing the envelope by enabling it again in
; registers 8 to 10 does not work correctly, the envelope must be restarted
; by writing to register 13)
ENVELOPE_CPU_SAVING     equ     1
; select how tone and noise being enabled on the same channel should be handled
;   bit 0 = 0: play tone frequency
;   bit 0 = 1: play noise frequency
;         >15: use distortion specified in bits 4-7 (defaults to 30h for noise)
toneAndNoiseModeA       equ     1
toneAndNoiseModeB       equ     30h
toneAndNoiseModeC       equ     1
; if non-zero, the envelope emulation routine is disabled
NO_ENVELOPE_IRQ         equ     0
; DAVE channels assigned to each AY channel
ayDaveChnA              equ     0
ayDaveChnB              equ     1
ayDaveChnC              equ     2

  if NO_ENVELOPE_IRQ == 0

envelopeInterrupt:
    if (ENV_SRATE_DIV < 2) && (ENABLE_300HZ_IRQ < 1)
        ld    a, 13h
        out   (0b4h), a
    endif
    if ENABLE_300HZ_IRQ < 1
        push  hl
    endif
        push  bc
.l1:    ld    hl, 0000h                 ; * envelope counter
    if AY_ZX
        ld    bc, 010000h - (((110841 * ENV_SRATE_DIV) + 500) / 1000)
    else
      if ENABLE_300HZ_IRQ < 1
        ld    bc, 010000h - (((62500 * ENV_SRATE_DIV) + 500) / 1000)
      else
        ld    bc, 010000h - (((62500 * ENV_SRATE_DIV) + 150) / 300)
      endif
    endif
        add   hl, bc
.l2:    jr    c, .l19                   ; * JR if envelope is stopped
.l3:    ld    bc, 0ffffh                ; * envelope frequency
.l4:    ld    a, 0                      ; * envelope state (0 to 15)
.l5:    dec   a                         ; * envelope direction (INC A or DEC A)
        add   hl, bc
        jr    nc, .l5
        ld    (.l1 + 1), hl
        cp    10h
.l6:    jr    nc, .l21                  ; * envelope mode
.l7:    ld    (.l4 + 1), a
.l8:    or    low ayVolumeTable
        ld    l, a
.l9:    ld    h, high ayVolumeTable
        ld    a, (hl)
        pop   bc
.l10:   jr    .l12                      ; * envelope enable mode
.l11:   out   (0a8h + ayDaveChnA), a    ; envelope on channel A only
    if ENABLE_STEREO == 0
;        out   (0ach + ayDaveChnA), a
    endif
.l12:   pop   hl
        ret
.l13:   out   (0a8h + ayDaveChnA), a    ; envelope on channels A and B
    if ENABLE_STEREO == 0
;        out   (0ach + ayDaveChnA), a
    endif
.l14:
    if ENABLE_STEREO != 0
        ld    l, a                      ; envelope on channel B only (Carry=0)
        rra
        scf
        adc   a, l
        rra
    endif
        out   (0a8h + ayDaveChnB), a
;        out   (0ach + ayDaveChnB), a
        pop   hl
        ret
.l15:   out   (0a8h + ayDaveChnA), a    ; envelope on channels A and C
    if ENABLE_STEREO == 0
;        out   (0ach + ayDaveChnA), a
    endif
.l16:
    if ENABLE_STEREO == 0
        out   (0a8h + ayDaveChnC), a
    endif
;        out   (0ach + ayDaveChnC), a    ; envelope on channel C only
        pop   hl
        ret
.l17:   out   (0a8h + ayDaveChnA), a    ; envelope on channels A, B, and C
    if ENABLE_STEREO == 0
;        out   (0ach + ayDaveChnA), a
    endif
.l18:
    if ENABLE_STEREO == 0
        out   (0a8h + ayDaveChnC), a
    endif
;        out   (0ach + ayDaveChnC), a    ; envelope on channels B and C
    if ENABLE_STEREO != 0
        ld    l, a                      ; NOTE: Carry is always 0 here
        rra
        scf
        adc   a, l
        rra
    endif
        out   (0a8h + ayDaveChnB), a
;        out   (0ach + ayDaveChnB), a
        pop   hl
        ret
.l19:   ld    (.l1 + 1), hl
        pop   bc
        pop   hl
        ret
.l20:   ld    l, low (ayVolumeTable + 15)       ; envelope modes 11 and 13
        defb  01h                       ; = LD BC, nnnn
.l21:   ld    l, low ayVolumeTable      ; envelope modes 0 to 7, 9, and 15
        ld    a, 18h                    ; = JR +nn
        ld    (.l2), a                  ; stop envelope
        jp    .l9
.l22:   and   0fh                       ; envelope modes 8 and 12
        jp    .l7
.l23:   jp    m, .l24                   ; envelope modes 10 and 14
        xor   1fh
        ld    l, a
        ld    h, 3dh                    ; set direction to DEC A
        ld    (.l4 + 1), hl             ; assume .l5 = .l4 + 2
        jp    .l8
.l24:   cpl
        ld    l, a
        ld    h, 3ch                    ; set direction to INC A
        ld    (.l4 + 1), hl
        jp    .l8

  endif
; -----------------------------------------------------------------------------

    macro ayVolTableMacro
ayVolumeTable:
        defb   0,  1,  2,  3,  4,  5,  6,  9
        defb  12, 17, 22, 28, 36, 44, 53, 63
    endm

    macro ayRegMaskTableMacro
ayRegisterMaskTable:
        defb  0ffh, 00fh, 0ffh, 00fh, 0ffh, 00fh, 01fh, 0ffh
        defb  01fh, 01fh, 01fh, 0ffh, 0ffh, 00fh, 0ffh, 0ffh
    endm

    macro ayRegistersMacro
ayRegisters:
        defb  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
        defb  00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    endm

        align 16

    if ($ & 0030h) == 0020h
        block 16, 00h
    endif

ayTablesBegin:

    if (ayTablesBegin & 0030h) == 0000h
        ayVolTableMacro
        ayRegMaskTableMacro
    endif
    if (ayTablesBegin & 0030h) == 0010h
        ayRegMaskTableMacro
    endif
    if (ayTablesBegin & 0030h) == 0030h
        ayVolTableMacro
        ayRegistersMacro
    endif

        assert  ($ & 000fh) == 0

ayRegWriteTable:
        defb  low (ayRegisterWrite.l3 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l3 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l4 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l4 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l6 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l6 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l7 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l5 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l9 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l10 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l11 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l12 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l12 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l15 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l8 - (ayRegisterWrite.l1 + 2))
        defb  low (ayRegisterWrite.l8 - (ayRegisterWrite.l1 + 2))

        assert  ($ & 000fh) == 0

    if (ayTablesBegin & 0030h) == 0000h
        ayRegistersMacro
    endif
    if (ayTablesBegin & 0030h) == 0010h
        ayRegistersMacro
        ayVolTableMacro
    endif
    if (ayTablesBegin & 0030h) == 0030h
        ayRegMaskTableMacro
    endif

        assert  $ == (ayTablesBegin + 64)

    if NO_ENVELOPE_IRQ == 0

envelopeModeTable:
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l22 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l23 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l20 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l22 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l20 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l23 - (envelopeInterrupt.l6 + 2))
        defb  low (envelopeInterrupt.l21 - (envelopeInterrupt.l6 + 2))

        assert  ($ & 000fh) == 0

envelopeEnableTable:
        defb  low (envelopeInterrupt.l12 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l11 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l14 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l13 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l16 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l15 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l18 - envelopeInterrupt.l11)
        defb  low (envelopeInterrupt.l17 - envelopeInterrupt.l11)

        assert  ($ & 0007h) == 0

    endif

setChannelAmplitude:
        cp    10h
        jr    c, .l1
    if NO_ENVELOPE_IRQ == 0
        res   3, b
        ld    a, (envelopeInterrupt.l4 + 1)
    else
        xor   a
    endif
.l1:                                    ; HL = ayRegWriteTable + (8 + channel)
    if ((ayVolumeTable ^ ayRegWriteTable) & 0ff00h) != 0
      if ayVolumeTable > ayRegWriteTable
        inc   h
      else
        dec   h
      endif
    endif
        or    low ayVolumeTable
    if ENABLE_STEREO != 0
        bit   0, l                      ; Z = 0: channel B, Z = 1: channel A, C
    endif
        ld    l, a
        ld    a, (hl)
    if ENABLE_STEREO != 0
        jr    z, .l2
        ld    l, a                      ; NOTE: Carry is always 0 here
        rra
        scf
        adc   a, l
        rra
    endif
;        out   (c), a
;        set   2, c
.l2:    out   (c), a
    if NO_ENVELOPE_IRQ == 0
.l3:    ld    hl, envelopeEnableTable   ; *
        ld    a, l                      ; NOTE: envelopeEnableTable
        or    b                         ; should be aligned to 16 bytes
        cp    low (envelopeEnableTable + 8)
        jr    c, .l4
        xor   b
.l4:    cp    l
        jr    z, .l5                    ; envelope enable bit has not changed ?
        ld    (.l3 + 1), a
        ld    l, a
        ld    a, (hl)
        ld    (envelopeInterrupt.l10 + 1), a
      if ENVELOPE_CPU_SAVING != 0
        ld    a, (envelopeInterrupt.l6 + 1)     ; check envelope mode:
        cp    low (envelopeInterrupt.l22 - (envelopeInterrupt.l6 + 2))
        jr    c, .l5                    ; hold or not continue ?
        ld    a, low envelopeEnableTable
        sub   l
        sbc   a, a
        and   20h
        or    18h                       ; JR +nn or JR C, +nn
        ld    (envelopeInterrupt.l2), a ; disable envelope if it is not used
      endif
    endif
.l5:    pop   bc
;        pop   af
        ret

setChannelAFreq:
        ld    c, 0a0h + (ayDaveChnA * 2)
        ld    a, (ayRegisters + 7)
        ld    hl, (ayRegisters)
    if (toneAndNoiseModeA < 16) && ((toneAndNoiseModeA & 1) == 0)
        rrca
        jr    nc, setToneGenFrequency   ; tone generator enabled ?
        and   04h
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
    endif
    if (toneAndNoiseModeA < 16) && ((toneAndNoiseModeA & 1) != 0)
        bit   3, a
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
        rrca
        jr    nc, setToneGenFrequency   ; tone generator enabled ?
    endif
    if toneAndNoiseModeA > 15
        and   09h
        jr    z, setToneGenAAsNoise     ; tone + noise generator enabled ?
        cp    08h
        jr    z, setToneGenFrequency    ; tone generator only ?
        jr    c, setNoiseGenFreq        ; noise generator only ?
    endif
        xor   a                         ; channel disabled
        out   (0a0h + (ayDaveChnA * 2)), a
        out   (0a1h + (ayDaveChnA * 2)), a
        ret

setChannelBFreq:
        ld    c, 0a0h + (ayDaveChnB * 2)
        ld    a, (ayRegisters + 7)
        ld    hl, (ayRegisters + 2)
    if (toneAndNoiseModeB < 16) && ((toneAndNoiseModeB & 1) == 0)
        bit   1, a
        jr    z, setToneGenFrequency    ; tone generator enabled ?
        and   10h
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
    endif
    if (toneAndNoiseModeB < 16) && ((toneAndNoiseModeB & 1) != 0)
        bit   4, a
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
        and   02h
        jr    z, setToneGenFrequency    ; tone generator enabled ?
    endif
    if toneAndNoiseModeB > 15
        and   12h
        jr    z, setToneGenBAsNoise     ; tone + noise generator enabled ?
        cp    10h
        jr    z, setToneGenFrequency    ; tone generator only ?
        jr    c, setNoiseGenFreq        ; noise generator only ?
    endif
        xor   a                         ; channel disabled
        out   (0a0h + (ayDaveChnB * 2)), a
        out   (0a1h + (ayDaveChnB * 2)), a
        ret

setChannelCFreq:
        ld    c, 0a0h + (ayDaveChnC * 2)
        ld    a, (ayRegisters + 7)
        ld    hl, (ayRegisters + 4)
    if (toneAndNoiseModeC < 16) && ((toneAndNoiseModeC & 1) == 0)
        bit   2, a
        jr    z, setToneGenFrequency    ; tone generator enabled ?
        and   20h
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
    endif
    if (toneAndNoiseModeC < 16) && ((toneAndNoiseModeC & 1) != 0)
        bit   5, a
        jr    z, setNoiseGenFreq        ; noise generator enabled ?
        and   04h
        jr    z, setToneGenFrequency    ; tone generator enabled ?
    endif
    if toneAndNoiseModeC > 15
        and   24h
        jr    z, setToneGenCAsNoise     ; tone + noise generator enabled ?
        cp    20h
        jr    z, setToneGenFrequency    ; tone generator only ?
        jr    c, setNoiseGenFreq        ; noise generator only ?
    endif
        xor   a                         ; channel disabled
        out   (0a0h + (ayDaveChnC * 2)), a
        out   (0a1h + (ayDaveChnC * 2)), a
        ret

ayToneDistModeA equ (toneAndNoiseModeA > 15) && ((toneAndNoiseModeA & 1) == 0)
ayToneDistModeB equ (toneAndNoiseModeB > 15) && ((toneAndNoiseModeB & 1) == 0)
ayToneDistModeC equ (toneAndNoiseModeC > 15) && ((toneAndNoiseModeC & 1) == 0)

    if ayToneDistModeA
setToneGenAAsNoise:
        ld    a, toneAndNoiseModeA & 0f0h
        jp    setToneGenFrequency_
    endif

    if ayToneDistModeB
setToneGenBAsNoise:
        ld    a, toneAndNoiseModeB & 0f0h
        jp    setToneGenFrequency_
    endif

    if ayToneDistModeC
setToneGenCAsNoise:
        ld    a, toneAndNoiseModeC & 0f0h
        defb  0feh                      ; = CP nn
    endif

setToneGenFrequency:
    if ayToneDistModeA || ayToneDistModeB || ayToneDistModeC
        xor   a
    endif

    if AY_ZX
setToneGenFrequency_:
    if ayToneDistModeA || ayToneDistModeB || ayToneDistModeC
        ld    (.l1 + 1), a
    endif
        ld    b, h
        ld    a, l
        sra   b
        rra
        sra   b
        rra
        sra   b
        rra
        adc   a, l
        ld    l, a
        dec   hl
        ld    a, b
        adc   a, h
        cp    10h
        jr    nc, .l2                   ; overflow ?
.l1:
    if ayToneDistModeA || ayToneDistModeB || ayToneDistModeC
        or    00h                       ; * non-zero for tone + noise
    endif
        out   (c), l
        inc   c
        out   (c), a
        ret
.l2:    inc   l
        inc   a
        jr    z, .l1
        ld    l, 0ffh
        ld    a, 0fh
        jp    .l1
    else
setToneGenFrequency_:
        add   hl, hl
        dec   hl
        bit   4, h
        jr    nz, .l2                   ; overflow ?
.l1:
    if ayToneDistModeA || ayToneDistModeB || ayToneDistModeC
        or    h                         ; non-zero for tone + noise
    endif
        out   (c), l
        inc   c
    if ayToneDistModeA || ayToneDistModeB || ayToneDistModeC
        out   (c), a
    else
        out   (c), h
    endif
        ret
.l2:    ld    l, 1
        inc   h
        jr    z, .l1
        ld    hl, 0fffh
        jp    .l1
    endif

    if (toneAndNoiseModeA > 15) && ((toneAndNoiseModeA & 1) != 0)
setToneGenAAsNoise:
        ld    h, toneAndNoiseModeA & 0f0h
        jp    setNoiseGenFreq_
    endif

    if (toneAndNoiseModeB > 15) && ((toneAndNoiseModeB & 1) != 0)
setToneGenBAsNoise:
        ld    h, toneAndNoiseModeB & 0f0h
        jp    setNoiseGenFreq_
    endif

    if (toneAndNoiseModeC > 15) && ((toneAndNoiseModeC & 1) != 0)
setToneGenCAsNoise:
        ld    h, toneAndNoiseModeC & 0f0h
        jp    setNoiseGenFreq_
    endif

    if  AY_ZX
setNoiseGenFreq:
        ld    h, 30h

setNoiseGenFreq_:
        ld    a, (ayRegisters + 6)
        cp    1
        adc   a, 0
        ld    l, a
        rra
        sla   l
        rra
        adc   a, l
        dec   a
        out   (c), a
        inc   c
        out   (c), h
        ret
    else
setNoiseGenFreq:
        ld    h, 30h

setNoiseGenFreq_:
        ld    a, (ayRegisters + 6)
        add   a, a
        add   a, a
        jr    nz, .l1
        ld    a, 4
.l1:    dec   a
        out   (c), a
        inc   c
        out   (c), h
        ret
    endif
; -----------------------------------------------------------------------------
;; reset AY-3-8912 emulation
;
;ayReset:
;        di
;        ld    hl, ayRegisters - 1
;        ld    bc, 10afh
;        xor   a
;.l1:    inc   hl
;        out   (c), a
;        ld    (hl), a
;        dec   c
;        djnz  .l1
;        res   3, l                      ; register 7
;        ld    (hl), 3fh
;    if NO_ENVELOPE_IRQ == 0
;        ld    (envelopeInterrupt.l4 + 1), a
;        ld    a, 18h                    ; = JR +nn
;        ld    (envelopeInterrupt.l2), a
;        ld    hl, MIN_ENV_FREQVAL
;        ld    (envelopeInterrupt.l3 + 1), hl
;        ld    a, low (envelopeInterrupt.l12 - envelopeInterrupt.l11)
;        ld    (envelopeInterrupt.l10 + 1), a
;        ld    a, low envelopeEnableTable
;        ld    (setChannelAmplitude.l3 + 1), a
;    endif
;        ld    a, 04h
;        out   (0bfh), a
;        ld    c, b
;        call  .l2
;        ld    l, b
;        call  .l2                       ; L = 1 kHz interrupts per video frame
;        ld    a, 25
;        cp    l
;        ld    a, 01h
;        rla
;        rla
;        out   (0bfh), a                 ; Z80 <= 5 MHz: 04h, > 5 MHz: 06h
;        ld    a, 10h                    ; use 17-bit noise generator
;        out   (0a6h), a
;    if (NO_ENVELOPE_IRQ == 0) && (ENABLE_300HZ_IRQ < 1)
;        ld    a, 33h
;    else
;        ld    a, 30h
;    endif
;        out   (0b4h), a                 ; enable 1 kHz and video interrupts
;        ret
;.l2:    in    a, (0b4h)
;        and   11h
;        or    c
;        rlca
;        and   66h
;        ld    c, a                      ; -ON--ON-
;        rlca                            ; ON--ON--
;        xor   c                         ; OXN-OXN-
;        bit   2, a
;        jr    z, .l3
;        inc   l                         ; 1 kHz interrupt
;.l3:    cp    0c0h
;        jr    c, .l2                    ; not 50 Hz interrupt ?
;        ret
;
;; read AY-3-8912 register A, returning the value in A
;
;ayRegisterRead:
;        and   0fh
;        or    low ayRegisters
;        ld    l, a
;        ld    h, high ayRegisters
;        ld    a, (hl)
;        or    a
;        ret

; write C to AY-3-8912 register A
; NOTE: interrupts may be enabled on return
ayRegisterWriteDE:
        ld      a,(de)
        inc     de
ayRegisterWrite:
        ld      b,a
        ld      a,c
        inc     c
;        push  af
        and   0fh
        or    low ayRegisterMaskTable
        ld    l, a
        ld    h, high ayRegisterMaskTable
        ld    a, b
        and   (hl)
    if ayRegisters == (ayRegisterMaskTable | 0020h)
        set   5, l
    else
        res   5, l
    endif
        cp    (hl)
        jr    z, .l2                    ; register not changed ?
        ld    (hl), a
        push  bc
    if ayRegWriteTable == (ayRegisters | 0010h)
        set   4, l
    else
        res   4, l
    endif
        ld    a, (hl)
        ld    (.l1 + 1), a
.l1:    jr    .l8                       ; *
.l2:
    if NO_ENVELOPE_IRQ == 0
        ld    a, l
        xor   low (ayRegisters + 13)
        jr    z, .l16                   ; envelope restart ?
    endif
;        pop   af
        ret
.l3:    call  setChannelAFreq           ; tone generator A frequency
        pop   bc
;        pop   af
        ret
.l4:    call  setChannelBFreq           ; tone generator B frequency
        pop   bc
;        pop   af
        ret
.l5:    call  setChannelAFreq           ; mixer
        call  setChannelBFreq
.l6:    call  setChannelCFreq           ; tone generator C frequency
        pop   bc
;        pop   af
        ret
.l7:    ld    a, (ayRegisters + 7)      ; noise generator frequency
    if (toneAndNoiseModeA & 1) == 0
        xor   07h
        ld    b, a
        and   09h
    else
        ld    b, a
        and   08h
    endif
        call  z, setChannelAFreq
    if (toneAndNoiseModeB & 1) == 0
        ld    a, b
        and   12h
    else
        bit   4, b
    endif
        call  z, setChannelBFreq
    if (toneAndNoiseModeC & 1) == 0
        ld    a, b
        and   24h
    else
        bit   5, b
    endif
        call  z, setChannelCFreq
.l8:    pop   bc
;        pop   af
        ret
.l9:    ld    a, (ayRegisters + 8)      ; channel A amplitude / envelope enable
    if NO_ENVELOPE_IRQ == 0
        ld    bc, 09a8h + ayDaveChnA
    else
        ld    c, 0a8h + ayDaveChnA
    endif
        jp    setChannelAmplitude
.l10:   ld    a, (ayRegisters + 9)      ; channel B amplitude / envelope enable
    if NO_ENVELOPE_IRQ == 0
        ld    bc, 0aa8h + ayDaveChnB
    else
        ld    c, 0a8h + ayDaveChnB
    endif
        jp    setChannelAmplitude
.l11:   ld    a, (ayRegisters + 10)     ; channel C amplitude / envelope enable
    if ENABLE_STEREO == 0
      if NO_ENVELOPE_IRQ == 0
        ld    bc, 0ca8h + ayDaveChnC
      else
        ld    c, 0a8h + ayDaveChnC
      endif
    else
      if NO_ENVELOPE_IRQ == 0
        ld    bc, 0cach + ayDaveChnC
      else
        ld    c, 0ach + ayDaveChnC
      endif
    endif
        jp    setChannelAmplitude
.l12:
    if NO_ENVELOPE_IRQ == 0
        ld    hl, (ayRegisters + 11)    ; envelope generator frequency
        ld    a, h
        or    a
        jr    nz, .l13
        ld    a, MIN_ENV_FREQVAL
        cp    l
        jr    c, .l13
        ld    l, a                      ; limit envelope frequency
.l13:   ld    (envelopeInterrupt.l3 + 1), hl
        pop   bc
;        pop   af
        ret
    else
        jr    .l8
    endif
.l15:                                   ; envelope generator mode / restart
    if NO_ENVELOPE_IRQ == 0
        pop   bc
.l16:   ld    hl, (envelopeInterrupt.l3 + 1)
        ld    (envelopeInterrupt.l1 + 1), hl
        ld    a, 38h                    ; = JR C, +nn
        ld    (envelopeInterrupt.l2), a ; enable envelope
        ld    a, (ayRegisters + 13)
        or    low envelopeModeTable
        ld    l, a
        ld    h, high envelopeModeTable
        and   04h
        ld    a, (hl)
        ld    (envelopeInterrupt.l6 + 1), a
        ld    hl, 3c00h                 ; INC A, state = 0
        ld    a, l
        jr    nz, .l17                  ; attack ?
        ld    hl, 3d0fh                 ; DEC A, state = 15
        ld    a, 3fh
.l17:   ld    (envelopeInterrupt.l4 + 1), hl    ; assume eInt.l5 = eInt.l4 + 2
        call  .l18
;        pop   af
        ret
.l18:   call  envelopeInterrupt.l10     ; NOTE: this will pop return address
    else
        jr    .l8
    endif

; unused routines

  if 0

; write 11 AY registers (0 to 10) from table beginning at DE

ayRegisterWriteAllI:
        ld    hl, 11
        add   hl, de
        ld    e, l
        ld    d, h
        dec   de
        push  hl
        call  ayRegisterWriteAllD
        pop   de
        ret

; write 11 AY registers (10 to 0) from table ending at DE

ayRegisterWriteAllD:
;       call  getCPCPageForDE
        push  bc
        push  ix
        ld    bc, ayRegisterMaskTable + 11
        ld    hl, ayRegisters + 11
        ld    ix, 0020h
.l1:    dec   c
        dec   l
        ex    de, hl
        ld    a, (bc)
        and   (hl)
        dec   hl
        ex    de, hl
        cp    (hl)
        add   ix, ix
        jr    z, .l2
        ld    (hl), a
        inc   ixl
.l2:    jp    nc, .l1
        ex    (sp), ix                  ; restore IX, push register change mask
        ex    de, hl                    ; HL = table start address - 1
        ex    (sp), hl                  ; HL = change mask, push table address
        ex    de, hl                    ; DE = change mask
;   if NO_ENVELOPE_IRQ == 0
;       ld    l, low (ayRegWriteTable + 11)
;       ld    a, d
;       and   18h
;       call  nz, .l3
;       ld    l, low (ayRegWriteTable + 13)
;       call  .l3
;   endif
        ld    l, low (ayRegWriteTable + 8)
        ld    a, d
        rrca
        call  c, .l3
        ld    l, low (ayRegWriteTable + 9)
        rrca
        call  c, .l3
        ld    l, low (ayRegWriteTable + 10)
        rrca
        call  c, .l3
        ld    a, e
        and   0c3h
        call  nz, setChannelAFreq
        ld    a, e
        and   0cch
        call  nz, setChannelBFreq
        ld    a, e
        and   0f0h
        call  nz, setChannelCFreq
        pop   de
        pop   bc
;       jp    restoreCPCPaging
        ret
.l3:    push  af
        push  bc
        ld    h, high ayRegWriteTable
        ld    a, (hl)
        ld    (ayRegisterWrite.l1 + 1), a
        jp    ayRegisterWrite.l1

  endif

; =============================================================================


; Objects handling.
; 32 bytes for image
; 1 for colour
; 3 for room, x and y
; 3 for starting room, x and y.
; 254 = disabled.
; 255 = object in player's pockets.

; Show items present.

shwob  ld hl,objdta        ; objects table.
       ld de,33            ; distance to room number.
       add hl,de           ; point to room data.
       ld a,(numob)        ; number of objects in the game.
       ld b,a              ; loop counter.
shwob0 push bc             ; store count.
       push hl             ; store item pointer.
       ld a,(scno)         ; current location.
       cp (hl)             ; same as an item?
       call z,dobjc        ; yes, display object in colour.
       pop hl              ; restore pointer.
       pop bc              ; restore counter.
       ld de,39            ; distance to next item.
       add hl,de           ; point to it.
       djnz shwob0         ; repeat for others.
       ret

; Display object.
; hl must point to object's room number.

dobj   inc hl              ; point to x.
dobj0  ld de,dispx         ; coordinates.
       ldi                 ; transfer x coord.
       ldi                 ; transfer y too.
       ld de,10000h-24h    ; minus 36.
       add hl,de           ; point to image.
dobj1  jp sprite           ; draw this sprite.

dobjc  call dobj           ; display object.
       ld a,(hl)           ; put ink in c register.
       and 07h
       or 40h
       ld (colch5+1),a
colch5 ld a,(coltabl)
       ld c,a

; Need to write attribute routine here.
; set up colour in c register first.

cobj   ld a,(hl)           ; get colour byte.
       and a               ; test it.
       ret m               ; colour not set.
       ld h,high attaddr/4 ; quarter of attrubte address.
       ld a,(dispx)        ; x coord.
       and 248             ; only want multiple of 8.
       rla                 ; multiply by 4.
       rl h
       rla
       rl h                ; high byte now set up.
       ld l,a
       ld a,(dispy)        ; take y position.
       rra                 ; divide it by 8.
       rra
       rra
       and 31              ; remove unwanted bits.
       add a,l             ; add to low byte.
       ld l,a              ; low byte of address.
 
       ld a,(dispx)        ; x coordinate.
       ld b,3              ; default rows to write.
       and 7               ; does x straddle cells?
       jr nz,cobj0         ; yes, loop counter is good.
       dec b               ; one less row to write.
cobj0  ld a,h
       add a,high (MAP-attaddr)
       ld d,a
       ld e,l
       ld a,(de)
       or a
       jr z,cobjy1
       ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
cobjy1 inc l               ; next cell.
       inc e
       ld a,(de)
       or a
       jr z,cobjy2
       ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
cobjy2 inc l               ; next cell.
       ld a,(dispy)        ; y coordinate.
       and 7               ; straddling cells?
       jr z,cobj1          ; no, only 2 wide.
       inc e
       ld a,(de)
       or a
       jr z,cobj1
       ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
cobj1  ld de,001eh
       add hl,de           ; next row.
       djnz cobj0
       ret
 
;       ld de,30            ; distance to next line down.
;       ld a,(dispx)        ; x coordinate.
;       ld b,3              ; default rows to write.
;       and 7               ; does x straddle cells?
;       jr nz,cobj0         ; yes, loop counter is good.
;       dec b               ; one less row to write.
;cobj0  ld a,(hl)           ; get attributes.
;       and 248             ; remove ink.
;       or c                ; put in the new ink.
;       ld (hl),a           ; write back again.
;       inc l               ; next cell.
;       ld a,(hl)           ; get attributes.
;       and 248             ; remove ink.
;       or c                ; put in the new ink.
;       ld (hl),a           ; write back again.
;       inc l               ; next cell.
;       ld a,(dispy)        ; y coordinate.
;       and 7               ; straddling cells?
;       jr z,cobj1          ; no, only 2 wide.
;       ld a,(hl)           ; get attributes.
;       and 248             ; remove ink.
;       or c                ; put in the new ink.
;       ld (hl),a           ; write back again.
;cobj1  add hl,de           ; next row.
;       djnz cobj0
;       ret

; Remove an object.

remob  ld hl,numob         ; number of objects in game.
       cp (hl)             ; are we checking past the end?
       ret nc              ; yes, can't get non-existent item.
       push af             ; remember object.
       call getob          ; pick it up if we haven't already got it.
       pop af              ; retrieve object number.
       call gotob          ; get its address.
       ld (hl),254         ; remove it.
       ret

; Pick up object number held in the accumulator.

getob  ld hl,numob         ; number of objects in game.
       cp (hl)             ; are we checking past the end?
       ret nc              ; yes, can't get non-existent item.
       call gotob          ; check if we already have it.
       ret z               ; we already do.
       ex de,hl            ; object address in de.
       ld hl,scno          ; current screen.
       cp (hl)             ; is it on this screen?
       ex de,hl            ; object address back in hl.
       jr nz,getob0        ; not on screen, so nothing to delete.
       ld (hl),255         ; pick it up.
       inc hl              ; point to x coord.
getob1 ld e,(hl)           ; x coord.
       inc hl              ; back to y coord.
       ld d,(hl)           ; y coord.
       ld (dispx),de       ; set display coords.
       ld de,10000h-23h    ; minus graphic size.
       add hl,de           ; point to graphics.
       call dobj1          ; delete object sprite.
       ld a,(bcol)         ; first block colour.
       or 40h
       ld (colch1+1),a
colch1 ld a,(coltabl)
       ld c,a              ; set up colour.
       jp cobj             ; colour object's old position.
getob0 ld (hl),255         ; pick it up.
       ret

; Got object check.
; Call with object in accumulator, returns zero set if in pockets.

gotob  ld hl,numob         ; number of objects in game.
       cp (hl)             ; are we checking past the end?
       jr nc,gotob0        ; yes, we can't have a non-existent object.
       call findob         ; find the object.
gotob1 cp 255              ; in pockets?
       ret
gotob0 ld a,254            ; missing.
       jr gotob1

findob ld hl,objdta        ; objects.
       ld de,39            ; size of each object.
       and a               ; is it zero?
       jr z,fndob1         ; yes, skip loop.
       ld b,a              ; loop counter in b.
fndob2 add hl,de           ; point to next one.
       djnz fndob2         ; repeat until we find address.
fndob1 ld e,33             ; distance to room it's in.
       add hl,de           ; point to room.
       ld a,(hl)           ; fetch status.
       ret

; Drop object number at (dispx, dispy).

drpob  ld hl,numob         ; number of objects in game.
       cp (hl)             ; are we checking past the end?
       ret nc              ; yes, can't drop non-existent item.
       call gotob          ; make sure object is in inventory.
       ld a,(scno)         ; screen number.
       cp (hl)             ; already on this screen?
       ret z               ; yes, nothing to do.
       ld (hl),a           ; bring onto screen.
       inc hl              ; point to x coord.
       ld a,(dispx)        ; sprite x coordinate.
       ld (hl),a           ; set x coord.
       inc hl              ; point to object y.
       ld a,(dispy)        ; sprite y coordinate.
       ld (hl),a           ; set the y position.
       ld de,10000h-23h    ; minus graphic size.
       add hl,de           ; point to graphics.
       call dobj1          ; delete object sprite.
       ld c,(hl)           ; put ink in c register.
       jp cobj             ; colour the object.

; Seek objects at sprite position.

skobj  ld hl,objdta        ; pointer to objects.
       ld de,33            ; distance to room number.
       add hl,de           ; point to room data.
       ld de,39            ; size of each object.
       ld a,(numob)        ; number of objects in game.
       ld b,a              ; set up the loop counter.
skobj0 ld a,(scno)         ; current room number.
       cp (hl)             ; is object in here?
       call z,skobj1       ; yes, check coordinates.
       add hl,de           ; point to next object in table.
       djnz skobj0         ; repeat for all objects.
       ld a,255            ; end of list and nothing found, return 255.
       ret
skobj1 inc hl              ; point to x coordinate.
       ld a,(hl)           ; get coordinate.
       sub (ix+8)          ; subtract sprite x.
       add a,15            ; add sprite height minus one.
       cp 31               ; within range?
       jp nc,skobj2        ; no, ignore object.
       inc hl              ; point to y coordinate now.
       ld a,(hl)           ; get coordinate.
       sub (ix+9)          ; subtract the sprite y.
       add a,15            ; add sprite width minus one.
       cp 31               ; within range?
       jp nc,skobj3        ; no, ignore object.
       pop de              ; remove return address from stack.
       ld a,(numob)        ; objects in game.
       sub b               ; subtract loop counter.
       ret                 ; accumulator now points to object.
skobj3 dec hl              ; back to y position.
skobj2 dec hl              ; back to room.
       ret


; Spawn a new sprite.

spawn  ld hl,sprtab        ; sprite table.
numsp1 ld a,NUMSPR         ; number of sprites.
       ld de,TABSIZ        ; size of each entry.
spaw0  ex af,af'           ; store loop counter.
       ld a,(hl)           ; get sprite type.
       inc a               ; is it an unused slot?
       jr z,spaw1          ; yes, we can use this one.
       add hl,de           ; point to next sprite in table.
       ex af,af'           ; restore loop counter.
       dec a               ; one less iteration.
       jr nz,spaw0         ; keep going until we find a slot.

; Didn't find one but drop through and set up a dummy sprite instead.

spaw1  push ix             ; existing sprite address on stack.
       ld (spptr),hl       ; store spawned sprite address.
       ld (hl),c           ; set the type.
       inc hl              ; point to image.
       ld (hl),b           ; set the image.
       inc hl              ; next byte.
       ld (hl),0           ; frame zero.
       inc hl              ; next byte.
       ld a,(ix+X)         ; x coordinate.
       ld (hl),a           ; set sprite coordinate.
       inc hl              ; next byte.
       ld a,(ix+Y)         ; y coordinate.
       ld (hl),a           ; set sprite coordinate.
       inc hl              ; next byte.
       ex de,hl            ; swap address into de.
       ld hl,(spptr)       ; restore address of details.
       ld bc,5             ; number of bytes to duplicate.
       ldir                ; copy first version to new version.
       ex de,hl            ; swap address into de.
       ld a,(ix+10)        ; direction of original.
       ld (hl),a           ; set the direction.
       inc hl              ; next byte.
       ld (hl),b           ; reset parameter.
       inc hl              ; next byte.
       ld (hl),b           ; reset parameter.
       inc hl              ; next byte.
       ld (hl),b           ; reset parameter.
       inc hl              ; next byte.
       ld (hl),b           ; reset parameter.
rtssp  ld ix,(spptr)       ; address of new sprite.
evis1  call evnt09         ; call sprite initialisation event.
       ld ix,(spptr)       ; address of new sprite.
       call sspria         ; display the new sprite.
       pop ix              ; address of original sprite.
       ret

spptr  defw 0              ; spawned sprite pointer.
seed   defb 0              ; seed for random numbers.
score  defb "000000"       ; player's score.
hiscor defb "000000"       ; high score.
bonus  defb "000000"       ; bonus.
grbase defw 15360          ; graphics base address.

checkx ld a,e              ; x position.
       cp 24               ; off screen?
       ret c               ; no, it's okay.
       pop hl              ; remove return address from stack.
       ret

; Displays the current score.

dscor  call preprt         ; set up font and print position.
       call checkx         ; make sure we're in a printable range.
       ld a,(prtmod)       ; get print mode.
       and a               ; standard size text?
       jp nz,bscor0        ; no, show double-height.
dscor0 push bc             ; place counter onto the stack.
       push hl
       ld a,(hl)           ; fetch character.
       call pchar          ; display character.
       call gaadd          ; get attribute address.
acolor ld a,07h            ; current cell colours.
       ld (hl),a           ; write to attribute cell.
       ld hl,dispy         ; y coordinate.
       inc (hl)            ; move along one.
       pop hl
       inc hl              ; next score column.
       pop bc              ; retrieve character counter.
       djnz dscor0         ; repeat for all digits.
       ld hl,(blkptr)      ; blocks.
       ld (grbase),hl      ; set graphics base.
dscor2 ld hl,(dispx)       ; general coordinates.
       ld (charx),hl       ; set up display coordinates.
       ret

; Displays the current score in double-height characters.

bscor0 push bc             ; place counter onto the stack.
       push hl
       ld a,(hl)           ; fetch character.
       call bchar          ; display big char.
       pop hl
       inc hl              ; next score column.
       pop bc              ; retrieve character counter.
       djnz bscor0         ; repeat for all digits.
       jp dscor2           ; tidy up line and column variables.

; Adds number in the hl pair to the score.

addsc  ld de,score+1       ; ten thousands column.
       ld bc,10000         ; amount to add each time.
       call incsc          ; add to score.
       inc de              ; thousands column.
       ld bc,1000          ; amount to add each time.
       call incsc          ; add to score.
       inc de              ; hundreds column.
       ld bc,100           ; amount to add each time.
       call incsc          ; add to score.
       inc de              ; tens column.
       ld bc,10            ; amount to add each time.
       call incsc          ; add to score.
       inc de              ; units column.
       ld bc,1             ; units.
incsc  push hl             ; store amount to add.
       and a               ; clear the carry flag.
       sbc hl,bc           ; subtract from amount to add.
       jr c,incsc0         ; too much, restore value.
       pop af              ; delete the previous amount from the stack.
       push de             ; store column position.
       call incsc2         ; do the increment.
       pop de              ; restore column.
       jp incsc            ; repeat until all added.
incsc0 pop hl              ; restore previous value.
       ret
incsc2 ld a,(de)           ; get amount.
       inc a               ; add one to column.
       ld (de),a           ; write new column total.
       cp '9'+1            ; gone beyond range of digits?
       ret c               ; no, carry on.
       ld a,'0'            ; mae it zero.
       ld (de),a           ; write new column total.
       dec de              ; back one column.
       jr incsc2

; Add bonus to score.

addbo  ld de,score+5       ; last score digit.
       ld hl,bonus+5       ; last bonus digit.
       and a               ; clear carry.
       ld bc,0630h         ; 6 digits to add, ASCII '0' in c.
addbo0 ld a,(de)           ; get score.
       adc a,(hl)          ; add bonus.
       sub c               ; 0 to 18.
       ld (hl),c           ; zeroise bonus.
       dec hl              ; next bonus.
       cp 58               ; carried?
       jr c,addbo1         ; no, do next one.
       sub 10              ; subtract 10.
addbo1 ld (de),a           ; write new score.
       dec de              ; next score digit.
       ccf                 ; set carry for next digit.
       djnz addbo0         ; repeat for all 6 digits.
       ret

; Swap score and bonus.

swpsb  ld de,score         ; first score digit.
       ld hl,bonus         ; first bonus digit.
       ld b,6              ; digits to add.
swpsb0 ld a,(de)           ; get score and bonus digits.
       ld c,(hl)
       ex de,hl            ; swap pointers.
       ld (hl),c           ; write bonus and score digits.
       ld (de),a
       inc hl              ; next score and bonus.
       inc de
       djnz swpsb0         ; repeat for all 6 digits.
       ret

; Get print address.

gprad  ld a,(dispx)        ; returns scr. add. in de.
       ld e,a              ; place in e for now.
       and 24              ; which of 3 segments do we need?
       add a,high scraddr  ; add 64 for start address of screen.
       ld d,a              ; that's our high byte.
       ld a,e              ; restore x coordinate.
       rrca                ; multiply by 32.
       rrca
       rrca
       and 0e0h            ; lines within segment.
       ld e,a              ; set up low byte for x.
       ld a,(dispy)        ; now get y coordinate.
       add a,e             ; add to low byte.
       ld e,a              ; final low byte.
       ret

; Get property buffer address of char at (dispx, dispy) in hl.

pradd  ld a,(dispx)        ; x coordinate.
       rrca                ; multiply by 32.
       rrca
       rrca
       ld l,a              ; store shift in l.
       and 3               ; high byte bits.
       add a,high MAP      ; 88 * 256 = 64768, start of properties map.
       ld h,a              ; that's our high byte.
       ld a,l              ; restore shift result.
       and 0e0h            ; only want low bits.
       ld l,a              ; put into low byte.
       ld a,(dispy)        ; fetch y coordinate.
       and 1fh             ; should be in range 0 - 31.
       add a,l             ; add to low byte.
       ld l,a              ; new low byte.
       ret

; Get attribute address of char at (dispx, dispy) in hl.

gaadd  ld a,(dispx)        ; x coordinate.
       rrca                ; multiply by 32.
       rrca
       rrca
       ld l,a              ; store shift in l.
       and 3               ; high byte bits.
       add a,high attaddr  ; 88 * 256 = 22528, start of screen attributes.
       ld h,a              ; that's our high byte.
       ld a,l              ; restore shift result.
       and 0e0h            ; only want low bits.
       ld l,a              ; put into low byte.
       ld a,(dispy)        ; fetch y coordinate.
       and 1fh             ; should be in range 0 - 31.
       add a,l             ; add to low byte.
       ld l,a              ; new low byte.
       ret

pchar  rlca                ; multiply char by 8.
       rlca
       rlca
       ld e,a              ; store shift in e.
       and 7               ; only want high byte bits.
       ld d,a              ; store in d.
       ld a,e              ; restore shifted value.
       and 248             ; only want low byte bits.
       ld e,a              ; that's the low byte.
       ld hl,(grbase)      ; address of graphics.
       add hl,de           ; add displacement.
pchark call gprad          ; get screen address.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
;       dec de              ; back again.
;       inc d               ; next screen row down.
;       ldi                 ; transfer byte.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(hl)           ; get image byte.
       ld (de),a           ; copy to screen.
       ret

; Print attributes, properties and pixels.

colpat defb 0
pbpattr
       ld hl,chgfx         ;PUTBLOCK command
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl

pattr  
    if aflag
;       push af
       call wbloc          ; save blockinfo
;       pop af
    endif
pattr2
       ld b,a              ; store cell in b register for now.
       ld e,a              ; displacement in e.
       ld d,0              ; no high byte.
       ld hl,(proptr)      ; pointer to properties.
       add hl,de           ; property cell address.
       ld c,(hl)           ; fetch byte.
       ld a,c              ; put into accumulator.
       cp COLECT           ; is it a collectable?
       jp nz,pattr1        ; no, carry on as normal.
       ld a,b              ; restore cell.
       ld (colpat),a       ; store collectable block.
pattr1 call pradd          ; get property buffer address.
       ld (hl),c           ; write property.
       ld a,b              ; get block number.

; Print attributes, no properties.

panp   ld e,a              ; displacement in e.
       ld d,0              ; no high byte.
       ld hl,(colptr)      ; pointer to colours.
       add hl,de           ; colour cell address.
       ld a,(hl)           ; fetch byte.
       ld (colch3+1),a
colch3 ld a,(coltabl)
       ld c,a
       call gaadd          ; get attribute address.
       ld (hl),c           ; write colour.
       ld a,b              ; restore cell.
; Print character pixels, no more.

pchr   call pchar          ; show character in accumulator.
       ld hl,dispy         ; y coordinate.
       inc (hl)            ; move along one.
       ret

;----------------------------------------------
; Write block
;----------------------------------------------

    if aflag
wbloc
pbptr   ld de,0000h
        ld hl,scno
        ldi                ; write screen.
        ld hl,dispx
        ldi                ; write x position of block.
        ldi                ; write y position of block.
        ld (de),a          ; store block number
        inc de
        ld (pbptr+1),de
        ret
    endif

; Shifter sprite routine for objects.

sprit7 xor 7
       inc a
sprit3 rl l                ; shift into position.
       rl c
       rl h
       dec a               ; one less iteration.
       jp nz,sprit3
       ld a,l
       ld l,c
       ld c,h
       ld h,a
       jp sprit0           ; now apply to screen.

sprite push hl             ; store sprite graphic address.
       call scadd          ; get screen address in hl.
       ex de,hl            ; switch to de.
       pop hl              ; restore graphic address.
       ld a,(dispy)        ; y position.
       and 7               ; position straddling cells.
       ld b,a              ; store in b register.
       ld a,16             ; pixel height.
sprit1 ex af,af'
       ld c,(hl)           ; fetch first byte.
       inc hl              ; next byte.
       push hl             ; store source address.
       ld l,(hl)
       ld h,0
       ld a,b              ; position straddling cells.
       and a               ; is it zero?
       jr z,sprit0         ; yes, apply to screen.
       cp 5
       jr nc,sprit7
       and a               ; clear carry.
sprit2 rr c
       rr l
       rr h
       dec a
       jp nz,sprit2
sprit0 ld a,(de)           ; fetch screen image.
       xor c               ; merge with graphic.
       ld (de),a           ; write to screen.
       inc e               ; next screen byte.
       ld a,(de)           ; fetch screen image.
       xor l               ; combine with graphic.
       ld (de),a           ; write to screen.
       inc de              ; next screen address.
       ld a,(de)           ; fetch screen image.
       xor h               ; combine with graphic.
       ld (de),a           ; write to screen.
       dec de              ; left to middle byte.
       dec e               ; back to start byte.
       inc d               ; increment line number.
       ld a,d              ; segment address.
       and 7               ; reached end of segment?
       jp nz,sprit6        ; no, just do next line within cell.
       ld a,e              ; low byte.
       add a,32            ; look down.
       ld e,a              ; new address.
       jp c,sprit6         ; done.
       ld a,d              ; high byte.
       sub 8               ; start of segment.
       ld d,a              ; new high byte.
sprit6 pop hl              ; restore source address.
       inc hl              ; next source byte.
       ex af,af'
       dec a
       jp nz,sprit1
       ret

; Get room address.

groom  ld a,(scno)         ; screen number.
groomx ld de,0             ; start at zero.
       ld hl,(scrptr)      ; pointer to screens.
       and a               ; is it the first one?
groom1 jr z,groom0         ; no more screens to skip.
       ld c,(hl)           ; low byte of screen size.
       inc hl              ; point to high byte.
       ld b,(hl)           ; high byte of screen size.
       inc hl              ; next address.
       ex de,hl            ; put total in hl, pointer in de.
       add hl,bc           ; skip a screen.
       ex de,hl            ; put total in de, pointer in hl.
       dec a               ; one less iteration.
       jr groom1           ; loop until we reach the end.
groom0 ld hl,(scrptr)      ; pointer to screens.
       add hl,de           ; add displacement.
       ld a,(numsc)        ; number of screens.
       ld d,0              ; zeroise high byte.
       ld e,a              ; displacement in de.
       add hl,de           ; add double displacement to address.
       add hl,de
       ret

; Draw present room.

droom  ld a,(wintop)       ; window top.
       ld (dispx),a        ; set x coordinate.
droom2 ld hl,(blkptr)      ; blocks.
       ld (grbase),hl      ; set graphics base.
       call groom          ; get address of current room.
       xor a               ; zero in accumulator.
       ld (comcnt),a       ; reset compression counter.
       ld a,(winhgt)       ; height of window.
droom0 push af             ; store row counter.
       ld a,(winlft)       ; window left edge.
       ld (dispy),a        ; set cursor position.
       ld a,(winwid)       ; width of window.
droom1 push af             ; store column counter.
       call flbyt          ; decompress next byte on the fly.
       push hl             ; store address of cell.
       call pattr2         ; show attributes and block.
       pop hl              ; restore cell address.
       pop af              ; restore loop counter.
       dec a               ; one less column.
       jr nz,droom1        ; repeat for entire line.
       ld a,(dispx)        ; x coord.
       inc a               ; move down one line.
       ld (dispx),a        ; set new position.
       pop af              ; restore row counter.
       dec a               ; one less row.
       jr nz,droom0        ; repeat for all rows.
       ret

; Decompress bytes on-the-fly.

flbyt  ld a,(comcnt)       ; compression counter.
       and a               ; any more to decompress?
       jr nz,flbyt1        ; yes.
       ld a,(hl)           ; fetch next byte.
       inc hl              ; point to next cell.
       cp 255              ; is this byte a control code?
       ret nz              ; no, this byte is uncompressed.
       ld a,(hl)           ; fetch byte type.
       ld (combyt),a       ; set up the type.
       inc hl              ; point to quantity.
       ld a,(hl)           ; get quantity.
       inc hl              ; point to next byte.
flbyt1 dec a               ; one less.
       ld (comcnt),a       ; store new quantity.
       ld a,(combyt)       ; byte to expand.
       ret


combyt defb 0              ; byte type compressed.
comcnt defb 0              ; compression counter.

; Ladder down check.

laddd  ld a,(ix+8)         ; x coordinate.
       and 254             ; make it even.
       ld (ix+8),a         ; reset it.
       ld h,(ix+9)         ; y coordinate.
numsp5 add a,SPR_HGT       ; look down 16 pixels.
       ld l,a              ; coords in hl.
       jr laddv

; Ladder up check.

laddu  ld a,(ix+8)         ; x coordinate.
       and 254             ; make it even.
       ld (ix+8),a         ; reset it.
       ld h,(ix+9)         ; y coordinate.
numsp6 add a,SPR_HGT-2     ; look 2 pixels above feet.
       ld l,a              ; coords in hl.
laddv  ld (dispx),hl       ; set up test coordinates.
       call tstbl          ; get map address.
       call ldchk          ; standard ladder check.
       ret nz              ; no way through.
       inc hl              ; look right one cell.
       call ldchk          ; do the check.
       ret nz              ; impassable.
       ld a,(dispy)        ; y coordinate.
       and 7               ; position straddling block cells.
       ret z               ; no more checks needed.
       inc hl              ; look to third cell.
       call ldchk          ; do the check.
       ret                 ; return with zero flag set accordingly.

; Can go up check.

cangu  ld a,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
       sub 2               ; look up 2 pixels.
       ld l,a              ; coords in hl.
       ld (dispx),hl       ; set up test coordinates.
       call tstbl          ; get map address.
       call lrchk          ; standard left/right check.
       ret nz              ; no way through.
       inc hl              ; look right one cell.
       call lrchk          ; do the check.
       ret nz              ; impassable.
       ld a,(dispy)        ; y coordinate.
       and 7               ; position straddling block cells.
       ret z               ; no more checks needed.
       inc hl              ; look to third cell.
       call lrchk          ; do the check.
       ret                 ; return with zero flag set accordingly.

; Can go down check.

cangd  ld a,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
numsp3 add a,SPR_HGT       ; look down 16 pixels.
       ld l,a              ; coords in hl.
       ld (dispx),hl       ; set up test coordinates.
       call tstbl          ; get map address.
       call plchk          ; block, platform check.
       ret nz              ; no way through.
       inc hl              ; look right one cell.
       call plchk          ; block, platform check.
       ret nz              ; impassable.
       ld a,(dispy)        ; y coordinate.
       and 7               ; position straddling block cells.
       ret z               ; no more checks needed.
       inc hl              ; look to third cell.
       call plchk          ; block, platform check.
       ret                 ; return with zero flag set accordingly.

; Can go left check.

cangl  ld l,(ix+8)         ; x coordinate.
       ld a,(ix+9)         ; y coordinate.
       sub 2               ; look left 2 pixels.
       ld h,a              ; coords in hl.
       jr cangh            ; test if we can go there.

; Can go right check.

cangr  ld l,(ix+8)         ; x coordinate.
       ld a,(ix+9)         ; y coordinate.
       add a,16            ; look right 16 pixels.
       ld h,a              ; coords in hl.

cangh  ld (dispx),hl       ; set up test coordinates.
cangh2 ld b,SPR_HGT/8+1    ; default rows to write.
       ld a,l              ; x position.
       and 7               ; does x straddle cells?
       jr nz,cangh0        ; yes, loop counter is good.
       dec b               ; one less row to write.
cangh0 call tstbl          ; get map address.
       ld de,32            ; distance to next cell.
cangh1 call lrchk          ; standard left/right check.
       ret nz              ; no way through.
       add hl,de           ; look down.
       djnz cangh1
       ret

; Check left/right movement is okay.

lrchk  ld a,(hl)           ; fetch map cell.
       cp WALL             ; is it passable?
       jr z,lrchkx         ; no.
       cp FODDER           ; fodder has to be dug.
       jr z,lrchkx         ; not passable.
always xor a               ; report it as okay.
       ret
lrchkx xor a               ; reset all bits.
       inc a
       ret

; Check platform or solid item is not in way.

plchk  ld a,(hl)           ; fetch map cell.
       cp WALL             ; is it passable?
       jr z,lrchkx         ; no.
       cp FODDER           ; fodder has to be dug.
       jr z,lrchkx         ; not passable.
       cp PLATFM           ; platform is solid.
       jr z,plchkx         ; not passable.
       cp LADDER           ; is it a ladder?
       jr z,lrchkx         ; on ladder, deny movement.
plchk0 xor a               ; report it as okay.
       ret
plchkx ld a,(dispx)        ; x coordinate.
       and 7               ; position straddling blocks.
       jr z,lrchkx         ; on platform, deny movement.
       jr plchk0

; Check ladder is available.

ldchk  ld a,(hl)           ; fetch cell.
       cp LADDER           ; is it a ladder?
       ret                 ; return with zero flag set accordingly.

; Get collectables.

getcol ld b,COLECT         ; collectable blocks.
       call tded           ; test for collectable blocks.
       cp b                ; did we find one?
       ret nz              ; none were found, job done.
       call gtblk          ; get block.
       call evnt20         ; collected block event.
       jr getcol           ; repeat until none left.

; Get collectable block.

gtblk  ld (hl),0           ; make it empty now.
       ld de,MAP           ; map address.
       and a               ; clear carry.
       sbc hl,de           ; find cell number.
       ld a,l              ; get low byte of cell number.
       and 31              ; 0 - 31 is column.
       ld d,a              ; store y in d register.
       add hl,hl           ; multiply by 8.
       add hl,hl
       add hl,hl           ; x is now in h.
       ld e,h              ; put x in e.
       ld (dispx),de       ; set display coordinates.

       ld a,(colpat)       ; get collectable block used on this screen.
       rlca                ; multiply char by 8.
       rlca
       rlca
       ld e,a              ; store shift in e.
       and 7               ; only want high byte bits.
       ld d,a              ; store in d.
       ld a,e              ; restore shifted value.
       and 248             ; only want low byte bits.
       ld e,a              ; that's the low byte.
       ld hl,chgfx         ; address of graphics.
       add hl,de           ; add displacement.
       call gprad          ; get screen address.

       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       inc hl              ; next image byte.
       inc d               ; next screen row down.
       ld a,(de)           ; get image byte.
       xor (hl)            ; merge with screen image.
       ld (de),a           ; copy to screen.
       call gaadd          ; get attribute address for block.
       ld a,(bcol)         ; first block colour.
       ld (colch4+1),a
colch4 ld a,(coltabl)
       ld (hl),a           ; set block attribute.
       ret

; Touched deadly block check.
; Returns with DEADLY (must be non-zero) in accumulator if true.

tded   ld l,(ix+8)         ; x coordinate.
       ld h,(ix+9)         ; y coordinate.
       ld (dispx),hl       ; set up test coordinates.
       call tstbl          ; get map address.
       ld de,31            ; default distance to next line down.
       cp b                ; is this the required block?
       ret z               ; yes.
       inc hl              ; next cell.
       ld a,(hl)           ; fetch type.
       cp b                ; is this deadly/custom?
       ret z               ; yes.
       ld a,(dispy)        ; horizontal position.
       ld c,a              ; store column in c register.
       and 7               ; is it straddling cells?
       jr z,tded0          ; no.
       inc hl              ; last cell.
       ld a,(hl)           ; fetch type.
       cp b                ; is this the block?
       ret z               ; yes.
       dec de              ; one less cell to next row down.
tded0  add hl,de           ; point to next row.
       ld a,(hl)           ; fetch left cell block.
       cp b                ; is this fatal?
       ret z               ; yes.
       inc hl              ; next cell.
       ld a,(hl)           ; fetch type.
       cp b                ; is this fatal?
       ret z               ; yes.
       ld a,c              ; horizontal position.
       and 7               ; is it straddling cells?
       jr z,tded1          ; no.
       inc hl              ; last cell.
       ld a,(hl)           ; fetch type.
       cp b                ; is this fatal?
       ret z               ; yes.
tded1  ld a,(dispx)        ; vertical position.
       and 7               ; is it straddling cells?
       ret z               ; no, job done.
       add hl,de           ; point to next row.
       ld a,(hl)           ; fetch left cell block.
       cp b                ; is this fatal?
       ret z               ; yes.
       inc hl              ; next cell.
       ld a,(hl)           ; fetch type.
       cp b                ; is this fatal?
       ret z               ; yes.
       ld a,c              ; horizontal position.
       and 7               ; is it straddling cells?
       ret z               ; no.
       inc hl              ; last cell.
       ld a,(hl)           ; fetch final type.
       ret                 ; return with final type in accumulator.


; Fetch block type at (dispx, dispy).

tstbl  ld a,(dispx)        ; fetch x coord.
       rlca                ; divide by 8,
       rlca                ; and multiply by 32.
       ld d,a              ; store in d.
       and 0e0h            ; mask off high bits.
       ld e,a              ; low byte.
       ld a,d              ; restore shift result.
       and 3               ; high bits.
       ld d,a              ; got displacement in de.
       ld a,(dispy)        ; y coord.
       rra                 ; divide by 8.
       rra
       rra
       and 31              ; only want 0 - 31.
       add a,e             ; add to displacement.
       ld e,a              ; displacement in de.
       ld hl,MAP           ; position of dummy screen.
       add hl,de           ; point to address.
       ld a,(hl)           ; fetch byte there.
       ret

; Jump - if we can.
; Requires initial speed to be set up in accumulator prior to call.

jump   neg                 ; switch sign so we jump up.
       ld c,a              ; store in c register.
;       ld a,(ix+8)         ; x coordinate.
;       ld h,(ix+9)         ; y coordinate.
;numsp4 add a,16            ; look down 16 pixels.
;       ld l,a              ; coords in hl.
;       and 7               ; are we on platform boundary?
;       ret nz              ; no, cannot jump.
;       ld (dispx),hl       ; set up test coordinates.
;       ld b,a              ; copy to b register.
;       call tstbl          ; get map address.
;       call plchk          ; block, platform check.
;       jr nz,jump0         ; it's solid, we can jump.
;       inc hl              ; look right one cell.
;       call plchk          ; block, platform check.
;       jr nz,jump0         ; it's solid, we can jump.
;       ld a,b              ; y coordinate.
;       and 7               ; position straddling block cells.
;       ret z               ; no more checks needed.
;       inc hl              ; look to third cell.
;       call plchk          ; block, platform check.
;       ret z               ; not solid, don't jump.
jump0  ld a,(ix+13)        ; jumping flag.
       and a               ; is it set?
       ret nz              ; already in the air.
       inc (ix+13)         ; set it.
       ld (ix+14),c        ; set jump height.
       ret

hop    ld a,(ix+13)        ; jumping flag.
       and a               ; is it set?
       ret nz              ; already in the air.
       ld (ix+13),255      ; set it.
       ld (ix+14),0        ; set jump table displacement.
       ret

randomx 
       ld d,a              ; multiplication parameter.
       call random		   ; random number 0 - 255.
       ld h,a			   ; second multiplication parameter.
       call imul		   ; multiply together.
       ld a,h		 	   ; put result in accumulator.
       ld (varrnd),a	   ; write to random variable.
       ret

; Random numbers code.
; Pseudo-random number generator, 8-bit.

random ld hl,seed          ; set up seed pointer.
       ld a,(hl)           ; get last random number.
       ld b,a              ; copy to b register.
       rrca                ; multiply by 32.
       rrca
       rrca
       xor 31
       add a,b
       sbc a,255
       ld (hl),a           ; store new seed.
       ld (varrnd),a       ; return number in variable.
       ret

ktestx ld hl,keys          ; keys.
       ld e,a	           ; key number in de.
       ld d,0
       add hl,de           ; point to key.
       ld a,(hl)           ; get key.

; Keyboard test routine.

ktest  ld b,a              ; key to test in b.
       and 0f0h
       rrca                ; to find position within row.
       rrca
       rrca
       rrca
       inc a
       ld c,a
       ld a,b
       and 15              ; mask bits d0-d3 for row.
       out (0b5h),a
       in a,(0b5h)         ; read port
ktest1 rra                 ; rotate bit out of result.
       dec c               ; loop counter.
       jp nz,ktest1        ; repeat until bit for position in carry.
       ret


; Joystick and keyboard reading routines.

joykey ld a,(contrl)       ; control flag.
       dec a               ; is it the keyboard?
       jr z,joyjoy         ; no, it's Kempston joystick.
       dec a               ; Sinclair?
       jr z,joysin         ; read Sinclair joystick.

; Keyboard controls.

       ld hl,keys+6        ; address of last key.
       ld e,0              ; zero reading.
       ld d,7              ; keys to read.
joyke0 ld a,(hl)           ; get key from table.
       call ktest          ; being pressed?
       ccf                 ; complement the carry.
       rl e                ; rotate into reading.
       dec hl              ; next key.
       dec d               ; one less to do.
       jp nz,joyke0        ; repeat for all keys.
       ld a,e
       jr joyjo2           ; store the value.

; EXT1/INT joystick controls.

joyjoy ld      e,255
       call    extjoy      ;read ext1 joy
       ld      e,0ffh
       ld a,08
       out (0b5h),a        ;keyboard row select
       in a,(0b5h)         ;ins space rshift . / , del M
       rlca
       rlca
       rl e
       ld a,07
       out (0b5h),a
       in a,(0b5h)          ;alt enter left hold up right down stop
       rrca
       rrca
       rrca
       rl e                ;right down stop alt enter left hold up
       rrca
       rrca
       rrca
       rl e                ;left hold up right down stop alt enter
       rrca
       rrca
       rrca
       rrca
       rl e                ;down stop alt enter left hold up right 
       rrca
       rrca
       rl e                ;up right  down stop alt enter left hold 
       ld a,e
       and c
       cpl
joyjo2 ld (joyval),a       ; remember value.
       ret

; EXT2 joystick controls.

joysin ld      e,4
       call    extjoy      ;read ext1 joy
       ld      a,c
       cpl
       jr      joyjo2

extjoy ld bc,05ffh
extjy1 ld a,e
       add a,b
       out (0b5h),a
       in a,(0b6h)
       rrca
       rl c
       djnz extjy1
       rr c
       ret c
       res 4,c
       ret

; Display message.

;dmsg   ld hl,nummsg        ; total messages.
;       cp (hl)             ; does this one exist?
;       ret nc              ; no, nothing to display.
dmsg   ld hl,msgdat        ; pointer to messages.
       call getwrd         ; get message number.
dmsg3  call preprt         ; pre-printing stuff.
       call checkx         ; make sure we're in a printable range.
       ld a,(prtmod)       ; print mode.
       and a               ; standard size?
       jp nz,bmsg1         ; no, double-height text.
dmsg0  push hl             ; store string pointer.
       ld a,(hl)           ; fetch byte to display.
       and 127             ; remove any end marker.
       cp 13               ; newline character?
       jr z,dmsg1
       call pchar          ; display character.
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; current cell colours.
       ld (hl),a           ; write to attribute cell.
       call nexpos         ; display position.
       jr nz,dmsg2         ; not on a new line.
       call nexlin         ; next line down.
dmsg2  pop hl
       ld a,(hl)           ; fetch last character.
       rla                 ; was it the end?
       jp c,dscor2         ; yes, job done.
       inc hl              ; next character to display.
       jr dmsg0
dmsg1  ld hl,dispx         ; x coordinate.
       inc (hl)            ; newline.
       ld a,(hl)           ; fetch position.
       cp 24               ; past screen edge?
       jr c,dmsg4          ; no, it's okay.
       ld (hl),0           ; restart at top.
dmsg4  inc hl              ; y coordinate.
       ld (hl),0           ; carriage return.
       jr dmsg2
prtmod defb 0              ; print mode, 0 = standard, 1 = double-height.

; Display message in big text.

bmsg1  ld a,(hl)           ; get character to display.
       push hl             ; store pointer to message.
       and 127             ; only want 7 bits.
       cp 13               ; newline character?
       jr z,bmsg2
       call bchar          ; display big char.
bmsg3  pop hl              ; retrieve message pointer.
       ld a,(hl)           ; look at last character.
       inc hl              ; next character in list.
       rla                 ; was terminator flag set?
       jr nc,bmsg1         ; no, keep going.
       ret
bmsg2  ld hl,charx         ; x coordinate.
       inc (hl)            ; newline.
       inc (hl)            ; newline.
       ld a,(hl)           ; fetch position.
       cp 23               ; past screen edge?
       jr c,bmsg3          ; no, it's okay.
       ld (hl),0           ; restart at top.
       inc hl              ; y coordinate.
       ld (hl),0           ; carriage return.
       jr bmsg3


; Big character display.

bchar  rlca                ; multiply char by 8.
       rlca
       rlca
       ld e,a              ; store shift in e.
       and 7               ; only want high byte bits.
       ld d,a              ; store in d.
       ld a,e              ; restore shifted value.
       and 248             ; only want low byte bits.
       ld e,a              ; that's the low byte.
fontadr ld hl,initEP        ; address of font.
       add hl,de           ; add displacement.
       call gprad          ; get screen address.
       ex de,hl            ; font in de, screen address in hl.
       ld b,8              ; height of character in font.
bchar0 ld a,(de)           ; get a bit of the font.
       inc de              ; next line of font.
       ld (hl),a           ; write to screen.
       inc h               ; down a line.
       ld (hl),a           ; write to screen.
       call nline          ; next line down.
       djnz bchar0         ; repeat.
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; current colour.
       ld (hl),a           ; set attribute.
       ld c,a              ; copy colour to c.
       ld de,32            ; distance to next line.
       add hl,de           ; point to second cell.
       ld a,h              ; high byte of address.
       cp high (attaddr+300h) ; past edge of screen?
       jr nc,bchar1        ; yes, don't write to printer buffer/sysvars.
       ld (hl),c           ; set second cell's attributes.
bchar1 call nexpos         ; display position.
       jp nz,bchar2        ; not on a new line.
bchar3 inc (hl)            ; newline.
       call nexlin         ; next line check.
bchar2 jp dscor2           ; tidy up line and column variables.

; Display a character.

achar  ld b,a              ; copy to b.
       call preprt         ; get ready to print.
       ld a,(prtmod)       ; print mode.
       and a               ; standard size?
       ld a,b              ; character in accumulator.
       jp nz,bchar         ; no, double-height text.
       call pchar          ; display character.
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; current cell colours.
       ld (hl),a           ; write to attribute cell.
       call nexpos         ; display position.
       jp z,bchar3         ; next line down.
       jp bchar2           ; tidy up.

; Get next print column position.

nexpos ld hl,dispy         ; display position.
       inc (hl)
;       ld a,(hl)           ; get coordinate.
;       inc a               ; move along one position.
;       and 31              ; reached edge of screen?
;       ld (hl),a           ; set new position.
       dec hl              ; point to x now.
       ret                 ; return with status in zero flag.

; Get next print line position.

nexlin inc (hl)            ; newline.
       ld a,(hl)           ; vertical position.
       cp 24               ; past screen edge?
       ret c               ; no, still okay.
       ld (hl),0           ; restart at top.
       ret

; Pre-print preliminaries.

preprt ld de,(fontadr+1)   ; font pointer.
       ld (grbase),de      ; set up graphics base.
prescr ld de,(charx)       ; display coordinates.
       ld (dispx),de       ; set up general coordinates.
       ret

; On entry: hl points to word list
;           a contains word number.

getwrd and a               ; first word in list?
       ret z               ; yep, don't search.
       ld b,a
getwd0 ld a,(hl)
       inc hl
       cp 128              ; found end?
       jr c,getwd0         ; no, carry on.
       djnz getwd0         ; until we have right number.
       ret


; Bubble sort.

bsort  ld b,NUMSPR - 1     ; sprites to swap.
       ld ix,sprtab        ; sprite table.
bsort0 push bc             ; store loop counter for now.

       ld a,(ix+0)         ; first sprite type.
       inc a               ; is it switched off?
       jr z,swemp          ; yes, may need to switch another in here.

       ld a,(ix+TABSIZ)    ; check next slot exists.
       inc a               ; is it enabled?
       jr z,bsort2         ; no, nothing to swap.

       ld a,(ix+(3+TABSIZ)); fetch next sprite's coordinate.
       cp (ix+3)           ; compare with this x coordinate.
       jr c,bsort1         ; next sprite is higher - may need to switch.
bsort2 ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       pop bc              ; retrieve loop counter.
       djnz bsort0         ; repeat for remaining sprites.
       ret

bsort1 ld a,(ix+TABSIZ)    ; sprite on/off flag.
       inc a               ; is it enabled?
       jr z,bsort2         ; no, nothing to swap.
       call swspr          ; swap positions.
       jr bsort2

swemp  ld a,(ix+TABSIZ)    ; next table entry.
       inc a               ; is that one on?
       jr z,bsort2         ; no, nothing to swap.
       call swspr          ; swap positions.
       jr bsort2

; Swap sprites.

swspr  push ix             ; table address on stack.
       pop hl              ; pop into hl pair.
       ld d,h              ; copy to de pair.
       ld e,l
       ld bc,TABSIZ        ; distance to second entry.
       add hl,bc           ; point to second sprite entry.
       ld b,TABSIZ         ; bytes to swap.
swspr0 ld c,(hl)           ; fetch second byte.
       ld a,(de)           ; fetch first byte.
       ld (hl),a           ; copy to second.
       ld a,c              ; second byte in accumulator.
       ld (de),a           ; copy to first sprite entry.
       inc de              ; next byte.
       inc hl              ; next byte.
       djnz swspr0         ; swap all bytes in table entry.
       ret


; Process sprites.

pspr   ld b,NUMSPR         ; sprites to process.
       ld ix,sprtab        ; sprite table.
pspr1  push bc             ; store loop counter for now.
       ld a,(ix+0)         ; fetch sprite type.
       cp 9                ; within range of sprite types?
       call c,pspr2        ; yes, process this one.
       ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       pop bc              ; retrieve loop counter.
       djnz pspr1          ; repeat for remaining sprites.
       ret
pspr2  ld (ogptr),ix       ; store original sprite pointer.
       call pspr3          ; do the routine.
rtorg  ld ix,(ogptr)       ; restore original pointer to sprite.
rtorg0 ret
pspr3  ld hl,evtyp0        ; sprite type events list.
pspr4  add a,a             ; double accumulator.
       ld e,a              ; copy to de.
       ld d,0              ; no high byte.
       add hl,de           ; point to address of routine.
       ld e,(hl)           ; address low.
       inc hl              ; next byte of address.
       ld d,(hl)           ; address high.
       ex de,hl            ; swap address into hl.
       jp (hl)             ; go there.
ogptr  defw 0              ; original sprite pointer.

; Address of each sprite type's routine.

evtyp0 defw evnt00
evtyp1 defw evnt01
evtyp2 defw evnt02
evtyp3 defw evnt03
evtyp4 defw evnt04
evtyp5 defw evnt05
evtyp6 defw evnt06
evtyp7 defw evnt07
evtyp8 defw evnt08


; Display sprites.

dspr   ld b,NUMSPR/2       ; number of sprites to display.
dspr0  push bc             ; store loop counter for now.
       ld a,(ix+0)         ; get sprite type.
       inc a               ; is it enabled?
       jr nz,dspr1         ; yes, it needs deleting.
dspr5  ld a,(ix+5)         ; new type.
       inc a               ; is it enabled?
       jr nz,dspr3         ; yes, it needs drawing.

dspr2  push ix             ; put ix on stack.
       pop hl              ; pop into hl.
       ld e,l              ; copy to de.
       ld d,h

;dspr2  ld e,ixl            ; copy ix to de.
;       ld d,ixh
;       ld l,e              ; copy to hl.
;       ld h,d
       ld bc,5             ; distance to new type.
       add hl,bc           ; point to new properties.
       ldi                 ; copy to old positions.
       ldi
       ldi
       ldi
       ldi
       ld c,TABSIZ*2       ; distance to next odd/even entry.
       add ix,bc           ; next sprite.
       pop bc              ; retrieve loop counter.
       djnz dspr0          ; repeat for remaining sprites.
       ret
;dspr1  ld a,(ix+3)         ; old x coord.
;       cp 177              ; beyond maximum?
;       jr nc,dspr5         ; yes, don't delete it.
dspr1  ld a,(ix+5)         ; type of new sprite.
       inc a               ; is this enabled?
       jr nz,dspr4         ; yes, display both.
dspr6  call sspria         ; show single sprite.
       jp dspr2

; Displaying two sprites.  Don't bother redrawing if nothing has changed.

dspr4  ld a,(ix+4)         ; old y.
       cp (ix+9)           ; compare with new value.
       jr nz,dspr7         ; they differ, need to redraw.
       ld a,(ix+3)         ; old x.
       cp (ix+8)           ; compare against new value.
       jr nz,dspr7         ; they differ, need to redraw.
       ld a,(ix+2)         ; old frame.
       cp (ix+7)           ; compare against new value.
       jr nz,dspr7         ; they differ, need to redraw.
       ld a,(ix+1)         ; old image.
       cp (ix+6)           ; compare against new value.
       jp z,dspr2          ; everything is the same, don't redraw.
dspr7  call sspric         ; delete old sprite, draw new one simultaneously.
       jp dspr2
dspr3  call ssprib         ; show single sprite.
       jp dspr2


; Get sprite address calculations.
; gspran = new sprite, gsprad = old sprite.

gspran ld l,(ix+8)         ; new x coordinate.
       ld h,(ix+9)         ; new y coordinate.
       ld (dispx),hl       ; set display coordinates.
       ld a,(ix+6)         ; new sprite image.
       call gfrm           ; fetch start frame for this sprite.
       ld a,(hl)           ; frame in accumulator.
       add a,(ix+7)        ; new add frame number.
       jp gspra0

gsprad ld l,(ix+3)         ; x coordinate.
       ld h,(ix+4)         ; y coordinate.
       ld (dispx),hl       ; set display coordinates.
       ld a,(ix+1)         ; sprite image.
       call gfrm           ; fetch start frame for this sprite.
       ld a,(hl)           ; frame in accumulator.
       add a,(ix+2)        ; add frame number.

gspra0 ld e,00h            ; multiply by 128.
       srl a
       rr e
       ld d,a
    if bflag
       ld l,e
       rra
       rr l
       ld h,a
       add hl,de
       ex de,hl
    endif

       ld hl,sprgfx        ; address of play sprites.
       add hl,de           ; point to frame.

       ld a,(dispy)        ; y coordinate.
       and 6               ; position within byte boundary.
       ld c,a              ; low byte of table displacement.
       rlca                ; multiply by 32.
       rlca                ; already a multiple
       rlca                ; of 2, so just 4
    if bflag
       ld d,a
       rlca                ; shifts needed.
       add a,d
    else
       rlca                ; shifts needed.
    endif

       ld e,a              ; put displacement in low byte of de.
       ld d,0              ; zero the high byte.
       ld b,d              ; no high byte for mask displacement either.
       add hl,de           ; add to sprite address.
       ex de,hl            ; need it in de for now.
       ld hl,spmask        ; pointer to mask table.
       add hl,bc           ; add displacement to pointer.
       ld c,(hl)           ; left mask.
       inc hl
       ld b,(hl)           ; right mask.

; Drop into screen address routine.
; This routine returns a screen address for (dispx, dispy) in hl.

scadd  ld a,(dispx)        ; coordinate.
       ld l,a              ; low byte of table.
       ld h,high SCADTB    ; high byte of 64256 (SCADTB).
       ld a,(hl)           ; fetch high byte.
       inc h               ; point to low byte table.
       ld l,(hl)           ; fetch low byte.
       ld h,a              ; hl points to start of line.
       ld a,(dispy)        ; y pixel coordinate.
       rrca                ; divide by 8.
       rrca
       rrca
       and 31              ; squares 0 - 31 across screen.
       add a,l             ; add to address.
       ld l,a              ; copy to hl = address of screen.
       ret

spmask defb 255,0,63,192,15,240,3,252


; These are the sprite routines.
; sspria = single sprite, old (ix).
; ssprib = single sprite, new (ix+5).
; sspric = both sprites, old (ix) and new (ix+5).

sspria call gsprad         ; get old sprite address.
sspri2 ld a,SPR_HGT        ; vertical lines.
sspri0 ex af,af'           ; store line counter away in alternate registers.
       call dline          ; draw a line.
       ex af,af'           ; restore line counter.
       dec a               ; one less to go.
       jp nz,sspri0
       ret

ssprib call gspran         ; get new sprite address.
       jp sspri2

sspric call gsprad         ; get old sprite address.
       exx                 ; store addresses.
       call gspran         ; get new sprite addresses.

    rept SPR_HGT-1
       call draw_del_line  ; draw a line. / restore old addresses. / delete a line.
       exx                 ; flip to new sprite addresses.
    endm

draw_del_line
       call dline          ; draw a line.
       exx                 ; restore old addresses.

; Drop through.
; Line drawn, now work out next target address.

dline  ld a,(de)           ; graphic data.
       and c               ; mask away what's not needed.
       xor (hl)            ; XOR with what's there.
       ld (hl),a           ; bung it in.
       inc l               ; next screen address.
       inc l               ; next screen address.
       ld a,(de)           ; fetch data.
       and b               ; mask away unwanted bits.
       xor (hl)            ; XOR with what's there.
       ld (hl),a           ; bung it in.
       inc de              ; next graphic.
       dec l               ; one character cell to the left.
       ld a,(de)           ; second bit of data.
       xor (hl)            ; XOR with what's there.
       ld (hl),a           ; bung it in.
       inc de              ; point to next line of data.
       dec l               ; another char left.

; Line drawn, now work out next target address.

nline  inc h               ; increment pixel.
       ld a,h              ; get pixel address.
       and 7               ; straddling character position?
       ret nz              ; no, we're on next line already.
       ld a,h              ; get pixel address.
       sub 8               ; subtract 8 for start of segment.
       ld h,a              ; new high byte of address.
       ld a,l              ; get low byte of address.
       add a,32            ; one line down.
       ld l,a              ; new low byte.
       ret nc              ; not reached next segment yet.
       ld a,h              ; address high.
       add a,8             ; add 8 to next segment.
       ld h,a              ; new high byte.
       cp high attaddr     ; reached end of screen?
       ret c               ; not yet.
       ld h,high emptysc   ; back empty
       ret


; Animates a sprite.

animsp ld hl,frmno         ; game frame.
       and (hl)            ; is it time to change the frame?
       ret nz              ; not this frame.
       ld a,(ix+6)         ; sprite image.
       call gfrm           ; get frame data.
       inc hl              ; point to frames.
       ld a,(ix+7)         ; sprite frame.
       inc a               ; next one along.
       cp (hl)             ; reached the last frame?
       jr c,anims0         ; no, not yet.
       xor a               ; start at first frame.
anims0 ld (ix+7),a         ; new frame.
       ret
animbk ld hl,frmno         ; game frame.
       and (hl)            ; is it time to change the frame?
       ret nz              ; not this frame.
       ld a,(ix+6)         ; sprite image.
       call gfrm           ; get frame data.
       inc hl              ; point to frames.
       ld a,(ix+7)         ; sprite frame.
       and a               ; first one?
       jr nz,rtanb0        ; yes, start at end.
       ld a,(hl)           ; last sprite.
rtanb0 dec a               ; next one along.
       jr anims0           ; set new frame.

; Check for collision with other sprite, strict enforcement.

sktyp  ld hl,sprtab        ; sprite table.
numsp2 ld a,NUMSPR         ; number of sprites.
sktyp0 ex af,af'           ; store loop counter.
       ld (skptr),hl       ; store pointer to sprite.
       ld a,(hl)           ; get sprite type.
       cp b                ; is it the type we seek?
       jr z,coltyp         ; yes, we can use this one.
sktyp1 ld hl,(skptr)       ; retrieve sprite pointer.
       ld de,TABSIZ        ; size of each entry.
       add hl,de           ; point to next sprite in table.
       ex af,af'           ; restore loop counter.
       dec a               ; one less iteration.
       jp nz,sktyp0        ; keep going until we find a slot.
       ld hl,0             ; default to ROM address - no sprite.
       ld (skptr),hl       ; store pointer to sprite.
       or h                ; don't return with zero flag set.
       ret                 ; didn't find one.
skptr  defw 0              ; search pointer.

coltyp ld a,(ix+0)         ; current sprite type.
       cp b                ; seeking sprite of same type?
       jr z,colty1         ; yes, need to check we're not detecting ourselves.
colty0 ld de,X             ; distance to x position in table.
       add hl,de           ; point to coords.
       ld e,(hl)           ; fetch x coordinate.
       inc hl              ; now point to y.
       ld d,(hl)           ; that's y coordinate.

; Drop into collision detection.

colc16 ld a,(ix+X)         ; x coord.
       sub e               ; subtract x.
       jr nc,colc1a        ; result is positive.
       neg                 ; make negative positive.
colc1a cp 16               ; within x range?
       jr nc,sktyp1        ; no - they've missed.
       ld c,a              ; store difference.
       ld a,(ix+Y)         ; y coord.
       sub d               ; subtract y.
       jr nc,colc1b        ; result is positive.
       neg                 ; make negative positive.
colc1b cp 16               ; within y range?
       jr nc,sktyp1        ; no - they've missed.
       add a,c             ; add x difference.
       cp 26               ; only 5 corner pixels touching?
       ret c               ; carry set if there's a collision.
       jp sktyp1           ; try next sprite in table.

colty1 push ix             ; base sprite address onto stack.
       pop de              ; pop it into de.
       ex de,hl            ; flip hl into de.
       sbc hl,de           ; compare the two.
       ex de,hl            ; restore hl.
       jr z,sktyp1         ; addresses are identical.
       jp colty0

; Display number.

disply ld bc,displ0        ; display workspace.
       call num2ch         ; convert accumulator to string.
displ1 dec bc              ; back one character.
       ld a,(bc)           ; fetch digit.
       or 128              ; insert end marker.
       ld (bc),a           ; new value.
       ld hl,displ0        ; display space.
       jp dmsg3            ; display the string.
displ0 defb 0,0,0,13+128


; Initialise screen.

initsc ld a,(roomtb)       ; whereabouts in the map are we?
       call tstsc          ; find displacement.
       cp 255              ; is it valid?
       ret z               ; no, it's rubbish.
       ld (scno),a         ; store new room number.
       ret

; Test screen.

tstsc  ld hl,mapdat-MAPWID ; start of map data, subtract width for negative.
       ld b,a              ; store room in b for now.
       add a,MAPWID        ; add width in case we're negative.
       ld e,a              ; screen into e.
       ld d,0              ; zeroise d.
       add hl,de           ; add displacement to map data.
       ld a,(hl)           ; find room number there.
       ret

; Screen left.

scrl   ld a,(roomtb)       ; present room table pointer.
       dec a               ; room left.
scrl0  call tstsc          ; test screen.
       inc a               ; is there a screen this way?
       ret z               ; no, return to loop.
       ld a,b              ; restore room displacement.
       ld (roomtb),a       ; new room table position.
scrl1  call initsc         ; set new screen.
       ld hl,restfl        ; restart screen flag.
       ld (hl),2           ; set it.
       ret
scrr   ld a,(roomtb)       ; room table pointer.
       inc a               ; room right.
       jr scrl0
scru   ld a,(roomtb)       ; room table pointer.
       sub MAPWID          ; room up.
       jr scrl0
scrd   ld a,(roomtb)       ; room table pointer.
       add a,MAPWID        ; room down.
       jr scrl0

; Jump to new screen.

nwscr  ld hl,mapdat        ; start of map data.
       ld bc,256*80        ; zero room count, 80 to search.
nwscr0 cp (hl)             ; have we found a match for screen?
       jr z,nwscr1         ; yes, set new point in map.
       inc hl              ; next room.
       inc c               ; count rooms.
       djnz nwscr0         ; keep looking.
       ret
nwscr1 ld a,c              ; room displacement.
       ld (roomtb),a       ; set the map position.
       jr scrl1            ; draw new room.


; Gravity processing.

grav   ld a,(ix+13)        ; in-air flag.
       and a               ; are we in the air?
       ret z               ; no we are not.
       inc a               ; increment it.
       jp z,ogrv           ; set to 255, use old gravity.
       ld (ix+13),a        ; write new setting.
       rra                 ; every other frame.
       jr nc,grav0         ; don't apply gravity this time.
       ld a,(ix+14)        ; pixels to move.
       cp 16               ; reached maximum?
       jr z,grav0          ; yes, continue.
       inc (ix+14)         ; slow down ascent/speed up fall.
grav0  ld a,(ix+14)        ; get distance to move.
       sra a               ; divide by 2.
       and a               ; any movement required?
       ret z               ; no, not this time.
       cp 128              ; is it up or down?
       jr nc,gravu         ; it's up.
gravd  ld b,a              ; set pixels to move.
gravd0 call cangd          ; can we go down?
       jr nz,gravst        ; can't move down, so stop.
       inc (ix+8)          ; adjust new x coord.
       djnz gravd0
       ret
gravu  neg                 ; flip the sign so it's positive.
       ld b,a              ; set pixels to move.
gravu0 call cangu          ; can we go up?
       jp nz,ifalls        ; can't move up, go down next.
       dec (ix+8)          ; adjust new x coord.
       djnz gravu0
       ret
gravst ld a,(ix+14)        ; jump pointer high.
       ld (ix+13),0        ; reset falling flag.
       ld (ix+14),0        ; store new speed.
       cp 8                ; was speed the maximum?
evftf  jp z,evnt15         ; yes, fallen too far.
       ret

; Old gravity processing for compatibility with 4.6 and 4.7.

ogrv   ld e,(ix+14)        ; get index to table.
       ld d,0              ; no high byte.
       ld hl,jtab          ; jump table.
       add hl,de           ; hl points to jump value.
       ld a,(hl)           ; pixels to move.
       cp 99               ; reached the end?
       jr nz,ogrv0         ; no, continue.
       dec hl              ; go back to previous value.
       ld a,(hl)           ; fetch that from table.
       jr ogrv1
ogrv0  inc (ix+14)         ; point to next table entry.
ogrv1  and a               ; any movement required?
       ret z               ; no, not this time.
       cp 128              ; is it up or down?
       jr nc,ogrvu         ; it's up.
ogrvd  ld b,a              ; set pixels to move.
ogrvd0 call cangd          ; can we go down?
       jr nz,ogrvst        ; can't move down, so stop.
       inc (ix+8)          ; adjust new x coord.
       djnz ogrvd0
       ret
ogrvu  neg                 ; flip the sign so it's positive.
       ld b,a              ; set pixels to move.
ogrvu0 call cangu          ; can we go up?
       jr nz,ogrv2         ; can't move up, go down next.
       dec (ix+8)          ; adjust new x coord.
       djnz ogrvu0
       ret
ogrvst ld e,(ix+14)        ; get index to table.
       ld d,0              ; no high byte.
       ld hl,jtab          ; jump table.
       add hl,de           ; hl points to jump value.
       ld a,(hl)           ; fetch byte from table.
       cp 99               ; is it the end marker?
       ld (ix+13),0        ; reset jump flag.
       ld (ix+14),0        ; reset pointer.
       jp evftf
ogrv2  ld hl,jtab          ; jump table.
       ld b,0              ; offset into table.
ogrv4  ld a,(hl)           ; fetch table byte.
       cp 100              ; hit end or downward move?
       jr c,ogrv3          ; yes.
       inc hl              ; next byte of table.
       inc b               ; next offset.
       jr ogrv4            ; keep going until we find crest/end of table.
ogrv3  ld (ix+14),b        ; set next table offset.
       ret

; Initiate fall check.

ifall  ld a,(ix+13)        ; jump pointer flag.
       and a               ; are we in the air?
       ret nz              ; if set, we're already in the air.
       ld h,(ix+9)         ; y coordinate.
       ld a,SPR_HGT        ; look down 16 pixels.
       add a,(ix+8)        ; add x coordinate.
       ld l,a              ; coords in hl.
       ld (dispx),hl       ; set up test coordinates.
       call tstbl          ; get map address.
       call plchk          ; block, platform check.
       ret nz              ; it's solid, don't fall.
       inc hl              ; look right one cell.
       call plchk          ; block, platform check.
       ret nz              ; it's solid, don't fall.
       ld a,(dispy)        ; y coordinate.
       and 7               ; position straddling block cells.
       jr z,ifalls         ; no more checks needed.
       inc hl              ; look to third cell.
       call plchk          ; block, platform check.
       ret nz              ; it's solid, don't fall.
ifalls inc (ix+13)         ; set in air flag.
       ld (ix+14),0        ; initial speed = 0.
       ret
tfall  ld a,(ix+13)        ; jump pointer flag.
       and a               ; are we in the air?
       ret nz              ; if set, we're already in the air.
       call ifall          ; do fall test.
       ld a,(ix+13)        ; get falling flag.
       and a               ; is it set?
       ret z               ; no.
       ld (ix+13),255      ; we're using the table.
       jr ogrv2            ; find position in table.


; Get frame data for a particular sprite.

gfrm   rlca                ; multiple of 2.
       ld e,a              ; copy to de.
       ld d,0              ; no high byte as max sprite is 128.
       ld hl,(frmptr)      ; frames used by game.
       add hl,de           ; point to frame start.
       ret

; Find sprite list for current room.

sprlst ld a,(scno)         ; screen number.
sprls2 ld hl,(nmeptr)      ; pointer to enemies.
       ld b,a              ; loop counter in b register.
       and a               ; is it the first screen?
       ret z               ; yes, don't need to search data.
       ld de,NMESIZ        ; bytes to skip.
sprls1 ld a,(hl)           ; fetch type of sprite.
       inc a               ; is it an end marker?
       jr z,sprls0         ; yes, end of this room.
       add hl,de           ; point to next sprite in list.
       jr sprls1           ; continue until end of room.
sprls0 inc hl              ; point to start of next screen.
       djnz sprls1         ; continue until room found.
       ret


; Clear all but a single player sprite.

nspr   ld b,NUMSPR         ; sprite slots in table.
       ld ix,sprtab        ; sprite table.
       ld de,TABSIZ        ; distance to next odd/even entry.
nspr0  ld a,(ix+0)         ; fetch sprite type.
       and a               ; is it a player?
       jr z,nspr1          ; yes, keep this one.
       ld (ix+0),255       ; delete sprite.
       ld (ix+5),255       ; remove next type.
       add ix,de           ; next sprite.
       djnz nspr0          ; one less space in the table.
       ret
nspr1  ld (ix+0),255       ; delete sprite.
       add ix,de           ; point to next sprite.
       djnz nspr2          ; one less to do.
       ret
nspr2  ld (ix+0),255       ; delete sprite.
       ld (ix+5),255       ; remove next type.
       add ix,de           ; next sprite.
       djnz nspr2          ; one less space in the table.
       ret


; Two initialisation routines.
; Initialise sprites - copy everything from list to table.

ispr   ld b,NUMSPR         ; sprite slots in table.
       ld ix,sprtab        ; sprite table.
ispr2  ld a,(hl)           ; fetch byte.
       cp 255              ; is it an end marker?
       ret z               ; yes, no more to do.
ispr1  ld a,(ix+0)         ; fetch sprite type.
       cp 255              ; is it enabled yet?
       jr nz,ispr4         ; yes, try another slot.
       ld a,(ix+5)         ; next type.
       cp 255              ; is it enabled yet?
       jr z,ispr3          ; no, process this one.
ispr4  ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       djnz ispr1          ; repeat for remaining sprites.
       ret                 ; no more room in table.
ispr3  call cpsp           ; initialise a sprite.
       djnz ispr2          ; one less space in the table.
       ret

; Initialise sprites - but not player, we're keeping the old one.

kspr   ld b,NUMSPR         ; sprite slots in table.
       ld ix,sprtab        ; sprite table.
kspr2  ld a,(hl)           ; fetch byte.
       cp 255              ; is it an end marker?
       ret z               ; yes, no more to do.
       and a               ; is it a player sprite?
       jr nz,kspr1         ; no, add to table as normal.
       ld de,NMESIZ        ; distance to next item in list.
       add hl,de           ; point to next one.
       jr kspr2
kspr1  ld a,(ix+0)         ; fetch sprite type.
       cp 255              ; is it enabled yet?
       jr nz,kspr4         ; yes, try another slot.
       ld a,(ix+5)         ; next type.
       cp 255              ; is it enabled yet?
       jr z,kspr3          ; no, process this one.
kspr4  ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       djnz kspr1          ; repeat for remaining sprites.
       ret                 ; no more room in table.
kspr3  call cpsp           ; copy sprite to table.
       djnz kspr2          ; one less space in the table.
       ret

; Copy sprite from list to table.

cpsp   ld a,(hl)           ; fetch byte from table.
       ld (ix+0),a         ; set up type.
       ld (ix+PAM1ST),a    ; set up type.
       inc hl              ; move to next byte.
       ld a,(hl)           ; fetch byte from table.
       ld (ix+6),a         ; set up image.
       inc hl              ; move to next byte.
       ld a,(hl)           ; fetch byte from table.
       ld (ix+3),200       ; set initial coordinate off screen.
       ld (ix+8),a         ; set up coordinate.
       inc hl              ; move to next byte.
       ld a,(hl)           ; fetch byte from table.
       ld (ix+9),a         ; set up coordinate.
       inc hl              ; move to next byte.
       xor a               ; zeroes in accumulator.
       ld (ix+7),a         ; reset frame number.
       ld (ix+10),a        ; reset direction.
;       ld (ix+12),a        ; reset parameter B.
       ld (ix+13),a        ; reset jump pointer low.
       ld (ix+14),a        ; reset jump pointer high.
       ld (ix+16),255      ; reset data pointer to auto-restore.
       push ix             ; store ix pair.
       push hl             ; store hl pair.
       push bc
evis0  call evnt09         ; perform event.
       pop bc
       pop hl              ; restore hl.
       pop ix              ; restore ix.
       ld de,TABSIZ        ; distance to next odd/even entry.
       add ix,de           ; next sprite.
       ret

; Clear the play area window.

clw    ld hl,(wintop)      ; get coordinates of window.
       ld (dispx),hl       ; put into dispx for calculation.
       ld a,(winhgt)       ; height of window.
       ld b,a              ; copy to b register.
clw3   push bc             ; store lines on stack.
       ld a,(winwid)       ; width of window.
clw2   ex af,af'           ; store column counter.
       call gprad          ; get print address.
       xor a               ; zero byute to write.
       ld b,8              ; pixel height of each cell.
clw1   ld (de),a           ; copy to screen.
       inc d               ; next screen row down.
       djnz clw1
       call gaadd          ; get attribute address.
       ld a,(acolor+1)     ; get colour.
       ld (hl),a           ; write colour.
       ld hl,dispy         ; column position.
       inc (hl)            ; next column.
       ex af,af'           ; restore column counter.
       dec a               ; one less to do.
       jr nz,clw2          ; repeat for remaining columns.
       ld a,(winlft)       ; get left edge.
       ld (dispy),a        ; reset y.
       ld hl,dispx         ; line.
       inc (hl)            ; next line down.
       pop bc              ; restore line counter.
       djnz clw3           ; repeat down the screen.
       ld hl,(wintop)      ; get coordinates of window.
       ld (charx),hl       ; put into display position.
       ret

; Effects code.
; Ticker routine is called 25 times per second.

scrly  ret
       defw txtscr         ; get screen address.
       ld b,8              ; 8 pixel rows.
       push hl             ; store screen address.
scrly1 push bc             ; store rows on stack.
       push hl
       ld a,(txtwid)       ; characters wide.
       ld b,a              ; put into the loop counter.
       and a               ; reset carry flag.
scrly0 rl (hl)             ; rotate left.
       dec l               ; char left.
       djnz scrly0         ; repeat for width of ticker message.
       pop hl
       inc h               ; next row down.
       pop bc              ; retrieve row counter from stack.
       djnz scrly1         ; repeat for all rows.
       ld hl,(txtpos)      ; get text pointer.
       ld a,(hl)           ; find character we're displaying.
       and 127             ; remove end marker bit if applicable.
       cp 13               ; is it newline?
       jr nz,scrly5        ; no, it's okay.
       ld a,32             ; convert to a space instead.
scrly5 rlca
       rlca
       rlca                ; multiply by 8 to find char.
       ld b,a              ; store shift in b.
       and 3               ; keep within 768-byte range of font.
       ld d,a              ; that's our high byte.
       ld a,b              ; restore the shift.
       and 248
       ld e,a
       ld hl,(fontadr+1)   ; font address.
       add hl,de           ; point to image of character.
       ex de,hl            ; need the address in de.
       pop hl

       ld a,(txtbit)
       ld c,a
       ld b,8
scrly3 ld a,(de)           ; get image of char line.
       and c               ; test relevant bit of char.
       jr z,scrly2         ; not set - skip.
       inc (hl)            ; set bit.
scrly2 inc h               ; next line of window.
       inc de              ; next line of char.
       djnz scrly3
       ld hl,txtbit        ; bit of text to display.
       rrc (hl)            ; next bit of char to use.
       ret nc              ; not reached end of character yet.
       ld hl,(txtpos)      ; text pointer.
       ld a,(hl)           ; what was the character?
       inc hl              ; next character in message.
       rla                 ; end of message?
;       ret nc              ; not yet, exit here.
;       ld a,201            ; code for ret.
;       ld (scrly),a        ; disable scrolling routine.
       jr nc,scrly6        ; not yet - continue.
scrly4 ld hl,(txtini)      ; start of scrolling message.
scrly6 ld (txtpos),hl      ; new text pointer position.
       ret

iscrly call prescr         ; set up display position.
       ld hl,msgdat        ; text messages.
       ld a,b              ; width.
       dec a               ; subtract one.
       cp 32               ; is it between 1 and 32?
       jr nc,iscrl0        ; no, disable messages.
       ld a,c              ; message number.
       ld d,b              ; copy width to d.
       call getwrd         ; find message start.
       ld b,d              ; restore width to b register.
       ld (txtini),hl      ; set initial text position.
       ld a,42             ; code for ld hl,(nn).
iscrl0 ld (scrly),a        ; enable/disable scrolling routine.
       call prescr         ; set up display position.
       call gprad          ; get print address.
       ld l,b              ; width in b so copy to hl.
       ld h,0              ; no high byte.
       dec hl              ; width minus one.
       add hl,de           ; add width.
       ld (txtscr),hl      ; set text screen address.
       ld a,b              ; width.
       ld (txtwid),a       ; set width in working storage.
       ld hl,txtbit        ; bit of text to display.
       ld (hl),128         ; start with leftmost bit.
       jr scrly4

iclock ld d,a
       ld e,60
       call idiv		   ; d = d/e, remainder in a. */
       push af
       ld a,d
       call disply
       ld hl,chary
       inc (hl)
       pop af
       ld bc,displ0
       call num2dd
       jp displ1

border or a
       jr z,setbr1
       rra
       jr nc,setbrd
       set 2,a
setbrd or 0c0h
setbr1 out (81h),a
       ret

ipaper and 07h             ; convert speccy colour
       rla                 ; multiply by 8 to get paper.
       rla
       rla
       ld c,a              ; paper colour in c register.
       ld a,(colcsp+1)     ; permanent attributes.
       and 0c7h            ; retain ink.
       jr gtcol

iink
       and 07h             ; convert speccy colour
       ld c,a
colcsp ld a,00h            ; permanent attributes.
       and 0f8h            ; retain paper.
gtcol  or c                ; merge in new ink.
icolour
       ld (colcsp+1),a     ; set permanent attributes.
       ld l,a
       ld h,high coltabl
       ld a,(hl)
       ld (acolor+1),a     
       ret

ispink and 7               ; convert speccy colour */
       or 40h
       ld l,a              ; set permanent attributes.
       ld h,high coltabl
       ld c,(hl)
       jp cspr

       defs     low -$
coltabl db      000h,00ch,009h,00dh,00ah,00eh,00bh,00fh
        db      0c0h,0cch,0c9h,0cdh,0cah,0ceh,0cbh,0cfh
        db      090h,09ch,099h,09dh,09ah,09eh,09bh,09fh
        db      0d0h,0dch,0d9h,0ddh,0dah,0deh,0dbh,0dfh
        db      0a0h,0ach,0a9h,0adh,0aah,0aeh,0abh,0afh
        db      0e0h,0ech,0e9h,0edh,0eah,0eeh,0ebh,0efh
        db      0b0h,0bch,0b9h,0bdh,0bah,0beh,0bbh,0bfh
        db      0f0h,0fch,0f9h,0fdh,0fah,0feh,0fbh,0ffh
        db      000h,004h,001h,005h,002h,006h,003h,007h
        db      040h,044h,041h,045h,042h,046h,043h,047h
        db      010h,014h,011h,015h,012h,016h,013h,017h
        db      050h,054h,051h,055h,052h,056h,053h,057h
        db      020h,024h,021h,025h,022h,026h,023h,027h
        db      060h,064h,061h,065h,062h,066h,063h,067h
        db      030h,034h,031h,035h,032h,036h,033h,037h
        db      070h,074h,071h,075h,072h,076h,073h,077h
        db      000h,0c0h,090h,0d0h,0a0h,0e0h,0b0h,0f0h
        db      00ch,0cch,09ch,0dch,0ach,0ech,0bch,0fch
        db      009h,0c9h,099h,0d9h,0a9h,0e9h,0b9h,0f9h
        db      00dh,0cdh,09dh,0ddh,0adh,0edh,0bdh,0fdh
        db      00ah,0cah,09ah,0dah,0aah,0eah,0bah,0fah
        db      00eh,0ceh,09eh,0deh,0aeh,0eeh,0beh,0feh
        db      00bh,0cbh,09bh,0dbh,0abh,0ebh,0bbh,0fbh
        db      00fh,0cfh,09fh,0dfh,0afh,0efh,0bfh,0ffh
        db      000h,040h,010h,050h,020h,060h,030h,070h
        db      004h,044h,014h,054h,024h,064h,034h,074h
        db      001h,041h,011h,051h,021h,061h,031h,071h
        db      005h,045h,015h,055h,025h,065h,035h,075h
        db      002h,042h,012h,052h,022h,062h,032h,072h
        db      006h,046h,016h,056h,026h,066h,036h,076h
        db      003h,043h,013h,053h,023h,063h,033h,073h
        db      007h,047h,017h,057h,027h,067h,037h,077h

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


sprtab equ $

       block NUMSPR * TABSIZ,255

;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
;       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
ssprit defb 255,255,255,255,255,255,255,0,192,120,0,0,0,255,255,255,255

roomtb defb 34                     ; room number.

; Everything below here will be generated by the editors.

; Sounds.

fx1    defb 128+15         ; volume and mixer.
       defb 31             ; white noise.
       defw 1000           ; tone register.
       defb 128+15         ; volume and mixer.
       defb 25             ; white noise.
       defw 1000           ; tone register.
       defb 128+14         ; volume and mixer.
       defb 19             ; white noise.
       defw 1000           ; tone register.
       defb 128+13         ; volume and mixer.
       defb 13             ; white noise.
       defw 1000           ; tone register.
       defb 128+12         ; volume and mixer.
       defb 7              ; white noise.
       defw 1000           ; tone register.
       defb 128+11         ; volume and mixer.
       defb 0              ; white noise.
       defw 1000           ; tone register.
       defb 128+10         ; volume and mixer.
       defb 6              ; white noise.
       defw 1000           ; tone register.
       defb 128+8          ; volume and mixer.
       defb 12             ; white noise.
       defw 1000           ; tone register.
       defb 128+6          ; volume and mixer.
       defb 18             ; white noise.
       defw 1000           ; tone register.
       defb 128+3          ; volume and mixer.
       defb 24             ; white noise.
       defw 1000           ; tone register.
       defb 255

fx2    defb 064+15         ; volume and mixer.
       defb 27             ; white noise.
       defw 1000           ; tone register.
       defb 064+14         ; volume and mixer.
       defb 31             ; white noise.
       defw 2000           ; tone register.
       defb 064+13         ; volume and mixer.
       defb 28             ; white noise.
       defw 3000           ; tone register.
       defb 064+12         ; volume and mixer.
       defb 31             ; white noise.
       defw 2000           ; tone register.
       defb 064+11         ; volume and mixer.
       defb 29             ; white noise.
       defw 1000           ; tone register.
       defb 064+10         ; volume and mixer.
       defb 31             ; white noise.
       defw 2000           ; tone register.
       defb 064+9          ; volume and mixer.
       defb 30             ; white noise.
       defw 3000           ; tone register.
       defb 064+8          ; volume and mixer.
       defb 31             ; white noise.
       defw 2000           ; tone register.
       defb 064+7          ; volume and mixer.
       defb 31             ; white noise.
       defw 1000           ; tone register.
       defb 064+6          ; volume and mixer.
       defb 31             ; white noise.
       defw 2000           ; tone register.
       defb 255

fx3    defb 064+15         ; volume and mixer.
       defb 0              ; white noise.
       defw 4000           ; tone register.
       defb 064+15         ; volume and mixer.
       defb 0              ; white noise.
       defw 4100           ; tone register.
       defb 064+14         ; volume and mixer.
       defb 0              ; white noise.
       defw 4200           ; tone register.
       defb 064+14         ; volume and mixer.
       defb 0              ; white noise.
       defw 4300           ; tone register.
       defb 064+13         ; volume and mixer.
       defb 0              ; white noise.
       defw 4400           ; tone register.
       defb 064+13         ; volume and mixer.
       defb 0              ; white noise.
       defw 4500           ; tone register.
       defb 064+12         ; volume and mixer.
       defb 0              ; white noise.
       defw 4600           ; tone register.
       defb 064+12         ; volume and mixer.
       defb 0              ; white noise.
       defw 4700           ; tone register.
       defb 064+11         ; volume and mixer.
       defb 0              ; white noise.
       defw 4800           ; tone register.
       defb 064+10         ; volume and mixer.
       defb 0              ; white noise.
       defw 4900           ; tone register.
       defb 255

       defb 99             ; temporary marker.

; User routine.  Put your own code in here to be called with USER instruction.
; if USER has an argument it will be passed in the accumulator.

user   ret

; Game-specific data and events code generated by the compiler ------------------

        defs    low -$
initEP
        ld      bc,100h+28      ;set bias d
        ld      d,18h*8h        ;56,120,248
        exos    16
        ld      bc,100h+27      ;set border d
        ld      d,00h
        exos    16
        ld      bc,000h+14      ;read internal speaker status
    if pflag=1
        exos    16
        xor     a
        inc     d
        dec     d               ;=0 Internal speaker active. 
        jr      z,speakon
        ld      a,80h
speakon ld      (speakrv+1),a
    endif
;        in      a,(0b0h)        ;check EP64
;        cp      0fch
;        jr      nz,reqvid
;        ld      a,0ffh
;        di
;        jr      ep64
        ld      hl,vidsg
        ld      a,"A"
        cpi
        jr      nz,reqvid
        ld      a,(hl)
        cp      0fch
        jr      c,reqvid
        out     (0b3h),a
        jp      skiplpt
reqvid  call    vidreq
        di
        out     (0b3h),a        ;video page 1 and lpt
        ld      hl,scraddr
        ld      de,scraddr+1
        ld      bc,1affh
        ld      (hl),l
        ldir
        and     03h
        push    af              ;value for set LPT registers
        rrca
        rrca
        push    af              ;screen address high
        ld      (vlpb+5),a
        add     a,((high lptaddr) and 3fh)+high (low lptaddr + (screeny+9)*10h)
        ld      (vsyncep+15h),a
;        inc     a
        ld      (vsyncep+25h),a
        ld      hl,vlpb
        ld      de,lptaddr
        ld      c,10h
        push    de
        ldir
        pop     hl
        ld      bc,(24*8-1)*10h
        ldir
        ld      hl,vsyncep
        ld      bc,syncln
        ldir
        pop     af
        or      ((high scraddr) and 3fh)
        ld      h,a
        ld      l,00h
        ld      ix,lptaddr+04h
        ld      c,03h
fillfl
flthird ld      b,08h
        ld      a,h
        and     0e0h
        add     a,18h
        ld      d,a
        ld      a,h
        and     18h
        rrca
        rrca
        rrca
        or      d
        ld      de,0010h
fil1chr ld      (ix+2),l
        ld      (ix+3),h
        ld      (ix+0),l
        ld      (ix+1),a
        add     ix,de
        inc     h
        djnz    fil1chr
        dec     h
        ld      a,h
        and     0f8h
        ld      h,a
        ld      a,l
        add     a,20h
        ld      l,a
        jr      nz,flthird
        ld      a,h
        add     a,08h
        ld      h,a
        dec     c
        jr      nz,fillfl
        pop     af
        rlca
        rlca
        or      0c0h or (((high lptaddr) and 30h)/10h)
        ld      b,a
        xor     a
        out     (82h),a
        ld      a,b
        out     (83h),a
skiplpt di
        ld      a,0c3h
        ld      hl,intrut
        ld      (0038h),a
        ld      (0039h),hl
        call    ayReset
        ei
        ld      hl,copychrx
        ld      de,MAP+100h
        push    de
        ld      bc,cpychln
        ldir
        ld      a,10h
        out     (0a7h),a
        ret

copychrx
        phase   MAP+100h
        in      a,(0b2h)
        ex      af,af'
        ld      a,0ffh
        out     (0b2h),a
        ld      hl,(0bff4h)
        ld      a,l
        add     a,06h
        ld      l,a
        ld      a,(hl)
        inc     l
        ld      l,(hl)
        srl     l
        rra
        rr      l
        ld      h,a
        res     6,h
        set     5,l
        ld      de,SCADTB
        ld      a,60h
copychr push    hl
        ld      bc,0080h
        ldi
        add     hl,bc
        inc     c
        cp      60h-40h
        jr      nc,nolow1
        add     hl,bc
        ldi
        add     hl,bc
        inc     c
        jr      lower
nolow1  ldi
        add     hl,bc
        inc     c
        add     hl,bc
lower   ldi
        add     hl,bc
        inc     c
        ldi
        add     hl,bc
        inc     c
        ldi
        add     hl,bc
        inc     c
        ldi
        add     hl,bc
        inc     c
        ldi
        add     hl,bc
        inc     c
        ldi
        pop     hl
        inc     hl
        dec     a
        jr      nz,copychr
        ld      hl,SCADTB
        ld      de,initEP
        ld      bc,0300h
        ex      af,af'
        out     (0b2h),a
        ret
        dephase
cpychln equ     $-copychrx
; -----------------------------------------------------------------------------
; reset AY-3-8912 emulation

ayReset:
;        di
        ld    hl, ayRegisters - 1
        ld    bc, 10afh
        xor   a
.l1:    inc   hl
        out   (c), a
        ld    (hl), a
        dec   c
        djnz  .l1
        res   3, l                      ; register 7
        ld    (hl), 3fh
    if NO_ENVELOPE_IRQ == 0
        ld    (envelopeInterrupt.l4 + 1), a
        ld    a, 18h                    ; = JR +nn
        ld    (envelopeInterrupt.l2), a
        ld    hl, MIN_ENV_FREQVAL
        ld    (envelopeInterrupt.l3 + 1), hl
        ld    a, low (envelopeInterrupt.l12 - envelopeInterrupt.l11)
        ld    (envelopeInterrupt.l10 + 1), a
        ld    a, low envelopeEnableTable
        ld    (setChannelAmplitude.l3 + 1), a
    endif
        ld    a, 04h
        out   (0bfh), a
        ld    c, b
        call  .l2
        ld    l, b
        call  .l2                       ; L = 1 kHz interrupts per video frame
        ld    a, 25
        cp    l
        ld    a, 03h
        rla
        rla
        out   (0bfh), a                 ; Z80 <= 5 MHz: 04h, > 5 MHz: 06h
        ld    a, 10h                    ; use 17-bit noise generator
        out   (0a6h), a
    if NO_ENVELOPE_IRQ == 0
        ld    a, 33h
    else
        ld    a, 30h
    endif
        out   (0b4h), a                 ; enable 1 kHz and video interrupts
        ret
.l2:    in    a, (0b4h)
        and   11h
        or    c
        rlca
        and   66h
        ld    c, a                      ; -ON--ON-
        rlca                            ; ON--ON--
        xor   c                         ; OXN-OXN-
        bit   2, a
        jr    z, .l3
        inc   l                         ; 1 kHz interrupt
.l3:    cp    0c0h
        jr    c, .l2                    ; not 50 Hz interrupt ?
        ret

;reqpage exos    24
;        jp      nz,reset
;        ld      a,c
;        ret

vidreq  ld      hl,endprg1
        ld      c,00h
nxtseg  ld      (hl),c
        inc     hl
        exos    24
        jr      z,contreq
        cp      7fh
        jp      nz,reset
contreq ld      a,c
        cp      0fch
        jr      c,nxtseg
        push    af
givebck dec     hl
        ld      c,(hl)
        exos    25
        jr      z,givebck
        pop     af
        ret

vlpb    db      0ffh,14h,0fh,2fh,00h,00h,00h,00h    ;               192
        db      00h,19h,92h,0dbh,24h,6dh,0b6h,0ffh
vsyncep db      0feh,9eh,3fh,20h,00h,00h,00h,00h    ;               2   192+120
        db      040h,40h,51h,50h,61h,60h,70h,70h
        db      0f8h,1eh,1ah,24h,ept,00h,00h,00h    ;lores 2 ep txt  8
        db      00h,0ffh,00h,00h,00h,00h,00h,00h
        db      0feh,42h,1ah,24h,epl,00h,00h,00h    ;ep line         2
        db      00h,0ffh,49h,0d9h,0dbh,0a2h,0a6h,5dh
        db      0d8h,02h,3fh,00h,00h,00h,00h,00h    ;sync           40
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      0fdh,00h,3fh,00h,00h,00h,00h,00h    ;               3
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      0feh,00h,06h,3fh,00h,00h,00h,00h    ;               2
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      0ffh,00h,3fh,20h,00h,00h,00h,00h    ;               1
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      0eah,02h,06h,3fh,06h,00h,00h,00h    ;               22
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      0d8h,03h,3fh,00h,00h,00h,00h,00h    ;               40
        db      000h,00h,00h,00h,00h,00h,00h,00h
        db      110,99,53,155,155,27,27,14,26,110    ;ep text
        db      34,18,36,136,136,136,136,132,34,34
        db      32,34,4,8,8,136,136,132,32,32
        db      44,42,4,11,11,11,11,4,28,44
        db      32,34,4,8,10,8,10,4,2,32
        db      34,36,4,8,137,8,9,4,34,34
        db      110,99,14,27,153,156,25,142,44,110
        db      0,0,0,0,0,0,0,0,0,0
        db      0ch,0ch,0ch,44h,0cch,0cch,88h,30h,30h,30h    ;line
        db      50h,0f0h,0f0h,0a0h,3ch,3ch,3ch,54h,0fch,0fch
syncln  equ     $-vsyncep
initEPl equ     $-initEP
endprg1 defs    100h
eop

fillen  equ $-startpr
