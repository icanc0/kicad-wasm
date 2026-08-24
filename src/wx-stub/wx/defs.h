// Minimal wx/defs.h stub — pass-through wxT/wxS/wxASCII_STR.
#pragma once

// wxChar is either wchar_t (wide) or char (ANSI) in real wx; we always
// pick char since we're headless-ASCII in this port.
using wxChar = char;

#ifndef wxT
#define wxT(x)  x
#endif
#ifndef wxS
#define wxS(x)  x
#endif
#ifndef wxASCII_STR
#define wxASCII_STR(x) x
#endif

// wxWidgets-style bool aliases (rarely used by KiCad now).
#ifndef wxABI_VERSION
#define wxABI_VERSION 302
#endif
