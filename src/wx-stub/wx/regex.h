// Minimal wx/regex.h stub, backed by std::regex.
#pragma once
#include "wx/string.h"
#include <regex>

enum {
    wxRE_DEFAULT  = 0,
    wxRE_EXTENDED = 0,
    wxRE_ICASE    = 1,
    wxRE_NOSUB    = 0,
    wxRE_NEWLINE  = 0,
    wxRE_ADVANCED = 0,
};

class wxRegEx {
    std::regex m_re;
    bool m_ok = false;
public:
    wxRegEx() = default;
    wxRegEx(const wxString& pattern, int flags = wxRE_DEFAULT) {
        Compile(pattern, flags);
    }
    bool Compile(const wxString& pattern, int flags = wxRE_DEFAULT) {
        try {
            auto opts = std::regex::ECMAScript;
            if (flags & wxRE_ICASE) opts = opts | std::regex::icase;
            m_re = std::regex(pattern.ToStdString(), opts);
            m_ok = true;
        } catch (...) {
            m_ok = false;
        }
        return m_ok;
    }
    bool IsValid() const { return m_ok; }
    bool Matches(const wxString& s, int = 0) const {
        if (!m_ok) return false;
        return std::regex_search(s.ToStdString(), m_re);
    }
    size_t Replace(wxString* str, const wxString& with, size_t = 0) const {
        if (!m_ok || !str) return 0;
        std::string out = std::regex_replace(str->ToStdString(), m_re, with.ToStdString());
        *str = wxString(out);
        return 1;
    }
};
