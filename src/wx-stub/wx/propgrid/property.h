// Minimal wx/propgrid/property.h stub. Property-editor infrastructure.
#pragma once
#include "wx/defs.h"
#include "wx/string.h"
#include "wx/arrstr.h"

class wxPGChoices {
    wxArrayString m_labels;
public:
    wxPGChoices() = default;
    wxPGChoices(const wxArrayString& labels) : m_labels(labels) {}
    size_t GetCount() const { return m_labels.GetCount(); }
    wxString GetLabel(size_t i) const {
        return i < m_labels.GetCount() ? m_labels[i] : wxString();
    }
    void Add(const wxString& s, int = 0) { m_labels.Add(s); }
    void Clear() { m_labels.Clear(); }
    bool IsOk() const { return true; }
    wxArrayString GetLabels() const { return m_labels; }
    int GetValue(size_t i) const { return static_cast<int>(i); }
    int GetValue(const wxString&) const { return -1; }
    int Index(const wxString& s) const {
        for (size_t i = 0; i < m_labels.GetCount(); ++i)
            if (m_labels[i] == s) return static_cast<int>(i);
        return -1;
    }
    int Index(int v) const { return v; }
};

class wxPGProperty {
public:
    virtual ~wxPGProperty() = default;
};

class wxPropertyGrid {
public:
    virtual ~wxPropertyGrid() = default;
};
