; Game engine code --------------------------------------------------------------

; Arcade Game Designer.
; (C) 2008 - 2018 Jonathan Cauldwell.
; ZX Spectrum Engine v0.7.

; Global definitions.

SIMASK equ 248             ; SPRITEINK mask - allows users to set BRIGHT/FLASH/CLUT as well.
SHRAPN equ 63926           ; shrapnel table, just below screen address table.
SCADTB equ 64256           ; screen address table, just below map.
MAP    equ 64768           ; properties map buffer.
loopa  equ 23681           ; loop counter system variable.
loopb  equ 23728           ; loop counter system variable.
loopc  equ 23729           ; loop counter system variable.

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

NUMSPR equ 12              ; number of sprites.
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

       org 32000
start  equ $

; Set up the font.

       ld hl,font-256      ; address of font.
       ld (23606),hl       ; set up game font.

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
       ld hl,(23606)       ; font.
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
       ld a,(23693)        ; current colour.
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
       ld a,(23693)        ; current colour.
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
       and 28              ; anything pressed?
       jr z,dbox12         ; no, nothing.
       and 16              ; fire button pressed?
mod1   jp nz,fstd          ; yes, job done.
       call dbar           ; delete bar.
       ld a,(joyval)       ; joystick reading.
       and 8               ; going up?
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

prskey call debkey         ; debounce key.
prsky0 call vsync          ; vertical synch.
       call 654            ; return keyboard state in e.
       inc e               ; is it 255?
       jr z,prsky0         ; yes, repeat until key pressed.

; Debounce keypress.

debkey call vsync          ; update scrolling, sounds etc.
       call 654            ; d=shift, e=key.
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
       ld b,a              ; outer loop.
       ld a,(23624)        ; border colour.
       rra                 ; put border bits into d0, d1 and d2.
       rra
       rra
       ld c,a              ; first value to write to speaker.
       ld a,b              ; sound.
       and a               ; test it.
       jp m,vsync6         ; play white noise.
vsync2 ld a,c              ; get speaker value.
       out (254),a         ; write to speaker.
       xor 248             ; toggle all except the border bits.
       ld c,a              ; store value for next time.
       ld d,b              ; store loop counter.
vsync3 ld hl,clock         ; previous clock setting.
       ld a,(23672)        ; current clock setting.
       cp (hl)             ; subtract last reading.
       jp nz,vsync4        ; yes, no more processing please.
       djnz vsync3         ; loop.
       ld b,d              ; restore loop counter.
       djnz vsync2         ; continue noise.
vsync4 ld a,d              ; where we got to.
vsynca ld (sndtyp),a       ; remember for next time.
vsync1 ld a,(23672)        ; clock low.
       rra                 ; rotate bit into carry.
       call c,vsync5       ; time to play sound and do shrapnel/ticker stuff.
       ld hl,clock         ; last clock reading.
vsync0 ld a,(23672)        ; current clock reading.
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
       and 248             ; only retain the speaker/earphone bits.
       or c                ; merge with border colour.
       out (254),a         ; write to speaker.
       ld a,(23672)        ; current clock setting.
       cp (hl)             ; subtract last reading.
       jp nz,vsync8        ; yes, no more processing please.
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
       pop ix              ; retrieve sprite pointer.
       ret

; Clear screen routine.

cls    ld hl,16384         ; screen address.
       ld (hl),l           ; blank first byte.
       ld de,16385         ; second byte.
       ld bc,6144          ; bytes to copy.
       ldir                ; blank them all.
       ld a,(23693)        ; fetch attributes.
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

setpal ld bc,48955         ; register select.
       ld a,64             ; mode select.
       out (c),a           ; set ULAplus mode.
       ld b,255            ; data write.
       ld a,1              ; mode on.
       out (c),a           ; switch on ULAplus.

       ld b,64             ; number of palette table entries to write.
setpa1 ld hl,palett        ; palette we want.
       ld e,0              ; register number.
setpa0 push bc             ; store counter.
       ld b,191            ; register select.
       ld a,e              ; register number to write.
       out (c),a           ; write to port.
       ld b,255            ; data select.
       ld a,(hl)           ; get colour data from table.
       out (c),a           ; write to port.
       inc e               ; next clut entry.
       inc hl              ; next table entry.
       pop bc              ; restore counter from stack.
       djnz setpa0         ; set rest of palette.
       ret

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
       add a,88            ; attributes start at 88*256=22528.
       ld h,a              ; that's our high byte sorted.
       ld a,l              ; vertical/64 - same as vertical*4.
       and 224             ; want a multiple of 32.
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
txtscr defw 16406

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

plot   ld l,(ix+3)         ; x integer.
       ld h,(ix+5)         ; y integer.
       ld (dispx),hl       ; workspace coordinates.
       ld a,(ix+0)         ; type.
       and a               ; is it a laser?
       jr z,plot1          ; yes, draw laser instead.
plot0  ld a,h              ; which pixel within byte do we
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
shoot1 add a,7             ; down 7 pixels.
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
vapou3 ld de,7*256+7       ; mid-point of sprite.
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
       jp c,star7          ; found one we can use.
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
       jp star0
star1  call qrand          ; get quick random number.
       ld (ix+3),a         ; set x coord.
       ld a,(wnrgtx)       ; get edge of screen.
       add a,15            ; add width of sprite minus 1.
       jp star9
star2  call qrand          ; get quick random number.
       ld (ix+3),a         ; set x coord.
       ld a,(wnlftx)       ; get edge of screen.
       jp star9
star3  ld a,(wnbotx)       ; get edge of screen.
       add a,15            ; height of sprite minus one pixel.
       jp star8


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
       cp 16               ; within range?
       jr c,lcol4          ; yes, collision occurred.
lcol2  pop hl              ; restore laser pointer from stack.
       jr lcol3
lcol4  pop hl              ; restore laser pointer.
       ret                 ; return with carry set for collision.

; Main game engine code starts here.

game   equ $

; Set up screen address table.

setsat ld hl,16384         ; start of screen.
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

       call setpal         ; set up ULAplus palette.
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
inipbl call initsc         ; set up first screen.
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
       ret
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

w8912  ld hl,snddat        ; start of AY-3-8912 register data.
       ld de,14*256        ; start with register 0, 14 to write.
       ld c,253            ; low byte of port to write.
w8912a ld b,255            ; port 65533=select soundchip register.
       out (c),e           ; tell chip which register we're writing.
       ld a,(hl)           ; value to write.
       ld b,191            ; port 49149=write value to register.
       out (c),a           ; this is what we're putting there.
       inc e               ; next sound chip register.
       inc hl              ; next byte to write.
       dec d               ; decrement loop counter.
       jp nz,w8912a        ; repeat until done.
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
       ld de,65500         ; minus 36.
       add hl,de           ; point to image.
dobj1  jp sprite           ; draw this sprite.

dobjc  call dobj           ; display object.
       ld c,(hl)           ; put ink in c register.

; Need to write attribute routine here.
; set up colour in c register first.

cobj   ld a,(hl)           ; get colour byte.
       and a               ; test it.
       ret m               ; colour not set.
       ld h,22             ; quarter of attrubte address.
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
       
       ld de,30            ; distance to next line down.
       ld a,(dispx)        ; x coordinate.
       ld b,3              ; default rows to write.
       and 7               ; does x straddle cells?
       jr nz,cobj0         ; yes, loop counter is good.
       dec b               ; one less row to write.
cobj0  ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
       inc l               ; next cell.
       ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
       inc l               ; next cell.
       ld a,(dispy)        ; y coordinate.
       and 7               ; straddling cells?
       jr z,cobj1          ; no, only 2 wide.
       ld a,(hl)           ; get attributes.
       and 248             ; remove ink.
       or c                ; put in the new ink.
       ld (hl),a           ; write back again.
cobj1  add hl,de           ; next row.
       djnz cobj0
       ret

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
       ld de,65501         ; minus graphic size.
       add hl,de           ; point to graphics.
       call dobj1          ; delete object sprite.
       ld a,(bcol)         ; first block colour.
       and 7               ; only want ink attribute.
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
       ld de,65501         ; minus graphic size.
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
score  defb '000000'       ; player's score.
hiscor defb '000000'       ; high score.
bonus  defb '000000'       ; bonus.
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
       ld a,(23693)        ; current cell colours.
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
       ld bc,6*256+48      ; 6 digits to add, ASCII '0' in c.
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
       add a,64            ; add 64 for start address of screen.
       ld d,a              ; that's our high byte.
       ld a,e              ; restore x coordinate.
       rrca                ; multiply by 32.
       rrca
       rrca
       and 224             ; lines within segment.
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
       add a,253           ; 88 * 256 = 64768, start of properties map.
       ld h,a              ; that's our high byte.
       ld a,l              ; restore shift result.
       and 224             ; only want low bits.
       ld l,a              ; put into low byte.
       ld a,(dispy)        ; fetch y coordinate.
       and 31              ; should be in range 0 - 31.
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
       add a,88            ; 88 * 256 = 22528, start of screen attributes.
       ld h,a              ; that's our high byte.
       ld a,l              ; restore shift result.
       and 224             ; only want low bits.
       ld l,a              ; put into low byte.
       ld a,(dispy)        ; fetch y coordinate.
       and 31              ; should be in range 0 - 31.
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

pattr  ld b,a              ; store cell in b register for now.
       ld e,a              ; displacement in e.
       ld d,0              ; no high byte.
       ld hl,(proptr)      ; pointer to properties.
       add hl,de           ; property cell address.
       ld c,(hl)           ; fetch byte.
       call pradd          ; get property buffer address.
       ld (hl),c           ; write property.
       ld a,b              ; restore cell.

; Print attributes, no properties.

panp   ld e,a              ; displacement in e.
       ld d,0              ; no high byte.
       ld hl,(colptr)      ; pointer to colours.
       add hl,de           ; colour cell address.
       ld c,(hl)           ; fetch byte.
       call gaadd          ; get attribute address.
       ld (hl),c           ; write colour.
       ld a,b              ; restore cell.

; Print character pixels, no more.

pchr   call pchar          ; show character in accumulator.
       ld hl,dispy         ; y coordinate.
       inc (hl)            ; move along one.
       ret

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
       call pattr          ; show attributes and block.
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
numsp5 add a,16            ; look down 16 pixels.
       ld l,a              ; coords in hl.
       jr laddv

; Ladder up check.

laddu  ld a,(ix+8)         ; x coordinate.
       and 254             ; make it even.
       ld (ix+8),a         ; reset it.
       ld h,(ix+9)         ; y coordinate.
numsp6 add a,14            ; look 2 pixels above feet.
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
numsp3 add a,16            ; look down 16 pixels.
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
cangh2 ld b,3              ; default rows to write.
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
       ld hl,(blkptr)      ; blocks.
       ld (grbase),hl      ; set graphics base.
       xor a               ; block zero.
       jp pattr            ; display block on screen.

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
       and 224             ; mask off high bits.
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


; Keyboard test routine.

ktest  ld c,a              ; key to test in c.
       and 7               ; mask bits d0-d2 for row.
       inc a               ; in range 1-8.
       ld b,a              ; place in b.
       srl c               ; divide c by 8
       srl c               ; to find position within row.
       srl c
       ld a,5              ; only 5 keys per row.
       sub c               ; subtract position.
       ld c,a              ; put in c.
       ld a,254            ; high byte of port to read.
ktest0 rrca                ; rotate into position.
       djnz ktest0         ; repeat until we've found relevant row.
       in a,(254)          ; read port (a=high, 254=low).
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
       jr joyjo1           ; store the value.

; Kempston joystick controls.

joyjoy ld bc,31            ; port for Kempston interface.
       in a,(c)            ; read it.
joyjo3 ld e,a              ; copy to e register.
       ld a,(keys+5)       ; key six.
       call ktest          ; being pressed?
       jr c,joyjo0         ; not pressed.
       set 5,e             ; set bit d5.
joyjo0 ld a,(keys+6)       ; key seven.
       call ktest          ; being pressed?
       jr c,joyjo1         ; not pressed.
       set 6,e             ; set bit d6.
joyjo1 ld a,e              ; copy e register to accumulator.
joyjo2 ld (joyval),a       ; remember value.
       ret

; Sinclair joystick controls.

joysin ld bc,61438         ; port for Sinclair 2.
       in a,(c)            ; read joystick.
       ld d,a              ; clear values.
       xor a               ; clear accumulator.
       ld e,16             ; Kempston fire bit value.
       bit 0,d             ; fire bit pressed?
       call z,joysi0       ; add bit.
       ld e,1              ; Kempston bit value.
       bit 3,d             ; fire bit pressed?
       call z,joysi0       ; add bit.
       ld e,2              ; Kempston bit value.
       bit 4,d             ; fire bit pressed?
       call z,joysi0       ; add bit.
       ld e,8              ; Kempston bit value.
       bit 1,d             ; fire bit pressed?
       call z,joysi0       ; add bit.
       ld e,4              ; Kempston bit value.
       bit 2,d             ; fire bit pressed?
       call z,joysi0       ; add bit.
       jr joyjo3           ; read last 2 keys a la Kempston.

joysi0 add a,e             ; add bit value.
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
       ld a,(23693)        ; current cell colours.
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
       ld hl,(23606)       ; address of font.
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
       ld a,(23693)        ; current colour.
       ld (hl),a           ; set attribute.
       ld c,a              ; copy colour to c.
       ld de,32            ; distance to next line.
       add hl,de           ; point to second cell.
       ld a,h              ; high byte of address.
       cp 91               ; past edge of screen?
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
       ld a,(23693)        ; current cell colours.
       ld (hl),a           ; write to attribute cell.
       call nexpos         ; display position.
       jp z,bchar3         ; next line down.
       jp bchar2           ; tidy up.

; Get next print column position.

nexpos ld hl,dispy         ; display position.
       ld a,(hl)           ; get coordinate.
       inc a               ; move along one position.
       and 31              ; reached edge of screen?
       ld (hl),a           ; set new position.
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

preprt ld de,(23606)       ; font pointer.
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

gspra0 rrca                ; multiply by 128.
       ld d,a              ; store in d.
       and 128             ; low byte bit.
       ld e,a              ; got low byte.
       ld a,d              ; restore result.
       and 127             ; high byte bits.
       ld d,a              ; displacement high byte.
       ld hl,sprgfx        ; address of play sprites.
       add hl,de           ; point to frame.

       ld a,(dispy)        ; y coordinate.
       and 6               ; position within byte boundary.
       ld c,a              ; low byte of table displacement.
       rlca                ; multiply by 32.
       rlca                ; already a multiple
       rlca                ; of 2, so just 4
       rlca                ; shifts needed.
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
       ld h,251            ; high byte of 64256 (SCADTB).
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
sspri2 ld a,16             ; vertical lines.
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
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
       call dline          ; draw a line.
       exx                 ; restore old addresses.
       call dline          ; delete a line.
       exx                 ; flip to new sprite addresses.
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
       cp 88               ; reached end of screen?
       ret c               ; not yet.
       ld h,56             ; back to ROM.
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
       ld a,16             ; look down 16 pixels.
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
       ld a,(23693)        ; get colour.
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
       ld hl,(23606)       ; font address.
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

;       block NUMSPR * TABSIZ,255

       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
       defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
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


WINDOWTOP equ 0
WINDOWLFT equ 2
WINDOWHGT equ 20
WINDOWWID equ 28 ;³¸ÿ
MAPWID equ 10
       defb 255,255,255,255,255,255,255,255,255,255
mapdat equ $
       defb 255,27,255,20,255,23,255,255,255,255
       defb 255,255,255,19,21,22,24,25,26,255
       defb 255,255,14,13,12,11,10,18,17,255
       defb 255,255,255,15,3,0,4,6,8,255
       defb 255,255,255,16,2,1,5,7,9,255
       defb 255,255,255,255,255,255,255,255,255,255
stmap  defb 35
evnt00 equ $
       call cangd
       jp nz,a00017
       call tfall
