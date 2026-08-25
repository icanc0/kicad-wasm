// Minimal wx/strconv.h stub. wx-strconv wraps ICU/Iconv for wxString
// wide<->char conversions. In our char-only wxString, most methods
// are identity.
#pragma once
#include "wx/string.h"
#include "wx/debug.h"    // real wx: transitively via wx/strconv.h
#include <cstddef>

class wxMBConv {
public:
    virtual ~wxMBConv() = default;
    // Real wx: converts wchar_t → multibyte. We're char-only; pass through.
    virtual size_t FromWChar(char*, size_t, const wchar_t*, size_t = 0) const { return 0; }
    virtual size_t ToWChar(wchar_t*, size_t, const char*, size_t = 0) const   { return 0; }
    virtual size_t MB2WC(wchar_t*, const char*, size_t) const { return 0; }
    virtual size_t WC2MB(char*, const wchar_t*, size_t) const { return 0; }
};

class wxMBConvUTF8   : public wxMBConv {};
class wxMBConvUTF16  : public wxMBConv {};
class wxCSConv       : public wxMBConv {
public:
    wxCSConv() = default;
    wxCSConv(const wxString&) {}
    wxCSConv(int) {}
};

extern wxMBConv* wxConvCurrent;
inline wxMBConv wxConvUTF8;
inline wxMBConv wxConvLibc;
inline wxMBConv* wxConvUI = nullptr;
inline wxMBConv* wxConvFileName = nullptr;
