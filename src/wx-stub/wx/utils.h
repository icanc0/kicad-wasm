// Minimal wx/utils.h stub — misc runtime helpers used by KiCad.
#pragma once
#include "wx/string.h"
#include "wx/arrstr.h"
#include <cstdlib>

inline bool wxGetEnv(const wxString& name, wxString* out) {
    const char* v = std::getenv(name.c_str());
    if (!v) return false;
    if (out) *out = wxString(v);
    return true;
}
inline bool wxSetEnv(const wxString& name, const wxString& value) {
    return setenv(name.c_str(), value.c_str(), 1) == 0;
}
inline bool wxUnsetEnv(const wxString& name) {
    return unsetenv(name.c_str()) == 0;
}

inline void wxMilliSleep(unsigned long) {}
inline void wxMicroSleep(unsigned long) {}

inline unsigned long wxGetProcessId() { return 0; }
inline wxString      wxGetUserName()  { return wxString("kicad-wasm"); }
inline wxString      wxGetHostName()  { return wxString("browser"); }

// wxExecute — real one spawns a subprocess; WASM has no processes.
enum { wxEXEC_ASYNC = 0, wxEXEC_SYNC = 1, wxEXEC_SHOW_CONSOLE = 0 };
inline long wxExecute(const wxString&, int = wxEXEC_ASYNC, void* = nullptr) { return -1; }
inline long wxExecute(char**, int = wxEXEC_ASYNC, void* = nullptr) { return -1; }
inline long wxExecute(const wxString&, wxArrayString&, wxArrayString&, int = wxEXEC_SYNC) { return -1; }
inline long wxShell(const wxString& = wxString()) { return -1; }

inline wxString wxNow() { return wxString(); }
