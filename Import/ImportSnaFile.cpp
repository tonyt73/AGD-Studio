//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "ImportSnaFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
std::vector<String>  ImportSnaFile::m_Keywords =
{
	/* Some keywords. */
	"IF",				// if.
	"SPRITEUP",			// move sprite up.
	"SPRITEDOWN",		// move sprite down.
	"SPRITELEFT",		// move sprite left.
	"SPRITERIGHT",		// move sprite right.
	"ENDIF",			// endif.
	"CANGOUP",			// sprite can go up test.
	"CANGODOWN",		// sprite can go down test.
	"CANGOLEFT",		// sprite can go left test.
	"CANGORIGHT",		// sprite can go right test.
	"LADDERABOVE",		// ladder above test.
	"LADDERBELOW",		// ladder below test.
	"DEADLY",			// check if touching deadly block.
	"CUSTOM",    		// check if touching custom block.
	".",				// number.
	"TO",           	// variable to increment.
	"FROM",          	// variable to decrement.
	"BY",	          	// multiply or divide by.

	/* Sprite variables. */

	"TYPE",				// first parameter.
	"IMAGE",			// image number.
	"FRAME",			// frame number.
	"Y",				// vertical position.
	"X",				// horizontal position.
	"DIRECTION",		// user sprite parameter.
	"SETTINGA",			// sprite parameter a.
	"SETTINGB",			// sprite parameter b.
	"SCREEN",			// screen number.
	"LIVES",			// lives.
	"A",				// variable.
	"B",				// variable.
	"C",				// variable.
	"D",				// variable.
	"E",				// variable.
	"F",				// variable.
	"G",				// variable.
	"H",				// variable.
	"I",				// variable.
	"J",				// variable.
	"K",				// variable.
	"L",				// variable.
	"M",				// variable.
	"N",				// variable.
	"O",				// variable.
	"P",				// variable.
	"Q",				// variable.
	"R",				// variable.
	"S",				// variable.
	"T",				// variable.
	"LINE",				// x coordinate.
	"COLUMN",			// y coordinate.
	"CLOCK",			// clock.
	"RND",				// last random number variable.
	"OBJ",				// last object variable.
	"OPT",				// menu option variable.
	"GOT",				// function.
	"KEY",				// function.

	/* Commands. */

	"COLLISION",		// collision with sprite.
	"=",				// equals, ignored.
	">",				// greater than.
	"<>",				// not equal to.
	"<=",				// less than or equal to.
	"LET",				// x = y.
	"ANIMATE",			// animate sprite.
	"ANIMBACK",			// animate sprite backwards.
	"PUTBLOCK",			// put block on screen.
	"NEXTLEVEL",		// next level.
	"RESTART",			// restart game.
	"SPAWN",			// spawn new sprite.
	"REMOVE",			// remove this sprite.
	"GETRANDOM",		// variable.
	"ELSE",				// else.
	"SHOWSCORE",		// show score.
	"SCORE",			// increase score.
	"SOUND",			// play sound.
	"BEEP",				// play beeper sound.
	"CLS",				// clear screen.
	"BORDER",			// set border.
	"COLOUR",			// set all attributes.
	"DELAY",			// pause for a while.
	"MESSAGE",			// display a message.
	"MENU",				// menu in a box.
	"INV",				// inventory menu.
	"KILL",				// kill the player.
	"ADD",				// add to variable.
	"SUBTRACT",			// subtract from variable.
	"DISPLAY",			// display number.
	"SCREENUP",			// up a screen.
	"SCREENDOWN",		// down a screen.
	"SCREENLEFT",		// left a screen.
	"SCREENRIGHT",		// right a screen.
	"WAITKEY",			// wait for keypress.
	"JUMP 7",			// jump.
	"FALL",				// fall.
	"OTHER",			// select second collision sprite.
	"SPAWNED",			// select spawned sprite.
	"ENDSPRITE",		// select original sprite.
	"ENDGAME",			// end game with victory.
	"GET",				// get object.
	"PUT",				// drop object.
	"DETECTOBJ",		// detect object.
	"; ASM",			// encode.
	"EXIT",				// exit.
	"REPEAT",			// repeat.
	"ENDREPEAT",		// endrepeat.
	"MULTIPLY",			// multiply.
	"DIVIDE",			// divide.
	"SPRITEINK",		// set sprite ink.
	"TRAIL",			// leave a trail.
	"LASER",			// shoot a laser.
	"EXPLODE",			// start a shrapnel explosion.
	"; FADE",			// fade unsupported.
	"TICKER",			// ticker message.
	"MESSAGE",			// big message.
	"REDRAW",			// redraw the play area.
	"SILENCE",			// silence AY channels.
	"WAITKEY",			// controlmenu unsupported.
	"; DIG",			// dig unsupported.
	"STAR",				// star.
	"BIGSCORE",			// show score double-height.
	"STOPFALL"			// stop falling.
};
//---------------------------------------------------------------------------
std::vector<String>  ImportSnaFile::m_EventFiles =
{
    "event.Player Control",
    "event.Sprite type 1",
    "event.Sprite type 2",
    "event.Sprite type 3",
    "event.Sprite type 4",
    "event.Sprite type 5",
    "event.Sprite type 6",
    "event.Sprite type 7",
    "event.Sprite type 8",
    "event.Game initialisation",
    "event.Initialise sprite",
    "event.Kill player",
    "event.Introduction Menu",
    "eEvent.Main loop 1",
    "event.Main loop 2",
    "event.Restart screen",
    "event.Fell too far",
    "event.Lost game",
    "event.Completed game",
    "event.New High Score"
};
//---------------------------------------------------------------------------
__fastcall ImportSnaFile::ImportSnaFile()
: ImportFile()
{
}
//---------------------------------------------------------------------------
bool __fastcall ImportSnaFile::Process(const String& file)
{
    if (TFile::Exists(file))
    {
        m_Snapshot = std::make_unique<ZXSpectrum48KSnapshot>();
        if (m_Snapshot->Load(file))
        {
            // get values
            m_ValueOf.WindowPosition.Y = m_Snapshot->Byte(m_Snapshot->Location.Window+0);
            m_ValueOf.WindowPosition.X = m_Snapshot->Byte(m_Snapshot->Location.Window+1);
            m_ValueOf.WindowSize.cy = m_Snapshot->Byte(m_Snapshot->Location.Window+2);
            m_ValueOf.WindowSize.cx = m_Snapshot->Byte(m_Snapshot->Location.Window+3);
            m_ValueOf.Rooms = m_Snapshot->Byte(m_Snapshot->Location.NumberOfScreens);

            // get addresses
            m_AddressOf.SpriteFrames = m_Snapshot->Word(m_Snapshot->Location.Pointers + 0) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.SpriteData = m_Snapshot->Word(m_Snapshot->Location.Pointers + 2) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.BlockImageData = m_Snapshot->Word(m_Snapshot->Location.Pointers + 4) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.BlockAttrsData = m_Snapshot->Word(m_Snapshot->Location.Pointers + 6) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.BlockPropsData = m_Snapshot->Word(m_Snapshot->Location.Pointers + 8) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.ScreenLayouts = m_Snapshot->Word(m_Snapshot->Location.Pointers + 10) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.EnemyPositions = m_Snapshot->Word(m_Snapshot->Location.Pointers + 12) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.AYSoundFx = m_Snapshot->Word(m_Snapshot->Location.Pointers + 14) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.Messages = m_Snapshot->Word(m_Snapshot->Location.Pointers + 16) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.Objects = m_Snapshot->Word(m_Snapshot->Location.Pointers + 18) - m_Snapshot->Location.StuffToSkip;
            m_AddressOf.EventCode = m_Snapshot->Word(m_Snapshot->Location.Pointers + 20) - m_Snapshot->Location.StuffToSkip;

            ImportWindow();
            ImportMessages();
            ImportEvents();
            ImportFont();
            ImportBlocks();
            ImportSprites();
            ImportObjects();
            ImportScreens();
            ImportMap();
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportWindow() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportMessages() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportEvents() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportFont() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportBlocks() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportSprites() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportObjects() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportScreens() const
{
}
//---------------------------------------------------------------------------
void __fastcall ImportSnaFile::ImportMap() const
{
}
//---------------------------------------------------------------------------

