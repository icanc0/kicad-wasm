// Minimal wx/crt.h stub — wx C runtime wrappers. Just forward to CRT.
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "wx/string.h"

inline int      wxAtoi(const char* s)         { return std::atoi(s); }
inline FILE*    wxFopen(const wxString& path, const wxString& mode) {
    return std::fopen(path.c_str(), mode.c_str());
}
inline double   wxAtof(const char* s)         { return std::atof(s); }
inline long     wxAtol(const char* s)         { return std::atol(s); }
inline int      wxStrcmp(const char* a, const char* b) { return std::strcmp(a, b); }
inline size_t   wxStrlen(const char* s)       { return std::strlen(s); }
inline char*    wxStrdup(const char* s)       { return ::strdup(s); }
inline int      wxSprintf(char* buf, const char* fmt, ...) {
    std::va_list ap; va_start(ap, fmt);
    int n = std::vsprintf(buf, fmt, ap);
    va_end(ap); return n;
}
inline int      wxSnprintf(char* buf, size_t sz, const char* fmt, ...) {
    std::va_list ap; va_start(ap, fmt);
    int n = std::vsnprintf(buf, sz, fmt, ap);
    va_end(ap); return n;
}