a00017 call skobj
       ld (varobj),a
       ld a,255
       ld hl,varobj
       cp (hl)
       jp z,a00465
       ld a,(varobj)
       call getob
       ld a,50
       ld (sndtyp),a
       ld a,1
       ld hl,scno
       cp (hl)
       jp nz,a00128
       ld a,(vark)
       inc a
       ld (vark),a
       ld a,79
       ld (23693),a
       ld a,20
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(vark)
       call disply
a00128 ld a,16
       ld hl,scno
       cp (hl)
       jp nz,a00194
       ld a,(vark)
       inc a
       ld (vark),a
       ld a,79
       ld (23693),a
       ld a,20
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(vark)
       call disply
a00194 ld a,7
       ld hl,scno
       cp (hl)
       jp nz,a00272
       ld a,3
       call gotob
       jp c,a00272
       ld a,(vark)
       inc a
       ld (vark),a
       ld a,79
       ld (23693),a
       ld a,20
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(vark)
       call disply
a00272 ld a,13
       ld hl,scno
       cp (hl)
       jp nz,a00314
       ld a,9
       call gotob
       jp c,a00314
       ld a,(varc)
       inc a
       ld (varc),a
a00314 ld a,17
       ld hl,scno
       cp (hl)
       jp nz,a00389
       ld a,(numlif)
       inc a
       ld (numlif),a
       ld a,78
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(numlif)
       call disply
       ld a,1
       ld (varh),a
a00389 ld a,19
       ld hl,scno
       cp (hl)
       jp nz,a00465
       ld a,(numlif)
       inc a
       ld (numlif),a
       ld a,78
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(numlif)
       call disply
       ld a,1
       ld (vari),a
a00465 ld a,223
       cp (ix+9)
       jp nc,a00510
       call scrr
       ld a,32
       ld (ix+9),a
       ld a,(ix+8)
       ld (varo),a
       ld a,(ix+9)
       ld (varp),a
a00510 ld a,16
       cp (ix+9)
       jp c,a00554
       call scrl
       ld a,208
       ld (ix+9),a
       ld a,(ix+8)
       ld (varo),a
       ld a,(ix+9)
       ld (varp),a
a00554 ld a,2
       cp (ix+8)
       jp c,a00599
       call scru
       ld a,140
       ld (ix+8),a
       ld a,(ix+8)
       ld (varo),a
       ld a,(ix+9)
       ld (varp),a
a00599 ld a,140
       cp (ix+8)
       jp nc,a00644
       call scrd
       ld a,8
       ld (ix+8),a
       ld a,(ix+8)
       ld (varo),a
       ld a,(ix+9)
       ld (varp),a
a00644 call laddd
       jp nz,a00683
       ld a,2
       ld (varl),a
       call laddu
       jp nz,a00679
       ld a,1
       ld (varl),a
a00679 jp a00691
a00683 xor a
       ld (varl),a
a00691 ld a,(joyval)
       and 1
       jp z,a00931
       call cangr
       jp nz,a00931
       ld a,(joyval)
       and 4
       jp z,a00787
       call laddd
       jp nz,a00741
       jp a00783
a00741 xor a
       ld hl,vara
       cp (hl)
       jp nz,a00766
       xor a
       call animsp
a00766 xor a
       ld (ix+6),a
       inc (ix+9)
       inc (ix+9)
a00783 jp a00931
a00787 ld a,(joyval)
       and 8
       jp z,a00860
       call laddu
       jp nz,a00814
       jp a00855
a00814 xor a
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a00846
       xor a
       call animsp
a00846 inc (ix+9)
       inc (ix+9)
a00855 jp a00931
a00860 ld a,1
       ld (vard),a
       xor a
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a00922
       xor a
       call animsp
       xor a
       cp (ix+7)
       jp nz,a00922
       ld a,20
       ld (sndtyp),a
a00922 inc (ix+9)
       inc (ix+9)
a00931 ld a,(joyval)
       and 2
       jp z,a01171
       call cangl
       jp nz,a01171
       ld a,(joyval)
       and 4
       jp z,a01027
       call laddd
       jp nz,a00981
       jp a01022
a00981 xor a
       ld hl,vara
       cp (hl)
       jp nz,a01005
       xor a
       call animsp
a01005 ld a,1
       ld (ix+6),a
       dec (ix+9)
       dec (ix+9)
a01022 jp a01171
a01027 ld a,(joyval)
       and 8
       jp z,a01100
       call laddu
       jp nz,a01054
       jp a01095
a01054 ld a,1
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a01086
       xor a
       call animsp
a01086 dec (ix+9)
       dec (ix+9)
a01095 jp a01171
a01100 ld a,2
       ld (vard),a
       ld a,1
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a01162
       xor a
       call animsp
       xor a
       cp (ix+7)
       jp nz,a01162
       ld a,20
       ld (sndtyp),a
a01162 dec (ix+9)
       dec (ix+9)
a01171 ld a,(joyval)
       and 8
       jp z,a01244
       ld a,3
       ld (vard),a
       call laddu
       jp nz,a01244
       ld a,2
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a01235
       xor a
       call animsp
a01235 dec (ix+8)
       dec (ix+8)
a01244 ld a,(joyval)
       and 4
       jp z,a01317
       ld a,3
       ld (vard),a
       call laddd
       jp nz,a01317
       ld a,2
       ld (ix+6),a
       xor a
       ld hl,vara
       cp (hl)
       jp nz,a01308
       xor a
       call animsp
a01308 inc (ix+8)
       inc (ix+8)
a01317 ld a,(joyval)
       and 16
       jp z,a01378
       ld a,1
       ld hl,varl
       cp (hl)
       jp nz,a01351
       jp a01378
a01351 call cangd
       jp nz,a01365
       jp a01378
a01365 ld a,40
       ld (sndtyp),a
       call hop
a01378 ld b,DEADLY
       call tded
       cp b
       jp nz,a01423
       ld a,(varo)
       ld (ix+8),a
       ld a,(varp)
       ld (ix+9),a
       ld hl,deadf
       ld (hl),h
a01423 jp grav
evnt01 equ $
       xor a
       ld hl,vara
       cp (hl)
       jp nz,b00027
       xor a
       call animsp
b00027 ret
evnt02 equ $
       xor a
       ld hl,vara
       cp (hl)
       jp nz,c00027
       xor a
       call animsp
c00027 ld b,0
       call sktyp
       jp nc,c02813
       ld a,(joyval)
       and 64
       jp z,c02813
       ld a,9
       call minve
       call silenc
       ld a,(ix+8)
       ld (vare),a
       ld a,(ix+9)
       ld (varf),a
       xor a
       ld hl,scno
       cp (hl)
       jp nz,c00324
       xor a
       ld hl,varopt
       cp (hl)
       jp nz,c00324
       ld a,8
       ld (charx),a
       ld a,28
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,9
       ld (charx),a
       ld a,28
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,80
       ld (sndtyp),a
       ld (ix+5),255
c00324 ld a,11
       ld hl,scno
       cp (hl)
       jp nz,c00563
       ld a,5
       ld hl,varopt
       cp (hl)
       jp nz,c00563
       ld a,2
       ld (charx),a
       ld a,20
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,3
       ld (charx),a
       ld a,20
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
c00563 ld a,4
       ld hl,scno
       cp (hl)
       jp nz,c00859
       ld a,6
       ld hl,varopt
       cp (hl)
       jp nz,c00859
       ld a,71
       ld (23693),a
       ld a,2
       ld (charx),a
       ld a,11
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,21
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,22
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,3
       ld (charx),a
       ld a,11
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,21
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,22
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
       ld a,136
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,6
       call drpob
c00859 ld a,9
       ld hl,scno
       cp (hl)
       jp nz,c01145
       ld a,8
       ld hl,varopt
       cp (hl)
       jp nz,c01145
       ld a,4
       ld (charx),a
       ld a,2
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,5
       ld (charx),a
       ld a,2
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,45
       ld (sndtyp),a
       ld (ix+5),255
       ld a,136
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,8
       call drpob
c01145 ld a,20
       ld hl,scno
       cp (hl)
       jp nz,c01353
       ld a,15
       ld hl,varopt
       cp (hl)
       jp nz,c01353
       ld a,4
       ld (charx),a
       ld a,8
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,60
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,5
       ld (charx),a
       ld a,8
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,61
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,80
       ld (sndtyp),a
       ld (ix+5),255
       ld a,8
       ld (ix+8),a
       ld a,216
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,15
       call drpob
c01353 ld a,13
       ld hl,scno
       cp (hl)
       jp nz,c01544
       ld a,7
       ld hl,varopt
       cp (hl)
       jp nz,c01544
       ld a,17
       ld (charx),a
       ld a,14
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,45
       ld (sndtyp),a
       ld (ix+5),255
       ld a,48
       ld (ix+8),a
       ld a,216
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,7
       call drpob
c01544 ld a,14
       ld hl,scno
       cp (hl)
       jp nz,c01697
       ld a,11
       ld hl,varopt
       cp (hl)
       jp nz,c01697
       ld a,15
       ld (charx),a
       ld a,7
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,56
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,80
       ld (sndtyp),a
       ld (ix+5),255
       ld a,136
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,11
       call drpob
c01697 ld a,5
       ld hl,scno
       cp (hl)
       jp nz,c01912
       ld a,10
       ld hl,varopt
       cp (hl)
       jp nz,c01912
       ld a,(ix+8)
       ld (vare),a
       ld a,(ix+9)
       ld (varf),a
       ld a,72
       ld (ix+8),a
       ld a,176
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,10
       call drpob
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
       ld a,(varf)
       ld (ix+9),a
       ld a,(vare)
       ld (ix+8),a
       push ix
       ld b,75
       call delay
       pop ix
       ld c,24
       ld a,(ix+9)
       add a,c
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,14
       call drpob
       ld a,(varf)
       ld (ix+9),a
       ld a,70
       ld (sndtyp),a
c01912 ld a,14
       ld hl,scno
       cp (hl)
       jp nz,c02144
       ld a,14
       ld hl,varopt
       cp (hl)
       jp nz,c02144
       ld a,9
       ld (charx),a
       ld a,11
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,55
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,72
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,73
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
       ld a,136
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,14
       call drpob
c02144 ld a,16
       ld hl,scno
       cp (hl)
       jp nz,c02311
       ld a,9
       ld hl,varopt
       cp (hl)
       jp nz,c02311
       ld a,72
       ld (ix+8),a
       ld a,120
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,9
       call drpob
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
       push ix
       ld b,50
       call delay
       pop ix
       ld a,80
       ld (sndtyp),a
       ld a,128
       ld (ix+8),a
       ld a,168
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,2
       call drpob
c02311 ld a,15
       ld hl,scno
       cp (hl)
       jp nz,c02503
       ld a,17
       ld hl,varopt
       cp (hl)
       jp nz,c02503
       ld a,15
       ld (charx),a
       ld a,20
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,52
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       ld a,52
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,60
       ld (sndtyp),a
       ld (ix+5),255
       ld a,136
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,17
       call drpob
c02503 ld a,23
       ld hl,scno
       cp (hl)
       jp nz,c02689
       ld a,18
       ld hl,varopt
       cp (hl)
       jp nz,c02689
       ld a,5
       ld (charx),a
       ld a,24
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,45
       ld (sndtyp),a
       push ix
       ld b,50
       call delay
       pop ix
       ld a,6
       ld (charx),a
       ld a,24
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,45
       ld (sndtyp),a
       ld (ix+5),255
c02689 ld a,10
       ld hl,scno
       cp (hl)
       jp nz,c02794
       ld a,16
       ld hl,varopt
       cp (hl)
       jp nz,c02794
       ld a,4
       ld (charx),a
       ld a,17
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,45
       ld (sndtyp),a
       ld (ix+5),255
c02794 ld a,(vare)
       ld (ix+8),a
       ld a,(varf)
       ld (ix+9),a
c02813 ret
evnt03 equ $
       xor a
       ld hl,varc
       cp (hl)
       jp nz,d00201
       xor a
       cp (ix+11)
       jp nz,d00119
       call cangl
       jp nz,d00106
       dec (ix+9)
       dec (ix+9)
       ld c,16
       ld a,(ix+9)
       sub c
       ld (ix+9),a
       call cangd
       jp nz,d00085
       ld a,1
       ld (ix+11),a
d00085 ld c,16
       ld a,(ix+9)
       add a,c
       ld (ix+9),a
       jp d00115
d00106 ld a,1
       ld (ix+11),a
d00115 jp d00201
d00119 call cangr
       jp nz,d00193
       inc (ix+9)
       inc (ix+9)
       ld c,16
       ld a,(ix+9)
       add a,c
       ld (ix+9),a
       call cangd
       jp nz,d00172
       xor a
       ld (ix+11),a
d00172 ld c,16
       ld a,(ix+9)
       sub c
       ld (ix+9),a
       jp d00201
d00193 xor a
       ld (ix+11),a
d00201 xor a
       call animsp
       ld b,0
       call sktyp
       jp nc,d00231
       ld hl,deadf
       ld (hl),h
d00231 ret
evnt04 equ $
       ld a,71
       and 7
       ld c,a
       call cspr
       xor a
       cp (ix+11)
       jp nz,e00099
       call cangd
       jp nz,e00078
       inc (ix+8)
       inc (ix+8)
       xor a
       ld hl,vara
       cp (hl)
       jp nz,e00073
       xor a
       call animsp
e00073 jp e00095
e00078 ld a,1
       ld (ix+11),a
       ld a,35
       ld (sndtyp),a
e00095 jp e00164
e00099 call cangu
       jp nz,e00147
       dec (ix+8)
       dec (ix+8)
       xor a
       ld hl,vara
       cp (hl)
       jp nz,e00142
       xor a
       call animsp
e00142 jp e00164
e00147 xor a
       ld (ix+11),a
       ld a,35
       ld (sndtyp),a
e00164 ld b,0
       call sktyp
       jp nc,e00186
       ld hl,deadf
       ld (hl),h
e00186 ld a,3
       cp (ix+6)
       jp nz,e00213
       ld a,70
       and 7
       ld c,a
       call cspr
e00213 ld a,6
       cp (ix+6)
       jp nz,e00241
       ld a,77
       and 7
       ld c,a
       call cspr
e00241 ret
evnt05 equ $
       xor a
       ld hl,vara
       cp (hl)
       jp nz,f00027
       xor a
       call animsp
f00027 ld b,0
       call sktyp
       jp nc,f00647
       ld a,(joyval)
       and 64
       jp z,f00647
       ld a,9
       call minve
       call silenc
       ld a,(ix+8)
       ld (vare),a
       ld a,(ix+9)
       ld (varf),a
       ld a,25
       ld hl,scno
       cp (hl)
       jp nz,f00325
       ld a,4
       ld hl,varopt
       cp (hl)
       jp nz,f00325
       ld a,9
       ld (charx),a
       ld a,14
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,10
       ld (charx),a
       ld a,14
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,50
       ld (sndtyp),a
       ld (ix+5),255
f00325 ld a,1
       ld hl,scno
       cp (hl)
       jp nz,f00564
       ld a,4
       ld hl,varopt
       cp (hl)
       jp nz,f00564
       ld a,15
       ld (charx),a
       ld a,22
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,16
       ld (charx),a
       ld a,22
       ld (chary),a
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld hl,chgfx
       ld (grbase),hl
       ld hl,(charx)
       ld (dispx),hl
       xor a
       call pattr
       ld hl,(dispx)
       ld (charx),hl
       ld a,50
       ld (sndtyp),a
       ld (ix+5),255
f00564 ld a,5
       ld hl,scno
       cp (hl)
       jp nz,f00647
       ld a,3
       ld hl,vark
       cp (hl)
       jp nz,f00628
       ld a,19
       ld hl,varopt
       cp (hl)
       jp nz,f00628
       ld a,27
       ld (scno),a
       call nwscr
f00628 ld a,(vare)
       ld (ix+8),a
       ld a,(varf)
       ld (ix+9),a
f00647 ret
evnt06 equ $
       xor a
       cp (ix+11)
       jp nz,g00085
       call cangl
       jp nz,g00072
       dec (ix+9)
       dec (ix+9)
       ld c,16
       ld a,(ix+9)
       sub c
       ld (ix+9),a
       ld c,16
       ld a,(ix+9)
       add a,c
       ld (ix+9),a
       jp g00080
