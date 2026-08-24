// Minimal wx/stdpaths.h stub — standard app paths.
// In the WASM host, "standard paths" don't really apply — return
// browser-mounted virtual FS roots.
#pragma once
#include "wx/string.h"

class wxStandardPaths {
public:
    static wxStandardPaths& Get() {
        static wxStandardPaths s;
        return s;
    }
    wxString GetExecutablePath() const  { return wxString("/wasm/kicad"); }
    wxString GetDataDir() const         { return wxString("/wasm/data"); }
    wxString GetLocalDataDir() const    { return wxString("/wasm/data"); }
    wxString GetConfigDir() const       { return wxString("/wasm/config"); }
    wxString GetUserConfigDir() const   { return wxString("/wasm/config"); }
    wxString GetUserDataDir() const     { return wxString("/wasm/data"); }
    wxString GetUserLocalDataDir() const{ return wxString("/wasm/data"); }
    wxString GetTempDir() const         { return wxString("/tmp"); }
    wxString GetPluginsDir() const      { return wxString("/wasm/plugins"); }
    wxString GetResourcesDir() const    { return wxString("/wasm/resources"); }
    wxString GetDocumentsDir() const    { return wxString("/wasm/documents"); }
    wxString GetAppDocumentsDir() const { return wxString("/wasm/documents"); }
    wxString GetLocalizedResourcesDir(const wxString&) const { return GetResourcesDir(); }
};

using wxStandardPathsBase = wxStandardPaths;
