//---------------------------------------------------------------------------
#ifndef BlockTypesH
#define BlockTypesH
//---------------------------------------------------------------------------
const String g_BlockTypes[] = {
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
const TColor g_BlockColors[7] = {
    clGray,     // empty
    clBlue,     // platform
    clWebOrange,// wall
    clGreen,    // ladder
    clFuchsia,  // fodder
    clRed,      // deadly
    clYellow,   // custom
};
//---------------------------------------------------------------------------
#endif // BlockTypesH