g00072 ld a,1
       ld (ix+11),a
g00080 jp g00149
g00085 call cangr
       jp nz,g00141
       inc (ix+9)
       inc (ix+9)
       ld c,16
       ld a,(ix+9)
       add a,c
       ld (ix+9),a
       ld c,16
       ld a,(ix+9)
       sub c
       ld (ix+9),a
       jp g00149
g00141 xor a
       ld (ix+11),a
g00149 ld a,1
       cp (ix+11)
       jp nz,g00208
       xor a
       ld hl,vara
       cp (hl)
       jp nz,g00208
       xor a
       call animsp
       ld a,3
       cp (ix+7)
       jp nz,g00208
       ld a,35
       ld (sndtyp),a
g00208 xor a
       cp (ix+11)
       jp nz,g00267
       xor a
       ld hl,vara
       cp (hl)
       jp nz,g00267
       xor a
       call animbk
       ld a,3
       cp (ix+7)
       jp nz,g00267
       ld a,35
       ld (sndtyp),a
g00267 ld b,0
       call sktyp
       jp nc,g00289
       ld hl,deadf
       ld (hl),h
g00289 ld a,8
       cp (ix+6)
       jp nz,g00317
       ld a,6
       and 7
       ld c,a
       call cspr
g00317 ret
evnt07 equ $
       ret
evnt08 equ $
       ret
evnt09 equ $
       ld a,4
       cp (ix+5)
       jp nz,j00024
       ld a,1
       ld (ix+11),a
j00024 xor a
       cp (ix+5)
       jp nz,j00068
       ld a,(varo)
       ld (ix+8),a
       ld a,(varp)
       ld (ix+9),a
       ld a,(ix+8)
       inc a
       ld (ix+8),a
j00068 ret
evnt10 equ $
       ld a,(vara)
       inc a
       ld (vara),a
       ld a,2
       ld hl,vara
       cp (hl)
       jp nc,k00040
       xor a
       ld (vara),a
k00040 ld a,1
       ld hl,varh
       cp (hl)
       jp nz,k00168
       ld a,12
       call gotob
       jp c,k00168
       ld a,(ix+8)
       ld (vare),a
       ld a,(ix+9)
       ld (varf),a
       ld a,40
       ld (ix+8),a
       ld a,88
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,12
       call drpob
       ld a,(vare)
       ld (ix+8),a
       ld a,(varf)
       ld (ix+9),a
       ld a,(varh)
       inc a
       ld (varh),a
k00168 ld a,1
       ld hl,vari
       cp (hl)
       jp nz,k00295
       ld a,13
       call gotob
       jp c,k00295
       ld a,(ix+8)
       ld (vare),a
       ld a,(ix+9)
       ld (varf),a
       ld a,8
       ld (ix+8),a
       ld a,24
       ld (ix+9),a
       ld a,(ix+9)
       ld h,a
       ld a,(ix+8)
       ld l,a
       ld (dispx),hl
       ld a,13
       call drpob
       ld a,(vare)
       ld (ix+8),a
       ld a,(varf)
       ld (ix+9),a
       ld a,(vari)
       inc a
       ld (vari),a
k00295 ld a,27
       ld hl,scno
       cp (hl)
       jp nz,k00425
       xor a
       ld hl,varg
       cp (hl)
       jp nz,k00425
       ld a,69
       ld (23693),a
       ld a,2
       ld (charx),a
       ld a,3
       ld (chary),a
       ld a,11
       call dmsg
       ld a,70
       ld (23693),a
       ld a,18
       ld (charx),a
       ld a,12
       ld (chary),a
       ld a,20
       call dmsg
       ld a,(varg)
       inc a
       ld (varg),a
       push ix
       ld b,25
       call delay
       pop ix
k00425 ld a,27
       ld hl,scno
       cp (hl)
       jp nz,k00456
       call prskey
       ld hl,gamwon
       ld (hl),h
k00456 ret
evnt11 equ $
       ret
evnt12 equ $
       ld a,70
       ld (23693),a
       call cls
       ld a,2
       ld (charx),a
       ld a,10
       ld (chary),a
       xor a
       call dmsg
       ld a,1
       ld (charx),a
       ld a,18
       call dmsg
       ld a,69
       ld (23693),a
       ld a,4
       ld (charx),a
       xor a
       ld (chary),a
       ld a,12
       call dmsg
       ld a,68
       ld (23693),a
       ld a,18
       ld (charx),a
       xor a
       ld (chary),a
       ld a,13
       call dmsg
       ld a,71
       ld (23693),a
       ld a,1
       ld (charx),a
       ld a,15
       ld (chary),a
       ld a,14
       call dmsg
       ld a,8
       ld (charx),a
       ld a,2
       ld (chary),a
       ld a,15
       call dmsg
       ld a,70
       ld (23693),a
       ld a,4
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,16
       call dmsg
       ld a,5
       ld (23693),a
       ld a,6
       ld (charx),a
       ld a,8
       ld (chary),a
       ld a,10
       call dmsg
       ld a,10
       ld (charx),a
       ld a,8
       ld (chary),a
       ld a,10
       call dmsg
       ld a,8
       ld (charx),a
       ld a,23
       ld (chary),a
       ld a,10
       call dmsg
       ld a,69
       ld (23693),a
       ld a,9
       ld (charx),a
       ld a,23
       ld (chary),a
       ld a,10
       call dmsg
       ld a,78
       ld (23693),a
       ld a,4
       ld (charx),a
       ld a,20
       ld (chary),a
       ld a,8
       call dmsg
       ld a,86
       ld (23693),a
       ld a,12
       ld (charx),a
       ld a,10
       ld (chary),a
       ld a,8
       call dmsg
       ld a,94
       ld (23693),a
       ld a,12
       ld (charx),a
       ld a,12
       ld (chary),a
       ld a,8
       call dmsg
       ld a,102
       ld (23693),a
       ld a,12
       ld (charx),a
       ld a,11
       ld (chary),a
       ld a,8
       call dmsg
       ld a,66
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,17
       call dmsg
       call prskey
       ret
evnt13 equ $
       xor a
       call 8859
       ld a,77
       ld (23693),a
       call cls
       call silenc
       ld a,75
       ld (23693),a
       ld a,20
       ld (charx),a
       ld a,2
       ld (chary),a
       xor a
       call dmsg
       ld a,77
       ld (23693),a
       xor a
       ld (varc),a
       xor a
       ld (varg),a
       ld a,128
       ld (varo),a
       ld a,32
       ld (varp),a
       ld a,3
       ld (numlif),a
       xor a
       ld (vark),a
       xor a
       ld (vare),a
       xor a
       ld (varf),a
       xor a
       ld (charx),a
       ld a,1
       ld (chary),a
       ld a,3
       call dmsg
       ld a,21
       ld (loopa),a
n00169 ld a,1
       ld (chary),a
       ld a,3
       call dmsg
       ld hl,loopa
       dec (hl)
       jp nz,n00169
       ld a,1
       ld (chary),a
       ld a,4
       call dmsg
       xor a
       ld (charx),a
       ld a,30
       ld (chary),a
       ld a,3
       call dmsg
       ld a,21
       ld (loopa),a
n00249 ld a,30
       ld (chary),a
       ld a,3
       call dmsg
       ld hl,loopa
       dec (hl)
       jp nz,n00249
       ld a,22
       ld (charx),a
       ld a,2
       ld (chary),a
       ld a,5
       call dmsg
       ld a,22
       ld (charx),a
       ld a,30
       ld (chary),a
       ld a,6
       call dmsg
       ld a,78
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,22
       ld (chary),a
       ld a,1
       call dmsg
       ld a,21
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(numlif)
       call disply
       ld a,21
       ld (charx),a
       ld a,2
       ld (chary),a
       ld a,7
       call dmsg
       ld a,79
       ld (23693),a
       ld a,20
       ld (charx),a
       ld a,19
       ld (chary),a
       ld a,2
       call dmsg
       ld a,20
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(vark)
       call disply
       ret
evnt14 equ $
       ret
evnt15 equ $
       ret
evnt16 equ $
       ld a,60
       ld (sndtyp),a
       push ix
       ld b,a
       call delay
       pop ix
       ld a,(numlif)
       dec a
       ld (numlif),a
       ld a,(varo)
       ld (ix+8),a
       ld a,(varp)
       ld (ix+9),a
       ld a,78
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,29
       ld (chary),a
       ld a,(numlif)
       call disply
       ret
evnt17 equ $
       push ix
       ld b,50
       call delay
       pop ix
       call cls
       ld a,77
       ld (23693),a
       ld a,10
       ld (charx),a
       ld a,10
       ld (chary),a
       xor a
       call dmsg
       ld a,9
       ld (charx),a
       ld a,18
       call dmsg
       ld a,206
       ld (23693),a
       ld a,12
       ld (charx),a
       ld a,12
       ld (chary),a
       ld a,21
       call dmsg
       ld a,79
       ld (23693),a
       ld a,14
       ld (charx),a
       ld a,15
       ld (chary),a
       ld a,14
       call dmsg
       push ix
       ld b,200
       call delay
       pop ix
       ret
evnt18 equ $
       ld a,69
       ld (23693),a
       call cls
       push ix
       ld b,50
       call delay
       pop ix
       ld a,1
       ld (charx),a
       xor a
       ld (chary),a
       ld a,19
       call dmsg
       ld a,70
       ld (23693),a
       ld a,21
       ld (charx),a
       ld a,11
       ld (chary),a
       ld a,20
       call dmsg
       call prskey
       ret
evnt19 equ $
       ret
evnt20 equ $
       ret
ptcusr ret
msgdat equ $
       defb 'FOGGYS;QUEST',141
       defb 'LIVES:',141
       defb 'CRYSTALS:',141
       defb '@',141
       defb '`',141
       defb '____________________________',141
       defb '$',141
       defb 'BY:;J.BLYTHE',141
       defb 'x',141
       defb ';KEY;BLUE;;',13
       defb 'CRYSTAL;BLU',13
       defb 'CRYSTAL;RED',13
       defb 'CRYSTAL;GRN',13
       defb ';;KEY;RED;;',13
       defb ';KEY;PINK;;',13
       defb ';;LADDER;;;',13
       defb ';;;BOMB;;;;',13
       defb ';THE;CUBE;;',13
       defb ';THE;SKULL;',13
       defb ';PIT;PLANT;',13
       defb ';;;ROCK;;;;',13
       defb 'EXTRA;LIFE;',13
       defb 'EXTRA;LIFE;',13
       defb ';;A;SEED;;;',13
       defb ';;BALLOON;;',13
       defb ';PICK;AXE;;',13
       defb ';;BRICKS;;;',13
       defb ';ICE;DRILL;',13
       defb ';;SPLICER;;',141
       defb 'z',141
       defb 'WELL;DONE;FOGGY!!',141
       defb ';;;;;;;;w___________x__y;;;.',13
       defb ';.;;;;;;@;;;;;;;;;;;;;;@',13
       defb ';;;;;;;;z;;;CONTROLS;;;@;.',13
       defb ';;;;;.;;@;;;;;;;;;;;;;;@;;;;;;.',13
       defb ';;;;.;;;@;;1;KEYBOARD;;z',13
       defb ';;;;;;;;@;;2;KEMPSTON;;@',13
       defb ';;;;;;;;z;;3;SINCLAIR;;@;;;;.',13
       defb ';;;;;;.;@;;;;;;;;;;;;;;@;;;;;.',13
       defb ';;.;;;;;`_xx___________$;;.',13
       defb ';;;;;;;;;;KEYS:O,P,Q,A',13
       defb ';;;;;;;;;;;;;;;I-INV.',13
       defb ';;;;;;;;;;;;;;;SPC-JUMP',141
       defb ';;;;;;;;;RUCKSACK;GAMES',13
       defb ';;;;;;;c;2017;JOHN;BLYTHE',141
       defb '/+',141
       defb '>',141
       defb '?',141
       defb ';;;;;;;;;POWERED;BY;AGD',141
       defb ';;;;;;;;;;v',13
       defb ';;;;;;;;;;u',141
       defb ';;;HOME;AT;LAST.;FOGGY;TAKES;A',13
       defb ';',13
       defb ';WELL;EARNED;REST;FROM;HOLIDAYS.',13
       defb ';',13
       defb ';;;;TIME;FOR;BIT;OF;TREASURE',13
       defb ';',13
       defb ';;;;;;;;HUNTING;INSTEAD!!!',13
       defb ';',13
       defb ';',13
       defb ';;;;;;;THANKS;FOR;PLAYING!',13
       defb ';',13
       defb ';CREDITS..',13
       defb ';',13
       defb ';CODING;AND;GFX;-;JOHN;BLYTHE',13
       defb ';ADDITIONAL;CODE;-;ANDY;JOHNS',13
       defb ';',13
       defb ';MANY;THANKS;TO..',13
       defb ';JONATHAN CAULDWELL;FOR;AGD',141
       defb 'PRESS;A;KEY',141
       defb 'IS;OVER..',141
nummsg defb 22
chgfx  equ $
       defb 0,0,0,0,0,0,0,0
       defb 12,108,97,128,30,222,222,32
       defb 70,6,102,97,0,51,179,48
       defb 0,8,65,0,16,0,130,32
       defb 126,129,141,141,129,161,129,126
       defb 255,126,189,90,165,66,129,0
       defb 255,126,189,90,165,66,129,0
       defb 255,126,189,90,165,66,129,0
       defb 255,126,189,90,165,66,129,0
       defb 239,239,170,69,170,0,239,0
       defb 248,254,174,87,171,23,139,87
       defb 75,87,75,87,0,87,75,87
       defb 75,87,74,69,34,48,15,0
       defb 126,255,170,85,3,187,56,66
       defb 183,183,0,248,240,0,192,128
       defb 215,215,0,29,13,0,3,1
       defb 12,25,30,76,56,28,14,24
       defb 12,88,48,38,72,68,36,24
       defb 239,239,170,69,170,0,239,0
       defb 0,0,0,0,0,0,0,0
       defb 181,0,96,6,0,85,170,255
       defb 96,96,96,255,170,0,64,96
       defb 6,6,6,255,170,0,4,6
       defb 132,41,16,90,32,148,1,40
       defb 79,159,0,79,0,159,149,79
       defb 250,253,0,250,0,253,85,250
       defb 126,129,141,141,129,161,129,126
       defb 126,129,141,141,129,161,129,126
       defb 168,130,42,162,136,42,162,42
       defb 168,130,42,162,136,42,162,42
       defb 168,130,42,162,136,42,162,42
       defb 0,0,0,0,66,16,36,255
       defb 219,255,85,170,255,0,30,12
       defb 109,255,85,170,255,0,120,48
       defb 63,64,180,160,128,133,255,0
       defb 252,2,1,5,13,161,255,0
       defb 240,252,87,172,240,44,5,14
       defb 13,63,245,58,15,26,160,112
       defb 0,0,0,0,0,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 254,124,184,80,160,64,128,0
       defb 127,62,29,10,5,2,1,0
       defb 0,0,0,0,0,0,0,0
       defb 0,0,0,0,32,0,0,0
       defb 0,0,0,8,0,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 128,64,160,208,232,244,250,253
       defb 8,0,8,255,128,0,128,0
       defb 1,2,5,11,23,47,95,191
       defb 0,106,64,0,64,0,66,0
       defb 24,24,36,36,102,126,231,255
       defb 0,0,0,0,0,0,0,0
       defb 54,111,221,221,122,50,1,0
       defb 124,214,191,255,235,213,170,124
       defb 56,254,255,221,243,127,157,98
       defb 0,112,236,222,254,251,223,62
       defb 0,15,63,111,254,249,239,112
       defb 60,78,191,255,245,106,52,24
       defb 8,8,4,8,16,32,16,8
       defb 255,255,255,255,255,255,255,255
       defb 85,171,87,175,95,191,127,255
       defb 1,2,5,10,21,42,85,170
       defb 61,104,208,168,208,128,192,128
       defb 188,22,11,21,11,1,3,1
       defb 255,117,170,16,66,0,0,0
       defb 0,0,0,0,0,0,0,0
       defb 139,197,227,241,185,221,175,151
       defb 255,250,210,82,64,64,0,0
       defb 0,0,0,0,0,0,76,255
       defb 90,165,219,102,189,102,60,90
       defb 76,246,251,187,95,70,128,0
       defb 14,23,45,44,44,88,224,0
       defb 102,91,164,90,219,25,100,154
       defb 1,131,103,90,38,28,0,0
       defb 176,176,176,176,176,176,176,176
       defb 13,21,13,21,13,21,13,21
