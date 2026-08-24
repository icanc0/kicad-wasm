// Minimal wx/tokenzr.h stub — string tokenization.
#pragma once
#include "wx/string.h"
#include "wx/arrstr.h"
#include <string>

enum wxStringTokenizerMode {
    wxTOKEN_DEFAULT       = 0,
    wxTOKEN_RET_EMPTY     = 1,
    wxTOKEN_RET_EMPTY_ALL = 2,
    wxTOKEN_RET_DELIMS    = 3,
    wxTOKEN_STRTOK        = 4,
};

class wxStringTokenizer {
    std::string m_s;
    std::string m_delims;
    size_t m_pos = 0;
    wxStringTokenizerMode m_mode = wxTOKEN_DEFAULT;
public:
    wxStringTokenizer() = default;
    wxStringTokenizer(const wxString& s,
                      const wxString& delims = " \t\r\n",
                      wxStringTokenizerMode mode = wxTOKEN_DEFAULT) {
        SetString(s, delims, mode);
    }
    void SetString(const wxString& s,
                   const wxString& delims = " \t\r\n",
                   wxStringTokenizerMode mode = wxTOKEN_DEFAULT) {
        m_s = s.ToStdString();
        m_delims = delims.ToStdString();
        m_pos = 0;
        m_mode = mode;
    }
    bool HasMoreTokens() const {
        return m_pos < m_s.size();
    }
    wxString GetNextToken() {
        if (!HasMoreTokens()) return wxString();
        // Skip leading delimiters (unless RET_EMPTY_ALL).
        if (m_mode != wxTOKEN_RET_EMPTY_ALL) {
            while (m_pos < m_s.size() && m_delims.find(m_s[m_pos]) != std::string::npos) ++m_pos;
        }
        if (m_pos >= m_s.size()) return wxString();
        size_t start = m_pos;
        while (m_pos < m_s.size() && m_delims.find(m_s[m_pos]) == std::string::npos) ++m_pos;
        wxString tok(m_s.substr(start, m_pos - start));
        if (m_pos < m_s.size()) ++m_pos;  // consume delimiter
        return tok;
    }
    size_t CountTokens() const {
        // Cheap approximation — count delimiter transitions.
        size_t c = 0; bool in_tok = false;
        for (char ch : m_s) {
            bool is_delim = m_delims.find(ch) != std::string::npos;
            if (!is_delim && !in_tok) { c++; in_tok = true; }
            else if (is_delim) in_tok = false;
        }
        return c;
    }
};

inline wxArrayString wxSplit(const wxString& s, wxChar sep, wxChar /*escape*/ = 0) {
    wxArrayString out;
    std::string delim(1, sep);
    wxStringTokenizer tok(s, wxString(delim), wxTOKEN_RET_EMPTY_ALL);
    while (tok.HasMoreTokens()) out.Add(tok.GetNextToken());
    return out;
}
