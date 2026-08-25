// Minimal wx/font.h stub — font attributes.
#pragma once
#include "wx/defs.h"
#include "wx/string.h"

enum wxFontFamily {
    wxFONTFAMILY_DEFAULT    = 70,
    wxFONTFAMILY_DECORATIVE = 71,
    wxFONTFAMILY_ROMAN      = 72,
    wxFONTFAMILY_SCRIPT     = 73,
    wxFONTFAMILY_SWISS      = 74,
    wxFONTFAMILY_MODERN     = 75,
    wxFONTFAMILY_TELETYPE   = 76,
};
enum wxFontStyle {
    wxFONTSTYLE_NORMAL  = 90,
    wxFONTSTYLE_ITALIC  = 93,
    wxFONTSTYLE_SLANT   = 94,
};
enum wxFontWeight {
    wxFONTWEIGHT_NORMAL = 400,
    wxFONTWEIGHT_LIGHT  = 300,
    wxFONTWEIGHT_BOLD   = 700,
};
enum wxFontEncoding {
    wxFONTENCODING_DEFAULT = 0,
    wxFONTENCODING_SYSTEM  = 1,
    wxFONTENCODING_UTF8    = 65001,
};

class wxFont {
public:
    wxFont() = default;
    wxFont(int, wxFontFamily, wxFontStyle, wxFontWeight, bool = false,
           const wxString& = wxString(), wxFontEncoding = wxFONTENCODING_DEFAULT) {}
    bool IsOk() const { return true; }
    int  GetPointSize() const { return 10; }
    wxFontFamily GetFamily() const { return wxFONTFAMILY_DEFAULT; }
    wxFontStyle  GetStyle()  const { return wxFONTSTYLE_NORMAL; }
    wxFontWeight GetWeight() const { return wxFONTWEIGHT_NORMAL; }
    wxString     GetFaceName() const { return wxString(); }
    bool GetUnderlined() const { return false; }
    bool GetStrikethrough() const { return false; }
    void SetPointSize(int) {}
    void SetFamily(wxFontFamily) {}
    void SetStyle(wxFontStyle) {}
    void SetWeight(wxFontWeight) {}
    void SetFaceName(const wxString&) {}
};

inline const wxFont wxNullFont;
