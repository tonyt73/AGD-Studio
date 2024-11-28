//---------------------------------------------------------------------------
#ifndef BlockTypesH
#define BlockTypesH
//---------------------------------------------------------------------------
static const String g_BlockTypes[] = {
    "EMPTYBLOCK",
    "PLATFORMBLOCK",
    "WALLBLOCK",
    "LADDERBLOCK",
    "FODDERBLOCK",
    "DEADLYBLOCK",
    "CUSTOMBLOCK"
};
//---------------------------------------------------------------------------
// colours for each block type
static const TColor g_BlockColors[7] = {
    (TColor)0x00404040, // grey     empty
    (TColor)0x00FF0000, // blue     platform
    (TColor)0x00006AFF, // orange   wall
    (TColor)0x0000FF00, // green    ladder
    (TColor)0x00FF00FF, // magenta  fodder
    (TColor)0x000000FF, // red      deadly
    (TColor)0x0000FFFF, // yellow   custom
};
//---------------------------------------------------------------------------
#endif // BlockTypesH
