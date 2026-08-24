// kicad-wasm kiplatform replacement for the unix-only files that
// pull in glib/poppler/libsecret (unnecessary in a browser).
// Provides the KIPLATFORM:: symbols the rest of KiCad links against.

#include <kiplatform/app.h>
#include <kiplatform/environment.h>
#include <kiplatform/secrets.h>
#include <wx/string.h>

namespace KIPLATFORM {

// ----- APP ---------------------------------------------------------------
namespace APP {

bool RegisterApplicationRestart(const wxString&)     { return false; }
bool UnregisterApplicationRestart()                  { return false; }
bool SupportsShutdownBlockReason()                   { return false; }
void SetShutdownBlockReason(wxWindow*, const wxString&) {}
void RemoveShutdownBlockReason(wxWindow*)            {}
void ForceTimerMessagesToMainQueue()                 {}
bool Init()                                          { return true; }
bool IsOperatingSystemUnsupported()                  { return false; }
bool AttachConsole(bool /*aTryAlloc*/)               { return false; }

}  // namespace APP

// ----- ENV ---------------------------------------------------------------
namespace ENV {

void     Init()                                                {}
bool     MoveToTrash(const wxString&, wxString& err)           { err = "not supported"; return false; }
bool     IsNetworkPath(const wxString&)                        { return false; }
wxString GetDocumentsDir()                                     { return wxString("/wasm/documents"); }
wxString GetUserConfigPath()                                   { return wxString("/wasm/config"); }
wxString GetUserCachePath()                                    { return wxString("/wasm/cache"); }
wxString GetUserDataPath()                                     { return wxString("/wasm/data"); }
wxString GetCommandLineStr()                                   { return wxString(); }

}  // namespace ENV

// ----- SECRETS -----------------------------------------------------------
namespace SECRETS {

bool GetSecret(const wxString&, const wxString&, wxString&) { return false; }
bool StoreSecret(const wxString&, const wxString&, const wxString&) { return false; }
bool DeleteSecret(const wxString&, const wxString&)         { return false; }

}  // namespace SECRETS

}  // namespace KIPLATFORM