bcol   equ $
       defb 71
       defb 77
       defb 78
       defb 77
       defb 78
       defb 86
       defb 79
       defb 116
       defb 94
       defb 65
       defb 65
       defb 65
       defb 65
       defb 78
       defb 69
       defb 69
       defb 68
       defb 4
       defb 1
       defb 69
       defb 86
       defb 71
       defb 71
       defb 65
       defb 71
       defb 7
       defb 86
       defb 94
       defb 205
       defb 214
       defb 222
       defb 66
       defb 71
       defb 7
       defb 69
       defb 65
       defb 7
       defb 71
       defb 66
       defb 67
       defb 68
       defb 65
       defb 70
       defb 70
       defb 65
       defb 69
       defb 70
       defb 87
       defb 87
       defb 66
       defb 80
       defb 66
       defb 66
       defb 70
       defb 64
       defb 68
       defb 66
       defb 71
       defb 71
       defb 71
       defb 66
       defb 68
       defb 70
       defb 70
       defb 70
       defb 66
       defb 66
       defb 66
       defb 119
       defb 69
       defb 71
       defb 71
       defb 67
       defb 68
       defb 4
       defb 66
       defb 4
       defb 87
       defb 80
bprop  equ $
       defb 0
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 0
       defb 0
       defb 0
       defb 0
       defb 2
       defb 0
       defb 0
       defb 0
       defb 0
       defb 0
       defb 0
       defb 5
       defb 3
       defb 3
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 0
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 0
       defb 0
       defb 0
       defb 0
       defb 0
       defb 0
       defb 2
       defb 0
       defb 0
       defb 0
       defb 2
       defb 0
       defb 2
       defb 0
       defb 3
       defb 0
       defb 0
       defb 1
       defb 2
       defb 1
       defb 1
       defb 1
       defb 2
       defb 0
       defb 0
       defb 0
       defb 0
       defb 2
       defb 2
       defb 2
       defb 2
       defb 2
       defb 0
       defb 0
       defb 1
       defb 1
       defb 0
       defb 0
       defb 0
       defb 0
       defb 0
sprgfx equ $
       defb 0,0,12,0,23,0,7,192,15,224,30,112,61,168,61,36,125,36,126,32,255,252,198,252,187,4,125,250,125,247,60,15
       defb 0,0,3,0,5,192,1,240,3,248,7,156,15,106,15,73,31,73,31,136,63,255,49,191,46,193,159,126,223,125,207,3
       defb 0,0,0,192,1,112,0,124,0,254,1,231,131,218,67,210,71,210,7,226,207,255,204,111,75,176,167,223,119,223,243,192
       defb 0,0,0,48,0,92,0,31,128,63,192,121,160,246,144,244,145,244,129,248,243,255,243,27,18,236,233,247,221,247,60,240
       defb 0,0,30,0,7,128,7,192,15,224,31,48,62,212,62,144,126,144,127,16,241,252,238,252,95,4,31,120,15,116,0,12
       defb 0,0,7,128,1,224,1,240,3,248,7,204,15,181,15,164,31,164,31,196,60,127,59,191,23,193,7,222,3,221,0,3
       defb 0,0,1,224,0,120,0,124,0,254,1,243,67,237,3,233,7,233,7,241,207,31,206,239,69,240,129,247,64,247,192,0
       defb 0,0,0,120,0,30,0,31,128,63,192,124,80,251,64,250,65,250,65,252,243,199,243,187,17,124,224,125,208,61,48,0
       defb 16,0,14,0,7,128,7,192,15,224,31,144,63,104,63,72,127,72,127,136,255,252,252,124,123,132,55,216,7,208,27,192
       defb 4,0,3,128,1,224,1,240,3,248,7,228,15,218,15,210,31,210,31,226,63,255,63,31,30,225,13,246,1,244,6,240
       defb 1,0,0,224,0,120,0,124,0,254,1,249,131,246,131,244,135,244,135,248,207,255,207,199,71,184,131,125,0,125,1,188
       defb 0,64,0,56,0,30,0,31,128,63,64,126,160,253,32,253,33,253,33,254,243,255,243,241,17,238,96,223,64,31,0,111
       defb 0,0,30,0,7,128,7,192,15,224,31,48,62,212,62,144,126,144,127,16,255,252,241,252,110,4,95,120,31,116,15,12
       defb 0,0,7,128,1,224,1,240,3,248,7,204,15,181,15,164,31,164,31,196,63,255,60,127,27,129,23,222,7,221,3,195
       defb 0,0,1,224,0,120,0,124,0,254,1,243,67,237,3,233,7,233,7,241,207,255,207,31,70,224,133,247,65,247,192,240
       defb 0,0,0,120,0,30,0,31,128,63,192,124,80,251,64,250,65,250,65,252,243,255,243,199,17,184,225,125,208,125,48,60
       defb 0,0,0,48,0,232,3,224,7,240,14,120,21,188,36,188,36,190,4,126,63,255,63,99,32,221,95,190,239,190,240,60
       defb 0,0,0,12,0,58,0,248,1,252,3,158,5,111,9,47,137,47,129,31,207,255,207,216,72,55,151,239,187,239,60,15
       defb 0,0,0,3,128,14,0,62,0,127,128,231,193,91,194,75,226,75,224,71,243,255,51,246,210,13,229,251,238,251,207,3
       defb 0,0,192,0,160,3,128,15,192,31,224,57,240,86,240,146,248,146,248,17,252,255,140,253,116,131,249,126,251,190,243,192
       defb 0,0,0,120,1,224,3,224,7,240,12,248,43,124,9,124,9,126,8,254,63,143,63,119,32,250,30,248,46,240,48,0
       defb 0,0,0,30,0,120,0,248,1,252,3,62,10,223,2,95,130,95,130,63,207,227,207,221,136,62,7,190,11,188,12,0
       defb 0,0,128,7,0,30,0,62,0,127,128,207,194,183,192,151,224,151,224,143,243,248,115,247,162,15,129,239,2,239,3,0
       defb 0,0,224,1,128,7,128,15,192,31,224,51,240,173,240,37,248,37,248,35,60,254,220,253,232,131,224,123,192,187,0,192
       defb 0,8,0,112,1,224,3,224,7,240,9,248,22,252,18,252,18,254,17,254,63,255,62,63,33,222,27,236,11,224,3,216
       defb 0,2,0,28,0,120,0,248,1,252,2,126,5,191,4,191,132,191,132,127,207,255,207,143,136,119,6,251,2,248,0,246
       defb 128,0,0,7,0,30,0,62,0,127,128,159,193,111,193,47,225,47,225,31,243,255,243,227,226,29,193,190,0,190,128,61
       defb 32,0,192,1,128,7,128,15,192,31,224,39,240,91,240,75,248,75,248,71,252,255,252,248,120,135,176,111,128,47,96,15
       defb 0,0,0,120,1,224,3,224,7,240,12,248,43,124,9,124,9,126,8,254,63,255,63,143,32,118,30,250,46,248,48,240
       defb 0,0,0,30,0,120,0,248,1,252,3,62,10,223,2,95,130,95,130,63,207,255,207,227,136,29,135,190,11,190,12,60
       defb 0,0,128,7,0,30,0,62,0,127,128,207,194,183,192,151,224,151,224,143,243,255,243,248,98,7,161,239,130,239,3,15
       defb 0,0,224,1,128,7,128,15,192,31,224,51,240,173,240,37,248,37,248,35,252,255,60,254,216,129,232,123,224,187,192,195
       defb 3,192,5,160,14,112,14,240,31,248,31,248,63,252,63,252,63,252,127,254,127,235,23,87,106,173,245,91,247,224,240,0
       defb 0,240,1,104,3,156,3,188,7,254,7,254,15,255,15,255,15,255,159,255,223,250,197,213,90,171,253,86,61,248,60,0
       defb 0,60,0,90,0,231,0,239,129,255,129,255,195,255,195,255,195,255,231,255,183,254,113,117,214,170,191,85,15,126,15,0
       defb 0,15,128,22,192,57,192,59,224,127,224,127,240,255,240,255,240,255,249,255,173,255,92,93,181,170,111,213,131,223,3,192
       defb 3,192,5,160,13,112,12,240,31,248,31,248,63,252,63,252,63,252,127,254,111,238,151,215,234,173,245,91,103,231,0,0
       defb 0,240,1,104,3,92,3,60,7,254,7,254,15,255,15,255,15,255,159,255,155,251,229,245,122,171,253,86,217,249,0,0
       defb 0,60,0,90,0,215,0,207,129,255,129,255,195,255,195,255,195,255,231,255,230,254,121,125,222,170,191,85,118,126,0,0
       defb 0,15,128,22,192,53,192,51,224,127,224,127,240,255,240,255,240,255,249,255,185,191,94,95,183,170,111,213,157,159,0,0
       defb 3,192,5,160,14,112,14,240,31,248,31,248,63,252,63,252,63,252,127,254,239,254,213,216,170,166,213,79,7,239,0,15
       defb 0,240,1,104,3,156,3,188,7,254,7,254,15,255,15,255,15,255,159,255,187,255,53,118,170,169,245,83,193,251,192,3
       defb 0,60,0,90,0,231,0,239,129,255,129,255,195,255,195,255,195,255,231,255,238,255,141,93,106,170,253,84,240,126,240,0
       defb 0,15,128,22,192,57,192,59,224,127,224,127,240,255,240,255,240,255,249,255,251,191,99,87,154,170,63,85,188,31,60,0
       defb 3,192,5,160,14,176,15,48,31,248,31,248,63,252,63,252,63,252,127,254,111,238,151,215,234,173,245,91,103,231,0,0
       defb 0,240,1,104,3,172,3,204,7,254,7,254,15,255,15,255,15,255,159,255,155,251,229,245,122,171,253,86,217,249,0,0
       defb 0,60,0,90,0,235,0,243,129,255,129,255,195,255,195,255,195,255,231,255,230,254,121,125,222,170,191,85,118,126,0,0
       defb 0,15,128,22,192,58,192,60,224,127,224,127,240,255,240,255,240,255,249,255,185,191,94,95,183,170,111,213,157,159,0,0
       defb 102,102,255,255,128,1,179,205,189,189,191,253,183,237,179,205,179,205,179,205,191,253,191,253,166,101,128,1,255,255,102,102
       defb 153,153,255,255,96,0,108,243,111,111,111,255,109,251,108,243,108,243,108,243,111,255,111,255,105,153,96,0,255,255,153,153
       defb 102,102,255,255,24,0,219,60,219,219,219,255,219,126,219,60,219,60,219,60,219,255,219,255,90,102,24,0,255,255,102,102
       defb 153,153,255,255,6,0,54,207,246,246,246,255,182,223,54,207,54,207,54,207,246,255,246,255,150,153,6,0,255,255,153,153
       defb 102,102,255,255,128,1,191,253,179,205,189,189,191,253,183,237,179,205,179,205,191,253,166,101,160,5,128,1,255,255,102,102
       defb 153,153,255,255,96,0,111,255,108,243,111,111,111,255,109,251,108,243,108,243,111,255,105,153,104,1,96,0,255,255,153,153
       defb 102,102,255,255,24,0,219,255,219,60,219,219,219,255,219,126,219,60,219,60,219,255,90,102,90,0,24,0,255,255,102,102
       defb 153,153,255,255,6,0,246,255,54,207,246,246,246,255,182,223,54,207,54,207,246,255,150,153,22,128,6,0,255,255,153,153
       defb 102,102,255,255,128,1,191,253,183,237,187,221,189,189,167,229,187,221,191,253,182,109,160,5,160,5,128,1,255,255,102,102
       defb 153,153,255,255,96,0,111,255,109,251,110,247,111,111,105,249,110,247,111,255,109,155,104,1,104,1,96,0,255,255,153,153
       defb 102,102,255,255,24,0,219,255,219,126,219,189,219,219,90,126,219,189,219,255,219,102,90,0,90,0,24,0,255,255,102,102
       defb 153,153,255,255,6,0,246,255,182,223,118,239,246,246,150,159,118,239,246,255,182,217,22,128,22,128,6,0,255,255,153,153
       defb 48,0,48,0,31,251,56,31,55,236,47,244,47,244,47,52,46,84,46,20,47,52,47,244,240,12,223,248,0,12,0,12
       defb 12,0,12,0,199,254,206,7,13,251,11,253,11,253,11,205,11,149,11,133,11,205,11,253,60,3,55,254,0,3,0,3
       defb 3,0,3,0,177,255,243,129,195,126,66,255,66,255,66,243,66,229,66,225,66,243,66,255,207,0,141,255,192,0,192,0
       defb 0,192,0,192,236,127,124,224,176,223,208,191,208,191,208,188,80,185,80,184,208,188,208,191,51,192,227,127,48,0,48,0
       defb 3,0,3,0,31,248,56,28,55,236,47,244,47,247,46,119,236,180,236,52,46,116,47,244,48,12,31,248,0,192,0,192
       defb 0,192,0,192,7,254,14,7,13,251,11,253,203,253,203,157,59,45,59,13,11,157,11,253,12,3,7,254,0,48,0,48
       defb 0,48,0,48,129,255,195,129,195,126,66,255,114,255,114,231,78,203,78,195,66,231,66,255,195,0,129,255,0,12,0,12
       defb 0,12,0,12,224,127,112,224,176,223,208,191,220,191,220,185,211,178,211,176,208,185,208,191,48,192,224,127,0,3,0,3
       defb 0,48,0,48,31,248,56,28,247,236,239,244,47,244,44,244,41,116,40,116,44,247,47,247,48,12,31,248,12,0,12,0
       defb 0,12,0,12,7,254,14,7,61,251,59,253,11,253,11,61,10,93,10,29,203,61,203,253,12,3,7,254,3,0,3,0
       defb 0,3,0,3,129,255,195,129,207,126,78,255,66,255,66,207,66,151,66,135,114,207,114,255,195,0,129,255,0,192,0,192
       defb 192,0,192,0,224,127,112,224,179,223,211,191,208,191,208,179,208,165,208,161,220,179,220,191,48,192,224,127,0,48,0,48
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,0,0,0,0,0,0,0,0,0,0,85,85,255,255
       defb 0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,255,255
       defb 0,0,0,0,0,0,0,0,0,0,85,85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,170,255,255
       defb 0,0,56,28,103,230,92,58,91,218,58,92,58,92,60,60,63,252,56,28,59,220,91,218,92,58,103,230,56,28,0,0
       defb 0,0,14,7,153,249,151,14,150,246,14,151,14,151,15,15,15,255,14,7,14,247,150,246,151,14,153,249,14,7,0,0
       defb 0,0,195,129,102,126,165,195,165,189,195,165,195,165,195,195,195,255,195,129,195,189,165,189,165,195,102,126,195,129,0,0
       defb 0,0,112,224,153,159,233,112,105,111,112,233,112,233,240,240,240,255,112,224,112,239,105,111,233,112,153,159,112,224,0,0
       defb 6,0,24,0,7,224,28,58,27,218,59,29,59,29,60,60,63,252,191,252,184,28,91,216,92,56,7,224,0,24,0,96
       defb 1,128,6,0,1,248,135,14,134,246,78,199,78,199,15,15,15,255,47,255,46,7,22,246,23,14,1,248,0,6,0,24
       defb 0,96,1,128,0,126,161,195,161,189,211,177,211,177,195,195,195,255,203,255,203,129,133,189,133,195,0,126,128,1,0,6
       defb 0,24,0,96,128,31,232,112,104,111,116,236,116,236,240,240,240,255,242,255,114,224,97,111,225,112,128,31,96,0,128,1
       defb 1,224,0,0,7,224,28,56,27,216,184,220,184,220,188,61,191,253,63,253,59,221,28,56,31,248,7,224,0,0,7,128
       defb 0,120,0,0,1,248,7,14,6,246,46,55,46,55,111,15,111,255,79,255,78,247,7,14,7,254,1,248,0,0,1,224
       defb 0,30,0,0,0,126,129,195,129,189,203,141,203,141,219,195,219,255,211,255,211,189,129,195,129,255,0,126,0,0,0,120
       defb 128,7,0,0,128,31,224,112,96,111,114,227,114,227,246,240,246,255,244,255,116,239,224,112,224,127,128,31,0,0,0,30
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,222,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,159,247,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,231,253,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,255,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,128,95,222,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,224,151,247,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,248,229,253,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,254,121,127,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,128,79,204,127,222,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,224,19,243,159,247,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,248,196,252,231,253,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,254,49,63,121,255,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0,63,128,79,204,79,214,63,158,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,128,15,224,19,243,147,245,143,231,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,224,3,248,196,252,100,253,227,249,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,56,0,254,49,63,89,63,120,254,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,128,17,128,145,32,72,64,72,204,109,214,127,222,63,140,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,32,4,96,36,72,18,16,18,51,155,117,159,247,15,227,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,8,1,24,9,18,4,132,196,140,102,221,231,253,195,248,255,255
       defb 0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,70,130,68,1,33,49,35,89,183,121,255,48,254,255,255
       defb 0,0,0,0,128,0,0,0,0,64,0,64,0,0,0,12,0,4,0,33,0,17,0,19,128,90,113,158,63,140,255,255
       defb 0,0,0,0,32,0,0,0,0,16,0,16,0,0,0,3,0,1,64,8,64,4,192,4,160,22,156,103,15,227,255,255
       defb 0,0,0,0,8,0,0,0,0,4,0,4,0,0,192,0,64,0,16,2,16,1,48,1,168,5,231,25,195,248,255,255
       defb 0,0,0,0,2,0,0,0,0,1,0,1,0,0,48,0,16,0,132,0,68,0,76,0,106,1,121,198,48,254,255,255
       defb 0,0,0,0,0,0,0,0,0,4,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,19,127,222,255,255
       defb 0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,8,192,4,159,247,255,255
       defb 0,0,0,0,0,0,0,0,64,0,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,48,1,231,253,255,255
       defb 0,0,0,0,0,0,0,0,16,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,76,0,121,255,255,255
       defb 127,254,192,3,160,153,176,77,152,37,172,1,150,65,171,33,181,145,186,201,189,101,158,177,175,89,183,173,192,3,127,254
       defb 159,255,240,0,104,38,108,19,102,9,107,0,101,144,106,200,109,100,110,178,111,89,103,172,107,214,109,235,240,0,159,255
       defb 231,255,60,0,154,9,219,4,89,130,26,192,25,100,26,178,27,89,155,172,91,214,25,235,154,245,219,122,60,0,231,255
       defb 249,255,15,0,102,130,54,193,150,96,6,176,6,89,134,172,70,214,38,235,150,245,198,122,102,189,182,222,15,0,249,255
       defb 0,0,0,0,0,8,0,0,0,8,0,4,0,8,0,4,0,2,0,5,0,2,0,33,0,66,0,36,0,66,0,36
       defb 0,0,0,0,0,2,0,0,0,2,0,1,0,2,0,1,128,0,64,1,128,0,64,8,128,16,0,9,128,16,0,9
       defb 0,0,0,0,128,0,0,0,128,0,64,0,128,0,64,0,32,0,80,0,32,0,16,2,32,4,64,2,32,4,64,2
       defb 0,0,0,0,32,0,0,0,32,0,16,0,32,0,16,0,8,0,20,0,8,0,132,0,8,1,144,0,8,1,144,0
       defb 0,0,0,0,0,2,0,0,0,2,0,4,0,2,0,4,0,10,0,84,0,8,0,84,0,136,0,68,0,34,0,68
       defb 0,0,0,0,128,0,0,0,128,0,0,1,128,0,0,1,128,2,0,21,0,2,0,21,0,34,0,17,128,8,0,17
       defb 0,0,0,0,32,0,0,0,32,0,64,0,32,0,64,0,160,0,64,5,128,0,64,5,128,8,64,4,32,2,64,4
       defb 0,0,0,0,8,0,0,0,8,0,16,0,8,0,16,0,40,0,80,1,32,0,80,1,32,2,16,1,136,0,16,1
       defb 3,128,3,128,1,128,3,128,3,128,3,128,3,0,3,0,3,128,3,128,3,128,3,128,1,128,3,128,3,128,3,128
       defb 0,224,0,224,0,96,0,224,0,224,0,224,0,192,0,192,0,224,0,224,0,224,0,224,0,96,0,224,0,224,0,224
       defb 0,56,0,56,0,24,0,56,0,56,0,56,0,48,0,48,0,56,0,56,0,56,0,56,0,24,0,56,0,56,0,56
       defb 0,14,0,14,0,6,0,14,0,14,0,14,0,12,0,12,0,14,0,14,0,14,0,14,0,6,0,14,0,14,0,14
       defb 7,224,7,224,7,224,3,224,3,224,7,224,7,224,7,224,7,224,7,224,7,224,7,224,7,224,7,192,7,224,7,224
       defb 1,248,1,248,1,248,0,248,0,248,1,248,1,248,1,248,1,248,1,248,1,248,1,248,1,248,1,240,1,248,1,248
       defb 0,126,0,126,0,126,0,62,0,62,0,126,0,126,0,126,0,126,0,126,0,126,0,126,0,126,0,124,0,126,0,126
       defb 128,31,128,31,128,31,128,15,128,15,128,31,128,31,128,31,128,31,128,31,128,31,128,31,128,31,0,31,128,31,128,31
       defb 31,248,31,240,31,240,31,248,31,248,15,248,31,248,31,248,31,248,31,240,31,248,31,248,15,248,15,248,31,248,31,248
       defb 7,254,7,252,7,252,7,254,7,254,3,254,7,254,7,254,7,254,7,252,7,254,7,254,3,254,3,254,7,254,7,254
       defb 129,255,1,255,1,255,129,255,129,255,128,255,129,255,129,255,129,255,1,255,129,255,129,255,128,255,128,255,129,255,129,255
       defb 224,127,192,127,192,127,224,127,224,127,224,63,224,127,224,127,224,127,192,127,224,127,224,127,224,63,224,63,224,127,224,127
