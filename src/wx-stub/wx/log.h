// Minimal wx/log.h stub for kicad-wasm.
// Discards all log output. Real WASM build routes to console.log later.
#pragma once
#include <cstdio>
#include "wx/defs.h"
#include "wx/debug.h"     // KiCad code assumes wxFAIL_MSG etc. via <wx/log.h>

#ifndef wxLOG_COMPONENT
#define wxLOG_COMPONENT "kicad-wasm"
#endif

// wxWidgets defines a whole taxonomy of logging levels.
using wxLogLevel = unsigned int;
constexpr wxLogLevel wxLOG_FatalError = 0;
constexpr wxLogLevel wxLOG_Error      = 1;
constexpr wxLogLevel wxLOG_Warning    = 2;
constexpr wxLogLevel wxLOG_Message    = 3;
constexpr wxLogLevel wxLOG_Status     = 4;
constexpr wxLogLevel wxLOG_Info       = 5;
constexpr wxLogLevel wxLOG_Debug      = 6;
constexpr wxLogLevel wxLOG_Trace      = 7;
constexpr wxLogLevel wxLOG_Progress   = 8;
constexpr wxLogLevel wxLOG_User       = 100;
constexpr wxLogLevel wxLOG_Max        = 10000;

// All the log macros. Discard-only for now; hook to console.log later.
#define WX_STUB_NOOP_VAR(...)  do { (void)sizeof(#__VA_ARGS__); } while(0)

#define wxLogError(...)    WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogWarning(...)  WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogMessage(...)  WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogInfo(...)     WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogDebug(...)    WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogTrace(...)    WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogStatus(...)   WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogVerbose(...)  WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxLogSysError(...) WX_STUB_NOOP_VAR(__VA_ARGS__)
#define wxVLogWarning(fmt, args)  WX_STUB_NOOP_VAR()

class wxLog {
public:
    static void SetActiveTarget(wxLog*) {}
    static wxLog* GetActiveTarget() { return nullptr; }
    static bool IsLevelEnabled(wxLogLevel, const char*) { return false; }
    static bool IsAllowedTraceMask(const char*) { return false; }
    static void EnableLogging(bool = true) {}
    static void FlushActive() {}
    virtual ~wxLog() = default;
};

class wxLogNull {
public:
    wxLogNull() = default;
    ~wxLogNull() = default;
};
