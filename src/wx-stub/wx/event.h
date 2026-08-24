// Minimal wx/event.h stub — event objects and macros for headless KiCad.
// The WASM build never delivers events; the classes exist so ctor/dtor
// resolve at compile+link time in files that declare event handlers.
#pragma once
#include "wx/string.h"
#include <cstdint>

using wxEventType = int;
constexpr wxEventType wxEVT_NULL          = 0;
constexpr wxEventType wxEVT_COMMAND       = 1;
constexpr wxEventType wxEVT_UPDATE_UI     = 2;
constexpr wxEventType wxEVT_MENU          = 3;
constexpr wxEventType wxEVT_BUTTON        = 4;
constexpr wxEventType wxEVT_TIMER         = 5;
constexpr wxEventType wxEVT_IDLE          = 6;
constexpr wxEventType wxEVT_CLOSE_WINDOW  = 7;
constexpr wxEventType wxEVT_TEXT          = 8;
constexpr wxEventType wxEVT_KEY_DOWN      = 9;
constexpr wxEventType wxEVT_KEY_UP        = 10;
constexpr wxEventType wxEVT_LEFT_DOWN     = 11;
constexpr wxEventType wxEVT_LEFT_UP       = 12;
constexpr wxEventType wxEVT_MOTION        = 13;
constexpr wxEventType wxEVT_MOUSEWHEEL    = 14;
constexpr wxEventType wxEVT_CHAR          = 15;
constexpr wxEventType wxEVT_CHAR_HOOK     = 16;

class wxObject { public: virtual ~wxObject() = default; };
class wxEvtHandler : public wxObject {
public:
    virtual bool ProcessEvent(class wxEvent&) { return false; }
    void Bind(wxEventType, ...) {}
    void Unbind(wxEventType, ...) {}
    void SetClientData(void*) {}
    void* GetClientData() { return nullptr; }
};

class wxEvent : public wxObject {
public:
    wxEvent(int = 0, wxEventType = wxEVT_NULL) {}
    virtual wxEvent* Clone() const { return nullptr; }
    wxEventType GetEventType() const { return m_type; }
    int  GetId() const { return m_id; }
    void Skip(bool = true) {}
    void StopPropagation() {}
    void ResumePropagation(int = -1) {}
    wxObject* GetEventObject() const { return nullptr; }
    void SetEventObject(wxObject*) {}
protected:
    wxEventType m_type = wxEVT_NULL;
    int         m_id   = 0;
};

class wxCommandEvent : public wxEvent {
public:
    wxCommandEvent(wxEventType = wxEVT_NULL, int = 0) {}
    wxString GetString() const { return m_str; }
    void SetString(const wxString& s) { m_str = s; }
    int GetInt() const { return m_int; }
    void SetInt(int i) { m_int = i; }
private:
    wxString m_str;
    int      m_int = 0;
};

class wxTimerEvent : public wxEvent {};
class wxIdleEvent  : public wxEvent {};
class wxCloseEvent : public wxEvent {
public:
    bool CanVeto() const { return false; }
    void Veto(bool = true) {}
};
class wxUpdateUIEvent : public wxEvent {
public:
    void Enable(bool) {}
    void Check(bool) {}
};
class wxKeyEvent   : public wxEvent {
public:
    int  GetKeyCode() const { return 0; }
    bool ShiftDown() const  { return false; }
    bool ControlDown() const{ return false; }
    bool AltDown() const    { return false; }
};
class wxMouseEvent : public wxEvent {
public:
    int  GetX() const { return 0; }
    int  GetY() const { return 0; }
    int  GetWheelRotation() const { return 0; }
    bool LeftIsDown() const { return false; }
    bool ShiftDown() const  { return false; }
    bool ControlDown() const{ return false; }
};

#define wxDECLARE_EVENT(name, evtcls)  extern const wxEventType name
#define wxDEFINE_EVENT(name, evtcls)   const wxEventType name = 0

#define wxDECLARE_EVENT_TABLE()
#define wxBEGIN_EVENT_TABLE(a, b)      static void a##_events_unused()
#define wxEND_EVENT_TABLE()            {}
#define DECLARE_EVENT_TABLE()
#define BEGIN_EVENT_TABLE(a, b)        static void a##_events_unused()
#define END_EVENT_TABLE()              {}

// wxEVT_COMMAND_ prefixed compat aliases KiCad sometimes uses.
constexpr wxEventType wxEVT_COMMAND_MENU_SELECTED   = wxEVT_MENU;
constexpr wxEventType wxEVT_COMMAND_BUTTON_CLICKED  = wxEVT_BUTTON;
constexpr wxEventType wxEVT_COMMAND_UPDATE_UI       = wxEVT_UPDATE_UI;
