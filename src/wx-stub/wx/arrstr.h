// Minimal wx/arrstr.h stub — wxArrayString as thin vector<wxString>.
#pragma once
#include "wx/string.h"
#include <algorithm>
#include <vector>

class wxArrayString {
    std::vector<wxString> m_v;
public:
    wxArrayString() = default;
    wxArrayString(std::initializer_list<wxString> il) : m_v(il) {}

    size_t GetCount() const { return m_v.size(); }
    size_t size()     const { return m_v.size(); }
    bool   IsEmpty()  const { return m_v.empty(); }
    bool   empty()    const { return m_v.empty(); }

    void Add(const wxString& s, size_t copies = 1) {
        for (size_t i = 0; i < copies; ++i) m_v.push_back(s);
    }
    void push_back(const wxString& s) { m_v.push_back(s); }
    void Clear() { m_v.clear(); }
    void clear() { m_v.clear(); }

    wxString&       operator[](size_t i)       { return m_v[i]; }
    const wxString& operator[](size_t i) const { return m_v[i]; }
    wxString&       Item(size_t i)       { return m_v[i]; }
    const wxString& Item(size_t i) const { return m_v[i]; }

    int Index(const wxString& s, bool = true, bool = false) const {
        auto it = std::find(m_v.begin(), m_v.end(), s);
        return it == m_v.end() ? -1 : static_cast<int>(it - m_v.begin());
    }

    auto begin()       { return m_v.begin(); }
    auto end()         { return m_v.end();   }
    auto begin() const { return m_v.begin(); }
    auto end()   const { return m_v.end();   }
};
