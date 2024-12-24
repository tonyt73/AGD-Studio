//---------------------------------------------------------------------------
#ifndef BlockTypesH
#define BlockTypesH
//---------------------------------------------------------------------------
[[clang::no_destroy]] static const String g_BlockTypes[]  = {
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
    static_cast<TColor>(0x00404040), // grey     empty
    static_cast<TColor>(0x00FF0000), // blue     platform
    static_cast<TColor>(0x00006AFF), // orange   wall
    static_cast<TColor>(0x0000FF00), // green    ladder
    static_cast<TColor>(0x00FF00FF), // magenta  fodder
    static_cast<TColor>(0x000000FF), // red      deadly
    static_cast<TColor>(0x0000FFFF), // yellow   custom
};
//---------------------------------------------------------------------------
#endif // BlockTypesH
