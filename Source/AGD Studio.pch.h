#ifndef pch_H
#define pch_H
//---------------------------------------------------------------------------
// Ignore Compiler Warnings
// Annoyances
#pragma clang diagnostic ignored "-Wpadded"
//#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wsign-conversion"
//#pragma clang diagnostic ignored "-Wunused-parameter"
//#pragma clang diagnostic ignored "-Wignored-attributes"
//#pragma clang diagnostic ignored "-Wglobal-constructors"
//#pragma clang diagnostic ignored "-Wexit-time-destructors"
//#pragma clang diagnostic ignored "-Wshadow-field-in-constructor"
#pragma clang diagnostic ignored "-Wnonportable-system-include-path"
// VCL language extensions
#pragma clang diagnostic ignored "-Wlanguage-extension-token"   // __property
#pragma clang diagnostic ignored "-Wunused-private-field"       // appears when using property read/writes
// Older languages
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wc++98-compat-extra-semi"
#pragma clang diagnostic ignored "-Wborland-ignored-pragmas"

//---------------------------------------------------------------------------
// VCL
#include <vcl.h>
#include <Vcl.Graphics.hpp>
#include <Vcl.Themes.hpp>
#include <Vcl.Styles.hpp>
#include <Xml.Win.msxmldom.hpp>
//---------------------------------------------------------------------------
// System
#include <System.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Readers.hpp>
#include <System.JSON.Writers.hpp>
//---------------------------------------------------------------------------
// STL
#include <algorithm>
#include <memory>
#include <tchar.h>
#include <list>
#include <vector>
#include <map>
#include <math.h>
#include <stack>
#include <iterator>
//---------------------------------------------------------------------------
// Templates
#include "Templates/enumerate.h"
//---------------------------------------------------------------------------
#pragma hdrstop

[[clang::no_destroy]] const String ApplicationName = "AGD Studio";

#endif // pch_h