frmlst equ $
       defb 0,4
       defb 4,4
       defb 8,4
       defb 12,3
       defb 15,3
       defb 18,4
       defb 22,3
       defb 25,8
       defb 33,1
       defb 34,2
       defb 36,3,39,0
scdat  equ $
       defw 425,471,436,372,323,381,312,298,276,343,255,305,230,299,292,268,350,320,349,203,222,352,366,303,202,225
       defw 236,382
       defb 2,2,1,1,1,3,1,3,3,2,255,1,4,2,2,1,1,6,2,1,1,1,2,1,3,3,2,1,14,16,16,15,1
       defb 255,3,4,1,14,16,16,0,16,0,16,255,0,5,15,1,2,8,3,2,0,17,16,0,15,2,3,1,14,16,0,17,16
       defb 74,16,0,75,255,0,6,16,15,1,3,0,0,0,17,0,0,15,1,14,0,75,0,0,16,0,17,255,0,7,74,16,76
       defb 2,2,255,0,7,16,255,0,5,17,255,0,10,17,0,1,3,255,13,4,0,0,0,16,76,255,0,17,1,1,1,14,255,0,4
       defb 74,16,255,0,18,2,1,1,255,0,6,17,255,0,8,13,13,255,0,7,4,24,25,1,255,0,8,13,13,13,21,22,0,0
       defb 2,1,16,255,0,7,28,28,1,255,0,8,17,0,0,21,22,0,0,1,3,2,0,0,0,19,19,0,0,28,28,1,13,13,13
       defb 255,0,8,21,22,0,0,1,3,1,0,0,0,13,13,13,4,24,25,3,8,1,1,13,13,255,0,6,21,22,0,0,2
       defb 3,1,255,0,5,16,15,7,3,2,14,17,16,255,0,8,21,22,0,13,1,3,1,255,0,5,17,0,15,1,1,0,0
       defb 17,255,0,5,255,13,6,2,1,3,2,255,0,8,1,1,255,0,8,15,1,2,5,1,2,1,3,1,14,255,0,8,1
       defb 2,255,0,10,6,1,24,25,18,6,18,9,10,255,0,7,2,1,255,0,5,13,13,13,6,0,15,2,77,78,1,14,0,0
       defb 11,255,0,4,19,19,0,1,1,255,0,4,13,7,2,1,13,54,54,2,77,78,2,18,10,0,11,255,0,4,19,19,13
       defb 1,1,0,13,13,13,1,2,3,3,2,54,54,2,24,25,1,0,11,0,11,255,0,4,13,13,5,3,1,13,1,2,1
       defb 3,3,3,2,2,0,0,1,77,78,1,0,11,0,11,0,0,13,13,1,3,3,1
       defb 255,3,5,1,3,1,1,17,0,0,1,77,78,2,0,11,0,11,0,0,6,1,1,8,255,3,4,1,23,23,3,3,3
       defb 2,16,76,17,2,24,25,1,0,12,18,11,0,0,0,2,1,3,23,23,1,3,3,3,23,23,23,3,1,16,75,1,3
       defb 12,10,1,0,0,0,11,0,0,0,2,3,23,23,0,1,2,1,1,23,0,23,1,3,1,16,2,3,3,11,14,0,0,0
       defb 11,0,0,0,1,3,23,255,0,4,15,1,2,23,23,23,3,1,2,2,3,1,11,255,0,4,11,13,13,13,2,3,23,23
       defb 255,0,4,17,1,3,3,23,2,3,3,1,3,1,12,9,9,9,18,13,2,1,1,3,23,23,255,0,6,15,1,255,3,6
       defb 7,2,255,0,5,1,1,3,3,23,0,0,23,255,0,6,19,19,3,3,3,1,1,1,14,255,0,5,2,3,3,23,0
       defb 54,54,255,0,9,1,1,1,14,17,16,76,255,0,5,1,3,23,0,23,54,54,23,0,255,13,5,8,1,1,0,16,0,0
       defb 16,255,0,6,2,3,23,0,0,23,23,3,23,1,2,2,2,1,1,2,0,0,16,0,0,17,255,0,5,17,1,1,23,23,23
       defb 3,3,1,3,3,2,1,1,14,16,16,76,0,17,255,0,6,13,13,13,1,3,3,23,3,1,255,3,4,1,1,14,74
       defb 16,75,255,0,9,15,1,2,1,3,1,3,1,1,2,1,2,3,6,1,0,0,17,255,0,4,13,13,13,255,0,4,11
       defb 7,1,2,1,1,0,17,11,0,0,1,2,14,255,0,7,2,1,1,255,0,4,12,9,26,24,25,26,9,18,11,18,9
       defb 255,0,8,13,13,1,5,2,13,17,255,0,5,29,29,0,0,0,11,255,0,9,17,2,1,2,3,3,1,13,13,19,19
       defb 0,0,29,29,0,0,0,11,255,0,8,13,13,1,255,3,5,2,1,13,13,13,26,24,25,26,255,13,11,2,1,1,255,3,6
       defb 7,255,1,4,2,2,255,1,5,2,1,2,2,1,2,1,1,3,3,6,255,3,6,2,255,3,4,1,3,3,3,2,1
       defb 3
       defb 255,0,5,23,3,3,2,1,1,21,22,1,1,2,1,1,21,22,1,1,1,2,3,23,5,23,255,0,4,23,23,3,1
       defb 14,0,0,21,22,15,14,16,15,1,21,22,17,16,15,1,1,3,23,3,255,0,4,23,3,3,1,0,0,0,21,22,0
       defb 74,16,0,2,21,22,0,16,76,15,2,1,3,1,255,0,5,23,3,2,0,0,0,21,22,0,0,17,0,1,21,22,74
       defb 16,0,0,16,15,1,2,255,0,4,23,23,1,14,0,0,0,21,22,255,0,4,8,21,22,0,17,0,0,17,0,16,255,0,5
       defb 23,3,1,75,0,0,0,21,22,255,0,4,2,21,22,255,0,6,75,255,0,4,23,3,3,2,1,0,0,0,21,22,255,0,4
       defb 1,21,22,255,0,12,23,3,1,14,0,0,0,21,22,255,0,4,1,13,13,17,255,0,11,23,3,1,17,0,0,0,21
       defb 22,255,0,5,2,1,13,13,255,0,9,23,23,3,8,1,13,21,22,13,13,255,0,5,16,1,1,2,255,13,6,0,0,0
       defb 23,3,3,3,2,1,21,22,16,76,255,0,5,16,15,1,7,1,2,1,1,2,1,255,0,4,23,3,1,1,14,21,22
       defb 17,255,0,6,17,0,0,1,3,3,1,3,3,3,255,0,4,23,3,1,14,0,21,22,255,0,10,15,1,1,23,23,23
       defb 3,0,0,0,23,3,3,2,0,0,21,22,255,0,12,15,5,3,1,3,255,0,4,23,3,1,17,0,21,22,255,0,13
       defb 15,1,1,1,255,0,4,23,3,1,16,0,21,22,255,0,21,23,3,1,2,0,21,22,0,38,38,255,0,4,38,38,255,0,11
       defb 23,23,3,7,1,17,21,22,31,38,38,31,0,0,0,38,38,31,31,255,0,9,23,3,23,3,1,13,13,13,255,20,4
       defb 13,13,13,255,20,4,255,13,6,255,0,4,23,23,3,3,1,2,255,1,5,2,1,1,8,255,1,4,2,7,1,2,1
       defb 23,3,1,1,3,1,3,3,1,2,2,1,1,2,1,1,7,1,1,255,3,4,1,2,1,1,3,23,1,1,16,1,3,3
       defb 1,1,14,0,16,0,0,16,76,0,0,0,1,2,1,8,1,14,15,2,1,3,2,14,16,15,2,1,14,0,0,74,16
       defb 0,0,17,255,0,4,16,15,1,17,16,76,0,15,1,1,1,0,16,76,16,255,0,5,75,255,0,7,17,0,1,0,17
       defb 255,0,4,1,14,74,16,0,17,255,0,15,1,255,0,6,1,0,0,17,255,0,17,2,1,21,22,13,13,13,1,255,0,13
       defb 13,13,13,255,0,6,21,22,15,2,3,2,255,0,13,7,1,1,255,0,6,21,22,0,1,7,1,255,0,6,13,13,13
       defb 255,0,4,1,3,1,255,0,6,21,22,0,15,1,1,255,0,13,1,3,8,255,0,6,21,22,0,0,1,1,13,13,255,0,11
       defb 2,3,1,255,0,6,21,22,0,0,1,1,14,255,0,12,1,3,1,255,0,8,13,13,1,2,255,0,13,1,1,1,255,0,9
       defb 15,2,7,255,13,6,255,0,7,1,2,1,13,13,255,0,8,1,1,17,6,0,0,6,255,0,8,1,3,2,14,255,0,9
       defb 1,1,13,255,0,9,13,13,13,1,3,1,255,0,7,13,13,13,2,3,8,13,255,0,10,15,8,1,1,255,0,9,15
       defb 1,23,3,1,13,17,255,0,9,1,3,2,17,255,0,8,17,1,0,23,3,1,255,13,4,255,0,5,17,1,3,1,16
       defb 0,0,0,17,255,13,5,1,0,23,23,3,1,5,1,2,13,13,13,21,22,13,1,23,3,13,21,22,13,13,255,1,4
       defb 2,1
       defb 255,0,7,3,1,21,22,1,3,23,255,0,21,3,1,21,22,1,3,23,255,0,20,23,3,1,21,0,2,3,3,23,255,0,18
       defb 23,3,1,14,0,0,15,1,2,1,3,23,23,255,0,14,23,3,1,1,255,0,4,74,16,15,2,1,7,3,3,23,255,0,8
       defb 23,23,3,2,1,2,14,255,0,5,16,76,0,15,1,2,1,1,3,23,23,0,23,0,0,3,1,1,2,14,16,0,0,0
       defb 19,19,0,0,17,255,0,4,16,15,1,2,1,1,3,3,23,23,1,14,0,17,0,17,0,0,0,13,13,255,0,7,17
       defb 0,0,0,15,1,1,2,2,1,255,0,42,13,13,255,0,12,255,13,8,17,255,0,19,3,5,1,1,2,1,1,2,13,13
       defb 255,0,18,23,255,3,7,5,2,13,13,13,0,0,0,21,22,255,13,10,255,0,4,23,0,0,23,23,3,3,3,2,0,0,0
       defb 21,22,255,1,5,2,1,1,2,1,255,0,9,23,23,3,1,0,0,0,21,22,2,3,3,3,23,3,3,23,23,3,255,0,10
       defb 23,3,1,0,0,0,21,22,1,3,23,23,0,0,23,0,0,23,255,0,11,3,2,13,13,0,21,22,1,8,23,255,0,8
       defb 54,54,255,0,7,23,3,1,14,0,0,21,22,1,3,255,0,9,54,54,255,0,8,3,1,0,0,0,21,22,2,3,23
       defb 255,0,18,3,1,21,22,13,13,13,1,3,255,0,8
       defb 255,0,10,23,3,1,21,22,1,1,1,3,3,23,23,0,0,3,3,23,3,255,0,11,3,1,21,22,0,15,255,1,5
       defb 8,255,1,5,18,9,9,10,255,0,7,23,1,21,22,0,0,0,16,17,255,0,4,16,76,255,0,5,11,255,0,7,23
       defb 1,21,22,0,0,0,17,255,0,5,17,255,0,6,11,255,0,8,1,21,22,255,0,16,11,255,0,7,23,1,13,13,19,19
       defb 17,255,0,7,17,255,0,5,11,255,0,7,23,3,1,1,255,13,6,0,255,13,6,0,0,0,11,255,0,9,23,3,1,1
       defb 7,1,1,16,0,15,1,1,3,3,1,0,0,0,12,255,9,5,10,255,0,6,23,23,3,1,17,0,75,1,3,255,23,4
       defb 255,0,8,11,0,0,23,255,0,5,1,17,40,39,16,17,1,23,0,0,23,23,0,23,0,0,23,23,3,11,24,25,1
       defb 3,0,23,0,23,1,16,40,40,16,16,1,0,0,0,255,3,4,2,1,1,3,1,12,77,78,15,1,3,0,0,0,3
       defb 1,13,13,1,1,3,0,0,0,1,2,1,1,14,16,16,1,14,17,24,25,0,16,1,255,0,4,23,3,3,23,23,255,0,5
       defb 16,0,0,74,16,17,0,0,0,38,38,0,17,1,23,255,0,12,18,17,18,10,0,17,255,0,4,38,38,0,0,2,23
       defb 255,0,15,11,255,0,6,34,35,0,0,1,23,255,0,15,11,0,0,0,19,19,37,32,33,36,0,7,255,0,13,255,13,14
       defb 23,23,255,0,9,54,54,0,2,1,1,3,3,1,5,2,1,3,1,1,3,0,23,255,0,10,54,54,0,23,23,3,3
       defb 23,0,23,23,3,23,23,0,23,255,0,15
       defb 0,0,0,23,3,1,0,0,45,255,0,7,8,255,5,5,8,255,0,8,3,1,14,255,0,12,43,6,42,255,0,6,45
       defb 0,0,0,3,1,75,255,0,4,46,255,0,8,5,0,46,255,0,10,8,1,255,0,25,23,3,1,19,19,255,0,11,5
       defb 255,0,8,23,23,0,23,3,1,255,5,4,8,0,46,255,0,15,3,3,23,3,1,14,0,0,0,43,5,255,0,8,7
       defb 255,0,8,255,1,4,14,0,0,0,45,0,5,255,0,18,16,15,14,0,0,0,46,0,0,5,255,0,18,17,255,0,8
       defb 5,5,7,255,0,13,46,255,0,11,5,42,255,0,26,5,45,255,0,7,7,5,5,5,255,0,5,255,13,4,5,5,7
       defb 0,0,0,7,255,0,5,7,5,5,42,0,43,7,255,0,5,1,2,1,255,0,17,41,19,8,8,255,0,4,3,7,1
       defb 255,0,17,41,41,7,42,255,0,4,23,3,3,13,0,0,7,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,5
       defb 0,0,0,17,0,0,23,3,1,0,0,38,38,255,0,12,38,38,0,0,17,1,1,2,0,0,3,2,31,31,38,38,255,31,12
       defb 38,38,31,31,2,2,7,3,0,3,3,1,255,20,20,1,3,23,23,0,23,3,1,1,1,2,1,2,1,1,2,255,1,4
       defb 2,1,1,5,1,1,1,2,1,3,23,0
       defb 3,23,3,23,23,3,3,23,23,3,23,255,0,8,23,3,3,23,23,3,8,3,23,1,1,2,2,1,8,1,1,1,2
       defb 1,3,23,255,0,4,23,3,255,1,4,2,1,1,2,1,0,16,0,17,0,0,0,16,76,0,15,1,3,255,0,4,3
       defb 2,14,16,0,0,74,16,17,15,1,0,17,255,0,5,17,0,0,0,15,1,23,0,0,0,1,14,0,75,0,0,0,17
       defb 0,0,1,255,0,11,17,1,3,23,0,23,1,0,40,40,255,0,7,17,255,0,8,38,0,13,1,23,0,0,0,1,17
       defb 255,0,7,17,0,255,13,5,0,0,255,13,4,1,3,255,0,4,23,1,13,13,0,0,255,13,5,1,1,2,1,1,0,0
       defb 2,1,3,1,3,23,255,0,5,3,7,2,0,0,1,1,2,3,1,3,23,3,3,2,0,0,1,3,23,23,255,0,8
       defb 23,1,0,0,2,3,3,23,3,0,0,23,3,1,0,0,1,3,255,0,11,1,0,0,1,3,23,255,0,5,1,2,0,0
       defb 1,23,255,0,11,2,0,0,1,23,255,0,6,23,1,0,0,1,3,255,0,10,23,3,1,1,3,23,255,0,6,5,1
       defb 0,0,1,23,255,0,11,23,3,0,23,255,0,6,23,3,1,1,2,3,0,23,255,0,21,23,3,3,23,255,0,161
       defb 0,0,0,45,255,0,10,44,255,0,8,7,5,21,22,5,255,0,25,21,22,255,0,12,46,255,0,10,45,0,0,21,22
       defb 8,255,0,25,21,22,255,0,28,5,255,0,16,46,255,0,38,7,255,0,5,46,255,0,13,7,5,5,7,255,0,14,8
       defb 5,5,8,255,0,6,12,10,255,0,6,5,255,0,10,11,255,0,9,11,255,0,4,46,255,0,12,11,255,0,9,11,255,0,6
       defb 255,5,5,7,255,0,5,11,255,0,9,11,0,0,53,255,0,7,12,255,9,5,18,12,10,255,0,5,45,0,0,11,255,0,6
       defb 8,255,0,9,45,0,11,255,0,6,46,0,11,255,0,10,17,255,0,7,11,255,0,8,11,0,0,53,0,0,0,7,0,0,0
       defb 16,255,0,7,11,255,0,8,11,255,0,7,255,13,5,17,0,0,7,255,5,5,7,255,0,5,11,255,0,6,5,1,1
       defb 2,1,1,13,21,22,5,42,0,11,0,43,5,255,0,5,11,0,0,53,255,0,4,3,23,23,3,1,2,21,22,5,0,0
       defb 12,9,9,5,18,9,9,10,0,11,255,0,6,6,0,0,0,23,3,1,21,22,8,255,0,5,8,21,22,7,5,5,5
       defb 7,255,0,5,5
       defb 23,23,3,23,3,1,21,22,8,5,0,5,0,5,7,21,22,7,255,0,9,8,3,2,1,1,2,14,21,22,255,0,5
       defb 43,5,21,22,255,0,11,2,1,14,16,0,0,21,22,255,0,6,5,21,22,255,0,5,45,255,0,4,5,1,2,0,17
       defb 0,43,7,5,0,5,0,5,5,5,8,21,22,255,0,7,46,0,0,0,7,6,255,0,10,46,43,5,21,22,255,0,10
       defb 5,8,5,0,0,0,19,19,255,0,7,5,21,22,0,45,255,0,9,255,13,7,255,0,8,21,22,255,0,9,45,5,255,1,5
       defb 2,5,5,5,7,255,0,4,5,0,22,255,0,11,3,23,3,23,3,1,14,255,0,20,5,0,0,0,23,3,1,0,0
       defb 45,255,0,5,5,255,0,5,7,5,0,0,0,21,22,255,0,5,3,2,0,46,255,0,5,5,7,255,0,10,21,22,5
       defb 0,0,0,23,1,14,255,0,6,5,42,255,0,7,46,0,0,0,21,22,255,0,4,3,1,255,0,20,21,22,5,0,0
       defb 23,1,14,255,0,10,45,255,0,9,21,0,0,0,23,3,2,17,255,0,4,8,255,0,17,5,0,0,3,1,16,76,255,0,24
       defb 23,1,13,0,0,0,38,38,0,0,7,0,5,0,5,0,5,0,5,7,38,38,0,0,0,5,0,54,54,1,1,31,31,31
       defb 38,38,255,31,12,38,38,31,31,31,5,0,54,54,3,2,255,20,22,13,0,0,0,23,3,2,255,1,7,2,255,1,6
       defb 2,2,1,1,1,2,1,1
       defb 255,44,28,255,0,33,46,255,0,26,45,255,0,7,19,19,255,0,10,46,0,0,0,8,7,5,5,0,8,0,5,8,0
       defb 5,0,7,5,0,6,0,8,5,0,5,0,7,5,0,5,0,8,43,54,54,42,255,0,11,39,38,255,0,10,44,0,54,54
       defb 255,0,11,45,40,40,255,0,10,17,255,0,24,45,0,0,13,255,0,13,11,255,0,13,1,255,0,8,46,255,0,4,11
       defb 0,0,0,45,255,0,5,46,0,0,0,1,255,0,13,11,255,0,13,1,255,0,13,11,255,0,13,1,255,0,12,11,11
       defb 255,0,13,8,255,0,12,11,11,255,0,13,1,255,0,12,11,12,10,255,0,11,75,2,0,0,0,17,255,0,8,12,18
       defb 11,10,255,0,9,74,16,1,0,0,0,16,76,255,0,9,11,11,0,0,0,17,255,0,5,17,1,3,255,13,9,21,22
       defb 13,13,13,24,25,255,13,10,1,3,1,2,1,1,1,5,1,1,1,21,22,2,1,1,77,78,1,2,1,1,7,1,1
       defb 2,2,1,3,3,255,0,4,23,0,23,3,2,21,22,2,3,23,32,33,255,0,12
       defb 14,255,0,9,6,21,22,5,44,44,44,24,77,78,25,255,44,7,255,0,5,46,0,54,54,54,5,21,22,255,0,4,27
       defb 24,25,27,0,0,0,45,255,0,5,45,255,0,4,54,54,54,5,21,22,255,0,5,30,30,255,0,15,54,54,54,7,21
       defb 22,255,0,5,30,30,0,0,19,19,255,0,14,43,5,5,7,0,0,7,27,24,25,27,7,5,5,7,5,8,5,255,0,7
       defb 45,0,0,0,43,0,42,0,0,43,0,77,78,0,42,43,0,42,43,0,42,255,0,6,46,255,0,11,77,78,255,0,26
       defb 24,25,0,0,45,255,0,18,46,0,0,0,37,32,33,36,255,0,4,46,255,0,17,44,0,0,38,38,255,0,16,75,255,0,9
       defb 38,38,255,0,16,16,76,255,0,8,38,38,255,0,15,74,16,255,0,9,38,38,255,0,15,17,16,255,0,9,38,38,255,0,15
       defb 16,16,76,255,0,8,38,38,0,0,17,255,0,12,16,16,0,17,255,0,7,38,38,0,0,16,76,255,0,10,17,13,13
       defb 17,16,255,0,7,38,38,0,17,16,255,0,5,255,13,7,1,1,255,13,8,66,67,67,65,255,13,7,1,1,1,3,1
       defb 7,1,14,15,1,3,1,1,1,2,1,2,1,66,65,255,1,7,2,0,0,23,255,0,6,23,23,255,0,6,23,0,23
       defb 255,0,8
       defb 255,44,4,15,255,1,4,2,1,14,0,44,0,15,2,1,3,23,0,0,0,23,23,3,3,1,255,0,6,15,14,0,16
       defb 17,255,0,6,16,1,3,3,23,3,3,1,1,2,14,255,0,9,75,0,46,255,0,5,17,15,1,2,1,1,2,14,16,16
       defb 255,0,4,46,255,0,16,17,16,45,0,0,17,16,76,255,0,5,46,255,0,15,17,255,0,4,75,255,0,25,46,255,0,12
       defb 45,255,0,12,45,255,0,26,45,255,0,23,46,255,0,11,45,255,0,89,75,255,0,27,17,255,0,26,74,16,17,255,0,4
       defb 13,255,0,21,16,16,76,0,38,38,5,38,38,255,0,16,17,0,0,13,13,31,31,38,38,5,38,38,31,31,13,13,255,0,4
       defb 17,0,0,0,255,13,7,1,1,255,20,4,5,255,20,4,1,2,255,13,8,1,1,1,3,1,7,1,14,15,1,3,1,1
       defb 6,2,1,2,1,3,8,255,1,7,2,0,0,23,255,0,6,23,23,255,0,8,23,255,0,8
       defb 44,44,21,22,0,255,44,4,255,0,4,44,255,0,13,44,0,0,21,22,255,0,26,21,22,255,0,7,46,255,0,18,21
       defb 22,255,0,18,45,0,40,19,255,0,4,21,22,0,46,255,0,18,40,19,255,0,4,21,22,255,0,19,59,57,57,57,58
       defb 59,57,58,59,58,255,0,4,45,255,0,12,45,0,54,54,54,0,0,59,57,58,255,0,17,45,0,0,54,54,54,255,0,12
       defb 51,24,25,49,0,0,46,255,0,11,45,255,0,8,51,48,48,48,50,49,255,0,21,51,50,50,255,48,4,49,255,0,19
       defb 51,48,48,50,255,48,5,49,255,0,17,51,255,47,9,48,49,255,0,15,51,48,255,47,9,50,48,49,255,0,7,17,255,0,5
       defb 51,48,48,47,47,47,48,48,48,50,255,47,5,49,255,0,5,74,16,0,17,0,0,51,50,50,48,48,47,47,47,42,43
       defb 48,255,47,6,49,255,0,5,16,0,16,0,51,48,48,50,48,48,47,47,47,0,0,50,48,48,48,50,48,48,48,49,0
       defb 17,0,0,16,255,13,10,50,50,5,5,50,50,255,13,12,1,1,1,3,1,7,1,2,1,1,3,50,52,52,50,1,2
       defb 1,3,2,1,7,1,1,8,1,1,2,0,0,23,255,0,6,23,1,50,52,52,50,2,23,0,0,23,23,255,0,7
       defb 13,255,44,27,1,17,255,0,7,59,57,57,58,255,0,15,1,16,75,255,0,25,1,16,16,76,255,0,18,45,255,0,5
       defb 2,13,13,17,255,0,24,1,2,1,13,61,255,0,19,46,0,0,0,3,23,3,1,13,255,0,4,45,255,0,10,59,57
       defb 58,0,0,59,57,58,23,0,23,3,1,255,0,11,59,58,0,0,0,45,255,0,8,3,1,255,0,6,40,39,0,0,59
       defb 57,58,46,255,0,12,23,1,255,0,6,40,40,255,0,19,2,255,0,6,17,255,0,20,1,17,255,0,4,74,16,255,0,20
       defb 3,13,255,0,5,16,76,255,0,5,75,255,0,13,3,1,255,0,4,17,16,0,0,17,0,0,74,16,255,0,5,17,255,0,7
       defb 23,2,0,0,0,74,16,16,76,0,16,76,0,0,16,76,17,0,0,0,16,0,75,255,0,5,23,1,0,0,17,0,16,16
       defb 0,17,16,0,0,17,16,0,16,0,0,74,16,17,16,255,0,5,3,2,13,61,16,0,16,16,0,16,16,19,61,16,16
       defb 0,16,0,0,61,16,16,16,76,0,0,54,54,23,3,1,255,13,22,0,54,54,0,23,7,255,1,4,3,1,1,1,2
       defb 1,2,1,3,1,1,1,8,255,1,4,2,255,0,9,23,23,255,0,8,23,255,0,8
       defb 255,0,11,50,52,52,50,255,0,24,50,52,52,50,23,255,0,22,23,50,52,52,48,23,23,255,0,19,50,50,50,48,52,52
       defb 255,50,4,255,0,17,23,50,255,0,8,50,255,0,18,50,255,0,8,50,23,255,0,17,48,50,50,50,52,52,50,50,50
       defb 48,255,0,19,23,23,50,52,52,50,23,255,0,6,23,255,0,16,48,52,52,50,255,0,4,23,0,23,23,23,255,0,14
       defb 23,50,52,52,48,0,0,255,50,4,48,255,50,4,255,0,13,50,52,52,50,23,0,50,255,0,4,39,39,17,50,255,0,13
       defb 50,52,52,50,0,0,50,255,0,4,39,39,0,48,23,255,0,9,255,50,4,52,52,50,23,23,48,0,0,255,50,4,48,48
       defb 255,0,9,23,50,0,0,0,52,52,50,48,50,50,0,0,50,23,23,255,0,12,23,48,0,0,0,52,52,255,0,6,50
       defb 23,255,0,14,50,19,19,0,52,52,255,0,6,48,255,0,15,255,50,4,52,52,0,0,17,255,50,4,255,0,8,54,54
       defb 255,0,8,48,52,52,255,50,4,255,0,11,54,54,255,0,7,23,50,52,52,50,255,0,23,50,50,52,52,50,48,255,0,12
       defb 255,0,11,50,52,52,50,23,255,0,21,23,48,50,52,52,50,48,255,0,20,23,48,50,0,52,52,0,50,48,23,255,0,14
       defb 23,0,23,23,48,50,0,0,52,52,0,0,50,48,23,0,0,0,23,255,0,8,255,50,4,48,50,0,0,0,52,52,0,0,0
       defb 255,50,4,48,50,50,50,255,0,6,50,255,0,20,50,255,0,6,48,255,0,20,50,255,0,5,23,50,52,52,50,48,255,50,7
       defb 48,50,48,255,50,4,52,52,48,23,255,0,5,50,52,52,50,50,50,48,50,42,255,0,4,43,50,50,48,48,50,52,52
       defb 50,255,0,6,50,255,0,8,44,39,38,44,255,0,8,48,255,0,6,50,255,0,8,51,39,38,49,255,0,8,50,23,255,0,5
       defb 50,52,52,50,48,50,50,42,0,255,50,4,0,43,48,50,50,50,52,52,50,23,255,0,5,50,52,52,50,42,255,0,12
       defb 43,50,52,52,50,255,0,5,23,48,52,52,255,0,16,52,52,50,255,0,6,50,52,52,255,0,5,51,0,38,38,0,49
       defb 255,0,5,52,52,50,255,0,5,23,50,52,52,255,0,5,50,31,38,38,31,50,255,0,5,52,52,48,255,0,6,50,52,52
       defb 255,0,5,50,255,20,4,50,17,0,38,38,0,52,52,50,255,0,4,54,54,48,52,52,0,0,19,19,0,50,255,68,4
       defb 50,16,76,0,0,0,52,52,50,23,0,0,0,54,54,255,50,4,48,255,50,7,48,50,50,50,48,48,255,50,4,255,0,13
       defb 23,0,23,255,0,6,23,23,255,0,7
       defb 255,44,28,0,0,0,45,255,0,5,46,255,0,15,45,0,46,255,0,27,44,255,0,18,7,5,5,5,57,58,0,0,46
       defb 44,7,5,5,7,0,6,0,0,8,5,5,7,0,0,5,7,255,0,5,8,255,0,5,44,5,0,0,45,255,0,5,54,54
       defb 255,0,6,45,255,0,7,59,57,57,5,38,38,0,0,5,0,0,5,54,54,5,0,0,5,255,0,12,44,5,38,38,0
       defb 59,58,255,0,14,59,7,255,0,5,44,8,57,58,0,0,5,0,0,5,45,0,5,0,0,5,255,0,6,5,57,58,0,0
       defb 46,44,5,255,0,4,8,5,5,8,0,0,8,5,5,7,255,0,6,5,45,255,0,4,44,7,59,58,255,0,8,45,0,0,0
       defb 59,57,58,0,0,0,7,0,0,0,59,57,57,255,0,27,44,255,0,27,44,7,57,58,255,0,4,59,57,57,58,0,0,0
       defb 59,57,57,58,59,57,57,7,57,58,0,0,0,44,5,0,45,255,0,7,46,255,0,11,46,255,0,4,44,5,255,0,5
       defb 59,57,58,255,0,8,59,58,0,0,5,0,0,59,57,57,58,6,255,0,14,46,255,0,11,44,5,17,0,59,58,255,0,16
       defb 8,255,0,5,44,5,16,17,255,0,13,19,19,255,0,4,17,0,0,21,22,44,5,5,8,0,8,0,5,0,5,0,8
       defb 0,8,0,8,0,5,0,7,0,7,5,5,5,7,21,22,8
       defb 255,44,11,24,25,24,25,24,25,255,44,11,0,0,45,255,0,4,46,0,0,0,255,47,6,0,0,45,46,0,0,0,45
       defb 255,0,14,255,47,6,255,0,22,255,47,6,255,0,11,8,5,5,7,255,0,4,45,38,38,24,25,24,25,24,25,38,38
       defb 255,0,5,7,5,8,5,7,42,0,43,5,7,0,0,31,38,38,43,42,43,42,43,42,38,38,31,0,0,7,5,42,0
       defb 46,5,75,0,0,45,0,43,8,5,255,20,12,5,5,42,0,0,45,0,5,13,0,0,0,46,0,43,255,5,14,42,255,0,5
       defb 8,1,13,255,0,25,5,3,2,255,0,25,5,23,1,17,5,5,21,22,5,7,0,0,0,8,5,5,7,0,0,0,7
       defb 5,5,7,21,22,7,5,8,23,1,16,76,0,21,22,43,5,0,0,0,5,42,43,5,0,0,0,5,42,43,5,21,22
       defb 0,0,0,3,1,13,0,0,21,22,0,43,5,0,5,42,0,0,43,5,0,5,42,0,0,5,21,22,0,0,0,1,14
       defb 0,0,0,21,22,255,0,15,255,5,5,7,1,17,0,0,0,21,22,255,0,20,5,1,255,13,4,5,0,6,0,5,255,0,17
       defb 7,3,1,1,1,2,17,0,0,0,43,5,0,5,0,7,0,5,0,5,0,7,0,5,0,8,21,22,5,0,23,3,3
       defb 1,13,255,0,19,21,22,5,0,0,0,23,3,2,255,0,19,21,22,6,0,0,23,23,3,1,0,5,0,53,0,7,0
       defb 5,0,8,0,7,0,5,0,5,0,8,0,5,0,5
       defb 255,44,16,0,0,0,255,44,10,54,54,255,0,9,46,255,0,14,44,44,54,54,45,255,0,20,46,0,0,44,44,255,0,15
       defb 59,57,58,255,0,6,45,0,44,44,255,0,18,46,255,0,7,44,44,255,0,20,59,58,255,0,4,44,44,255,0,6,59
       defb 57,57,58,255,0,16,44,44,38,38,255,0,24,44,44,38,38,255,0,21,59,57,58,44,44,255,0,6,45,255,0,6,59
       defb 58,255,0,11,44,44,255,0,26,44,44,255,0,17,45,255,0,5,59,58,0,44,44,255,0,8,59,57,58,255,0,15,44,44
       defb 46,255,0,25,44,44,255,0,21,59,58,0,0,0,44,44,255,0,12,59,57,57,58,255,0,10,44,44,255,0,5,59,57
       defb 58,0,46,255,0,14,45,0,44,44,255,0,26,44,59,58,21,22,255,0,8,53,255,0,14,44,44,59,21,22,57,58,255,0,21
       defb 44
       defb 255,44,15,255,0,12,44,44,255,0,6,46,255,0,16,54,54,54,44,44,0,0,40,39,255,0,11,45,255,0,7,54,54,54
       defb 44,44,0,0,38,41,255,0,22,44,44,59,57,57,57,58,255,0,21,44,44,255,0,24,46,0,44,44,255,0,6,45,0,0,0
       defb 59,58,255,0,7,45,255,0,6,44,44,255,0,26,44,44,255,0,20,19,19,255,0,4,44,44,0,0,45,255,0,10,59
       defb 58,255,0,4,59,57,57,58,0,0,0,44,44,255,0,26,44,44,255,0,26,44,44,255,0,5,46,255,0,4,59,58,255,0,10
       defb 45,0,0,0,44,44,255,0,26,44,44,0,0,0,59,57,57,58,255,0,19,44,44,255,0,26,44,44,0,0,46,255,0,9
       defb 59,57,57,58,255,0,4,45,255,0,5,44,44,255,0,26,44,44,255,0,8,53,0,0,53,255,0,9,53,0,0,53,0
       defb 44,59,57,57,58,59,57,58,255,0,9,59,57,58,255,0,8,44
       defb 255,44,11,23,3,2,68,62,2,3,23,255,44,10,54,54,41,41,44,255,41,6,64,63,62,42,255,41,9,54,54,44,44
       defb 54,54,255,41,8,64,63,62,42,255,41,10,54,54,44,44,44,255,41,8,64,63,1,3,23,255,44,6,41,41,41,255,44,5
       defb 255,41,8,64,3,1,44,0,0,44,255,41,8,44,0,0,44,44,255,41,4,44,44,44,23,23,44,255,0,4,44,255,41,8
       defb 44,0,0,44,44,255,41,4,44,255,0,9,44,41,41,41,255,44,6,0,0,44,44,41,41,41,44,44,255,0,9,44,41,41,41
       defb 44,255,0,7,44,44,255,41,4,44,0,255,44,9,41,41,41,44,23,44,23,23,3,1,1,2,44,255,41,4,44,0,66
       defb 41,38,38,255,41,12,64,63,62,62,62,44,44,41,41,41,44,0,66,38,38,38,31,38,255,41,9,64,63,255,62,4,44
       defb 255,41,4,44,0,44,66,47,47,47,65,41,41,41,255,44,4,23,44,23,23,3,1,1,2,44,255,41,4,44,0,0,44
       defb 67,67,67,44,44,41,41,44,255,0,11,44,41,41,41,44,44,0,255,44,6,41,41,41,255,44,10,0,0,44,255,41,4
       defb 44,0,44,255,41,15,54,54,44,0,0,44,255,41,4,44,0,44,255,41,15,54,54,44,0,0,44,66,38,38,38,44,44,44
       defb 38,38,38,65,255,44,6,255,41,5,44,44,44,0,0,66,31,31,38,38,255,31,5,38,65,255,0,5,255,44,7,255,0,4
       defb 66,255,47,9,65,44,255,0,16,44,255,67,9,255,0,18
       defb 3,1,13,0,71,0,255,71,4,6,21,22,6,71,71,255,0,12,23,3,1,13,255,9,6,18,21,22,18,9,10,255,0,13
       defb 23,3,1,0,6,0,0,6,0,7,21,22,5,0,11,71,71,46,71,71,71,255,0,8,3,2,255,0,4,70,0,0,21
       defb 22,0,0,12,255,9,6,10,255,0,7,1,1,0,0,0,45,0,0,0,21,22,7,255,0,5,44,44,0,11,255,0,6
       defb 23,1,14,255,0,7,21,22,255,0,9,11,255,0,5,23,3,2,0,45,255,0,6,21,22,5,0,8,0,8,0,0,0
       defb 5,11,8,0,5,0,26,3,3,1,255,0,8,21,22,0,45,255,0,7,11,255,0,4,53,2,1,14,255,0,8,21,22
       defb 255,0,8,46,11,255,0,27,11,255,0,10,17,255,0,16,11,255,0,4,53,255,13,4,5,16,8,0,5,0,7,21,22
       defb 7,0,8,0,7,0,8,0,8,11,7,0,5,0,26,1,2,1,1,13,16,255,0,4,5,21,22,255,0,9,12,255,9,5
       defb 3,3,3,2,1,16,76,0,0,0,7,21,22,5,255,0,14,23,0,23,3,1,13,255,0,5,21,22,255,0,6,46,0,0,0
       defb 45,255,0,7,23,3,1,255,0,4,7,21,22,8,255,0,15,23,3,2,1,14,255,0,4,5,21,22,0,0,0,45,255,0,11
       defb 23,3,1,14,0,0,0,46,0,0,0,21,22,5,0,0,0,45,34,35,255,0,8,3,2,14,0,0,0,45,0,0,0
       defb 8,21,22,255,0,4,24,77,78,25,255,0,7,1,14,255,0,8,5,21,22,5,255,0,4,77,78,255,0,8
       defb 255,0,4,45,255,0,37,46,255,0,7,255,6,5,255,0,21,46,0,6,70,70,19,6,255,0,7,46,0,0,0,71,0,0,0
       defb 71,0,0,0,71,0,71,71,6,19,19,0,6,255,0,11,6,0,6,0,6,0,6,0,6,0,6,24,25,19,19,19,6
       defb 255,0,11,70,255,0,11,69,38,38,19,6,255,0,11,6,0,0,71,71,0,71,0,19,19,71,0,69,38,38,71,6,0,0,0
       defb 46,255,0,8,21,22,6,6,0,6,0,6,6,6,24,25,255,6,4,255,0,11,6,21,22,6,0,0,70,0,0,0,70
       defb 11,11,0,0,70,255,0,9,45,0,0,0,21,22,255,0,7,45,12,11,18,9,10,255,0,8,71,0,71,0,6,21,22
       defb 6,0,71,255,0,6,12,255,9,5,255,0,6,255,6,5,21,22,6,6,6,255,0,6,46,0,0,12,9,9,255,0,6
       defb 6,0,0,70,255,0,4,70,6,255,0,13,45,255,0,4,6,255,71,4,0,0,71,71,6,255,0,18,255,6,5,21,22
       defb 6,6,6,255,0,19,70,0,0,6,21,22,6,0,70,255,0,10,45,255,0,5,46,255,0,6,21,22,70,0,0,46,255,0,12
       defb 54,54,255,0,7,6,21,22,6,255,0,6,46,255,0,8,54,54,255,0,8,21,22,255,0,25,6,21,22,6,255,0,14
       defb 255,0,23,11,255,0,9,46,255,0,17,11,255,0,21,45,255,0,5,11,255,0,9,44,0,44,0,44,0,44,0,44,0
       defb 44,0,44,0,44,0,0,0,11,255,0,27,11,255,0,27,11,255,0,4,5,0,7,0,5,255,0,15,7,0,5,11,5
       defb 0,5,255,0,24,12,10,255,0,27,11,255,0,27,11,255,0,27,12,10,0,0,5,0,59,57,58,0,5,0,5,0,5
       defb 0,8,0,6,0,7,0,5,0,5,0,0,0,7,11,5,0,18,255,9,12,10,255,0,11,12,9,9,7,0,59,58,255,0,9
       defb 12,255,9,9,18,5,18,9,9,255,0,4,45,255,0,18,6,45,0,0,0,5,0,59,58,255,0,20,5,255,0,13,45
       defb 255,0,17,8,0,5,0,7,0,5,0,5,0,8,0,5,0,7,0,5,0,7,0,5,0,8,0,7,255,0,17,46,255,0,41
       defb 255,0,25,11,255,0,4,45,255,0,19,46,0,0,11,255,0,27,11,255,0,27,11,255,0,8,44,255,0,8,45,255,0,4
       defb 44,255,0,4,11,255,0,14,34,35,255,0,11,11,0,0,5,0,7,0,5,0,0,0,5,0,5,8,24,25,5,0,5
       defb 0,5,0,0,0,5,0,5,11,5,255,0,5,53,0,0,0,53,0,0,5,24,25,8,0,0,0,53,0,0,0,53,0,0
       defb 11,255,0,13,26,24,25,26,255,0,10,11,255,0,14,29,29,255,0,11,11,255,0,10,19,19,0,0,29,29,255,0,11
       defb 11,0,0,5,0,5,0,7,0,5,0,5,7,5,26,24,25,26,0,7,0,5,0,5,0,8,0,7,11,5,0,255,9,12
       defb 18,11,255,0,11,12,9,9,9,10,255,0,11,12,255,9,14,0,11,255,0,13,45,255,0,13,11,0,0,45,255,0,24
       defb 11,255,0,11,46,255,0,15,11,255,0,22,45,255,0,4,11,255,0,27,11,255,0,26
       defb 255,0,21,24,25,255,0,14,45,255,0,11,77,78,255,0,15,46,0,0,0,44,255,0,6,24,25,255,0,7,45,255,0,18
       defb 39,38,0,0,0,45,255,0,22,39,38,255,0,24,7,7,24,25,7,7,0,0,0,48,0,48,0,48,0,68,0,48,0
       defb 68,0,68,0,0,8,255,7,4,42,77,78,0,7,255,0,24,43,42,0,26,255,0,24,38,0,0,4,255,0,27,27,255,0,24
       defb 34,35,0,7,0,0,0,48,0,48,0,48,0,68,0,48,0,68,0,68,0,0,8,255,7,5,24,25,7,42,0,0,0
       defb 255,9,12,10,0,0,0,12,9,9,9,18,11,11,255,0,5,9,9,10,255,0,9,11,255,0,8,11,11,0,0,0,45
       defb 0,0,0,11,255,0,14,46,0,0,0,12,11,10,0,45,255,0,4,11,255,0,11,44,255,0,7,11,11,255,0,6,11
       defb 255,0,19,11,11,255,0,20,45,255,0,5,11,11,255,0,10,46,255,0,15,11,12,9,9,10,255,0,23,11,0,0,0
       defb 11,0
       defb 255,0,5,46,255,0,6,45,0,45,255,0,5,39,255,0,27,39,0,0,46,255,0,24,11,255,0,6,45,57,58,255,0,15
       defb 46,0,0,11,0,71,71,71,34,35,71,0,0,0,59,57,57,58,0,45,0,0,55,75,73,255,0,6,11,71,1,1,1
       defb 24,25,1,255,0,12,17,0,0,0,46,0,0,0,11,1,14,0,0,77,78,255,0,4,46,255,0,7,55,16,0,0,59
       defb 58,0,0,71,1,14,23,23,0,77,78,0,72,73,255,0,5,45,55,72,73,0,16,255,0,5,71,1,12,9,9,10,0
       defb 24,25,23,17,255,0,8,17,0,74,16,73,255,0,4,1,14,0,23,0,11,0,15,14,0,16,73,255,0,6,74,16,0,0
       defb 16,0,45,75,0,64,1,0,23,0,0,11,255,0,4,16,255,0,6,61,0,16,73,0,16,76,0,61,0,15,1,255,0,4
       defb 11,255,0,4,16,61,0,34,35,0,0,61,13,16,0,0,16,0,0,17,0,0,69,255,0,4,11,255,0,4,16,61,37
       defb 32,33,36,13,13,1,13,17,61,16,0,0,16,61,0,69,255,0,4,11,0,0,21,22,13,13,24,25,24,25,1,1,3
       defb 1,255,13,16,21,22,1,1,1,2,1,1,3,3,23,3,1,1,2,1,1,1,2,2,255,1,6,2,1,21,22,3,3
       defb 1,1,3,255,54,4,255,3,14,11,3,1,21,22,23,23,3,3,44,255,54,4,44,23,23,23,0,0,23,0,23,23,0
       defb 23,0,23,11,3,2,21,22,0,0,23,23,255,44,6,255,0,4,23,255,0,8,11,3,2,21,22,255,0,6,23,255,0,14
       defb 23,0,11,3,2,21,22,255,0,23,11,3,1,21,22
