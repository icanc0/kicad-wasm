// Minimal wx/defs.h stub — pass-through wxT/wxS/wxASCII_STR.
#pragma once

// wxChar is either wchar_t (wide) or char (ANSI) in real wx; we always
// pick char since we're headless-ASCII in this port. wxUniChar is a
// wide-character abstraction — we approximate with char32_t.
using wxChar = char;
class wxUniChar {
    char32_t m_c = 0;
public:
    wxUniChar() = default;
    wxUniChar(char c)     : m_c((char32_t)(unsigned char)c) {}
    wxUniChar(int c)      : m_c((char32_t)c) {}
    wxUniChar(char32_t c) : m_c(c) {}
    operator int() const { return (int)m_c; }
    bool operator==(const wxUniChar& r) const { return m_c == r.m_c; }
    bool operator!=(const wxUniChar& r) const { return m_c != r.m_c; }
    bool operator<(const wxUniChar& r)  const { return m_c <  r.m_c; }
    int GetValue() const { return (int)m_c; }
};

// Print orientation / paper size — used by KiCad page_info.h even in
// headless mode as data carriers. Values are the real wxWidgets ones.
enum wxPrintOrientation {
    wxPORTRAIT  = 1,
    wxLANDSCAPE = 2,
};

enum wxPaperSize {
    wxPAPER_NONE   = 0,
    wxPAPER_LETTER = 1,
    wxPAPER_LEGAL  = 5,
    wxPAPER_A4     = 9,
    wxPAPER_A3     = 8,
    wxPAPER_A5     = 11,
    wxPAPER_TABLOID= 3,
    wxPAPER_11X17  = 3,
};

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
