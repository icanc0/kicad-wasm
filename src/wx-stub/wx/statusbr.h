// Minimal wx/statusbr.h stub — status bar widget.
#pragma once
#include "wx/window.h"

class wxStatusBar : public wxWindow {
public:
    wxStatusBar() = default;
    wxStatusBar(wxWindow* parent, wxWindowID id = wxID_ANY, long = 0,
                const wxString& = wxString()) { (void)parent; (void)id; }
    virtual void SetFieldsCount(int, const int* = nullptr) {}
    virtual void SetStatusText(const wxString&, int = 0) {}
    virtual wxString GetStatusText(int = 0) const { return wxString(); }
    virtual void SetStatusWidths(int, const int*) {}
    virtual void SetStatusStyles(int, const int*) {}
    virtual int  GetFieldsCount() const { return 0; }
    virtual void PushStatusText(const wxString&, int = 0) {}
    virtual void PopStatusText(int = 0) {}
};