numsc  defb 28
nmedat defb 0,0,112,72,4,3,72,176,6,4,40,208,2,5,64,192,255
       defb 6,4,72,152,0,0,16,176,5,5,120,144,255
       defb 6,4,32,136,4,6,120,144,0,0,56,80,1,7,128,112,1,7,128,160,255
       defb 0,0,136,88,4,3,72,152,4,6,96,112,255
       defb 0,0,64,24,6,4,80,152,2,5,40,88,255
       defb 0,0,32,168,2,5,32,136,5,5,120,72,1,10,104,96,255
       defb 0,0,80,32,6,6,104,168,4,3,8,192,4,6,72,144,1,7,128,64,1,7,128,176,255
       defb 0,0,32,32,4,3,88,56,4,3,24,184,255
       defb 0,0,72,32,6,4,32,104,4,6,16,128,255
       defb 0,0,8,80,2,5,32,56,1,7,128,80,1,7,128,192,6,4,56,136,255
       defb 0,0,120,64,2,5,16,112,1,9,80,104,1,9,48,112,255
       defb 0,0,120,216,4,3,24,128,2,5,16,192,1,10,72,160,1,10,88,160,1,10,104,160,1,10,120,160,255
       defb 0,0,120,216,1,7,120,104,1,7,120,128,4,6,16,120,255
       defb 0,0,120,216,4,3,48,112,2,5,120,96,255
       defb 0,0,120,176,2,5,120,128,255
       defb 0,0,8,112,3,3,32,88,3,3,32,136,2,5,112,88,255
       defb 0,0,16,112,6,3,40,48,1,7,112,120,2,5,128,80,6,8,72,80,6,8,72,160,255
       defb 0,0,128,216,2,5,136,144,6,4,88,112,4,3,8,64,4,6,40,112,255
       defb 0,0,16,216,1,7,32,88,1,7,32,152,6,6,8,80,6,8,64,120,6,4,104,168,255
       defb 0,0,80,96,6,4,56,184,6,6,104,160,255
       defb 0,0,136,144,2,5,56,184,6,3,80,128,255
       defb 0,0,72,208,1,7,72,88,1,7,128,40,255
       defb 0,0,72,112,4,3,72,160,255
       defb 0,0,40,104,6,3,96,104,2,5,40,160,255
       defb 0,0,72,32,4,8,40,56,4,8,56,72,4,8,72,88,4,8,40,128,4,8,56,144,4,8,72,160,255
       defb 0,0,72,32,5,5,72,80,4,8,40,56,4,8,40,168,255
       defb 0,0,72,32,4,8,24,120,4,8,104,120,1,10,24,184,255
       defb 0,0,120,64,1,9,0,168,1,1,88,176,255
