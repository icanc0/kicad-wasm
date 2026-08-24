// Minimal wx/confbase.h stub — enough for KiCad code that only names the
// wxConfigBase type without actually reading/writing config. Config in the
// WASM build is handled by JS host, not the C++ side.
#pragma once
#include "wx/string.h"

class wxConfigBase {
public:
    virtual ~wxConfigBase() = default;
    virtual bool Read(const wxString&, wxString*, const wxString& = wxString()) const { return false; }
    virtual bool Read(const wxString&, long*, long = 0) const { return false; }
    virtual bool Read(const wxString&, double*, double = 0.0) const { return false; }
    virtual bool Read(const wxString&, bool*, bool = false) const { return false; }
    virtual bool Write(const wxString&, const wxString&) { return false; }
    virtual bool Write(const wxString&, long) { return false; }
    virtual bool Write(const wxString&, double) { return false; }
    virtual bool Write(const wxString&, bool) { return false; }
    virtual bool Flush(bool = false) { return true; }
    static wxConfigBase* Get(bool = true) { return nullptr; }
    static wxConfigBase* Set(wxConfigBase*) { return nullptr; }
};
