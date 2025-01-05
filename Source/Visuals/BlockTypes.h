//---------------------------------------------------------------------------
#ifndef BlockTypesH
#define BlockTypesH
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
[[clang::no_destroy]] static const String g_BlockTypes[]  = {
    "EMPTYBLOCK",
    "PLATFORMBLOCK",
    "WALLBLOCK",
    "LADDERBLOCK",
    "FODDERBLOCK",
    "DEADLYBLOCK",
    "CUSTOMBLOCK",
    "WATERBLOCK",
    "COLLECTABLE"
};
//---------------------------------------------------------------------------
// colours for each block type
static const TColor g_BlockColors[] = {
    static_cast<TColor>(0x00404040), // grey     empty
    static_cast<TColor>(0x0000FFFF), // cyan     platform
    static_cast<TColor>(0x00006AFF), // orange   wall
    static_cast<TColor>(0x0000FF00), // green    ladder
    static_cast<TColor>(0x00FF00FF), // magenta  fodder
    static_cast<TColor>(0x000000FF), // red      deadly
    static_cast<TColor>(0x0000FFFF), // yellow   custom
    static_cast<TColor>(0x00FF0000), // blue     waterblock
    static_cast<TColor>(0x00FFFFFF), // white    collectable
};
//---------------------------------------------------------------------------
static_assert(sizeof(g_BlockTypes) / sizeof(g_BlockTypes[0]) == sizeof(g_BlockColors) / sizeof(g_BlockColors[0]));
//---------------------------------------------------------------------------
#endif // BlockTypesH