NUMOBJ equ 20
objdta equ $
       defb 63,192,64,32,95,208,95,232,95,244,81,244,84,20,81,148,95,244,95,244,64,4,127,252,42,168,127,252,127,252,0,0,69,255,128,208,255,128,208
       defb 1,128,2,192,7,96,14,208,31,248,30,200,31,72,30,200,39,252,79,254,79,234,37,84,0,0,79,254,155,109,159,255,69,254,56,56,254,56,56
       defb 1,128,2,192,7,96,14,208,31,248,30,200,31,72,30,200,39,252,79,254,79,234,37,84,0,0,79,254,155,109,159,255,66,254,16,48,254,16,48
       defb 1,128,2,192,7,96,14,208,31,248,30,200,31,72,30,200,39,252,79,254,79,234,37,84,0,0,79,254,155,109,159,255,68,7,32,168,7,32,168
       defb 63,192,64,32,95,208,95,232,95,244,81,244,84,20,81,148,95,244,95,244,64,4,127,252,42,168,127,252,127,252,0,0,66,23,40,200,23,40,200
       defb 63,192,64,32,95,208,95,232,95,244,81,244,84,20,81,148,95,244,95,244,64,4,127,252,42,168,127,252,127,252,0,0,67,15,80,192,15,80,192
       defb 0,4,0,12,0,0,1,254,0,170,0,0,64,12,96,12,96,12,96,12,0,0,255,254,170,170,0,0,96,12,96,12,7,9,8,104,9,8,104
       defb 15,0,17,128,0,0,2,192,2,192,7,224,27,248,39,252,88,126,121,62,120,122,121,54,121,42,56,84,30,184,7,224,1,6,104,176,6,104,176
       defb 1,0,3,128,7,64,11,160,23,80,47,168,127,84,255,250,85,84,43,168,21,80,11,160,5,64,2,128,1,0,0,0,6,20,16,40,20,16,40
       defb 7,192,27,176,61,120,102,204,99,140,97,12,83,148,46,232,20,80,77,100,111,236,53,88,112,28,5,64,123,188,252,126,7,13,24,208,13,24,208
       defb 7,0,52,0,119,4,244,8,174,12,232,26,238,112,245,192,214,133,187,85,221,223,174,112,87,142,74,250,53,84,15,248,68,14,64,96,14,64,96
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,46,0,126,0,93,0,235,0,209,0,170,0,124,0,71,7,32,88,7,32,88
       defb 0,0,0,0,3,192,7,224,1,128,63,252,76,50,93,186,113,142,119,238,119,238,113,142,93,186,76,50,63,252,0,0,68,17,48,24,17,48,24
       defb 0,0,0,0,3,192,7,224,1,128,63,252,76,50,93,186,113,142,119,238,119,238,113,142,93,186,76,50,63,252,0,0,68,19,56,24,19,56,24
       defb 0,0,1,128,7,224,9,112,19,248,19,152,63,188,57,244,121,190,79,254,94,226,127,194,95,194,43,196,149,91,98,166,6,255,0,16,255,0,16
       defb 7,192,9,224,25,240,23,240,31,240,31,176,15,32,7,192,1,0,1,0,0,128,0,128,0,64,2,32,5,32,0,192,5,10,40,136,10,40,136
       defb 0,0,120,0,30,0,7,0,3,160,1,80,0,224,1,80,3,184,7,28,14,12,20,6,40,6,80,2,160,2,64,0,6,21,8,216,21,8,216
       defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,254,254,234,234,212,212,170,170,212,212,170,170,212,212,2,14,16,24,14,16,24
       defb 0,0,0,0,0,0,0,8,55,228,85,122,79,245,86,122,53,164,3,200,4,32,13,176,16,8,53,172,49,140,31,248,69,6,24,64,6,24,64
       defb 120,0,132,0,165,80,133,88,132,0,120,26,128,2,192,127,199,201,207,201,204,127,205,89,204,111,237,217,109,239,12,127,3,26,64,184,26,64,184
