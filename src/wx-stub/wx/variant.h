// Minimal wx/variant.h stub — dynamic-typed value (like std::any).
#pragma once
#include "wx/string.h"
#include "wx/any.h"

class wxVariantData {
public:
    virtual ~wxVariantData() = default;
    virtual bool Eq(wxVariantData&) const { return false; }
    virtual wxString GetType() const { return {}; }
    virtual bool Write(wxString&) const { return false; }
    virtual bool Read(wxString&)        { return false; }
    virtual bool GetAsAny(wxAny*) const { return false; }
    virtual wxVariantData* Clone() const { return nullptr; }
    void IncRef() {}
    void DecRef() { delete this; }
};

class wxVariant {
    std::any m_val;
    wxString m_type;
public:
    wxVariant() = default;
    wxVariant(const wxString& val, const wxString& name = wxString()) : m_val(val), m_type("string") { (void)name; }
    wxVariant(long val)      : m_val(val), m_type("long") {}
    wxVariant(double val)    : m_val(val), m_type("double") {}
    wxVariant(bool val)      : m_val(val), m_type("bool") {}
    wxVariant(int val)       : m_val((long)val), m_type("long") {}

    wxString GetType() const { return m_type; }

    long   GetLong() const   { try { return std::any_cast<long>(m_val); }  catch (...) { return 0; } }
    double GetDouble() const { try { return std::any_cast<double>(m_val); }catch (...) { return 0.0; } }
    bool   GetBool() const   { try { return std::any_cast<bool>(m_val); }  catch (...) { return false; } }
    wxString GetString() const { try { return std::any_cast<wxString>(m_val); } catch (...) { return {}; } }

    bool IsNull() const { return !m_val.has_value(); }
};
