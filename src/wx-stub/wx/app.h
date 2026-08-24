// Minimal wx/app.h stub. Headless kicad-wasm has no wxApp.
#pragma once
#include "wx/event.h"

class wxAppConsoleBase : public wxEvtHandler {
public:
    virtual bool OnInit() { return true; }
    virtual int  OnExit() { return 0; }
    virtual int  OnRun()  { return 0; }
    virtual void OnFatalException() {}
    void SetAppName(const wxString&) {}
    wxString GetAppName() const { return wxString(); }
    void SetVendorName(const wxString&) {}
    void SetClassName(const wxString&) {}
    static wxAppConsoleBase* GetInstance() { return nullptr; }
    static void SetInstance(wxAppConsoleBase*) {}
    bool IsGUI() const { return false; }
    bool Yield(bool = false) { return true; }
    bool SafeYield(void* = nullptr, bool = false) { return true; }
};

class wxAppConsole : public wxAppConsoleBase {};
class wxApp        : public wxAppConsole {};

inline wxApp* wxTheApp = nullptr;
inline wxAppConsole* wxGetApp() { return nullptr; }

#define wxIMPLEMENT_APP(cls)      cls* g_##cls = nullptr;
#define wxIMPLEMENT_APP_NO_MAIN(cls)  cls* g_##cls = nullptr;
#define wxDECLARE_APP(cls)        extern cls* g_##cls