palett equ $
       defb 0,2,20,19,128,227,200,146,0,2,20,19,128,227,200,146
       defb 0,35,60,63,224,227,252,255,0,35,60,63,224,227,252,255
       defb 0,33,39,162,243,64,128,244,0,33,39,162,243,64,128,244
       defb 0,44,80,120,108,109,146,219,0,44,80,120,108,109,146,219
font   equ $
       defb 0,0,0,0,0,0,0,0
       defb 0,48,120,120,48,48,0,48
       defb 0,24,6,6,9,17,32,64
       defb 24,52,60,94,126,114,114,60
       defb 0,94,126,126,42,82,4,120
       defb 2,2,14,66,126,66,126,66
       defb 126,189,153,90,36,60,0,24
       defb 124,185,246,232,213,239,189,126
       defb 0,12,24,24,24,24,12,0
       defb 0,96,48,48,48,48,96,0
       defb 24,52,114,255,149,90,52,24
       defb 28,62,127,127,87,71,71,62
       defb 0,0,0,0,0,24,24,48
       defb 0,0,0,0,126,0,0,0
       defb 0,0,0,0,0,0,16,0
       defb 56,124,254,254,234,226,226,124
       defb 124,254,206,214,230,254,124,0
       defb 24,120,120,24,24,126,126,0
       defb 252,254,6,124,192,254,254,0
       defb 252,254,6,62,6,254,252,0
       defb 216,216,216,216,254,254,24,0
       defb 254,254,192,252,6,254,252,0
       defb 124,252,192,252,198,254,124,0
       defb 254,254,6,14,28,24,24,0
       defb 124,254,198,124,198,254,124,0
       defb 124,254,198,254,126,6,6,0
       defb 0,0,0,48,0,0,48,0
       defb 0,0,0,0,0,0,0,0
       defb 120,124,126,126,126,66,66,126
       defb 0,0,0,0,0,0,0,0
       defb 0,24,52,36,126,171,126,36
       defb 60,14,7,7,7,7,14,60
       defb 0,78,86,78,86,78,86,74
       defb 60,126,6,126,126,102,102,0
       defb 120,126,6,124,102,126,124,0
       defb 62,126,0,96,96,126,62,0
       defb 124,126,6,102,102,126,124,0
       defb 62,126,0,124,96,126,62,0
       defb 62,126,0,124,96,96,96,0
       defb 62,126,0,110,102,126,62,0
       defb 102,102,6,126,102,102,102,0
       defb 126,126,0,24,24,126,126,0
       defb 6,6,0,6,6,126,124,0
       defb 102,110,28,120,124,110,102,0
       defb 96,96,0,96,96,126,62,0
       defb 99,119,31,107,99,99,99,0
       defb 124,126,6,102,102,102,102,0
       defb 60,126,6,102,102,126,60,0
       defb 124,126,6,126,124,96,96,0
       defb 60,126,6,102,102,112,54,6
       defb 124,126,6,126,124,110,102,0
       defb 62,126,0,60,14,126,124,0
       defb 126,126,0,24,24,24,24,0
       defb 102,102,6,102,102,126,62,0
       defb 102,102,6,102,126,60,24,0
       defb 99,99,3,107,127,119,99,0
       defb 99,119,46,28,62,119,99,0
       defb 102,102,6,126,6,62,60,0
       defb 126,126,0,12,24,62,126,0
       defb 30,12,12,12,12,12,12,30
       defb 0,0,192,96,48,24,12,0
       defb 0,240,48,48,48,48,240,0
       defb 60,78,94,126,122,60,8,24
       defb 0,0,127,127,42,85,0,127
       defb 0,86,75,85,74,69,32,31
       defb 0,0,60,6,62,102,62,0
       defb 0,96,96,124,102,102,124,0
       defb 60,66,153,161,161,153,66,60
       defb 0,6,6,62,102,102,62,0
       defb 0,0,60,102,124,96,60,0
       defb 0,28,48,56,48,48,48,0
       defb 0,0,56,108,108,60,12,120
       defb 0,96,96,124,102,102,102,0
       defb 0,24,0,56,24,24,60,0
       defb 0,6,0,6,6,6,102,60
       defb 0,96,108,120,120,108,102,0
       defb 0,48,48,48,48,48,28,0
       defb 0,0,54,127,127,107,99,0
       defb 0,0,124,102,102,102,102,0
       defb 0,0,60,102,102,102,60,0
       defb 0,0,124,102,102,124,96,96
       defb 0,0,62,102,102,62,6,7
       defb 0,0,30,51,48,48,48,0
       defb 0,0,62,96,60,6,124,0
       defb 0,48,124,48,48,48,28,0
       defb 212,224,224,224,224,224,224,192
       defb 127,254,213,224,224,224,252,248
       defb 0,0,31,39,74,85,72,87
       defb 126,129,177,177,129,133,129,126
       defb 0,0,120,124,46,86,14,86
       defb 0,40,40,92,92,92,0,40
       defb 0,30,24,112,24,24,30,0
       defb 0,24,24,24,24,24,24,0
       defb 0,240,48,28,48,48,240,0
       defb 0,60,120,0,0,0,0,0
       defb 60,66,153,161,161,153,66,60
jtab   equ $
       defb 249,250,251,254,254,255,255,255,0,0,0,1,1,1,2,2,6,7,6,15,16,99
keys   defb 34,26,38,37,32,31,18,36,28,20,12
end 32000