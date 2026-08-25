// Minimal wx/dc.h stub — device-context type only.
// KiCad code that names wxDC in signatures compiles; actual GDI ops
// (DrawLine/Blit/etc) are no-op. Real drawing goes through KiCad's own
// PLOTTER / GAL layers, not wxDC.
#pragma once
#include "wx/defs.h"
#include "wx/gdicmn.h"
#include "wx/colour.h"
#include "wx/font.h"
#include "wx/string.h"

class wxPen {
public:
    wxPen() = default;
    wxPen(const wxColour&, int = 1, int = 0) {}
    bool IsOk() const { return true; }
};

class wxBrush {
public:
    wxBrush() = default;
    wxBrush(const wxColour&, int = 0) {}
    bool IsOk() const { return true; }
};

class wxDC {
public:
    virtual ~wxDC() = default;
    virtual void SetPen(const wxPen&) {}
    virtual void SetBrush(const wxBrush&) {}
    virtual void SetFont(const wxFont&) {}
    virtual void SetTextForeground(const wxColour&) {}
    virtual void SetTextBackground(const wxColour&) {}
    virtual void Clear() {}
    virtual void DrawLine(int, int, int, int) {}
    virtual void DrawLine(const wxPoint&, const wxPoint&) {}
    virtual void DrawRectangle(int, int, int, int) {}
    virtual void DrawRectangle(const wxRect&) {}
    virtual void DrawEllipse(int, int, int, int) {}
    virtual void DrawText(const wxString&, int, int) {}
    virtual void DrawText(const wxString&, const wxPoint&) {}
    virtual void DrawBitmap(const class wxBitmap&, int, int, bool = false) {}
    virtual wxSize GetSize() const { return {0, 0}; }
    virtual wxSize GetTextExtent(const wxString&) const { return {0, 0}; }
};

class wxClientDC   : public wxDC { public: wxClientDC(class wxWindow* = nullptr) {} };
class wxWindowDC   : public wxDC {};
class wxPaintDC    : public wxDC {};
class wxMemoryDC   : public wxDC { public: void SelectObject(const class wxBitmap&) {} };
class wxScreenDC   : public wxDC {};
class wxBufferedDC : public wxDC {};
class wxBufferedPaintDC : public wxDC {};
