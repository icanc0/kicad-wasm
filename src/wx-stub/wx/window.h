// Minimal wx/window.h stub — enough for KiCad code that just names the
// wxWindow type, calls Show/Hide, or attaches event handlers. Actual UI
// display is out of scope for kicad-wasm Phase 1 (headless).
#pragma once
#include "wx/event.h"
#include "wx/gdicmn.h"
#include "wx/string.h"

using wxWindowID = int;
constexpr wxWindowID wxID_ANY   = -1;
constexpr wxWindowID wxID_OK    = 5100;
constexpr wxWindowID wxID_CANCEL= 5101;
constexpr wxWindowID wxID_YES   = 5103;
constexpr wxWindowID wxID_NO    = 5104;
constexpr wxWindowID wxID_APPLY = 5102;
constexpr wxWindowID wxID_CLOSE = 5106;

// Common style flags KiCad code uses.
constexpr long wxDEFAULT_DIALOG_STYLE = 0;
constexpr long wxDEFAULT_FRAME_STYLE  = 0;
constexpr long wxCAPTION              = 0;
constexpr long wxRESIZE_BORDER        = 0;
constexpr long wxCLOSE_BOX            = 0;
constexpr long wxSTAY_ON_TOP          = 0;
constexpr long wxICON_INFORMATION     = 0;
constexpr long wxICON_WARNING         = 0;
constexpr long wxICON_ERROR           = 0;
constexpr long wxOK                   = 0;
constexpr long wxYES_NO               = 0;
constexpr long wxNO_DEFAULT           = 0;

class wxWindow : public wxEvtHandler {
    wxString m_title;
public:
    wxWindow() = default;
    wxWindow(wxWindow* parent, wxWindowID id) { (void)parent; (void)id; }
    virtual ~wxWindow() = default;

    // Placement / geometry.
    virtual bool Show(bool = true) { return true; }
    virtual bool Hide() { return true; }
    virtual bool IsShown() const { return false; }
    virtual void Close(bool = false) {}
    virtual void Destroy() {}
    virtual void Refresh(bool = true, const wxRect* = nullptr) {}
    virtual void Update() {}
    virtual void Layout() {}
    virtual void Fit() {}
    virtual void Move(int, int) {}
    virtual void SetSize(int, int, int, int, int = 0) {}
    virtual void SetSize(const wxSize&) {}
    virtual void SetSize(const wxRect&) {}
    virtual wxSize  GetSize() const     { return {0, 0}; }
    virtual wxSize  GetClientSize() const { return {0, 0}; }
    virtual wxPoint GetPosition() const { return {0, 0}; }
    virtual wxRect  GetRect() const     { return {}; }

    void SetTitle(const wxString& t) { m_title = t; }
    wxString GetTitle() const { return m_title; }
    void SetName(const wxString&) {}
    void SetLabel(const wxString&) {}
    wxString GetLabel() const { return {}; }

    void Enable(bool = true) {}
    bool IsEnabled() const { return true; }
    void SetFocus() {}
    bool HasFocus() const { return false; }

    wxWindow*   GetParent() const { return nullptr; }
    wxWindowID  GetId()     const { return wxID_ANY; }

    static wxWindow* FindFocus() { return nullptr; }
    static wxWindow* FindWindowById(wxWindowID, const wxWindow* = nullptr) { return nullptr; }
};

class wxTopLevelWindow : public wxWindow {};
class wxFrame          : public wxTopLevelWindow {};
class wxDialog         : public wxTopLevelWindow {};
class wxPanel          : public wxWindow {};

// wxDefaultSize / wxDefaultPosition sentinels.
inline const wxSize   wxDefaultSize{-1, -1};
inline const wxPoint  wxDefaultPosition{-1, -1};
