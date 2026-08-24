// Minimal wx/translation.h stub — headless kicad-wasm doesn't translate.
// _(...) and wxGetTranslation return the source string unchanged.
#pragma once
#include "wx/string.h"

#ifndef _
#define _(s)     wxString(s)
#endif
#ifndef wxTRANSLATE
#define wxTRANSLATE(s)  s
#endif

inline wxString wxGetTranslation(const wxString& s) { return s; }
inline wxString wxGetTranslation(const wxString& s, const wxString&) { return s; }
inline wxString wxPLURAL(const wxString& s, const wxString&, unsigned) { return s; }

class wxLocale {
public:
    wxLocale() = default;
    wxLocale(int) {}
    bool Init(int = 0, int = 0) { return true; }
    bool AddCatalog(const wxString&) { return true; }
    bool IsLoaded(const wxString&) const { return true; }
    wxString GetName() const { return wxString("C"); }
    static wxLocale* GetLanguageInfo(int) { return nullptr; }
};

class wxTranslations {
public:
    wxTranslations() = default;
    void SetLoader(void*) {}
    bool AddCatalog(const wxString&) { return true; }
    wxString GetString(const wxString& s) const { return s; }
    static wxTranslations* Get() { return nullptr; }
    static void            Set(wxTranslations*) {}
};

enum { wxLANGUAGE_DEFAULT = 0, wxLANGUAGE_ENGLISH = 1 };
